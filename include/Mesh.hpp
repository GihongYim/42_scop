#ifndef MESH_HPP
# define MESH_HPP

# include "Math.hpp"
# include "ObjParser.hpp"

# include <vector>
# include <glad/glad.h>

class Mesh
{
public:
	explicit Mesh(const ObjModel &model);
	Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
	~Mesh(void);

	void draw(void) const;

private:
	struct GpuVertex
	{
		Vec3 position;
		Vec3 color;
		Vec3 normal;
		Vec2 uv;
	};

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	GLsizei _indexCount;

	Mesh(const Mesh &other);
	Mesh &operator=(const Mesh &other);

	static Vec3 faceColor(std::size_t faceIndex);
	void upload(void);
	static void buildGpuData(
		const std::vector<Vertex> &sourceVertices,
		const std::vector<unsigned int> &sourceIndices,
		std::vector<GpuVertex> &gpuVertices,
		std::vector<unsigned int> &gpuIndices
	);
};

#endif
