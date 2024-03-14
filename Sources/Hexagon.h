#ifndef _HEXAGON_
#define _HEXAGON_

#define SCROLLBAR_WIDTH 200.0f



class hexagon : public sf::Drawable
{
protected:
    sf::Vector2f borders_size, shift;
    sf::Vector2f left_top, right_bottom, center;
    sf::Vector2f p[6]; // Kolejnoœæ punktów opisana w pliku PDF do laboratorium.
    sf::VertexArray square, hex;
    sf::Text name, up_corrner, left_corrner, right_corrner;
public:
    void Set_Borders(sf::Vector2f _left_top, sf::Vector2f _right_bottom);
    void Draw_Border(sf::RenderTarget& target, sf::RenderStates states) const;
    bool rhombus(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p, float& alpha, float& beta) const;
    void SetDrawParameters(sf::Vector2u draw_area_size);
    hexagon();

    std::shared_ptr<sf::Font> font;
private:
    float d_coefficient(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p) const;
};


class hexagon_RGB : public hexagon
{
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void SetDrawParameters(sf::Vector2u draw_area_size);
    hexagon_RGB();
};

class hexagon_CMY : public hexagon
{
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void SetDrawParameters(sf::Vector2u draw_area_size);
    hexagon_CMY();
};


class hexagon_HSL : public hexagon
{
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void SetDrawParameters(sf::Vector2u draw_area_size);
    hexagon_HSL();
};

class hexagon_HSB : public hexagon
{
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void SetDrawParameters(sf::Vector2u draw_area_size);
    hexagon_HSB();
};


#endif // !_HEXAGON_