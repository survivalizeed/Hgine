

#include "Manager.h"


void sur::Manager::Add(void* object, Type type)
{
	switch (type) {
	case Type::Square:
		_squares.push_back(static_cast<Square*>(object));
		break;
	case Type::Line:
		_lines.push_back(static_cast<Line*>(object));
		break;
	case Type::Form:
		_forms.push_back(static_cast<Form*>(object));
		break;
	case Type::Triangle:
		_triangles.push_back(static_cast<Triangle*>(object));
		break;
	case Type::Sprite:
		_sprites.push_back(static_cast<Sprite*>(object));
		break;
	case Type::ParticleSystem:
		_particles.push_back(static_cast<ParticleSystem*>(object));
		break;
	case Type::Light:
		_lights.push_back(static_cast<Light*>(object));
		break;
	case Type::Camera:
		_cameras.push_back(static_cast<Camera*>(object));
		break;
	case Type::Text:
		_texts.push_back(static_cast<Text*>(object));
		break;
	}
}

void sur::Manager::Remove(Type type, std::string_view name, i32 index)
{
	if (type == Type::Square) {
		if (name != "") {
			for (i32 i = 0; i < _squares.size(); ++i) {
				if (_squares[i]->GetName() == name) {
					_squares.erase(_squares.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			_squares.erase(_squares.begin() + index);
		}
	}
	if (type == Type::Line) {
		if (name != "") {
			for (i32 i = 0; i < _lines.size(); ++i) {
				if (_lines[i]->GetName() == name) {
					_lines.erase(_lines.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			_lines.erase(_lines.begin() + index);
		}
	}
	if (type == Type::Form) {
		if (name != "") {
			for (i32 i = 0; i < _forms.size(); ++i) {
				if (_forms[i]->GetName() == name) {
					_forms.erase(_forms.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			_forms.erase(_forms.begin() + index);
		}
	}
	if (type == Type::Triangle) {
		if (name != "") {
			for (i32 i = 0; i < _triangles.size(); ++i) {
				if (_triangles[i]->GetName() == name) {
					_triangles.erase(_triangles.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			_triangles.erase(_triangles.begin() + index);
		}
	}
	if (type == Type::Sprite) {
		if (name != "") {
			for (i32 i = 0; i < _sprites.size(); ++i) {
				if (_sprites[i]->GetName() == name) {
					_sprites.erase(_sprites.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			_sprites.erase(_sprites.begin() + index);
		}
	}
	if (type == Type::ParticleSystem) {
		if (name != "") {
			for (i32 i = 0; i < _particles.size(); ++i) {
				if (_particles[i]->GetName() == name) {
					_particles.erase(_particles.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			_particles.erase(_particles.begin() + index);
		}
	}
	if (type == Type::Light) {
		if (name != "") {
			for (i32 i = 0; i < _lights.size(); ++i) {
				if (_lights[i]->GetName() == name) {
					_lights.erase(_lights.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			_lights.erase(_lights.begin() + index);
		}
	}
	if (type == Type::Camera) {
		if (name != "") {
			for (i32 i = 0; i < _cameras.size(); ++i) {
				if (_cameras[i]->GetName() == name) {
					_cameras.erase(_cameras.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			_cameras.erase(_cameras.begin() + index);
		}
	}
	if (type == Type::Text) {
		if (name != "") {
			for (i32 i = 0; i < _texts.size(); ++i) {
				if (_texts[i]->GetName() == name) {
					_texts.erase(_texts.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			_texts.erase(_texts.begin() + index);
		}
	}
}

void sur::Manager::Delete(Type type, std::string_view name, i32 index)
{
	if (type == Type::Square) {
		if (name != "") {
			for (i32 i = 0; i < _squares.size(); ++i) {
				if (_squares[i]->GetName() == name) {
					delete _squares[i];
					_squares.erase(_squares.begin() + i);
				}
			}
		}
		else if (index >= 0) {
			delete _squares[index];
			_squares.erase(_squares.begin() + index);
		}
	}
	if (type == Type::Line) {
		if (name != "") {
			for (i32 i = 0; i < _lines.size(); ++i) {
				if (_lines[i]->GetName() == name) {
					delete _lines[i];
					_lines.erase(_lines.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			delete _lines[index];
			_lines.erase(_lines.begin() + index);
		}
	}
	if (type == Type::Form) {
		if (name != "") {
			for (i32 i = 0; i < _forms.size(); ++i) {
				if (_forms[i]->GetName() == name) {
					delete _lines[i];
					_forms.erase(_forms.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			delete _lines[index];
			_forms.erase(_forms.begin() + index);
		}
	}
	if (type == Type::Triangle) {
		if (name != "") {
			for (i32 i = 0; i < _triangles.size(); ++i) {
				if (_triangles[i]->GetName() == name) {
					delete _triangles[i];
					_triangles.erase(_triangles.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			delete _triangles[index];
			_triangles.erase(_triangles.begin() + index);
		}
	}
	if (type == Type::Sprite) {
		if (name != "") {
			for (i32 i = 0; i < _sprites.size(); ++i) {
				if (_sprites[i]->GetName() == name) {
					delete _sprites[i];
					_sprites.erase(_sprites.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			delete _sprites[index];
			_sprites.erase(_sprites.begin() + index);
		}
	}
	if (type == Type::ParticleSystem) {
		if (name != "") {
			for (i32 i = 0; i < _particles.size(); ++i) {
				if (_particles[i]->GetName() == name) {
					delete _particles[i];
					_particles.erase(_particles.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			delete _particles[index];
			_particles.erase(_particles.begin() + index);
		}
	}
	if (type == Type::Light) {
		if (name != "") {
			for (i32 i = 0; i < _lights.size(); ++i) {
				if (_lights[i]->GetName() == name) {
					delete _lights[i];
					_lights.erase(_lights.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			delete _lights[index];
			_lights.erase(_lights.begin() + index);
		}
	}
	if (type == Type::Camera) {
		if (name != "") {
			for (i32 i = 0; i < _cameras.size(); ++i) {
				if (_cameras[i]->GetName() == name) {
					delete _cameras[i];
					_cameras.erase(_cameras.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			delete _cameras[index];
			_cameras.erase(_cameras.begin() + index);
		}
	}
	if (type == Type::Text) {
		if (name != "") {
			for (i32 i = 0; i < _texts.size(); ++i) {
				if (_texts[i]->GetName() == name) {
					delete _texts[i];
					_texts.erase(_texts.begin() + i);
					break;
				}
			}
		}
		else if (index >= 0) {
			delete _texts[index];
			_texts.erase(_texts.begin() + index);
		}
	}
}

void sur::Manager::RemoveAll()
{
	_squares.clear();
	_lines.clear();
	_forms.clear();
	_triangles.clear();
	_sprites.clear();
	_particles.clear();
	_lights.clear();
	_texts.clear();
	_cameras.clear();
}

void sur::Manager::DeleteAll()
{
	for (auto& iter : _squares)
		delete iter;
	_squares.clear();
	for (auto& iter : _lines)
		delete iter;
	_lines.clear();
	for (auto& iter : _forms)
		delete iter;
	_forms.clear();
	for (auto& iter : _triangles)
		delete iter;
	_triangles.clear();
	for (auto& iter : _sprites)
		delete iter;
	_sprites.clear();
	for (auto& iter : _particles)
		delete iter;
	_particles.clear();
	for (auto& iter : _lights)
		delete iter;
	_lights.clear();
	for (auto& iter : _texts)
		delete iter;
	_texts.clear();
	for (auto& iter : _cameras)
		delete iter;
	_cameras.clear();
}

template<typename RetValue>
RetValue* sur::Manager::Get(std::string_view name, sur::i32 index) {
	using namespace sur;
	if (typeid(RetValue) == typeid(sur::Square)) {
		if (name != "") {
			for (i32 i = 0; i < _squares.size(); ++i) {
				if (_squares[i]->GetName() == name) {
					return (RetValue*)_squares[i];
				}
			}
			return (RetValue*)_defaultSquare;
		}
		else if (index >= 0) {
			return (RetValue*)_squares[index];
		}
		return (RetValue*)_defaultSquare;
	}
	if (typeid(RetValue) == typeid(sur::Line)) {
		if (name != "") {
			for (i32 i = 0; i < _lines.size(); ++i) {
				if (_lines[i]->GetName() == name) {
					return (RetValue*)_lines[i];
				}
			}
			return (RetValue*)_defaultLine;
		}
		else if (index >= 0) {
			return (RetValue*)_lines[index];
		}
		return (RetValue*)_defaultLine;
	}
	if (typeid(RetValue) == typeid(sur::Form)) {
		if (name != "") {
			for (i32 i = 0; i < _forms.size(); ++i) {
				if (_forms[i]->GetName() == name) {
					return (RetValue*)_forms[i];
				}
			}
			return (RetValue*)_defaultForm;
		}
		else if (index >= 0) {
			return (RetValue*)_forms[index];
		}
		return (RetValue*)_defaultForm;
	}
	if (typeid(RetValue) == typeid(sur::Triangle)) {
		if (name != "") {
			for (i32 i = 0; i < _triangles.size(); ++i) {
				if (_triangles[i]->GetName() == name) {
					return (RetValue*)_triangles[i];
				}
			}
			return (RetValue*)_defaultTriangle;
		}
		else if (index >= 0) {
			return (RetValue*)_triangles[index];
		}
		return (RetValue*)_defaultTriangle;
	}
	if (typeid(RetValue) == typeid(sur::Sprite)) {
		if (name != "") {
			for (i32 i = 0; i < _sprites.size(); ++i) {
				if (_sprites[i]->GetName() == name) {
					return (RetValue*)_sprites[i];
				}
			}
			return (RetValue*)_defaultSprite;
		}
		else if (index >= 0) {
			return (RetValue*)_sprites[index];
		}
		return (RetValue*)_defaultSprite;
	}
	if (typeid(RetValue) == typeid(sur::ParticleSystem)) {
		if (name != "") {
			for (i32 i = 0; i < _particles.size(); ++i) {
				if (_particles[i]->GetName() == name) {
					return (RetValue*)_particles[i];
				}
			}
			return (RetValue*)_defaultParticleSystem;
		}
		else if (index >= 0) {
			return (RetValue*)_particles[index];
		}
		return (RetValue*)_defaultParticleSystem;
	}
	if (typeid(RetValue) == typeid(sur::Light)) {
		if (name != "") {
			for (i32 i = 0; i < _lights.size(); ++i) {
				if (_lights[i]->GetName() == name) {
					return (RetValue*)_lights[i];
				}
			}
			return (RetValue*)_defaultLight;
		}
		else if (index >= 0) {
			return (RetValue*)_lights[index];
		}
		return (RetValue*)_defaultLight;
	}
	if (typeid(RetValue) == typeid(sur::Camera)) {
		if (name != "") {
			for (i32 i = 0; i < _cameras.size(); ++i) {
				if (_cameras[i]->GetName() == name) {
					return (RetValue*)_cameras[i];
				}
			}
			return (RetValue*)_defaultCamera;
		}
		else if (index >= 0) {
			return (RetValue*)_cameras[index];
		}
		return (RetValue*)_defaultCamera;
	}
	if (typeid(RetValue) == typeid(sur::Text)) {
		if (name != "") {
			for (i32 i = 0; i < _texts.size(); ++i) {
				if (_texts[i]->GetName() == name) {
					return (RetValue*)_texts[i];
				}
			}
			return (RetValue*)_defaultText;
		}
		else if (index >= 0) {
			return (RetValue*)_texts[index];
		}
		return (RetValue*)_defaultText;
	}
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