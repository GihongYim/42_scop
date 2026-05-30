NAME := scop

CXX := c++
CC := cc

CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -Iinclude
CFLAGS := -Wall -Wextra -Werror -Iinclude
LDFLAGS := -static-libstdc++ -static-libgcc

SRC_DIR := src
OBJ_DIR := obj
VENDOR_DIR := vendor
GLFW_DIR := $(VENDOR_DIR)/glfw
GLFW_INSTALL_DIR := $(GLFW_DIR)/install

CPP_SRCS := \
	$(SRC_DIR)/Application.cpp \
	$(SRC_DIR)/Math.cpp \
	$(SRC_DIR)/Mesh.cpp \
	$(SRC_DIR)/ObjParser.cpp \
	$(SRC_DIR)/Shader.cpp \
	$(SRC_DIR)/Window.cpp \
	$(SRC_DIR)/main.cpp

C_SRCS := \
	$(SRC_DIR)/glad.c

OBJS := $(CPP_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) \
	$(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GLFW_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null)
GLFW_LIBS := $(shell pkg-config --libs glfw3 2>/dev/null)
GLFW_LOCAL_LIB := $(firstword $(wildcard $(GLFW_INSTALL_DIR)/lib/libglfw3.a) $(wildcard $(GLFW_INSTALL_DIR)/lib64/libglfw3.a))

ifeq ($(strip $(GLFW_LIBS)),)
	ifneq ($(strip $(GLFW_LOCAL_LIB)),)
		GLFW_CFLAGS := -I$(GLFW_INSTALL_DIR)/include
		GLFW_LIBS := $(GLFW_LOCAL_LIB)
	else
		GLFW_LIBS := -lglfw
	endif
endif

LDLIBS := $(GLFW_LIBS) -lGL -ldl -pthread -lX11 -lXrandr -lXi -lXinerama -lXcursor

.PHONY: all clean fclean re glfw

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(GLFW_CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

glfw:
	@if [ ! -d "$(GLFW_DIR)/.git" ]; then \
		git clone --depth 1 --branch 3.3.10 https://github.com/glfw/glfw.git $(GLFW_DIR); \
	fi
	cmake -S $(GLFW_DIR) -B $(GLFW_DIR)/build \
		-DCMAKE_INSTALL_PREFIX=$(abspath $(GLFW_INSTALL_DIR)) \
		-DGLFW_BUILD_DOCS=OFF \
		-DGLFW_BUILD_EXAMPLES=OFF \
		-DGLFW_BUILD_TESTS=OFF
	cmake --build $(GLFW_DIR)/build
	cmake --install $(GLFW_DIR)/build
