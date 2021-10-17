

#pragma once

#include "../../../Includes.h"

namespace sur 
{
	class Object;
}

extern HWND _window_hwnd;

extern WNDCLASSEX _window_class;

extern HWND _console_hwnd;

extern sur::Vec2 _window_size;

extern sur::Vec2 _aspect_ratio;

extern sur::Color* _render_buffer;

extern bool _use_light;

extern sur::f32 _ambient_light;

extern std::string _resource_path;

extern std::string _sound_path;

extern std::vector<sur::Object> _objects;

extern std::vector<sur::i32> _hashes;

#if _WIN32 || _WIN64
#if _WIN64
#else
extern asIScriptEngine* _asEngine;
#endif
#endif