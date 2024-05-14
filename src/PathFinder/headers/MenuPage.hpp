#pragma once

#ifndef _MENUPAGE_HPP_
#define _MENUPAGE_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "UnweightedAlgorithmsPage.hpp"
#include "WeightedAlgorithmsPage.hpp"

/// \enum MenuResult
/// \brief Enum representing possible results of the menu page.
enum MenuResult { 
    Nothing,        ///< No action is taken.
    Weighted,       ///< Start the weighted algorithms page.
    Unweighted,     ///< Start the unweighted algorithms page.
    Quit            ///< Quit the application.
};

/// \class MenuPage
/// \brief Class representing the main menu page.
class MenuPage {
public:
    /// \brief Display the main menu page.
    /// \param window The SFML render window to display the menu on.
    /// \return The menu result based on user interaction.
    MenuResult Show(sf::RenderWindow& window);
};

#endif
