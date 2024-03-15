#ifndef _SCROLLBAR_
#define _SCROLLBAR_

#define _SCROLLBAR_WIDTH 200.0f

class Scrollbar : public sf::Drawable
{
private:
	const unsigned int width;
	unsigned int high;
	float current_high;
	sf::Vector2f left_top, right_bottom;
	float current_position_pointer; //from 0.0 to 1.0

	sf::Image image;
	sf::Texture* texture;
	sf::Sprite sprite;

	sf::VertexArray  triangle_left,	triangle_right, borders;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isHitBox(sf::Vector2f mouse_position, float& lightness_to_set);
	void SetPoitionPointerOnClick(sf::Vector2f mouse_position);
	void SetPoitionPointerResize();
	void SetDrawParamiters(sf::Vector2u draw_area_size);
	void createTexture();
	Scrollbar(sf::Vector2u draw_area_size);
	~Scrollbar();
};


#endif // !_HEXAGON_