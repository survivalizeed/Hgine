

#include "Manager.h"


void sur::Manager::Add(Object* object)
{
	for (i32 i = 0; i < _objects.size(); ++i) {
		if (_objects[i]->GetName() == object->GetName()) {
#ifdef _DEBUG
			Error("Manager::Add name already used. Use another");
#endif
			return;
		}
	}
}

void sur::Manager::Remove(std::string_view name, i32 index)
{
	if (name != "") {
		for (i32 i = 0; i < _objects.size(); ++i) {
			if (_objects[i]->GetName() == name) {
				_objects.erase(_objects.begin() + i);
				return;
			}
		}
	}
	else if (index >= 0) {
		_objects.erase(_objects.begin() + index);
	}
}

void sur::Manager::Delete(std::string_view name, i32 index)
{
	if (name != "") {
		for (i32 i = 0; i < _objects.size(); ++i) {
			if (_objects[i]->GetName() == name) {
				delete _objects[i];
				_objects.erase(_objects.begin() + i);
				return;
			}
		}
	}
	else if (index >= 0) {
		delete _objects[index];
		_objects.erase(_objects.begin() + index);
	}
}

void sur::Manager::Bind()
{
	static std::vector<Object*> all(_objects);
	if (all.size() != _objects.size())
		all = _objects;
	std::sort(all.begin(), all.end(), [](Object* l, Object* r) {
		if (l->layer < r->layer)
			return true;
		else
			return false;
		}
	);
	for (auto& iter : all) {
		if (iter->active)
			iter->Bind();
	}
}

void sur::Manager::SetActive(bool state, std::string_view name)
{
	for (auto& iter : _objects)
		if (iter->GetName() == name)
			iter->active = state;
}


void sur::Manager::RemoveAll()
{
	_objects.clear();
}

void sur::Manager::DeleteAll()
{
	for (auto& iter : _objects)
		delete iter;
	_objects.clear();
}

template<typename RetValue>
RetValue* sur::Manager::Get(std::string_view name, sur::i32 index) {
	using namespace sur;
	if (name != "") {
		for (i32 i = 0; i < _objects.size(); ++i) {
			if (_objects[i]->GetName() == name && _objects[i]->active) {
				return (RetValue*)_objects[i];
			}
		}
	}
	else if (index >= 0 && _objects[index]->active) {
		return (RetValue*)_objects[index];
	}
	if(typeid(RetValue) == typeid(Square))
		return (RetValue*)_defaultSquare;
	if (typeid(RetValue) == typeid(Line))
		return (RetValue*)_defaultLine;
	if (typeid(RetValue) == typeid(Triangle))
		return (RetValue*)_defaultTriangle;
	if (typeid(RetValue) == typeid(Form))
		return (RetValue*)_defaultForm;
	if (typeid(RetValue) == typeid(Sprite))
		return (RetValue*)_defaultSprite;
	if (typeid(RetValue) == typeid(ParticleSystem))
		return (RetValue*)_defaultParticleSystem;
	if (typeid(RetValue) == typeid(Light))
		return (RetValue*)_defaultLight;
	if (typeid(RetValue) == typeid(Camera))
		return (RetValue*)_defaultCamera;
	if (typeid(RetValue) == typeid(Text))
		return (RetValue*)_defaultText;
}

template sur::Square* sur::Manager::Get(std::string_view name, i32 index);
template sur::Line* sur::Manager::Get(std::string_view name, i32 index);
template sur::Form* sur::Manager::Get(std::string_view name, i32 index);
template sur::Triangle* sur::Manager::Get(std::string_view name, i32 index);
template sur::Sprite* sur::Manager::Get(std::string_view name, i32 index);
template sur::ParticleSystem* sur::Manager::Get(std::string_view name, i32 index);
template sur::Light* sur::Manager::Get(std::string_view name, i32 index);
template sur::Text* sur::Manager::Get(std::string_view name, i32 index);
template sur::Camera* sur::Manager::Get(std::string_view name, i32 index);