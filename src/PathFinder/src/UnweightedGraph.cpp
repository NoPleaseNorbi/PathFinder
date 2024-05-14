#include "../headers/UnweightedGraph.hpp"
#include <iostream>
#include <cmath>
#include <climits>

#define NEIGHBOURS_COUNT 4 // The amount of neighbours a node has if we don't allow going trough a corncer of a node

// Constructor
UnweightedGraph::UnweightedGraph(const std::vector<std::vector<CellState>>& vertices_of_the_graph, const sf::Vector2i& starting_point, const sf::Vector2i& ending_point) {
    finished = false;
    vertices = vertices_of_the_graph;
    start = starting_point; 
    end = ending_point;
    row_size = vertices.size();
    column_size = vertices[0].size();
    vertices[end.x][end.y] = Empty;
    distances.resize(vertices.size(), std::vector<int>(vertices.size(), INT_MAX)); // Initailize everything for INT_MAX to find the shortest possible path
    visited.resize(vertices.size(), std::vector<bool>(vertices.size(), false));
    distances[start.x][start.y] = 0;
}

bool UnweightedGraph::CheckCellValidity(const int& row, const int& col) {
    if (row < 0 || col < 0 || row >= row_size || col >= column_size) {
        return false;
    }
    if (visited[row][col] || vertices[row][col] == Obstacle) {
        return false;
    }
    
    return true;
}

void UnweightedGraph::RunBFS() {
    if (!bfs_queue.empty()) {
        sf::Vector2i cell = bfs_queue.front();
        int x = cell.x;
        int y = cell.y;
        vertices[x][y] = RouteHelper;
        bfs_queue.pop();

        for (int i = 0; i < NEIGHBOURS_COUNT; i++) {

            int adjx = x + row_adder[i];
            int adjy = y + col_adder[i];

            if (CheckCellValidity(adjx, adjy)) {
                distances[adjx][adjy] = distances[x][y] + 1;
                bfs_queue.push({ adjx, adjy });
                visited[adjx][adjy] = true;
            }
        }
    }
    else {
        finished = true;
    }
}

void UnweightedGraph::RunDFS() {
    if (!dfs_stack.empty()) {
        sf::Vector2i cell = dfs_stack.top();
        int x = cell.x;
        int y = cell.y;
        vertices[x][y] = RouteHelper;

        dfs_stack.pop();

        for (int i = 0; i < NEIGHBOURS_COUNT; i++) {
            int adjx = x + row_adder[i];
            int adjy = y + col_adder[i];

            if (CheckCellValidity(adjx, adjy) && !visited[adjx][adjy]) {
                distances[adjx][adjy] = distances[x][y] + 1;
                dfs_stack.push({ adjx, adjy });
                visited[adjx][adjy] = true;
            }
        }
    }
    else {
        finished = true;
    }
}

void UnweightedGraph::RunDijkstra() {
    if (!dijkstra_priority_queue.empty()) {
        auto cell = dijkstra_priority_queue.top();
        dijkstra_priority_queue.pop();
        int x = cell.second.x;
        int y = cell.second.y;
        vertices[x][y] = RouteHelper;
        int dist = cell.first;

        if (distances[x][y] < dist) {
            return;
        }

        visited[x][y] = true;

        for (int i = 0; i < NEIGHBOURS_COUNT; i++) {
            int adjx = x + row_adder[i];
            int adjy = y + col_adder[i];
            int new_dist = dist + 1;

            if (CheckCellValidity(adjx, adjy) && new_dist < distances[adjx][adjy]) {
                distances[adjx][adjy] = new_dist;
                dijkstra_priority_queue.push({ new_dist, sf::Vector2i(adjx, adjy) });
            }
        }
    }
    else {
        finished = true;
    }
}

void UnweightedGraph::RunAStar() {
    if (!astar_priority_queue.empty()) {
        std::pair<float, sf::Vector2i> current = astar_priority_queue.top();
        sf::Vector2i cell = current.second;
        int x = cell.x;
        int y = cell.y;
        vertices[x][y] = RouteHelper;
        astar_priority_queue.pop();

        if (x == end.x && y == end.y) {
            finished = true;
            return;
        }

        for (int i = 0; i < NEIGHBOURS_COUNT; i++) {
            int adjx = x + row_adder[i];
            int adjy = y + col_adder[i];

            if (CheckCellValidity(adjx, adjy)) {
                float new_cost = distances[x][y] + 1 + std::sqrt(std::pow(end.x - adjx, 2) + std::pow(end.y - adjy, 2)); // Heuristic cost
                if (!visited[adjx][adjy] || new_cost < distances[adjx][adjy]) {
                    distances[adjx][adjy] = new_cost;
                    astar_priority_queue.push({ new_cost, sf::Vector2i(adjx, adjy)});
                    visited[adjx][adjy] = true;
                }
            }
        }
    }
}

