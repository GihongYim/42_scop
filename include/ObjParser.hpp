#ifndef OBJ_PARSER_HPP
# define OBJ_PARSER_HPP

# include "Math.hpp"

# include <string>
# include <vector>

struct Vertex
{
	Vec3 position;
	Vec3 normal;
	Vec2 uv;

	Vertex(void);
	explicit Vertex(const Vec3 &pos);
	Vertex(const Vec3 &pos, const Vec3 &norm, const Vec2 &texCoord);
};

struct ObjModel
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

class ObjParser
{
public:
	static ObjModel parse(const std::string &path);

private:
	struct FaceIndex
	{
		int position;
		int texCoord;
		int normal;

		FaceIndex(void);
	};

	ObjParser(void);

	static FaceIndex parseFaceIndex(const std::string &token);
	static int parseIndex(const std::string &text);
	static int resolveIndex(int index, std::size_t size, const std::string &kind);
	static Vertex makeVertex(
		const FaceIndex &index,
		const std::vector<Vec3> &positions,
		const std::vector<Vec2> &texCoords,
		const std::vector<Vec3> &normals
	);
	static void centerModel(ObjModel &model);
};

#endif
