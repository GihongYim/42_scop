#include "ObjParser.hpp"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>

namespace
{
	struct ProjectedVertex
	{
		unsigned int tokenIndex;
		Vec2 point;

		ProjectedVertex(unsigned int index, const Vec2 &projected)
			: tokenIndex(index), point(projected)
		{
		}
	};

	float cross2d(const Vec2 &a, const Vec2 &b, const Vec2 &c)
	{
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}

	float polygonArea(const std::vector<ProjectedVertex> &vertices)
	{
		float area = 0.0f;

		for (std::size_t i = 0; i < vertices.size(); ++i)
		{
			const Vec2 &a = vertices[i].point;
			const Vec2 &b = vertices[(i + 1) % vertices.size()].point;

			area += a.x * b.y - b.x * a.y;
		}
		return area * 0.5f;
	}

	bool sameSign(float value, bool positive)
	{
		if (positive)
			return value > 0.000001f;
		return value < -0.000001f;
	}

	bool pointInTriangle(const Vec2 &point, const Vec2 &a, const Vec2 &b, const Vec2 &c, bool positive)
	{
		const float ab = cross2d(a, b, point);
		const float bc = cross2d(b, c, point);
		const float ca = cross2d(c, a, point);

		if (positive)
			return ab >= -0.000001f && bc >= -0.000001f && ca >= -0.000001f;
		return ab <= 0.000001f && bc <= 0.000001f && ca <= 0.000001f;
	}

	void fallbackFan(unsigned int count, std::vector<unsigned int> &triangles)
	{
		triangles.clear();
		for (unsigned int i = 1; i + 1 < count; ++i)
		{
			triangles.push_back(0);
			triangles.push_back(i);
			triangles.push_back(i + 1);
		}
	}
}

Vertex::Vertex(void)
	: position(), normal(), uv(), hasNormal(false), hasUv(false)
{
}

Vertex::Vertex(const Vec3 &pos)
	: position(pos), normal(), uv(), hasNormal(false), hasUv(false)
{
}

Vertex::Vertex(const Vec3 &pos, const Vec3 &norm, const Vec2 &texCoord)
	: position(pos), normal(norm), uv(texCoord), hasNormal(true), hasUv(true)
{
}

ObjParser::FaceIndex::FaceIndex(void)
	: position(0), texCoord(0), normal(0)
{
}

ObjModel ObjParser::parse(const std::string &path)
{
	std::ifstream file(path.c_str());
	std::vector<Vec3> positions;
	std::vector<Vec2> texCoords;
	std::vector<Vec3> normals;
	std::map<std::string, unsigned int> vertexMap;
	ObjModel model;
	std::string line;

	if (!file)
		throw std::runtime_error("failed to open obj file: " + path);

	while (std::getline(file, line))
	{
		std::stringstream stream(line);
		std::string type;

		stream >> type;
		if (type == "v")
		{
			Vec3 value;
			if (!(stream >> value.x >> value.y >> value.z))
				throw std::runtime_error("invalid obj vertex in: " + path);
			positions.push_back(value);
		}
		else if (type == "vt")
		{
			Vec2 value;
			if (!(stream >> value.x >> value.y))
				throw std::runtime_error("invalid obj texture coordinate in: " + path);
			texCoords.push_back(value);
		}
		else if (type == "vn")
		{
			Vec3 value;
			if (!(stream >> value.x >> value.y >> value.z))
				throw std::runtime_error("invalid obj normal in: " + path);
			normals.push_back(value);
		}
		else if (type == "f")
		{
			std::vector<std::string> faceTokens;
			std::string token;

			while (stream >> token)
				faceTokens.push_back(token);
			if (faceTokens.size() < 3)
				throw std::runtime_error("invalid obj face in: " + path);

			const std::vector<unsigned int> triangles = ObjParser::triangulateFace(faceTokens, positions);
			for (std::size_t i = 0; i + 2 < triangles.size(); i += 3)
			{
				const std::string triangle[3] = {
					faceTokens[triangles[i]],
					faceTokens[triangles[i + 1]],
					faceTokens[triangles[i + 2]]
				};

				for (int j = 0; j < 3; ++j)
				{
					std::map<std::string, unsigned int>::const_iterator found = vertexMap.find(triangle[j]);

					if (found != vertexMap.end())
					{
						model.indices.push_back(found->second);
					}
					else
					{
						const FaceIndex faceIndex = ObjParser::parseFaceIndex(triangle[j]);
						const Vertex vertex = ObjParser::makeVertex(
							faceIndex,
							positions,
							texCoords,
							normals
						);
						const unsigned int newIndex = static_cast<unsigned int>(model.vertices.size());

						model.vertices.push_back(vertex);
						model.indices.push_back(newIndex);
						vertexMap[triangle[j]] = newIndex;
					}
				}
			}
		}
	}

	if (file.bad())
		throw std::runtime_error("failed to read obj file: " + path);
	ObjParser::normalizeModel(model);
	return model;
}

