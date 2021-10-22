

#pragma once

#include "../../../Includes.h"

namespace sur::Manager
{

	struct Storage 
	{

		inline static std::vector<Square*> squares;
		inline static std::vector<Line*> lines;
		inline static std::vector<Form*> forms;
		inline static std::vector<Triangle*> triangles;
		inline static std::vector<Sprite*> sprites;
		inline static std::vector<ParticleSystem*> particles;
		inline static std::vector<Light*> lights;

	};

	struct Dummy
	{

		inline static Square defaultSquare = Square({ 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), Collider::None, "defaultSquare");
		inline static Line defaultLine = Line({ 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), "defaultLine");
		inline static Form defaultForm = Form({}, {}, Form::Modifier::None, Form::FillMode::Auto, Color(0, 0, 0), "defaultFrom");
		inline static Triangle defaultTriangle = Triangle({ 0.f, 0.f }, { 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), "defaultTriangle");
		inline static Sprite defaultSprite = Sprite("NONE", Sprite::FileType::Empty, { 0.f, 0.f }, Collider::None, "defaultSprite");
		inline static ParticleSystem defaultParticleSystem = ParticleSystem(new ParticleSettings(), "defaultParticleSystem");
		inline static Light defaultLight = Light({ 0.f, 0.f }, 0.f, 0.f, 0.f, Color(0, 0, 0), "defaultLight");

	};

	void Add(void* object, Type type);

	void Remove(Type type, std::string_view name, i32 index = 0);

	void Delete(Type type, std::string_view name, i32 index = 0);

	void RemoveAll();

	void DeleteAll();

}