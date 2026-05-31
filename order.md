✦ en.subject.pdf를 기준으로 분석한 결과, 현재 프로젝트는 필수 요구사항(Mandatory)을 100% 충족하고 있으며, 일부 보너스(Bonus) 기능까지
  구현된 완성도 높은 상태입니다.

  1. 프로젝트 완성도 확인 (Subject 준수 여부)

   * [성공] OBJ 파싱: src/ObjParser.cpp에서 직접 파일을 읽고 파싱합니다. (외부 라이브러리 미사용)
   * [성공] 행렬 연산: src/Math.cpp에서 변환(Translation), 회전(Rotation), 투영(Perspective) 행렬을 직접 구현했습니다.
   * [성공] 중심축 회전: ObjParser::normalizeModel에서 모델을 원점으로 정렬하고 크기를 표준화하여, 42 로고가 구석이 아닌 중심축을 기준으로
     회전하도록 했습니다.
   * [성공] 색상 및 텍스처: Mesh::faceColor를 통해 면마다 회색조(Grayscale)를 부여했고, Application::createCheerfulTexture에서
     절차적(Procedural)으로 "밝은 느낌"의 텍스처를 생성합니다.
   * [성공] 부드러운 전환: T 키를 누를 때 텍스처와 색상 사이가 부드럽게 섞이도록(Smooth transition) 구현되었습니다.
   * [보너스 포함] 복잡한 OBJ 처리: ObjParser::triangulateFace에 Ear Clipping 알고리즘이 구현되어 있어, 오목한(Concave) 다각형도 올바르게
     삼각형으로 나눕니다.

  ---

  2. 공부 시작 가이드 (추천 학습 순서)

  프로젝트가 이미 완성되어 있으므로, 코드를 하나씩 분석하며 3D 그래픽스의 원리를 이해하는 방식을 추천합니다. 아래 순서대로 공부해보세요.

  Step 1: OpenGL의 시작과 윈도우 (main.cpp, Window.cpp)
   * 가장 먼저 main.cpp에서 프로그램이 어떻게 시작되는지 보세요.
   * GLFW와 GLAD가 어떻게 윈도우를 만들고 OpenGL 함수를 사용할 준비를 하는지 이해하는 것이 첫 단계입니다.

  Step 2: 3D의 뇌, 선형대수 (Math.hpp, Math.cpp)
   * 3D 공간의 점들이 어떻게 화면(2D)으로 옮겨지는지 공부해야 합니다.
   * Mat4::perspective(원근 투영), Mat4::rotate(회전) 함수들이 어떤 수식을 사용하는지 찾아보세요. (Modern OpenGL에서 가장 중요한
     부분입니다.)

  Step 3: 데이터 로딩 (ObjParser.cpp)
   * .obj 파일은 단순한 텍스트 파일입니다. 이 텍스트를 어떻게 컴퓨터가 이해하는 Vertex(정점) 데이터 구조로 바꾸는지 코드를 따라가 보세요.
   * 특히 모델을 화면 정중앙에 오게 만드는 Normalization(정규화) 로직을 유심히 보세요.

  Step 4: GPU와의 대화 (Mesh.cpp, Shader.cpp)
   * CPU에 있는 데이터를 GPU로 보내는 VBO(Vertex Buffer Object), VAO(Vertex Array Object)의 개념을 공부하세요.
   * Shader.cpp에서 텍스트로 된 쉐이더 코드를 어떻게 컴파일하고 연결하는지 확인하세요.

  Step 5: 화면에 그리기 (shaders/ 폴더)
   * mesh.vert (Vertex Shader): 각 점의 위치를 계산합니다.
   * mesh.frag (Fragment Shader): 각 픽셀의 색상을 결정합니다. mix() 함수를 사용해 텍스처와 색상을 부드럽게 섞는 부분을 확인해보세요