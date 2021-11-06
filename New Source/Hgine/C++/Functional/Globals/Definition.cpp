

#include "../../../Includes.h"

namespace sur
{
	class Object;
	class Light;
	class Camera;
}

HWND _window_hwnd;

WNDCLASSEX _window_class;

HWND _console_hwnd;

sur::Vec2 _window_size;

sur::Vec2 _aspect_ratio;

sur::Color* _render_buffer;

sur::Color _background;

bool _use_light;

sur::f32 _ambient_light;

std::string _resource_path;

std::string _sound_path;

std::vector<sur::Object*> _objects;

std::vector<sur::Light*> _lights;

std::vector<sur::Camera*> _cameras;

std::vector<sur::i32> _hashes;

sur::Vec2 _camera_offset;

sur::Camera* _active_camera;

