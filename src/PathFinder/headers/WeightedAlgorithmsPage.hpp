#pragma once

#ifndef _WEIGHTEDALGORITHMSPAGE_HPP_
#define _WEIGHTEDALGORITHMSPAGE_HPP_

#include "../headers/Button.hpp"
#include "../headers/CellStates.hpp"
#include <SFML/Graphics.hpp>

/// \class WeightedPage
/// \brief Class for displaying weighted algorithms page.
class WeightedPage {
private:
    /// \brief Get the weight of an edge from user input.
    /// \param window The SFML render window to display input dialog.
    /// \return The weight of the edge entered by the user.
    int getEdgeWeight(sf::RenderWindow& window);

public:
    /// \brief Display the weighted algorithms page.
    /// \param window The SFML render window to display the page on.
    void Display(sf::RenderWindow& window);
};

#endif
