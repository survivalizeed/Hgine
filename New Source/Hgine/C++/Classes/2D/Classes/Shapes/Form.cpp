

#include "../Objects.h"

sur::Form::Form(const std::vector<Vec2f>& points, Color color, std::string_view name) 
{
	this->points = points;
	this->color = color;
	this->position(0, 0);
	this->type = Type::Form;
	this->name = name;
}

void sur::Form::SetPoint(u32 index, Vec2f position, bool inverseKinematic)
{
	if (index >= points.size()) {
#ifdef _DEBUG
		Error("Form SetPoint(...) index out of range. Make sure you don't index something that doesn't exist");
#endif
		return;
	}
	if(!inverseKinematic)
		points[static_cast<size_t>(index)] = position;
	else {
		std::vector<Vec2f> doubleExistance;
		std::vector<f32> lengths;	
		for (i32 i = points.size() - 1; i >= 1; --i) {
			lengths.push_back((points[i - 1] - points[i]).magnitude());
		}
		doubleExistance.push_back(points[0]);
		for (i32 i = 1; i < points.size() - 1; ++i) {
			doubleExistance.push_back(points[i]);
			doubleExistance.push_back(points[i]);
		}
		doubleExistance.push_back(points[points.size() - 1]);
		auto LookAt = [&](Vec2f line_start, Vec2f target, f32 length) -> Vec2f{
			Vec2f direction(target - line_start);
			direction.normalize();
			return direction * length + line_start;
		};
		Vec2f last(0,0);
		Vec2f transEnd = LookAt(doubleExistance[doubleExistance.size() - 2], position, lengths[0]);
		last = position - transEnd;
		doubleExistance[doubleExistance.size() - 2] = doubleExistance[doubleExistance.size() - 2] + last;
		doubleExistance[doubleExistance.size() - 1] = transEnd + last;
		for (i32 i = doubleExistance.size() - 4, c = 1; i >= 0; i -= 2, ++c) {
			transEnd = LookAt(doubleExistance[i], doubleExistance[i + 2], lengths[c]);
			last = doubleExistance[i + 2] - transEnd;
			doubleExistance[i] = doubleExistance[i] + last;
			doubleExistance[i + 1] = transEnd + last;
		}
		points.clear();
		for (auto& iter : doubleExistance)
			points.push_back(iter);

		auto end = points.end();
		for (auto it = points.begin(); it != end; ++it) {
			end = std::remove(it + 1, end, *it);
		}
		points.erase(end, points.end());

	}
}

sur::Vec2f sur::Form::GetPoint(u32 index)
{
	if (index >= points.size()) {
#ifdef _DEBUG
		Error("Form GetPoint(...) index out of range. Make sure you don't index something that doesn't exist");
#endif
		return { 0,0 };
	}
}

void sur::Form::Bind(bool render, bool wireframe)
{
	std::vector<Vec2f> tmp(points);
	for (auto& iter : tmp)
		iter = iter + position;
	if (render)
		if (wireframe)
			algorithm::DrawFormWire(points, color);
		else
			algorithm::DrawForm(points, color);
}




/*std::vector<Vec2> pointsVec2;
		for (auto& iter : points)
			pointsVec2.push_back(ATS(iter));


		std::vector<f32> distBetweenBefore;
		for (i32 i = 0; i < pointsVec2.size() - 1; ++i) {
			distBetweenBefore.push_back(Absolute(pointsVec2[i] - pointsVec2[i + 1]).magnitude());
		}
		pointsVec2[index] = ATS(position);
		std::vector<f32> distBetweenAfter;
		for (i32 i = 0; i < pointsVec2.size() - 1; ++i) {
			distBetweenAfter.push_back(Absolute(pointsVec2[i] - pointsVec2[i + 1]).magnitude());
		}

		auto checkIfTheSame = [&](const std::vector<Vec2> after) -> bool
		{
			std::vector<f32> distBetween;
			for (i32 i = 0; i < after.size() - 1; ++i) {
				distBetween.push_back(Absolute(after[i] - after[i + 1]).magnitude());
			}
			for (i32 i = 0; i < distBetweenBefore.size(); ++i) {
				if (distBetweenBefore[i] != distBetween[i])
					return false;
			}
			return true;
		};

		while (!checkIfTheSame(pointsVec2)) {
			for (i32 i = 0; i < pointsVec2.size(); ++i) {

			}
		}*/