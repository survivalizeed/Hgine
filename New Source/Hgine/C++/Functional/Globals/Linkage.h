

#pragma once

#include "../../../Includes.h"

namespace sur 
{
	class Object;
	class Light;
	class Camera;
	struct ParticleSettings;
	struct Line;
	struct Triangle;
	struct Form;
	class Square;
	class Sprite;
	class ParticleSystem;
	class Font;
	struct Text;
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

extern std::vector<sur::Object*> _objects;

extern std::vector<sur::Light*> _lights_hgine;

extern std::vector<sur::i32> _hashes;

extern sur::Vec2 _camera_offset;

extern sur::Camera* _active_camera;

extern std::vector<sur::Square*> _squares;
extern std::vector<sur::Line*> _lines;
extern std::vector<sur::Form*> _forms;
extern std::vector<sur::Triangle*> _triangles;
extern std::vector<sur::Sprite*> _sprites;
extern std::vector<sur::ParticleSystem*> _particles;
extern std::vector<sur::Light*> _lights;
extern std::vector<sur::Text*> _texts;
extern std::vector<sur::Camera*> _cameras;

extern sur::Square* _defaultSquare;
extern sur::Line* _defaultLine;
extern sur::Form* _defaultForm;
extern sur::Triangle* _defaultTriangle;
extern sur::Sprite* _defaultSprite;
extern sur::ParticleSystem* _defaultParticleSystem;
extern sur::Light* _defaultLight;
extern sur::Text* _defaultText;
extern sur::Camera* _defaultCamera;