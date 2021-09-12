

#include "../Objects.h"

sur::Form::Form(const std::vector<Vec2f>& points, const Modifier& modifier, Color color, std::string_view name) 
{
	this->points = points;
	this->modifier = modifier;
	this->color = color;
	this->position(0, 0);
	this->type = Type::Form;
	this->name = name;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
}

void sur::Form::SetPoint(u32 index, Vec2f position)
{
	if (index >= points.size()) {
#ifdef _DEBUG
		Error("Form SetPoint(...) index out of range. Make sure you don't index something that doesn't exist");
#endif
		return;
	}
	if (modifier == Modifier::None)
		points[static_cast<size_t>(index)] = position;
	else if (modifier == Modifier::InverseKinematic) {
		std::vector<Vec2f> doubleExistance;
		std::vector<f32> lengths;	
		for (i32 i = static_cast<i32>(points.size()) - 1; i >= 1; --i) {
			lengths.push_back((points[static_cast<size_t>(i)- 1] - points[i]).magnitude());
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

		Vec2f last;
		Vec2f transEnd = LookAt(doubleExistance[doubleExistance.size() - 2], position, lengths[0]);
		last = position - transEnd;
		doubleExistance[doubleExistance.size() - 2] = doubleExistance[doubleExistance.size() - 2] + last;
		doubleExistance[doubleExistance.size() - 1] = transEnd + last;
		for (i32 i = static_cast<i32>(doubleExistance.size()) - 4, c = 1; i >= 0; i -= 2, ++c) {
			transEnd = LookAt(doubleExistance[i], 
				doubleExistance[static_cast<size_t>(i) + 2], 
				lengths[c]);
			last = doubleExistance[static_cast<size_t>(i) + 2] - transEnd;
			doubleExistance[i] += last;
			doubleExistance[static_cast<size_t>(i) + 1] = transEnd + last;
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

void sur::Form::Insert(u32 index, Vec2f position)
{
	if (index >= points.size()) {
#ifdef _DEBUG
		Error("Form Insert(...) index out of range. Make sure you don't index something that doesn't exist");
#endif
		return;
	}
	points.insert(points.begin() + index, position);
}

void sur::Form::Remove(u32 index)
{
	if (index >= points.size()) {
#ifdef _DEBUG
		Error("Form Remove(...) index out of range. Make sure you don't index something that doesn't exist");
#endif
		return;
	}
	points.erase(points.begin() + index);
}

void sur::Form::Bind(bool render, bool wireframe)
{
	std::vector<Vec2f> points_with_position(points);
	for (auto& iter : points_with_position)
		iter = iter + position;
	if (render)
		if (wireframe)
			algorithm::DrawFormWire(points_with_position, color);
		else
			algorithm::DrawForm(points_with_position, color);
}