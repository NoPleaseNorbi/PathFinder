#pragma once

#ifndef _CELLSTATES_HPP_
#define _CELLSTATES_HPP_

/// \enum CellState
/// \brief Enum representing different states of a cell.
enum CellState {
    Empty,          ///< Empty cell state, representing an empty space.
    Obstacle,       ///< Obstacle cell state, representing an impassable obstacle.
    Route,          ///< Route cell state, representing a cell that is part of a route.
    RouteHelper     ///< RouteHelper cell state, representing a cell that is search trough when simulating an algorithm.
};

#endif