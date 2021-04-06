I forgot to calculate the alpha angle. To calculate it just use the arcus tangent. Example: atan(y / x) -> to convert this into degrees multiply it with 180 / PI. Convert
it back by multiplying it with PI / 180.

In the end everything was to slow and didn't work properly so i used a rotationmatrix:

Vec2 Rotate(Vec2 pos, Vec2 origin, i32 Angle)
{
	Vec2 dist(pos - origin);
	return 	sur::Vec2((i32)(dist.x * cos(Angle * PI / 180) - dist.y * sin(Angle * PI / 180)),
		(i32)(dist.x * sin(Angle * PI / 180) + dist.y * cos(Angle * PI / 180))) + origin;
}