ObjParser::FaceIndex ObjParser::parseFaceIndex(const std::string &token)
{
	FaceIndex result;
	std::size_t firstSlash = token.find('/');

	if (firstSlash == std::string::npos)
	{
		result.position = ObjParser::parseIndex(token);
		return result;
	}

	result.position = ObjParser::parseIndex(token.substr(0, firstSlash));

	const std::size_t secondSlash = token.find('/', firstSlash + 1);
	if (secondSlash == std::string::npos)
	{
		result.texCoord = ObjParser::parseIndex(token.substr(firstSlash + 1));
		return result;
	}

	result.texCoord = ObjParser::parseIndex(token.substr(firstSlash + 1, secondSlash - firstSlash - 1));
	result.normal = ObjParser::parseIndex(token.substr(secondSlash + 1));
	return result;
}

int ObjParser::parseIndex(const std::string &text)
{
	char *end = NULL;
	long value;

	if (text.empty())
		return 0;
	value = std::strtol(text.c_str(), &end, 10);
	if (*end != '\0' || value == 0)
		throw std::runtime_error("invalid obj face index: " + text);
	return static_cast<int>(value);
}

int ObjParser::resolveIndex(int index, std::size_t size, const std::string &kind)
{
	int resolved;

	if (index > 0)
		resolved = index - 1;
	else
		resolved = static_cast<int>(size) + index;
	if (resolved < 0 || static_cast<std::size_t>(resolved) >= size)
		throw std::runtime_error("obj " + kind + " index out of range");
	return resolved;
}

Vec3 ObjParser::faceTokenPosition(const std::string &token, const std::vector<Vec3> &positions)
{
	const FaceIndex faceIndex = ObjParser::parseFaceIndex(token);

	return positions[ObjParser::resolveIndex(faceIndex.position, positions.size(), "position")];
}

