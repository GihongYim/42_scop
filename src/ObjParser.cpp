#include "ObjParser.hpp"

#include <cstdlib>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>

Vertex::Vertex(void)
	: position(), normal(), uv()
{
}

Vertex::Vertex(const Vec3 &pos)
	: position(pos), normal(), uv()
{
}

Vertex::Vertex(const Vec3 &pos, const Vec3 &norm, const Vec2 &texCoord)
	: position(pos), normal(norm), uv(texCoord)
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

			for (std::size_t i = 1; i + 1 < faceTokens.size(); ++i)
			{
				const std::string triangle[3] = {
					faceTokens[0],
					faceTokens[i],
					faceTokens[i + 1]
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
	ObjParser::centerModel(model);
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
		vertex.uv = texCoords[ObjParser::resolveIndex(index.texCoord, texCoords.size(), "texture coordinate")];
	if (index.normal != 0)
		vertex.normal = normals[ObjParser::resolveIndex(index.normal, normals.size(), "normal")];
	return vertex;
}

void ObjParser::centerModel(ObjModel &model)
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

	for (std::size_t i = 0; i < model.vertices.size(); ++i)
	{
		model.vertices[i].position.x -= center.x;
		model.vertices[i].position.y -= center.y;
		model.vertices[i].position.z -= center.z;
	}
}
