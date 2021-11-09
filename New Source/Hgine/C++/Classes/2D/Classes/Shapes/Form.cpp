

#include "../Objects.h"

sur::Form::Form(std::vector<Vec2f> points, const std::vector<i32>& indices, const Modifier& modifier, const FillMode& fillMode,
	Color color, std::string_view name) 
{
	std::vector<Vec2f> tmpPoints(points);
	std::sort(tmpPoints.begin(), tmpPoints.end(), [](Vec2f& l, Vec2f& r) {
		if (l.magnitude() < r.magnitude())
			return true;
		else
			return false;
		}
	);
	for (auto& iter : points)
		iter -= tmpPoints[0];

	this->points = points;
	this->indices = indices;
	this->modifier = modifier;
	this->fillMode = fillMode;
	this->color = color;
	if (tmpPoints.size() > 0)
		this->position = tmpPoints[0];
	else
		this->position(0, 0);
	this->original_position = position;
	this->type = Type::Form;
	this->name = name;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	_objects.push_back(this);
}

void sur::Form::SetPoint(u32 index, Vec2f position)
{
	if (index >= points.size()) {
#ifdef _DEBUG
		Error(("Form SetPoint(...) in " + name + " index out of range. Make sure you don't index something that doesn't exist").c_str());
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

sur::Vec2f sur::Form::GetPoint(u32 index) const
{
	if (index >= points.size()) {
#ifdef _DEBUG
		Error(("Form GetPoint(...) in " + name + " index out of range. Make sure you don't index something that doesn't exist").c_str());
#endif
		return { 0,0 };
	}
}

void sur::Form::SetIndex(u32 index, i32 what)
{
	if (index >= indices.size()) {
#ifdef _DEBUG
		Error(("Form SetIndex(...) in " + name + " index out of range. Make sure you don't index something that doesn't exist").c_str());
#endif
		return;
	}
	indices[static_cast<size_t>(index)] = what;
}

sur::i32 sur::Form::GetIndex(u32 index) const
{
	if (index >= indices.size()) {
#ifdef _DEBUG
		Error(("Form GetIndex(...) in " + name + " index out of range. Make sure you don't index something that doesn't exist").c_str());
#endif
		return 0;
	}
	return indices[static_cast<size_t>(index)];
}

void sur::Form::Insert(u32 index, Vec2f position)
{
	if (index >= points.size()) {
#ifdef _DEBUG
		Error(("Form Insert(...) in " + name + " index out of range. Make sure you don't index something that doesn't exist").c_str());
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
	if (childOfCamera) {
		position = original_position - STA(_camera_offset);
	}
	else {
		original_position = position + STA(_camera_offset);
	}

	DoRelevantChecks();

	std::vector<Vec2f> points_with_position(points);
	for (auto& iter : points_with_position)
		iter = iter + position;
	if (render) {
		if (modifier == Modifier::None || modifier == Modifier::InverseKinematic) {
			if (wireframe)
				algorithm::DrawFormWire(points_with_position, color);
			else
				if (fillMode == FillMode::Auto)
					algorithm::DrawFormAuto(points_with_position, color);
				else if (fillMode == FillMode::Index)
					algorithm::DrawFormIndex(points_with_position, indices, color);
		}
	}
}