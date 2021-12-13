

#include "../Objects.h"

sur::InputBox::InputBox(Font* font, Vec2f position, i32 spacingX, std::string_view name)
{
	this->textObj.font = font;
	this->position = position;
	this->original_position = position;
	this->textObj.spacingX = spacingX;
	this->textObj.original_spacingX = spacingX;
	this->name = name;
	this->text = text;
	this->type = Type::InputBox;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	_objects.push_back(this);
}

void sur::InputBox::Bind()
{

}
