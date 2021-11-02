

#pragma once

#include "../../../../Includes.h"

namespace sur
{
	enum class Type;
	class Sprite;

	class Font
	{
	private:

		i32 hash;
		Type type;
		std::string name;

		Sprite* all;

	public:

		std::string align;

		std::vector<Sprite> chars;

		Font() = default;

		Font(std::string_view file, i32 charCount, std::string_view align, Color colorToAlpha, std::string_view name);

		std::string_view GetName() const;

		Type GetType() const;

		i32 GetHash() const;

		void OffsetChar(char character, Vec2 offset);

		~Font();
	};
//=======================================================================
	class Text
	{
	private:

		i32 hash;
		Type type;
		std::string name;
		Vec2f original_position;

	public:

		i32 spacingX;
		i32 original_spacingX;
		bool childOfCamera;

		Vec2f position;
		std::string text;
		Font* font;

		Text() = default;

		Text(Font* font, Vec2f position, i32 spacingX, std::string_view text, std::string_view name);

		std::string_view GetName() const;

		Type GetType() const;

		i32 GetHash() const;

		void Scale(f32 intensity);

		void Bind(bool render);
	};
//=======================================================================
}
