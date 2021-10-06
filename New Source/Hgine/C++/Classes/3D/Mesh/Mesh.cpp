

#include "Mesh.h"

sur::Mesh::Mesh(const std::string& file, Vec3f position, Color color, Vec3f origin, const Mat3x3& projection)
{
	this->position = position;
	this->color = color;
	this->origin = origin;
	this->projection = projection;

    auto replacestr = [](std::string& input, char from, char to) {
        for (i32 i = 0; i < input.size(); ++i) {
            if (input[i] == from)
                input[i] = to;
        }
    };
    auto round = [=](f32 n) -> f32
    {
        f32 pow_10 = pow(10.0f, (f32)3);
        return ::round(n * pow_10) / pow_10;
    };
    std::ifstream f(file);
#ifdef _DEBUG
    if (!f) {
        Error(("Unable to read file: " + file).c_str());
    }
#endif
    std::vector<sur::Vec3f> verts;

    std::string buf;
    std::stringstream ss;
    std::string word;
    std::vector<std::string> words;
    bool once = false;

    ss << f.rdbuf();
    buf = ss.str();
    ss.str("");
    replacestr(buf, '\n', ' ');
    ss << buf;

    while (std::getline(ss, word, ' ')) {
        if (word == "" || word == " ") continue;
        words.push_back(word);
    }
    for (i32 i = 0; i < words.size(); ++i) {
        if (words[i] == "v")
            verts.push_back(sur::Vec3f(round(stof(words[i + 1])), round(stof(words[i + 2])), round(stof(words[i + 3]))));
        if (words[i] == "f") {
            std::string container[3];
            for (i32 c = 1; c <= 3; ++c) {
                for (i32 j = 0;; ++j) {
                    if (words[i + c][j] == '/')
                        break;
                    else
                        container[c - 1] += words[i + c][j];
                }
            }
            if (!once) {
                for (i32 a = 0; a < 3; ++a) {
                    std::vector<f32> values;
                    for (i32 c = 0; c < verts.size(); ++c) {
                        if (a == 0)
                            values.push_back(verts[c].x);
                        if (a == 1)
                            values.push_back(verts[c].y);
                        if (a == 2)
                            values.push_back(verts[c].z);
                    }
                    f32 min = *std::min_element(values.begin(), values.end());
                    for (i32 c = 0; c < verts.size(); ++c) {
                        if (a == 0)
                            verts[c].x += -min + 1;
                        if (a == 1)
                            verts[c].y += -min + 1;
                        if (a == 2)
                            verts[c].z += -min + 1;
                    }
                }
                for (auto& iter : verts) {
                    iter.x *= 100;
                    iter.y *= 100;
                    iter.z *= 100;
                }
                once = true;
            }
            triCon.push_back(
                {
                verts[stoi(container[0]) - 1],
                verts[stoi(container[1]) - 1],
                verts[stoi(container[2]) - 1],
                }
            );
        }
    }
}

void sur::Mesh::Rotate(Dimension dimension, i32 angle)
{
    switch (dimension)
    {
    case Dimension::X:
        angleX = angle;
        break;
    case Dimension::Y:
        angleY = angle;
        break;
    case Dimension::Z:
        angleZ = angle;
        break;
    }
}

void sur::Mesh::Move(Vec3f direction)
{
    origin = origin + direction;
    for (auto& iter : triCon)
    {
        iter.a = iter.a + direction;
        iter.b = iter.b + direction;
        iter.c = iter.c + direction;
    }
}

void sur::Mesh::Bind(bool render, bool wireframe, i32 perspectiveThreshold, i32 clipping)
{
    struct TrianglePosColContainer {
        Vec3f a, b, c;
        Color color;
    };
    std::vector<TrianglePosColContainer> renderableTris;

    std::vector<Vec3f> transformed;
    for (auto& iter : triCon)
    {
        for (i32 i = 0; i < 3; ++i) {
            Vec3f tmp{};
            if (i == 0)
                tmp = iter.a - origin;
            if (i == 1)
                tmp = iter.b - origin;
            if (i == 2)
                tmp = iter.c - origin + position;
            tmp = sur::RotateX(tmp, origin - origin, angleX);
            tmp = sur::RotateY(tmp, origin - origin, angleY);
            tmp = sur::RotateZ(tmp, origin - origin, angleZ);
            if (perspectiveThreshold != 0) {
                f32 z = 0;
                if (tmp.z + origin.z == 0) z = 1;
                else z = 1 / ((tmp.z + origin.z) / perspectiveThreshold);
                projection
                (
                    z, 0, 0,
                    0, z, 0,
                    0, 0, 1
                );
            }
            Vec3f projectedPoint = projection.multiplyWithVector(tmp);
            transformed.push_back(projectedPoint + origin);
        }
    }
    for (i32 i = 0; i < transformed.size(); i += 3) {

        Vec3f normal{}, line1{}, line2{};
        line1 = transformed[i + 1] - transformed[i];
        line2 = transformed[i + 2] - transformed[i];

        normal = line1.cross(line2);

        normal.normalize();

        Vec3f light(0, 0, 1);

        f32 dp = -light.dot(normal);

        dp = 1 - dp;

        if (normal.z > 0 && transformed[i].z > clipping && transformed[i + 1].z > clipping && transformed[i + 2].z > clipping) {
            renderableTris.push_back(
                {   // GetRValue and GetBValue have been changed. Idk why I needed to do so :|
                    transformed[i], transformed[i + 1], transformed[i + 2], Color(u32(GetBValue(color) * dp), u32(GetGValue(color) * dp), u32(GetRValue(color) * dp))
                }
            );
        }
    }
    std::sort(renderableTris.begin(), renderableTris.end(), [](TrianglePosColContainer& t1, TrianglePosColContainer& t2) {
        f32 z1 = (t1.a.z + t1.b.z + t1.c.z) / 3.f;
        f32 z2 = (t2.a.z + t2.b.z + t2.c.z) / 3.f;
        return z1 > z2;
        }
    );
    if (wireframe) {
        for (auto& iter : renderableTris) {
            algorithm::DrawTriangleWire(
                STA(Vec2((i32)iter.a.x, (i32)iter.a.y)),
                STA(Vec2((i32)iter.b.x, (i32)iter.b.y)),
                STA(Vec2((i32)iter.c.x, (i32)iter.c.y)),
                iter.color
            );
        }
    }
    else {
        for (auto& iter : renderableTris) {
            algorithm::DrawTriangle(
                STA(Vec2((i32)iter.a.x, (i32)iter.a.y)),
                STA(Vec2((i32)iter.b.x, (i32)iter.b.y)),
                STA(Vec2((i32)iter.c.x, (i32)iter.c.y)),
                iter.color
            );
        }
    }
}