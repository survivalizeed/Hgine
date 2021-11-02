

#include "Manager.h"

void sur::Manager::Add(void* object, Type type)
{
	switch (type) {
	case Type::Square:
		Storage::squares.push_back(static_cast<Square*>(object));
	case Type::Line:
		Storage::lines.push_back(static_cast<Line*>(object));
	case Type::Form:
		Storage::forms.push_back(static_cast<Form*>(object));
	case Type::Triangle:
		Storage::triangles.push_back(static_cast<Triangle*>(object));
	case Type::Sprite:
		Storage::sprites.push_back(static_cast<Sprite*>(object));
	case Type::ParticleSystem:
		Storage::particles.push_back(static_cast<ParticleSystem*>(object));
	case Type::Light:
		Storage::lights.push_back(static_cast<Light*>(object));
	}
}

void sur::Manager::Remove(Type type, std::string_view name, i32 index)
{
	if (type == Type::Square) {
		if (name != "") {
			for (i32 i = 0; i < Storage::squares.size(); ++i) {
				if (Storage::squares[i]->GetName() == name) {
					Storage::squares.erase(Storage::squares.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			Storage::squares.erase(Storage::squares.begin() + index);
		}
	}
	if (type == Type::Line) {
		if (name != "") {
			for (i32 i = 0; i < Storage::lines.size(); ++i) {
				if (Storage::lines[i]->GetName() == name) {
					Storage::lines.erase(Storage::lines.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			Storage::lines.erase(Storage::lines.begin() + index);
		}
	}
	if (type == Type::Form) {
		if (name != "") {
			for (i32 i = 0; i < Storage::forms.size(); ++i) {
				if (Storage::forms[i]->GetName() == name) {
					Storage::forms.erase(Storage::forms.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			Storage::forms.erase(Storage::forms.begin() + index);
		}
	}
	if (type == Type::Triangle) {
		if (name != "") {
			for (i32 i = 0; i < Storage::triangles.size(); ++i) {
				if (Storage::triangles[i]->GetName() == name) {
					Storage::triangles.erase(Storage::triangles.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			Storage::triangles.erase(Storage::triangles.begin() + index);
		}
	}
	if (type == Type::Sprite) {
		if (name != "") {
			for (i32 i = 0; i < Storage::sprites.size(); ++i) {
				if (Storage::sprites[i]->GetName() == name) {
					Storage::sprites.erase(Storage::sprites.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			Storage::sprites.erase(Storage::sprites.begin() + index);
		}
	}
	if (type == Type::ParticleSystem) {
		if (name != "") {
			for (i32 i = 0; i < Storage::particles.size(); ++i) {
				if (Storage::particles[i]->GetName() == name) {
					Storage::particles.erase(Storage::particles.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			Storage::particles.erase(Storage::particles.begin() + index);
		}
	}
	if (type == Type::Light) {
		if (name != "") {
			for (i32 i = 0; i < Storage::lights.size(); ++i) {
				if (Storage::lights[i]->GetName() == name) {
					Storage::lights.erase(Storage::lights.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			Storage::lights.erase(Storage::lights.begin() + index);
		}
	}
}

void sur::Manager::Delete(Type type, std::string_view name, i32 index)
{
}

void sur::Manager::RemoveAll()
{
}

void sur::Manager::DeleteAll()
{
}