std::vector<unsigned int> ObjParser::triangulateFace(const std::vector<std::string> &faceTokens, const std::vector<Vec3> &positions)
{
	std::vector<Vec3> facePositions;
	Vec3 normal(0.0f, 0.0f, 0.0f);
	std::vector<ProjectedVertex> projected;
	std::vector<ProjectedVertex> remaining;
	std::vector<unsigned int> triangles;

	if (faceTokens.size() == 3)
	{
		triangles.push_back(0);
		triangles.push_back(1);
		triangles.push_back(2);
		return triangles;
	}

	for (std::size_t i = 0; i < faceTokens.size(); ++i)
		facePositions.push_back(ObjParser::faceTokenPosition(faceTokens[i], positions));

	for (std::size_t i = 0; i < facePositions.size(); ++i)
	{
		const Vec3 &current = facePositions[i];
		const Vec3 &next = facePositions[(i + 1) % facePositions.size()];

		normal.x += (current.y - next.y) * (current.z + next.z);
		normal.y += (current.z - next.z) * (current.x + next.x);
		normal.z += (current.x - next.x) * (current.y + next.y);
	}

	for (std::size_t i = 0; i < facePositions.size(); ++i)
	{
		const Vec3 &position = facePositions[i];

		if (std::abs(normal.z) >= std::abs(normal.x) && std::abs(normal.z) >= std::abs(normal.y))
			projected.push_back(ProjectedVertex(static_cast<unsigned int>(i), Vec2(position.x, position.y)));
		else if (std::abs(normal.y) >= std::abs(normal.x) && std::abs(normal.y) >= std::abs(normal.z))
			projected.push_back(ProjectedVertex(static_cast<unsigned int>(i), Vec2(position.x, position.z)));
		else
			projected.push_back(ProjectedVertex(static_cast<unsigned int>(i), Vec2(position.z, position.y)));
	}

	remaining = projected;
	const bool positive = polygonArea(projected) >= 0.0f;
	unsigned int guard = 0;

	while (remaining.size() > 3 && guard < faceTokens.size() * faceTokens.size())
	{
		bool foundEar = false;

		for (std::size_t i = 0; i < remaining.size(); ++i)
		{
			const std::size_t prevIndex = (i + remaining.size() - 1) % remaining.size();
			const std::size_t nextIndex = (i + 1) % remaining.size();
			const ProjectedVertex &prev = remaining[prevIndex];
			const ProjectedVertex &curr = remaining[i];
			const ProjectedVertex &next = remaining[nextIndex];
			bool containsPoint = false;

			if (!sameSign(cross2d(prev.point, curr.point, next.point), positive))
				continue;

			for (std::size_t j = 0; j < remaining.size(); ++j)
			{
				if (j == prevIndex || j == i || j == nextIndex)
					continue;
				if (pointInTriangle(remaining[j].point, prev.point, curr.point, next.point, positive))
				{
					containsPoint = true;
					break;
				}
			}
			if (containsPoint)
				continue;

			triangles.push_back(prev.tokenIndex);
			triangles.push_back(curr.tokenIndex);
			triangles.push_back(next.tokenIndex);
			remaining.erase(remaining.begin() + static_cast<std::vector<ProjectedVertex>::difference_type>(i));
			foundEar = true;
			break;
		}

		if (!foundEar)
		{
			fallbackFan(static_cast<unsigned int>(faceTokens.size()), triangles);
			return triangles;
		}
		++guard;
	}

	if (remaining.size() == 3)
	{
		triangles.push_back(remaining[0].tokenIndex);
		triangles.push_back(remaining[1].tokenIndex);
		triangles.push_back(remaining[2].tokenIndex);
	}
	return triangles;
}

Vertex ObjParser::makeVertex(
	const FaceIndex &index,
	const std::vector<Vec3> &positions,
	const std::vector<Vec2> &texCoords,
	const std::vector<Vec3> &normals
)
{
	Vertex vertex;

	vertex.position = positions[ObjParser::resolveIndex(index.position, positions.size(), "position")];
	if (index.texCoord != 0)
	{
		vertex.uv = texCoords[ObjParser::resolveIndex(index.texCoord, texCoords.size(), "texture coordinate")];
		vertex.hasUv = true;
	}
	if (index.normal != 0)
	{
		vertex.normal = normals[ObjParser::resolveIndex(index.normal, normals.size(), "normal")];
		vertex.hasNormal = true;
	}
	return vertex;
}

void ObjParser::normalizeModel(ObjModel &model)
{
	if (model.vertices.empty())
		return;

	Vec3 min = model.vertices[0].position;
	Vec3 max = model.vertices[0].position;

	for (std::size_t i = 1; i < model.vertices.size(); ++i)
	{
		const Vec3 &position = model.vertices[i].position;

		if (position.x < min.x)
			min.x = position.x;
		if (position.y < min.y)
			min.y = position.y;
		if (position.z < min.z)
			min.z = position.z;
		if (position.x > max.x)
			max.x = position.x;
		if (position.y > max.y)
			max.y = position.y;
		if (position.z > max.z)
			max.z = position.z;
	}

	const Vec3 center(
		(min.x + max.x) * 0.5f,
		(min.y + max.y) * 0.5f,
		(min.z + max.z) * 0.5f
	);
	float maxExtent = max.x - min.x;

	if (max.y - min.y > maxExtent)
		maxExtent = max.y - min.y;
	if (max.z - min.z > maxExtent)
		maxExtent = max.z - min.z;
	if (maxExtent == 0.0f)
		maxExtent = 1.0f;

	for (std::size_t i = 0; i < model.vertices.size(); ++i)
	{
		model.vertices[i].position.x = (model.vertices[i].position.x - center.x) * (2.0f / maxExtent);
		model.vertices[i].position.y = (model.vertices[i].position.y - center.y) * (2.0f / maxExtent);
		model.vertices[i].position.z = (model.vertices[i].position.z - center.z) * (2.0f / maxExtent);
	}
}
