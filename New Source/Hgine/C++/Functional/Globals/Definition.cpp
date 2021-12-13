

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
	class Text;
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

std::vector<sur::Light*> _lights_hgine;

std::vector<sur::i32> _hashes;

sur::Vec2 _camera_offset;

sur::Camera* _active_camera;

bool _layer_changed;

std::vector<sur::Square*> _squares;
std::vector<sur::Line*> _lines;
std::vector<sur::Form*> _forms;
std::vector<sur::Triangle*> _triangles;
std::vector<sur::Sprite*> _sprites;
std::vector<sur::ParticleSystem*> _particles;
std::vector<sur::Light*> _lights;
std::vector<sur::Text*> _texts;
std::vector<sur::Camera*> _cameras;

sur::Square* _defaultSquare = new sur::Square({ 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), "defaultSquare");
sur::Line* _defaultLine = new sur::Line({ 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), "defaultLine");
sur::Form* _defaultForm = new sur::Form({}, {}, sur::Form::Modifier::None, sur::Form::FillMode::Auto, Color(0, 0, 0), "defaultFrom");
sur::Triangle* _defaultTriangle = new sur::Triangle({ 0.f, 0.f }, { 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), "defaultTriangle");
sur::Sprite* _defaultSprite = new sur::Sprite("NONE", sur::Sprite::FileType::Empty, { 0.f, 0.f }, "defaultSprite");
sur::ParticleSystem* _defaultParticleSystem = new sur::ParticleSystem(new sur::ParticleSettings(), "defaultParticleSystem");
sur::Light* _defaultLight = new sur::Light({ 0.f, 0.f }, 0.f, 0.f, 0.f, Color(0, 0, 0), "defaultLight");
sur::Text* _defaultText = new sur::Text(new sur::Font(), { 0.f,0.f }, 0, 0, "", "defaultText");
sur::Camera* _defaultCamera = new sur::Camera({ 0.f,0.f }, false, "defaultCamera");