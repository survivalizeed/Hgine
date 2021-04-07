

#include "Classes.h"

std::vector<i32> trigger_identitys;
std::vector<void*> trigger_ptrs;

extern sur::Map_Analyses _Amap;


//
//	Trigger: Rectangle
//
sur::Triggers::Rectangle::Rectangle(Vec2 position, Vec2 size, const std::string& name, i32 id, cb_ptr<Master*> callback)
	: Master(name, id, position, size, callback)
{
	type = Type::Trigger_Rectangle;
	trigger_identitys.push_back(id);
	trigger_ptrs.push_back(this);
}

void sur::Triggers::Rectangle::Bind() {
	for (i32 i = position.y; i < position.y + size.y; i++)
		for (i32 j = position.x; j < position.x + size.x; j++)
			_Amap.Trigger(j, i, id);
}