#include "Game.h"

extern sur::Map_Analyses _Amap;
extern sur::Input _input;

void saints::Kill(const std::string& name)
{
	using namespace sur::Instancer;
	State(Types::Object, true, "blood");
	Get<sur::Object>("blood")->SetPosition(Get<sur::Object>("player")->GetPosition() - Unit(20));
	State(Types::Object, false, "player");
}

void saints::Controls(sur::Object* woods, sur::Object* sky, f32 speed) {
	using namespace sur::Instancer;	
	
	static sur::Object nothing("n", { 0,0 }, "n", 0);

	if (_input.keyboard.Key(Keys::A)) {
		bool once = false, newOrder = false;
		i32 indexOfstore = 0;
		sur::Vec2 first;
		Get<sur::Object>("player")->FlipX(true);
		for (i32 i = 0; i < restricted::objects->size(); ++i) {
			sur::Object* tmp = Get<sur::Object>("", i);
			if (tmp->GetName() == "player") continue;
			if (tmp->GetName() == "woods") continue;
			if (tmp->GetName() == "sky") continue;
			auto store = tmp->Move({ 2 * speed,0 }, 0, true);
			if (!once) {
				first = store;
				if (first.x < nothing.Move({ 2 * speed,0 }, 0, true).x) {
					tmp->Move({ 2 * -speed,0 }, 0, false);
					break;
				}
				once = true;
			}
			if (store.x < first.x) {
				indexOfstore = i;
				nothing.Move({ f32(-first.x + store.x), 0 }, 0, false);
				for (i32 k = 0; k < restricted::objects->size(); ++k) {
					if (Get<sur::Object>("", k)->GetName() == "player") continue;
					if (Get<sur::Object>("", k)->GetName() == "woods") continue;
					if (Get<sur::Object>("", k)->GetName() == "sky") continue;
					if (indexOfstore == k) {
						newOrder = true;
						continue;
					}
					if (!newOrder)
						Get<sur::Object>("", k)->Move({ f32(-first.x + store.x), 0 }, 0, false);
					else {
						Get<sur::Object>("", k)->Move({ 2 * speed, 0 }, 0, false);
						Get<sur::Object>("", k)->Move({ f32(-first.x + store.x), 0 }, 0, false);
					}
				}
				goto leave1;
			}
		}
		woods->Move({ 1.2f * speed,0  }, 0, false);
		sky->Move({ 0.4f * speed, 0 }, 0, false);
	}
leave1:;
	if (_input.keyboard.Key(Keys::D)) {
		speed *= -1;
		bool once = false, newOrder = false;
		i32 indexOfstore = 0;
		sur::Vec2 first;
		Get<sur::Object>("player")->FlipX(false);
		for (i32 i = 0; i < restricted::objects->size(); ++i) {
			sur::Object* tmp = Get<sur::Object>("", i);
			if (tmp->GetName() == "player") continue;
			if (tmp->GetName() == "woods") continue;
			if (tmp->GetName() == "sky") continue;
			auto store = tmp->Move({ 2 * speed,0 }, 0, true);
			if (!once) {
				first = store;
				if (first.x > nothing.Move({ 2 * speed,0 }, 0, true).x) {
					tmp->Move({ 2 * -speed,0 }, 0, false);
					break;
				}
				once = true;
			}
			if (store.x > first.x) {
				indexOfstore = i;
				nothing.Move({ f32(-first.x + store.x), 0 }, 0, false);
				for (i32 k = 0; k < restricted::objects->size(); ++k) {
					if (Get<sur::Object>("", k)->GetName() == "player") continue;
					if (Get<sur::Object>("", k)->GetName() == "woods") continue;
					if (Get<sur::Object>("", k)->GetName() == "sky") continue;
					if (indexOfstore == k) {
						newOrder = true;
						continue;
					}
					if (!newOrder)
						Get<sur::Object>("", k)->Move({ f32(-first.x + store.x), 0 }, 0, false);
					else {
						Get<sur::Object>("", k)->Move({ 2 * speed, 0 }, 0, false);
						Get<sur::Object>("", k)->Move({ f32(-first.x + store.x), 0 }, 0, false);
					}
				}
				speed *= -1;
				goto leave2;
			}
		}
		woods->Move({ 1.2f * speed,0 }, 0, false);
		sky->Move({ 0.4f * speed, 0 }, 0, false);
		speed *= -1;
	}
leave2:;
	if (_input.keyboard.Key(Keys::S)) {
		bool once = false, newOrder = false;
		i32 indexOfstore = 0;
		sur::Vec2 first;
		for (i32 i = 0; i < restricted::objects->size(); ++i) {
			sur::Object* tmp = Get<sur::Object>("", i);
			if (tmp->GetName() == "player") continue;
			if (tmp->GetName() == "woods") continue;
			if (tmp->GetName() == "sky") continue;
			auto store = tmp->Move({ 0, 2 * speed }, 0, true);
			if (!once) {
				first = store;
				if (first.y < nothing.Move({ 0,2 * speed }, 0, false).y) {
					tmp->Move({ 0, 2 * -speed }, 0, false);
					break;
				}
				once = true;
			}
			if (store.y < first.y) {
				indexOfstore = i;
				nothing.Move({ 0, f32(-first.y + store.y) }, 0, false);
				for (i32 k = 0; k < restricted::objects->size(); ++k) {
					if (Get<sur::Object>("", k)->GetName() == "player") continue;
					if (Get<sur::Object>("", k)->GetName() == "woods") continue;
					if (Get<sur::Object>("", k)->GetName() == "sky") continue;
					if (indexOfstore == k) {
						newOrder = true;
						continue;
					}
					if (!newOrder)
						Get<sur::Object>("", k)->Move({ 0, f32(-first.y + store.y) }, 0, false);
					else {
						Get<sur::Object>("", k)->Move({ 0, 2 * speed }, 0, false);
						Get<sur::Object>("", k)->Move({ 0, f32(-first.y + store.y) }, 0, false);
					}
				}
				goto leave3;
			}
		}
		woods->Move({ 0, 1.2f * speed }, 0, false);
		sky->Move({ 0, 0.4f * speed }, 0, false);
	}
leave3:;
	if (_input.keyboard.Key(Keys::W)) {
		speed *= -1;
		bool once = false, newOrder = false;
		i32 indexOfstore = 0;
		sur::Vec2 first;
		for (i32 i = 0; i < restricted::objects->size(); ++i) {
			sur::Object* tmp = Get<sur::Object>("", i);
			if (tmp->GetName() == "player") continue;
			if (tmp->GetName() == "woods") continue;
			if (tmp->GetName() == "sky") continue;
			auto store = tmp->Move({ 0, 2 * speed }, 0, true);
			if (!once) {
				first = store;
				if (first.y > nothing.Move({ 0,2 * speed }, 0, false).y) {
					tmp->Move({ 0, 2 * -speed }, 0, false);
					break;
				}
				once = true;
			}
			if (store.y > first.y) {
				indexOfstore = i;
				nothing.Move({ 0, f32(-first.y + store.y) }, 0, false);
				for (i32 k = 0; k < restricted::objects->size(); ++k) {
					if (Get<sur::Object>("", k)->GetName() == "player") continue;
					if (Get<sur::Object>("", k)->GetName() == "woods") continue;
					if (Get<sur::Object>("", k)->GetName() == "sky") continue;
					if (indexOfstore == k) {
						newOrder = true;
						continue;
					}
					if (!newOrder)
						Get<sur::Object>("", k)->Move({ 0, f32(-first.y + store.y) }, 0, false);
					else {
						Get<sur::Object>("", k)->Move({ 0, 2 * speed }, 0, false);
						Get<sur::Object>("", k)->Move({ 0, f32(-first.y + store.y) }, 0, false);
					}
				}
				goto leave4;
			}
		}
		woods->Move({ 0, 1.2f * speed }, 0, false);
		sky->Move({ 0, 0.4f * speed }, 0, false);
	}
leave4:;
}

