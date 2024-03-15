#include "SFML/Graphics.hpp"
#include "Hexagon.h"
#include <numeric>
#include "ShareTechMono-Regular.h"


hexagon::hexagon()
{
    sf::VertexArray sq(sf::LinesStrip, 5);
    square = sq;
    square[0].color = sf::Color(140, 137, 137);
    square[1].color = sf::Color(140, 137, 137);
    square[2].color = sf::Color(140, 137, 137);
    square[3].color = sf::Color(140, 137, 137);
    square[4].color = sf::Color(140, 137, 137);

    sf::VertexArray h(sf::LinesStrip, 7);
    hex = h;
    hex[0].color = sf::Color::Black;
    hex[1].color = sf::Color::Black;
    hex[2].color = sf::Color::Black;
    hex[3].color = sf::Color::Black;
    hex[4].color = sf::Color::Black;
    hex[5].color = sf::Color::Black;
    hex[6].color = sf::Color::Black;

    font = std::make_shared<sf::Font>();
    font->loadFromMemory(&(ShareTechMono_Regular_ttf[0]), ShareTechMono_Regular_ttf.size());

    name.setFont(*font);
    name.setCharacterSize(21);
    name.setFillColor(sf::Color::Black);

    up_corrner.setFont(*font);
    up_corrner.setCharacterSize(21);
    up_corrner.setFillColor(sf::Color::Black);

    left_corrner.setFont(*font);
    left_corrner.setCharacterSize(21);
    left_corrner.setFillColor(sf::Color::Black);

    right_corrner.setFont(*font);
    right_corrner.setCharacterSize(21);
    right_corrner.setFillColor(sf::Color::Black);
}

hexagon_RGB::hexagon_RGB()
{
    name.setString("RGB");
    up_corrner.setString("R");
    left_corrner.setString("G");
    right_corrner.setString("B");
}

hexagon_CMY::hexagon_CMY()
{
    name.setString("CMK");
    up_corrner.setString("C");
    left_corrner.setString("M");
    right_corrner.setString("K");
}

hexagon_HSL::hexagon_HSL()
{
    name.setString("HSL");
    up_corrner.setString("H");
    left_corrner.setString("S");
    right_corrner.setString("L");
}

hexagon_HSB::hexagon_HSB()
{
    name.setString("HSB");
    up_corrner.setString("H");
    left_corrner.setString("S");
    right_corrner.setString("B");
}

//Trochê matematyki jeszcze nikomu nie zaszkodzi³o. Wiêc dwie kolejne metody to czysta matematyka.
float hexagon::d_coefficient(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p) const
{
    float A = p0.y - p1.y;
    float B = p1.x - p0.x;
    float C = p0.x * (p1.y - p0.y) - p0.y * (p1.x - p0.x);

    return 2 * ((A * p.x + B * p.y + C) / sqrt(A * A + B * B)) / sqrt(3.0f);
}

bool hexagon::rhombus(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p, float& alpha, float& beta) const
{
    float L = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
    sf::Vector2f p3(0.5f * (p0.x - p1.x) + 0.5f * sqrt(3.0f) * (p1.y - p0.y) + p0.x, 0.5f * sqrt(3.0f) * (p0.x - p1.x) - 0.5f * (p1.y - p0.y) + p0.y);

    beta = -d_coefficient(p0, p1, p) / L;
    alpha = d_coefficient(p0, p3, p) / L;

    if ((alpha > 1.0f) || (beta > 1.0f) || (alpha < 0.0f) || (beta < 0.0f)) return false; else return true;
}

void hexagon::Set_Borders(sf::Vector2f _left_top, sf::Vector2f _right_bottom)
{
    left_top = _left_top;
    right_bottom = _right_bottom;
    float a = ((right_bottom.y - left_top.y) / 2.0f + 0.5f) - 20.0f;
    center = left_top + sf::Vector2f((right_bottom.x - left_top.x) / 2.0f + 0.5f, (right_bottom.y - left_top.y) / 2.0f + 0.5f + 10);

    p[0] = center - sf::Vector2f(0.0f, a);
    p[1] = center - sf::Vector2f(0.5f * sqrt(3.0f) * a, 0.5f * a);
    p[2] = center - sf::Vector2f(0.5f * sqrt(3.0f) * a, -0.5f * a);
    p[3] = center + sf::Vector2f(0.0f, a);
    p[4] = center + sf::Vector2f(0.5f * sqrt(3.0f) * a, 0.5f * a);
    p[5] = center + sf::Vector2f(0.5f * sqrt(3.0f) * a, -0.5f * a);

    square[0].position = sf::Vector2f(left_top.x + 5.0f, left_top.y + 5.0f);
    square[1].position = sf::Vector2f(left_top.x + 5.0f, right_bottom.y - 5.0f);
    square[2].position = sf::Vector2f(right_bottom.x - 5.0f, right_bottom.y - 5.0f);
    square[3].position = sf::Vector2f(right_bottom.x - 5.0f, left_top.y + 5.0f);
    square[4].position = sf::Vector2f(left_top.x + 5.0f, left_top.y + 5.0f);

    for (int i = 0; i < 7; i++)
        hex[i].position = p[i % 6];

    name.setPosition(sf::Vector2f(left_top.x + 5.0f, left_top.y + 5.0f));
    up_corrner.setPosition(p[0]- sf::Vector2f(20.0f,  20.0f));
    left_corrner.setPosition(p[2] - sf::Vector2f(10.0f, 0.0f));
    right_corrner.setPosition(p[4] + sf::Vector2f(10.0f, 0.0f));
}

