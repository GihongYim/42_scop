#include "Mesh.hpp"

#include <cmath>
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
	const unsigned int hash = static_cast<unsigned int>((faceIndex * 1103515245u + 12345u) >> 16);
	const float shade = 0.38f + static_cast<float>(hash % 38u) / 100.0f;

	return Vec3(shade, shade, shade);
}

Vec3 Mesh::faceNormal(const Vertex &a, const Vertex &b, const Vertex &c)
{
	const Vec3 edge1(
		b.position.x - a.position.x,
		b.position.y - a.position.y,
		b.position.z - a.position.z
	);
	const Vec3 edge2(
		c.position.x - a.position.x,
		c.position.y - a.position.y,
		c.position.z - a.position.z
	);
	Vec3 normal(
		edge1.y * edge2.z - edge1.z * edge2.y,
		edge1.z * edge2.x - edge1.x * edge2.z,
		edge1.x * edge2.y - edge1.y * edge2.x
	);
	const float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	if (length == 0.0f)
		return Vec3(0.0f, 0.0f, 1.0f);
	normal.x /= length;
	normal.y /= length;
	normal.z /= length;
	return normal;
}

Vec2 Mesh::projectedUv(const Vec3 &position, const Vec3 &normal)
{
	const float ax = std::fabs(normal.x);
	const float ay = std::fabs(normal.y);
	const float az = std::fabs(normal.z);

	if (az >= ax && az >= ay)
		return Vec2(position.x * 0.5f + 0.5f, position.y * 0.5f + 0.5f);
	if (ay >= ax && ay >= az)
		return Vec2(position.x * 0.5f + 0.5f, position.z * 0.5f + 0.5f);
	return Vec2(position.z * 0.5f + 0.5f, position.y * 0.5f + 0.5f);
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
		unsigned int faceSourceIndices[3];
		Vertex faceVertices[3];
		Vec3 normal;

		for (std::size_t j = 0; j < 3; ++j)
		{
			faceSourceIndices[j] = sourceIndices[i + j];
			if (faceSourceIndices[j] >= sourceVertices.size())
				throw std::runtime_error("mesh index out of range");
			faceVertices[j] = sourceVertices[faceSourceIndices[j]];
		}
		normal = Mesh::faceNormal(faceVertices[0], faceVertices[1], faceVertices[2]);

		for (std::size_t j = 0; j < 3; ++j)
		{
			GpuVertex vertex;

			vertex.position = faceVertices[j].position;
			vertex.color = color;
			vertex.normal = faceVertices[j].hasNormal ? faceVertices[j].normal : normal;
			vertex.uv = faceVertices[j].hasUv ? faceVertices[j].uv : Mesh::projectedUv(vertex.position, normal);

			gpuVertices.push_back(vertex);
			gpuIndices.push_back(static_cast<unsigned int>(gpuIndices.size()));
		}
	}
}