void saints::Jump(sur::Object* woods, sur::Object* sky, f32 speed, bool up)
{
	//using namespace sur::Instancer;
	//if (up) {
	//	speed *= -1;
	//	bool once = false, newOrder = false;
	//	i32 indexOfstore = 0;
	//	sur::Vec2 first;
	//	for (i32 i = 0; i < restricted::objects->size(); ++i) {
	//		sur::Object* tmp = Get<sur::Object>("", i);
	//		if (tmp->GetName() == "player") continue;
	//		if (tmp->GetName() == "woods") continue;
	//		if (tmp->GetName() == "sky") continue;
	//		auto store = tmp->Move({ 0,2 * speed }, true);
	//		if (!once) {
	//			first = store;
	//			if (first.y > 2 * speed) {
	//				tmp->Move({ 0, 2 * -speed }, false);
	//				break;
	//			}
	//			once = true;
	//		}
	//		if (store.y > first.y) {
	//			indexOfstore = i;
	//			for (i32 k = 0; k < restricted::objects->size(); ++k) {
	//				if (Get<sur::Object>("", k)->GetName() == "player") continue;
	//				if (Get<sur::Object>("", k)->GetName() == "woods") continue;
	//				if (Get<sur::Object>("", k)->GetName() == "sky") continue;
	//				if (indexOfstore == k) {
	//					newOrder = true;
	//					continue;
	//				}
	//				if (!newOrder)
	//					Get<sur::Object>("", k)->Move({ 0, f32(-first.y + store.y) }, false);
	//				else
	//					Get<sur::Object>("", k)->Move({ 0, (f32)store.y }, false);
	//			}
	//			return;
	//		}
	//	}
	//	woods->Move({ 0, 1.2f * speed }, false);
	//	sky->Move({ 0, 0.4f * speed }, false);
	//}
	//else {
	static sur::Object nothing("n", { 0,0 }, "n", 0);
	using namespace sur::Instancer;
	bool once = false, newOrder = false;
	i32 indexOfstore = 0;
	sur::Vec2 first;
	for (i32 i = 0; i < restricted::objects->size(); ++i) {
		sur::Object* tmp = Get<sur::Object>("", i);
		if (tmp->GetName() == "player") continue;
		if (tmp->GetName() == "woods") continue;
		if (tmp->GetName() == "sky") continue;
		auto store = tmp->Move({ 0, speed }, 1, true);
		if (!once) {
			first = store;
			if (first.y < nothing.Move({ 0,speed }, 1, false).y) {
				tmp->Move({ 0, -speed }, 1, false);
				break;
			}
			once = true;
		}
		if (store.y < first.y) {
			indexOfstore = i;
			nothing.Move({ 0, f32(-first.y + store.y) }, 1, false);
			for (i32 k = 0; k < restricted::objects->size(); ++k) {
				if (Get<sur::Object>("", k)->GetName() == "player") continue;
				if (Get<sur::Object>("", k)->GetName() == "woods") continue;
				if (Get<sur::Object>("", k)->GetName() == "sky") continue;
				if (indexOfstore == k) {
					newOrder = true;
					continue;
				}
				if (!newOrder)
					Get<sur::Object>("", k)->Move({ 0, f32(-first.y + store.y) }, 1, false);
				else {
					Get<sur::Object>("", k)->Move({ 0, speed }, 1, false);
					Get<sur::Object>("", k)->Move({ 0, f32(-first.y + store.y) }, 1, false);
				}
			}
			return;
		}
	}
	woods->Move({ 0, 1.2f * speed }, 0, false);
	sky->Move({ 0, 0.4f * speed }, 0, false);
	//}
}


