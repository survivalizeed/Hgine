

#pragma once

#include "../../../Includes.h"

extern HWND _window_hwnd;

extern WNDCLASSEX _window_class;

extern HWND _console_hwnd;

extern sur::Vec2 _window_size;

extern sur::Vec2 _aspect_ratio;

extern Color* _render_buffer;

extern bool _debug;

extern bool _use_light;

extern f32 _ambient_light;

extern std::string _resource_path;

extern std::string _sound_path;
