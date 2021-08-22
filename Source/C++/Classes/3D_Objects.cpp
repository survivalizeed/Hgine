

#include "3D_Objects.h"
#include "../Functional/functional.h"
#include "../Functional/TemporaryObjects.h"

sur::Cuboid_Wire::Cuboid_Wire(Vec3f a, Vec3f b, Vec3f c, Vec3f d, Vec3f e, Vec3f f, Vec3f g, Vec3f h, Color color, Vec3f origin,
    const Mat3x3& projection) : color(color), origin(origin), projection(projection)
{
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    points[4] = e;
    points[5] = f;
    points[6] = g;
    points[7] = h;
}

sur::Cuboid_Wire::Cuboid_Wire(const Cuboid_Wire* const other, Color color, Vec3f origin, const Mat3x3& projection)
    : points(other->points), color(color), origin(origin), projection(projection) {}


void sur::Cuboid_Wire::Rotate(Dimension dimension, i32 angle)
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

void sur::Cuboid_Wire::Bind(bool Render, i32 perspectiveThreshold)
{
    std::vector<Vec2f> transformed;
    for (auto& iter : points)
    {
        Vec3f tmp = iter - origin;
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
        transformed.push_back(projectedPoint.toVec2f() + origin.toVec2f());
    }

    {
        sur::TMP::Line(transformed[0], transformed[1], color);
        sur::TMP::Line(transformed[1], transformed[2], color);
        sur::TMP::Line(transformed[2], transformed[3], color);
        sur::TMP::Line(transformed[3], transformed[0], color);

        sur::TMP::Line(transformed[0], transformed[4], color);
        sur::TMP::Line(transformed[1], transformed[5], color);
        sur::TMP::Line(transformed[2], transformed[6], color);
        sur::TMP::Line(transformed[3], transformed[7], color);

        sur::TMP::Line(transformed[4], transformed[5], color);
        sur::TMP::Line(transformed[5], transformed[6], color);
        sur::TMP::Line(transformed[6], transformed[7], color);
        sur::TMP::Line(transformed[7], transformed[4], color);
    }
    transformed.clear();
}

void sur::Cuboid_Wire::Move(Vec3f direction)
{
    origin = origin + direction;
    for (auto& iter : points)
    {
        iter = iter + direction;
    }
}





sur::Mesh::Mesh(const std::string& file, Vec3f position, Color color, Vec3f origin, const Mat3x3& projection)
    :   position(position), color(color), origin(origin), projection(projection)
{
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
   if (!f && _debug) {
       Error(("Unable to read file: " + file).c_str());
   }

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

void sur::Mesh::Bind(bool Render, bool preciseFill, i32 perspectiveThreshold, i32 clipping)
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
            if(i == 0)
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

        if(normal.z > 0 && transformed[i].z > clipping && transformed[i + 1].z > clipping && transformed[i + 2].z > clipping) {
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
    });
    for (auto& iter : renderableTris) {
        triangles.push_back(sur::Triangle(iter.a.toVec2f(), iter.b.toVec2f(), iter.c.toVec2f(), iter.color, "", 0));
    }
    for (auto& iter : triangles) {
        iter.Bind(Render, false, preciseFill);
    }
    triangles.clear();
    
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
