

#include "../Objects.h"

void sur::ExtendedSprite::Bind(bool render)
{
	if (childOfCamera) {
		position = original_position - STA(_camera_offset);
	}
	else {
		original_position = position + STA(_camera_offset);
	}
	hover = false;
	auto opt = Input::Mouse::Position();
	if (opt.has_value()) {
		Vec2f mpos = opt.value();
		if (algorithm::AABB(mpos, mpos, GetSquareOrSpriteStart(*this), GetSquareOrSpriteEnd(*this))) {
			if (onHoverStay != nullptr)
				onHoverStay(this);
			if (!previousHover) {
				if (onHoverEnter != nullptr)
					onHoverEnter(this);
			}
			if (Input::Mouse::RClickHeld() && onRClickHeld != nullptr)
				onRClickHeld(this);
			if (Input::Mouse::LClickHeld() && onLClickHeld != nullptr)
				onLClickHeld(this);
			if (Input::Mouse::RClickPress() && onRClickPress != nullptr)
				onRClickPress(this);
			if (Input::Mouse::LClickPress() && onLClickPress != nullptr)
				onLClickPress(this);
			hover = true;
		}
	}
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
		Set(ATS(scale.Forward2D(STA(points[i]) - scaleOrigin) + scaleOrigin) + ATS(position), colors[i]);
}