void UnweightedGraph::RunGBFS() {
    if (!gbfs_priority_queue.empty()) {
        std::pair<float, sf::Vector2i> current = gbfs_priority_queue.top();
        sf::Vector2i cell = current.second;
        int x = cell.x;
        int y = cell.y;
        vertices[x][y] = RouteHelper;
        gbfs_priority_queue.pop();

        if (x == end.x && y == end.y) {
            finished = true;
            return;
        }

        for (int i = 0; i < NEIGHBOURS_COUNT; i++) {
            int adjx = x + row_adder[i];
            int adjy = y + col_adder[i];

            if (CheckCellValidity(adjx, adjy)) {
                float new_cost = std::sqrt(std::pow(end.x - adjx, 2) + std::pow(end.y - adjy, 2)); // Heuristic cost
                if (!visited[adjx][adjy]) {
                    gbfs_priority_queue.push({ new_cost, sf::Vector2i(adjx, adjy)});
                    visited[adjx][adjy] = true;
                    distances[adjx][adjy] = distances[x][y] + 1;
                }
            }
        }
    }
}


void UnweightedGraph::setStart(const sf::Vector2i& starting_point) {
    start = starting_point;
}

void UnweightedGraph::setEnd(const sf::Vector2i& ending_point) {
    end = ending_point;
}

void UnweightedGraph::setObstacles(const std::vector<std::vector<CellState>>& obstacles) {
    vertices = obstacles;
}

std::vector<std::vector<CellState>> UnweightedGraph::TraceShortestPath() {
    if (!visited[end.x][end.y]) {
        std::cout << "No path found!" << std::endl;
        return vertices;
    }

    int x = end.x, y = end.y;
    while (x != start.x || y != start.y) { 
        vertices[x][y] = Route;
        int minimal_distance = INT_MAX;
        int next_x = -1;
        int next_y = -1;
        for (int i = 0; i < NEIGHBOURS_COUNT; i++) {
            int adjx = x + row_adder[i];
            int adjy = y + col_adder[i];

            if (adjx >= 0 && adjx < row_size && adjy >= 0 && adjy < column_size) {
                if (distances[adjx][adjy] < minimal_distance) {
                    minimal_distance = distances[adjx][adjy];
                    next_x = adjx;
                    next_y = adjy;
                }
            }
        }
        x = next_x;
        y = next_y;
    }
    return vertices;
}

std::vector<std::vector<CellState>> UnweightedGraph::getVertices() {
    return vertices;
}

bool UnweightedGraph::getFinished() {
    return finished;
}

// Mainly for resetting the grid, to the previous colors (white)
void UnweightedGraph::ResetAlgorithm() {
    finished = false;
    distances.assign(vertices.size(), std::vector<int>(vertices.size(), INT_MAX));
    visited.assign(vertices.size(), std::vector<bool>(vertices.size(), false));
    distances[start.x][start.y] = 0;
    vertices[end.x][end.y] = Empty;
    visited[start.x][start.y] = true;
}

void UnweightedGraph::SetUpBFS() {
    ResetAlgorithm();
    while (!bfs_queue.empty()) {
        bfs_queue.pop();
    }
    bfs_queue.push({ start.x, start.y });
}

void UnweightedGraph::SetUpDFS() {
    ResetAlgorithm();
    while (!dfs_stack.empty()) {
        dfs_stack.pop();
    }
    dfs_stack.push({ start.x, start.y });
}

void UnweightedGraph::SetUpDijkstra() {
    ResetAlgorithm();
    while (!dijkstra_priority_queue.empty()) {
        dijkstra_priority_queue.pop();
    }
    dijkstra_priority_queue.push({ 0, start });
}

void UnweightedGraph::SetUpAStar() {
    ResetAlgorithm();
    while (!astar_priority_queue.empty()) {
        astar_priority_queue.pop();
    }
    float initial_cost = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));
    astar_priority_queue.push({ initial_cost, { start.x, start.y } });
}

void UnweightedGraph::SetUpGBFS() {
    ResetAlgorithm();
    while (!gbfs_priority_queue.empty()) {
        gbfs_priority_queue.pop();
    }
    float initial_cost = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));
    gbfs_priority_queue.push({ initial_cost, { start.x, start.y } });
}