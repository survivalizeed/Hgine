

#include "../Objects.h"

sur::BoxHover::BoxHover(Object* objectToAttachTo, Vec2f start, Vec2f end)
{
	input1 = new Input;
	input2 = new Input;
	input3 = new Input;
	this->objectToAttachTo = objectToAttachTo;
	if (!start.isZero() || !end.isZero()) {
		this->start = start;
		this->end = end;
	}
}

void sur::BoxHover::CheckHover()
{
	Vec2f tmpStart = start + static_cast<Object*>(objectToAttachTo)->position;
	Vec2f tmpEnd = end + static_cast<Object*>(objectToAttachTo)->position;
	hover = false;
	auto opt = Input::Position();
	if (opt.has_value()) {
		Vec2f mpos = opt.value();
		if (algorithm::AABB(mpos, mpos, tmpStart, tmpEnd)) {
			if (onHoverStay != nullptr)
				onHoverStay(objectToAttachTo);
			if (!previousHover) {
				if (onHoverEnter != nullptr)
					onHoverEnter(objectToAttachTo);
			}
			if (Input::LClickHeld() && onHoverLClickHeld != nullptr)
				onHoverLClickHeld(objectToAttachTo);
			if (Input::RClickHeld() && onHoverRClickHeld != nullptr)
				onHoverRClickHeld(objectToAttachTo);
			if (input1->LClickPress() && onHoverLClickPress != nullptr)
				onHoverLClickPress(objectToAttachTo);
			if (input1->RClickPress() && onHoverRClickPress != nullptr)
				onHoverRClickPress(objectToAttachTo);
			if (input1->LClickRelease() && onHoverLClickRelease != nullptr)
				onHoverLClickRelease(objectToAttachTo);
			if (input1->RClickRelease() && onHoverRClickRelease != nullptr)
				onHoverRClickRelease(objectToAttachTo);
			hover = true;
		}
		else {
			if (onNotHover != nullptr)
				onNotHover(objectToAttachTo);
			if (Input::LClickHeld() && onNotHoverLClickHeld != nullptr)
				onNotHoverLClickHeld(objectToAttachTo);
			if (Input::RClickHeld() && onNotHoverRClickHeld != nullptr)
				onNotHoverRClickHeld(objectToAttachTo);
			if (input2->LClickPress() && onNotHoverLClickPress != nullptr)
				onNotHoverLClickPress(objectToAttachTo);
			if (input2->RClickPress() && onNotHoverRClickPress != nullptr)
				onNotHoverRClickPress(objectToAttachTo);
			if (input2->LClickRelease() && onNotHoverLClickRelease != nullptr)
				onNotHoverLClickRelease(objectToAttachTo);
			if (input2->RClickRelease() && onNotHoverRClickRelease != nullptr)
				onNotHoverRClickRelease(objectToAttachTo);
		}
	}
	if (Input::LClickHeld() && onLClickHeld != nullptr)
		onLClickHeld(objectToAttachTo);
	if (Input::RClickHeld() && onRClickHeld != nullptr)
		onRClickHeld(objectToAttachTo);
	if (input3->LClickPress() && onLClickPress != nullptr)
		onLClickPress(objectToAttachTo);
	if (input3->RClickPress() && onRClickPress != nullptr)
		onRClickPress(objectToAttachTo);
	if (input3->LClickRelease() && onLClickRelease != nullptr)
		onLClickRelease(objectToAttachTo);
	if (input3->RClickPress() && onRClickRelease != nullptr)
		onRClickRelease(objectToAttachTo);
	if (hover) {
		previousHover = true;
	}
	if (!hover && previousHover) {
		if (onHoverExit != nullptr)
			onHoverExit(objectToAttachTo);
		previousHover = false;
	}
}

sur::BoxHover::~BoxHover()
{
	delete input1, input2, input3;
}