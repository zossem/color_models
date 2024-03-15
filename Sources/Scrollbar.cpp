#include "SFML/Graphics.hpp"
#include "Scrollbar.h"
#include <numeric>
#include <iostream>


Scrollbar::Scrollbar(sf::Vector2u draw_area_size) : width(100)
{
	high = std::floor(((float)draw_area_size.y) / 1.5f);

	sf::VertexArray tri(sf::Triangles, 3);
	
	triangle_left = tri;
	triangle_right = tri;
	
	// define the color of the triangle's points
	triangle_left[0].color = sf::Color::Black;
	triangle_left[1].color = sf::Color::Black;
	triangle_left[2].color = sf::Color::Black;

	triangle_right[0].color = sf::Color::Black;
	triangle_right[1].color = sf::Color::Black;
	triangle_right[2].color = sf::Color::Black;

	sf::VertexArray rect(sf::LinesStrip, 5);
	borders = rect;

	borders[0].color = sf::Color(140, 137, 137);
	borders[1].color = sf::Color(140, 137, 137);
	borders[2].color = sf::Color(140, 137, 137);
	borders[3].color = sf::Color(140, 137, 137);
	borders[4].color = sf::Color(140, 137, 137);

	current_position_pointer = 0.0f;

	SetDrawParamiters( draw_area_size);

	
	image.create(width, high);
	texture = new sf::Texture();

	createTexture();
	sprite.setTexture(*texture);
	sprite.setPosition(left_top);
}

Scrollbar::~Scrollbar()
{
	delete texture;
}

void Scrollbar::createTexture()
{
	
	for (unsigned int x = (int)left_top.x; x < (width + (int)left_top.x); x++)
	{
		for (unsigned int y = (int)left_top.y; y < (high + (int)left_top.y); y++)
		{
			int color = ((y - left_top.y) * 255.0f / high) + 0.5f;
			image.setPixel(x- (int)left_top.x, y- (int)left_top.y, sf::Color(color, color, color));
		}
	}
	texture->loadFromImage(image);
	
}

void Scrollbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
	target.draw(triangle_left);
	target.draw(triangle_right);
	target.draw(borders);
}

bool Scrollbar::isHitBox(sf::Vector2f mouse_position, float& lightness_to_set)
{
	if (left_top.x <= mouse_position.x <= right_bottom.x && left_top.y <= mouse_position.y <= right_bottom.y)
	{
		SetPoitionPointerOnClick(mouse_position);
		lightness_to_set = current_position_pointer;
		return true;
	}
	else
	{
		return false;
	}	
}

void Scrollbar::SetPoitionPointerOnClick(sf::Vector2f mouse_position)
{
	current_position_pointer = (right_bottom.y - mouse_position.y) / current_high;
	SetPoitionPointerResize();
}


void Scrollbar::SetPoitionPointerResize()
{
	triangle_left[0].position = sf::Vector2f(left_top.x, right_bottom.y - (current_position_pointer * current_high));
	triangle_left[1].position = sf::Vector2f(left_top.x - 10.0f, right_bottom.y - (current_position_pointer * current_high) + 10.0f);
	triangle_left[2].position = sf::Vector2f(left_top.x - 10.0f, right_bottom.y - (current_position_pointer * current_high) - 10.0f);

	triangle_right[0].position = sf::Vector2f(right_bottom.x, right_bottom.y - (current_position_pointer * current_high));
	triangle_right[1].position = sf::Vector2f(right_bottom.x + 10.0f, right_bottom.y - (current_position_pointer * current_high) + 10.0f);
	triangle_right[2].position = sf::Vector2f(right_bottom.x + 10.0f, right_bottom.y - (current_position_pointer * current_high) - 10.0f);
}

void Scrollbar::SetDrawParamiters(sf::Vector2u draw_area_size)
{
	
	current_high = std::floor(((float)draw_area_size.y) / 1.5f);
	left_top = sf::Vector2f((float)draw_area_size.x - (_SCROLLBAR_WIDTH / 1.5f), (float)draw_area_size.y * 0.1f);
	right_bottom = sf::Vector2f(left_top.x + (float)width, left_top.y + current_high);


	borders[0].position = left_top;
	borders[1].position = sf::Vector2f(left_top.x, right_bottom.y);
	borders[2].position = right_bottom;
	borders[3].position = sf::Vector2f(right_bottom.x, left_top.y);
	borders[4].position = left_top;

	
	sprite.setScale(1.0f, current_high /high);
	sprite.setPosition(left_top);

	SetPoitionPointerResize();
}



