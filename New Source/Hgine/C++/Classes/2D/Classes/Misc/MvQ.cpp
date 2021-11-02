

#include "../Objects.h"

sur::Vec2 sur::MvQ::MoveQueue(Vec2f direction, i32 moveQueueIndex)
{
	auto round = [](f32& n)
	{
		f32 pow_10 = pow(10.0f, (f32)3);
		n = ::round(n * pow_10) / pow_10;
	};
	if (!mvContainer.contains(moveQueueIndex)) {
		mvContainer[moveQueueIndex] = MoveQueueContainer();
	}
	MoveQueueContainer cC = mvContainer[moveQueueIndex];
	if (direction.x > 0) {
		cC.counter_pos.x += direction.x;
		round(cC.counter_pos.x);
	}
	else {
		cC.counter_neg.x += direction.x;
		round(cC.counter_neg.x);
	}
	if (direction.y > 0) {
		cC.counter_pos.y += direction.y;
		round(cC.counter_pos.y);
	}
	else {
		cC.counter_neg.y += direction.y;
		round(cC.counter_neg.y);
	}

	Vec2 newDirection;

	while (cC.counter_pos.x >= static_cast<f32>(cC.counter_counter_pos.x))
	{
		newDirection.x++;
		cC.counter_counter_pos.x++;
	}
	while (cC.counter_pos.y >= static_cast<f32>(cC.counter_counter_pos.y))
	{
		newDirection.y++;
		cC.counter_counter_pos.y++;
	}
	while (cC.counter_neg.x <= static_cast<f32>(cC.counter_counter_neg.x))
	{
		newDirection.x--;
		cC.counter_counter_neg.x--;
	}
	while (cC.counter_neg.y <= static_cast<f32>(cC.counter_counter_neg.y))
	{
		newDirection.y--;
		cC.counter_counter_neg.y--;
	}

	mvContainer[moveQueueIndex] = cC;

	return newDirection;
}