

#include "../Objects.h"

sur::ExtendedSprite::ExtendedSprite(std::string_view file, FileType filetype, Vec2f position, Collider colliderType, std::string_view name, Color colorToAlpha)
{
	input1 = new Input;
	input2 = new Input;
	input3 = new Input;
	this->color = Color(0, 0, 0);
	this->position = position;
	this->original_position = position;
	this->type = Type::ExtendedSprite;
	this->collider = colliderType;
	this->name = name;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	_gameObjects.push_back(this);

	if (filetype == FileType::Hgineres)
		LoadHgineres(file);
	else if (filetype == FileType::PNG)
		LoadPng(file, colorToAlpha);
}

void sur::ExtendedSprite::Bind(bool render)
{
	if (childOfCamera) {
		position = original_position - STA(_camera_offset);
	}
	else {
		original_position = position + STA(_camera_offset);
	}
	hover = false;
	auto opt = Input::Position();
	if (opt.has_value()) {
		Vec2f mpos = opt.value();
		if (algorithm::AABB(mpos, mpos, GetSquareOrSpriteStart(*this), GetSquareOrSpriteEnd(*this))) {
			if (onHoverStay != nullptr)
				onHoverStay(this);
			if (!previousHover) {
				if (onHoverEnter != nullptr)
					onHoverEnter(this);
			}
			if (Input::LClickHeld() && onHoverLClickHeld != nullptr)
				onHoverLClickHeld(this);
			if (Input::RClickHeld() && onHoverRClickHeld != nullptr)
				onHoverRClickHeld(this);
			if (input1->LClickPress() && onHoverLClickPress != nullptr)
				onHoverLClickPress(this);
			if (input1->RClickPress() && onHoverRClickPress != nullptr)
				onHoverRClickPress(this);
			if (input1->LClickRelease() && onHoverLClickRelease != nullptr)
				onHoverLClickRelease(this);
			if (input1->RClickRelease() && onHoverRClickRelease != nullptr)
				onHoverRClickRelease(this);
			hover = true;
		}
		else {
			if (onNotHover != nullptr)
				onNotHover(this);
			if (Input::LClickHeld() && onNotHoverLClickHeld != nullptr)
				onNotHoverLClickHeld(this);
			if (Input::RClickHeld() && onNotHoverRClickHeld != nullptr)
				onNotHoverRClickHeld(this);
			if (input2->LClickPress() && onNotHoverLClickPress != nullptr)
				onNotHoverLClickPress(this);
			if (input2->RClickPress() && onNotHoverRClickPress != nullptr)
				onNotHoverRClickPress(this);
			if (input2->LClickRelease() && onNotHoverLClickRelease != nullptr)
				onNotHoverLClickRelease(this);
			if (input2->RClickRelease() && onNotHoverRClickRelease != nullptr)
				onNotHoverRClickRelease(this);
		}
	}
	if (Input::LClickHeld() && onLClickHeld != nullptr)
		onLClickHeld(this);
	if (Input::RClickHeld() && onRClickHeld != nullptr)
		onRClickHeld(this);
	if (input3->LClickPress() && onLClickPress != nullptr)
		onLClickPress(this);
	if (input3->RClickPress() && onRClickPress != nullptr)
		onRClickPress(this);
	if (input3->LClickRelease() && onLClickRelease != nullptr)
		onLClickRelease(this);
	if (input3->RClickPress() && onRClickRelease != nullptr)
		onRClickRelease(this);
	if (hover) {
		previousHover = true;
	}
	if (!hover && previousHover) {
		if (onHoverExit != nullptr)
			onHoverExit(this);
		previousHover = false;
	}
	if (collider != Collider::None)
		CheckCollision();
	if (CheckOutOfScreen())
		return;
	for (i32 i = 0; i < points.size(); ++i)
		Set(ATS(scale.Forward2D(STA(points[i]) - scaleOrigin) + scaleOrigin) + ATS(position), TintPixel(colors[i]));
}

sur::ExtendedSprite::~ExtendedSprite()
{
	delete input1, input2, input3;
}