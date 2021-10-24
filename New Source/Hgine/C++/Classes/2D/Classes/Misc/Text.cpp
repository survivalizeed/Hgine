

#include "../Objects.h"

sur::Text::Text(Font* font, Vec2f position, i32 spacingX, std::string_view text)
{
	this->font = font;
	this->position = position;
	this->spacingX = spacingX;
	this->original_spacingX = spacingX;
	this->text = text;
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
	f32 xIncrementPool = 0;
	i32 index = 0;
	for (i32 i = 0; i < text.size(); ++i) {
		for (i32 j = 0; j < font->align.size(); ++j) {
			if (text[i] == font->align[j]) {
				index = j;
				break;
			}
		}
		font->chars[index].position({ position.x + i * Unit(spacingX, Axis::X) + xIncrementPool, position.y});
		font->chars[index].Bind(true);
		xIncrementPool += font->chars[index].size.x;
	}
}