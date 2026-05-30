#include "Mesh.hpp"

#include <cstddef>
#include <stdexcept>

Mesh::Mesh(const ObjModel &model)
	: vertices(model.vertices), indices(model.indices), _vao(0), _vbo(0), _ebo(0), _indexCount(0)
{
	upload();
}

Mesh::Mesh(const std::vector<Vertex> &meshVertices, const std::vector<unsigned int> &meshIndices)
	: vertices(meshVertices), indices(meshIndices), _vao(0), _vbo(0), _ebo(0), _indexCount(0)
{
	upload();
}

void Mesh::upload(void)
{
	std::vector<GpuVertex> gpuVertices;
	std::vector<unsigned int> gpuIndices;

	Mesh::buildGpuData(vertices, indices, gpuVertices, gpuIndices);
	if (gpuVertices.empty() || gpuIndices.empty())
		throw std::runtime_error("mesh has no drawable geometry");

	_indexCount = static_cast<GLsizei>(gpuIndices.size());

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	if (!_vao || !_vbo || !_ebo)
		throw std::runtime_error("failed to create mesh buffers");

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		static_cast<GLsizeiptr>(gpuVertices.size() * sizeof(GpuVertex)),
		&gpuVertices[0],
		GL_STATIC_DRAW
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		static_cast<GLsizeiptr>(gpuIndices.size() * sizeof(unsigned int)),
		&gpuIndices[0],
		GL_STATIC_DRAW
	);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GpuVertex), reinterpret_cast<void *>(offsetof(GpuVertex, position)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GpuVertex), reinterpret_cast<void *>(offsetof(GpuVertex, color)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GpuVertex), reinterpret_cast<void *>(offsetof(GpuVertex, normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(GpuVertex), reinterpret_cast<void *>(offsetof(GpuVertex, uv)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

Mesh::~Mesh(void)
{
	if (_ebo)
		glDeleteBuffers(1, &_ebo);
	if (_vbo)
		glDeleteBuffers(1, &_vbo);
	if (_vao)
		glDeleteVertexArrays(1, &_vao);
}

void Mesh::draw(void) const
{
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

Vec3 Mesh::faceColor(std::size_t faceIndex)
{
	static const Vec3 colors[] = {
		Vec3(0.95f, 0.25f, 0.25f),
		Vec3(0.25f, 0.70f, 0.95f),
		Vec3(0.35f, 0.85f, 0.40f),
		Vec3(0.95f, 0.85f, 0.25f),
		Vec3(0.85f, 0.35f, 0.95f),
		Vec3(0.95f, 0.55f, 0.25f)
	};

	return colors[faceIndex % (sizeof(colors) / sizeof(colors[0]))];
}

void Mesh::buildGpuData(
	const std::vector<Vertex> &sourceVertices,
	const std::vector<unsigned int> &sourceIndices,
	std::vector<GpuVertex> &gpuVertices,
	std::vector<unsigned int> &gpuIndices
)
{
	for (std::size_t i = 0; i + 2 < sourceIndices.size(); i += 3)
	{
		const Vec3 color = Mesh::faceColor(i / 3);

		for (std::size_t j = 0; j < 3; ++j)
		{
			const unsigned int sourceIndex = sourceIndices[i + j];
			GpuVertex vertex;

			if (sourceIndex >= sourceVertices.size())
				throw std::runtime_error("mesh index out of range");

			vertex.position = sourceVertices[sourceIndex].position;
			vertex.color = color;
			vertex.normal = sourceVertices[sourceIndex].normal;
			vertex.uv = sourceVertices[sourceIndex].uv;

			gpuVertices.push_back(vertex);
			gpuIndices.push_back(static_cast<unsigned int>(gpuIndices.size()));
		}
	}
}
