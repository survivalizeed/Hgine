

#pragma once

#include "../../../Includes.h"

namespace sur 
{
	class GameObject;
	class Light;
	class Camera;
}

extern HWND _window_hwnd;

extern WNDCLASSEX _window_class;

extern HWND _console_hwnd;

extern sur::Vec2 _window_size;

extern sur::Vec2 _aspect_ratio;

extern sur::Color* _render_buffer;

extern sur::Color _background;

extern bool _use_light;

extern sur::f32 _ambient_light;

extern std::string _resource_path;

extern std::string _sound_path;

extern std::vector<sur::GameObject*> _gameObjects;

extern std::vector<sur::Light*> _lights;

extern std::vector<sur::Camera*> _cameras;

extern std::vector<sur::i32> _hashes;

extern sur::Vec2 _camera_offset;

extern sur::Camera* _active_camera;