void hexagon::Draw_Border(sf::RenderTarget& target, sf::RenderStates states) const
{   
    target.draw(square);
    target.draw(hex);  

    target.draw(name);
    target.draw(up_corrner);
    target.draw(right_corrner);
    target.draw(left_corrner);
  
    
    // Tu trzeba narysowaæ ramkê. I napisy.
}

void hexagon_RGB::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Tu trzeba narysowaæ szeœciok¹t RGB.
    float alfa, beta;
    sf::Vector2f point;
    sf::VertexArray to_draw(sf::Points, 1);

    for (float i = left_top.x; i < right_bottom.x; i += 1.0f)
    {
        for (float j = left_top.y; j < right_bottom.y; j += 1.0f)
        {
            point = sf::Vector2f(i, j);
            if (hexagon::rhombus(p[0], p[1], point, alfa, beta))
            {
                to_draw[0].position = point;
                to_draw[0].color = sf::Color(255, alfa * 255, beta * 255);
            }
            if (hexagon::rhombus(p[2], p[3], point, alfa, beta))
            {
                to_draw[0].position = point;
                to_draw[0].color = sf::Color(beta * 255,  255, alfa * 255);
            }
            if (hexagon::rhombus(p[4], p[5], point, alfa, beta))
            {
                to_draw[0].position = point;
                to_draw[0].color = sf::Color(alfa * 255, beta * 255,  255);
            }

            target.draw(to_draw);
        }
    }

    Draw_Border(target, states);
}



void hexagon_CMY::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Tu trzeba narysowaæ szeœciok¹t CMY.

    Draw_Border(target, states);
}



void hexagon_HSL::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Tu trzeba narysowaæ szeœciok¹t HSL.

    Draw_Border(target, states);
}



void hexagon_HSB::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Tu trzeba narysowaæ szeœciok¹t HSB.

    Draw_Border(target, states);
}

void hexagon::SetDrawParameters(sf::Vector2u draw_area_size)
{
    float border = std::min(std::floor(((float)draw_area_size.x - SCROLLBAR_WIDTH -1.0f)/ 2.0f), std::floor(((float)draw_area_size.y -1.0f)/ 2.0f));
    borders_size = sf::Vector2f(border, border);
    shift = sf::Vector2f(
        ((float)draw_area_size.x - SCROLLBAR_WIDTH - 1.0f - this->borders_size.x * 2.0f) / 2.0f,
        ((float)draw_area_size.y - 1.0f - this->borders_size.y * 2.0f) / 3.0f    );
}

void hexagon_RGB::SetDrawParameters(sf::Vector2u draw_area_size)
{
    hexagon::SetDrawParameters(draw_area_size);
    Set_Borders(sf::Vector2f(0.0f + shift.x , 0.0f + shift.y ), sf::Vector2f(borders_size.x + shift.x, borders_size.y + shift.y));
}


void hexagon_CMY::SetDrawParameters(sf::Vector2u draw_area_size)
{
    hexagon::SetDrawParameters(draw_area_size);
    Set_Borders(sf::Vector2f(borders_size.x + (shift.x *2.0f), 0.0f + shift.y), sf::Vector2f(borders_size.x * 2.0f + (shift.x * 2.0f), borders_size.y + shift.y));
}

void hexagon_HSL::SetDrawParameters(sf::Vector2u draw_area_size)
{
    hexagon::SetDrawParameters(draw_area_size);
    Set_Borders(sf::Vector2f(0.0f + shift.x, borders_size.y + (shift.y * 2.0f)), sf::Vector2f(borders_size.x + shift.x, borders_size.y * 2.0f + (shift.y * 2.0f)));
}

void hexagon_HSB::SetDrawParameters(sf::Vector2u draw_area_size)
{
    hexagon::SetDrawParameters(draw_area_size);
    Set_Borders(sf::Vector2f(borders_size.x + (shift.x * 2.0f), borders_size.y + (shift.y * 2.0f)), sf::Vector2f(borders_size.x * 2.0f + (shift.x * 2.0f), borders_size.y * 2.0f + (shift.y * 2.0f)));
}