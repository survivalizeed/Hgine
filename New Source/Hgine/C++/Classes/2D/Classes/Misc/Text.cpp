

#include "../Objects.h"

sur::Text::Text(Font* font, Vec2f position, i32 spacingX, i32 spacingY, std::string_view text, std::string_view name)
{
	this->font = font;
	this->position = position;
	this->original_position = position;
	this->spacingX = spacingX;
	this->original_spacingX = spacingX;
	this->spacingY = spacingY;
	this->original_spacingY = spacingY;
	this->name = name;
	this->text = text;
	this->scale = 1.f;
	this->color = Color(255, 255, 255);
	this->type = Type::Text;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	Manager::Add(this);
	_objects.push_back(this);
}


ACCESS_PRIVATE_FIELD(sur::Object, sur::Vec2f, original_position);
ACCESS_PRIVATE_FIELD(sur::Sprite, sur::Vec2f, scaleOrigin);
ACCESS_PRIVATE_FIELD(sur::Sprite, sur::Mat3x3, scale);
ACCESS_PRIVATE_FUN(sur::Sprite, bool(), CheckOutOfScreen);

sur::Vec2f sur::Text::GetSize()
{
	Vec2f size;
	i32 counter = 0;
	size.y = font->maxYOfSprites * scale;
	for (i32 i = 0; i < text.size(); ++i) {
		for (i32 j = 0; j < font->align.size(); ++j) {
			if (text[i] == font->align[j]) {
				size.x += font->chars[j].size.x * scale;
				size.x += Unit(spacingX, Axis::X) * scale;
				counter++;
				break;
			}
			if (text[i] == ' ') {
				size.x += Unit(spacingX * 3, Axis::X) * scale;
				break;
			}
			if (text[i] == '\n') {
				size.y -= font->maxYOfSprites * scale;
				size.y -= Unit(spacingY * 3, Axis::Y) * scale;
				break;
			}
		}
	}
	return { size.x, size.y};
}

void sur::Text::Bind()
{
	if (childOfCamera) {
		position = original_position - STA(_camera_offset);
	}
	else {
		original_position = position + STA(_camera_offset);
	}

	DoRelevantChecks();

	if (render) {
		f32 xIncrementPool = 0;
		f32 yIncrementPool = 0;
		i32 index = 0;
		for (i32 i = 0, xSpacingCounter = 0, ySpacingCounter = 0; i < text.size(); ++i, ++xSpacingCounter) {
			for (i32 j = 0; j < font->align.size(); ++j) {
				if (text[i] == font->align[j]) {
					index = j;
					break;
				}
			}
			if (text[i] == ' ') {
				xIncrementPool += Unit(spacingX, Axis::X) * 3;
				continue;
			}
			if (text[i] == '\n') {
				xSpacingCounter = -1;	//Because it gets incremeted the next run
				ySpacingCounter++;
				xIncrementPool = 0;
				yIncrementPool -= font->maxYOfSprites;
				continue;
			}
			spacingX = i32(original_spacingX * scale);
			spacingY = i32(original_spacingY * scale);
			font->chars[index].tint = tint;
			font->chars[index].SetPosition({ position.x + xSpacingCounter * Unit(spacingX, Axis::X) + xIncrementPool, 
				position.y + ySpacingCounter * Unit(-spacingY, Axis::Y) + yIncrementPool});
			if (font->chars[index].childOfCamera) {
				font->chars[index].position = font->chars[index].original_position - STA(_camera_offset);
			}
			else {
				font->chars[index].original_position = font->chars[index].position + STA(_camera_offset);
			}	
			font->chars[index].Scale(original_position, { scale, scale });
			bool renderCurrent = true;
			/*if (font->chars[index].CheckOutOfScreen())
				renderCurrent = false;*/
			Mat3x3& refScale = access_private::scale(font->chars[index]);
			Vec2f& refScaleOrigin = access_private::scaleOrigin(font->chars[index]);
			if(renderCurrent)
				for (i32 i = 0; i < font->chars[index].points.size(); ++i)
					Set(ATS(refScale.Forward2D(STA(font->chars[index].points[i]) - refScaleOrigin) + refScaleOrigin) + ATS(font->chars[index].position), TintPixel(color));

			xIncrementPool += font->chars[index].original_size.x;
		}
	}
}

