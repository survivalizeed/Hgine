#include <iostream>
#include <cmath>



typedef int i32;
struct Vec2 {

	i32 x = 0, y = 0;
	
	Vec2() = default;

	Vec2(i32 x, i32 y) : x(x), y(y) {}

	Vec2(const Vec2& vector2d) : x(vector2d.x), y(vector2d.y) {}

	inline Vec2 invert() { return { this->x * -1, this->y * -1 }; }
	inline float magnitude() { return (float)sqrt(pow(x, 2) + pow(y, 2)); }
	inline void absolute() { abs(x); abs(y); }
	inline void operator ()(i32 x, i32 y) { this->x = x; this->y = y; }
	inline void operator ()(const Vec2& vector2d) { x = vector2d.x; y = vector2d.y; }
	inline void operator =(const Vec2& vector2d) { x = vector2d.x; y = vector2d.y; }
	inline Vec2 operator +(const Vec2& other) const { return { x + other.x, y + other.y }; }
	inline Vec2 operator -(const Vec2& other) const { return { x - other.x, y - other.y }; }
	inline Vec2 operator *(const Vec2& other) const { return { x * other.x, y * other.y }; }
	inline Vec2 operator /(const Vec2& other) const { return { x / other.x, y / other.y }; }
	inline Vec2 operator --() { return { x - 1, y - 1 }; }
	inline Vec2 operator ++() { return { x + 1, y + 1 }; }
	inline bool operator ==(const Vec2& other) const { return (x == other.x && y == other.y) ? true : false; }
	inline bool operator !=(const Vec2& other) const { return (x != other.x && y != other.y) ? true : false; }
	inline bool operator >(Vec2 other) { return (magnitude() > other.magnitude()) ? true : false; }
	inline bool operator >=(Vec2 other) { return (magnitude() >= other.magnitude()) ? true : false; }
	inline bool operator <(Vec2 other) { return (magnitude() < other.magnitude()) ? true : false; }
	inline bool operator <=(Vec2 other) { return (magnitude() <= other.magnitude()) ? true : false; }
	friend std::ostream& operator<<(std::ostream& os, const Vec2& vector2d) {
		os << "X: " << vector2d.x << " Y: " << vector2d.y;
		return os;
	}
};





Vec2 RotateRelativeToOrigin(Vec2 pos, Vec2 origin, float deg) {
	/*___Maybe we want to always ceil() instead of round()___*/

	//Store if x or y of curret pixel is negative
	bool xne, yne;

	//Get distance between origin and pixel -> dist is the pixel's position relative to the origin
	Vec2 dist(pos - origin);

	//Check if dist has negative x or y -> helps us to interpret pos_new better
	if (dist.x < 0)
		xne = true;
	if (dist.y < 0)
		yne = true;
	
	//Make negative numbers positive
	dist.absolute();

	//Pythagoras 
	float hypothenuse = dist.magnitude(); // root(dist.x^2 + dist.y^2) 
	
	//Get the angle of alpha
	float angle = atan((float)dist.y / (float)dist.x) * 180.0 / PI + deg; // -> * 180 / PI arc measure to degrees 
	// -> added the deg as an offset
	
	//Calculate the new position of the pixel
	Vec2 pos_new((int)(cos(angle * PI / 180.0) * hypothenuse + 0.5f),
		(int)(sin(angle * PI / 180.0) * hypothenuse + 0.5f));

	//Make it match our alignments

	//return the new position
	return pos_new;
}
