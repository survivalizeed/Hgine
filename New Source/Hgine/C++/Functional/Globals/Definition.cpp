

#include "../../../Includes.h"

HWND _window_hwnd;

WNDCLASSEX _window_class;

HWND _console_hwnd;

sur::Vec2 _window_size;

sur::Vec2 _aspect_ratio;

Color* _render_buffer;

bool _debug = false;

bool _use_light;

f32 _ambient_light;

std::string _resource_path;

std::string _sound_path;