void saints::Gravity(sur::Master* obj, f32* m, bool allowed) {
	using namespace sur::Instancer;
	if (allowed) {
		*m += 0.025f * (*m / 1.8f);
		if (*m >= 9) *m = 9;
		saints::Jump(Get<sur::Object>("woods"), Get<sur::Object>("sky"), (*m) * 2, false);
	}
	else
		*m = 1.1f;
}

void saints::WallpaperScroll(sur::Object& obj) {
	sur::XYC buffer = obj.GetBuf();
	auto Set = [=](sur::Vec2 pos, Color col) {
		while (pos.x > _window_size.x)
			pos.x -= _window_size.x;
		while (pos.x < 0) 
			pos.x += _window_size.x;
		while (pos.y > _window_size.y) 
			pos.y -= _window_size.y;
		while (pos.y < 0) 
			pos.y += _window_size.y;
		_Amap.Render(pos,col);
	};
	for (i32 i = 0; i < buffer.X->size(); ++i) {
		Set(sur::Vec2(buffer.X->at(i), buffer.Y->at(i)) + ATS(obj.GetPosition()), buffer.C->at(i));
	}
}

void saints::Portals() {
	using namespace sur::Instancer;
	if (_input.mouse.LClick()) {
		sur::Vec2f size = Get<sur::Object>("portal_blue")->GetSize();
		Get<sur::Object>("portal_blue")
			->SetPosition({ _input.mouse.Position().x - (0.5f * size.x),_input.mouse.Position().y - (0.5f * size.y) });
	}
	if (_input.mouse.RClick()) {
		sur::Vec2f size = Get<sur::Object>("portal_orange")->GetSize();
		Get<sur::Object>("portal_orange")
			->SetPosition({ _input.mouse.Position().x - (0.5f * size.x),_input.mouse.Position().y - (0.5f * size.y) });
	}
}