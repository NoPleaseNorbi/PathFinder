#pragma once

#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include <SFML/Graphics.hpp>

/// \class Button
/// \brief A simple button class for SFML applications.

class Button {
public:
	/// \brief Default constructor.
	Button();

	/// \brief Constructor to initialize button with specified text, size, background color, and text color.
	/// \param button_text The text to display on the button.
	/// \param size The size of the button.
	/// \param background_color The background color of the button.
	/// \param text_color The color of the text on the button.
	Button(const std::string& button_text, const sf::Vector2f& size, const sf::Color& background_color, const sf::Color& text_color);
	
	/// \brief Copy constructor.
	Button(const Button& other);

	/// \brief Copy assignment operator.
	Button& operator=(const Button& other);

	/// \brief Move constructor.
	Button(Button&& other) noexcept;

	/// \brief Move assignment operator.
	Button& operator=(Button&& other) noexcept;

	/// \brief Set the font for the button's text.
	/// \param font The font to set.
	void setFont(const sf::Font& font);

	/// \brief Set the position of the button.
	/// \param point The position to set.
	void setPosition(const sf::Vector2f& point);

	/// \brief Set the background color of the button.
	/// \param color The color to set.
	void setBackgroundColor(const sf::Color& color);

	/// \brief Set the hover color of the button.
	/// \param color The color to set.
	void setHoverColor(const sf::Color& color);
	
	/// \brief Draw the button to a SFML render window.
	/// \param window The render window to draw to.
	void Draw(sf::RenderWindow& window);

	/// \brief Check if the mouse is over the button.
	/// \param window The render window to check the mouse position against.
	/// \return True if the mouse is over the button, otherwise false.
	bool MouseOver(const sf::RenderWindow& window);

private:
	sf::RectangleShape button;     //!< The button shape.
	sf::Text text;                 //!< The text displayed on the button.
	sf::Color _background_color;   //!< The background color of the button.
	sf::Color hover_color;         //!< The color of the button when hovered over.
};

#endif