

#pragma once

#include "../../../Includes.h"

namespace sur::Manager
{

#define IS inline static

	struct Storage 
	{

		IS std::vector<Square*> squares;
		IS std::vector<Line*> lines;
		IS std::vector<Form*> forms;
		IS std::vector<Triangle*> triangles;
		IS std::vector<Sprite*> sprites;
		IS std::vector<ParticleSystem*> particles;
		IS std::vector<Light*> lights;
		IS std::vector<Font*> fonts;
		IS std::vector<Text*> texts;
		IS std::vector<Camera*> cameras;

	};

	struct Dummy
	{

		IS Square defaultSquare = Square({ 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), "defaultSquare");
		IS Line defaultLine = Line({ 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), "defaultLine");
		IS Form defaultForm = Form({}, {}, Form::Modifier::None, Form::FillMode::Auto, Color(0, 0, 0), "defaultFrom");
		IS Triangle defaultTriangle = Triangle({ 0.f, 0.f }, { 0.f, 0.f }, { 0.f, 0.f }, Color(0, 0, 0), "defaultTriangle");
		IS Sprite defaultSprite = Sprite("NONE", Sprite::FileType::Empty, { 0.f, 0.f }, "defaultSprite");
		IS ParticleSystem defaultParticleSystem = ParticleSystem(new ParticleSettings(), "defaultParticleSystem");
		IS Light defaultLight = Light({ 0.f, 0.f }, 0.f, 0.f, 0.f, Color(0, 0, 0), "defaultLight");
		IS Font defaultFont = Font("NONE", 0, "", Color(0, 0, 0), "defaultFont");
		IS Text defaultText = Text(new Font(), { 0.f,0.f }, 0, "", "defaultText");
		IS Camera defaultCamera = Camera({ 0.f,0.f }, false, "defaultCamera");

	};

	void Add(void* object, Type type);

	void Remove(Type type, std::string_view name, i32 index = 0);

	void Delete(Type type, std::string_view name, i32 index = 0);

	void RemoveAll();

	void DeleteAll();

}