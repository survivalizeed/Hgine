

#include "../Objects.h"

void sur::Button::Bind(bool render)
{
	hover = false;
	auto opt = Input::Mouse::Position();
	if (opt.has_value()) {
		Vec2f mpos = opt.value();
		if (algorithm::AABB(mpos, mpos, GetSquareOrSpriteStart(*this), GetSquareOrSpriteEnd(*this))) {
			if (OnMouseHover != nullptr)
				OnMouseHover(this);
			if (!previousHover) {
				if (OnMouseHoverEnter != nullptr)
					OnMouseHoverEnter(this);
			}
			if (Input::Mouse::RClick() && OnMouseRClick != nullptr)
				OnMouseRClick(this);
			if (Input::Mouse::LClick() && OnMouseLClick != nullptr)
				OnMouseLClick(this);
			hover = true;
		}
	}
	if (hover) {
		previousHover = true;
	}
	if (!hover && previousHover) {
		if (OnMouseHoverExit != nullptr)
			OnMouseHoverExit(this);
		previousHover = false;
	}
	if (collider != Collider::None)
		CheckCollision();
	if (CheckOutOfScreen())
		return;
	for (i32 i = 0; i < points.size(); ++i)
		Set(ATS(scale.Forward2D(STA(points[i]) - scaleOrigin) + scaleOrigin) + ATS(position), colors[i]);
}