

#include "../GUI.h"

sur::Text::Text(Font* font, Vec2f position, i32 spacingX, std::string_view text, std::string_view name)
{
	this->font = font;
	this->position = position;
	this->original_position = position;
	this->spacingX = spacingX;
	this->original_spacingX = spacingX;
	this->name = name;
	this->text = text;
	this->type = Type::Text;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
}

void sur::Text::Scale(f32 intensity)
{
	for (i32 i = 0; i < font->chars.size(); ++i) {
		font->chars[i].Scale(position, { intensity, intensity });
	}
	spacingX = i32(original_spacingX * intensity);
}

void sur::Text::Bind(bool render)
{
	if (childOfCamera) {
		position = original_position - STA(_camera_offset);
	}
	else {
		original_position = position + STA(_camera_offset);
	}
	f32 xIncrementPool = 0;
	i32 index = 0;
	for (i32 i = 0; i < text.size(); ++i) {
		for (i32 j = 0; j < font->align.size(); ++j) {
			if (text[i] == font->align[j]) {
				index = j;
				break;
			}
		}
		if (text[i] == ' ') {
			xIncrementPool += Unit(spacingX * 3, Axis::X);
			continue;
		}
		font->chars[index].position({ position.x + i * Unit(spacingX, Axis::X) + xIncrementPool, position.y});
		font->chars[index].Bind(true);
		xIncrementPool += font->chars[index].size.x;
	}
}

std::string_view sur::Text::GetName() const
{
	return name;
}

sur::Type sur::Text::GetType() const
{
	return type;
}

sur::i32 sur::Text::GetHash() const
{
	return hash;
}
