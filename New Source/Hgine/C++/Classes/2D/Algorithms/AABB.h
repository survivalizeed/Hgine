

#pragma once

#include "../../../../Includes.h"

namespace sur::algorithm
{
	inline bool AABB(Vec2f fStart, Vec2f fEnd, Vec2f sStart, Vec2f sEnd) 
	{
		auto PointLaysInBetweenSquare = [=](Vec2f point, Vec2f s, Vec2f e) -> bool
		{
			if (point.x >= s.x && point.x <= e.x && point.y >= s.y && point.y <= e.y)
				return true;
			return false;
		};

		bool collision = false;

		collision = PointLaysInBetweenSquare(fStart, sStart, sEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(Vec2f(fStart.x, fEnd.y), sStart, sEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(fEnd, sStart, sEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(Vec2f(fEnd.x, fStart.y), sStart, sEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(sStart, fStart, fEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(Vec2f(sStart.x, sEnd.y), fStart, fEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(sEnd, fStart, fEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(Vec2f(sEnd.x, sStart.y), fStart, fEnd);

	leave:
		return collision;
	}

	inline bool AABBi32(Vec2 fStart, Vec2 fEnd, Vec2 sStart, Vec2 sEnd)
	{
		auto PointLaysInBetweenSquare = [=](Vec2 point, Vec2 s, Vec2 e) -> bool
		{
			if (point.x >= s.x && point.x <= e.x && point.y >= s.y && point.y <= e.y)
				return true;
			return false;
		};

		bool collision = false;

		collision = PointLaysInBetweenSquare(fStart, sStart, sEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(Vec2(fStart.x, fEnd.y), sStart, sEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(fEnd, sStart, sEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(Vec2(fEnd.x, fStart.y), sStart, sEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(sStart, fStart, fEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(Vec2(sStart.x, sEnd.y), fStart, fEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(sEnd, fStart, fEnd);
		if (collision) goto leave;

		collision = PointLaysInBetweenSquare(Vec2(sEnd.x, sStart.y), fStart, fEnd);

	leave:
		return collision;
	}
}
