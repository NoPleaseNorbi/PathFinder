#include "../headers/Button.hpp"

Button::Button() {
	button.setSize(sf::Vector2f(100, 100));
	_background_color = sf::Color::White;
	button.setFillColor(sf::Color::White);
	hover_color = sf::Color::Magenta;

	text.setString("button_text");
	text.setColor(sf::Color::Black);
}

Button::Button(const std::string& button_text, const sf::Vector2f& size, const sf::Color& background_color, const sf::Color& text_color) {
	button.setSize(size);
	_background_color = background_color;
	button.setFillColor(background_color);
	hover_color = sf::Color::Magenta;

	text.setString(button_text);
	text.setColor(text_color);
}

Button::Button(const Button& other) {
	button = other.button;
	text = other.text;
	_background_color = other._background_color;
	hover_color = other.hover_color;
}

Button& Button::operator=(const Button& other) {
	if (this != &other) {
		button = other.button;
		text = other.text;
		_background_color = other._background_color;
		hover_color = other.hover_color;
	}
	return *this;
}

Button::Button(Button&& other) noexcept {
	button = std::move(other.button);
	text = std::move(other.text);
	_background_color = std::move(other._background_color);
	hover_color = std::move(other.hover_color);
}

Button& Button::operator=(Button&& other) noexcept {
	if (this != &other) {
		button = std::move(other.button);
		text = std::move(other.text);
		_background_color = std::move(other._background_color);
		hover_color = std::move(other.hover_color);
	}
	return *this;
}

void Button::setFont(const sf::Font& font) {
	text.setFont(font);
}

void Button::setPosition(const sf::Vector2f& point) {
	button.setPosition(point);
	sf::FloatRect button_bound = button.getLocalBounds();
	sf::FloatRect text_bound = text.getLocalBounds();

	sf::Vector2f text_pos;
	text_pos.x = point.x + (button_bound.width / 2.0f) - (text_bound.width / 2.0f);
	text_pos.y = point.y + (button_bound.height / 2.0f) - (text_bound.height / 2.0f);

	text.setPosition(text_pos);
}

void Button::setBackgroundColor(const sf::Color& color) {
	button.setFillColor(color);
}

void Button::setHoverColor(const sf::Color& color) {
	hover_color = color;
}

void Button::Draw(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}

bool Button::MouseOver(const sf::RenderWindow& window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	bool isOver = button.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
	if (isOver) {
		button.setFillColor(hover_color);
	}
	else {
		button.setFillColor(_background_color);
	}
	return isOver;
}