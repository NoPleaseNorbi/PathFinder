#pragma once

#ifndef _UNWEIGHTEDALGORITHMSPAGE_HPP_
#define _UNWEIGHTEDALGORITHMSPAGE_HPP_

#include <SFML/Graphics.hpp>
#include "../headers/CellStates.hpp"
#include <vector>

/// \class UnweightedAlgorithmsPage
/// \brief Class for displaying unweighted algorithms page.
class UnweightedAlgorithmsPage {
private:
    /// \brief Reset the grid after running an algorithm, meaning it resets the magenta colored cells to white.
    void ResetGridAfterAlgorithm();

    /// \brief Reset the grid to initial state.
    void ResetGrid();
    
    std::vector<std::vector<CellState>> obstacles; ///< Grid representing obstacles in the maze.

public:
    /// \brief Display the unweighted algorithms page.
    /// \param window The SFML render window to display the page on.
    void Display(sf::RenderWindow& window);
};

#endif
