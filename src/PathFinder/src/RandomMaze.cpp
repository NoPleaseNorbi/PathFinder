#include "../headers/RandomMaze.hpp"
#include <ctime>
#include <stack>

RandomMaze::RandomMaze(const int& rows_number, const int& cols_number) {
	finished = false;
	rows = rows_number;
	cols = cols_number;
	current_row_for_random_maze = 0;
	current_col_for_random_maze = 0;
    grid.resize(rows, std::vector<CellState>(cols, CellState::Obstacle));
}

std::vector<std::pair<int, int>> RandomMaze::getNeighbors(const int& x, const int& y) {
	std::vector<std::pair<int, int>> neighbors;
	if (x > 1) {
		neighbors.push_back(std::make_pair(x - 2, y));
	}
	if (y > 1) {
		neighbors.push_back(std::make_pair(x, y - 2));
	}
	if (x < cols - 2) {
		neighbors.push_back(std::make_pair(x + 2, y));
	}
	if (y < rows - 2) {
		neighbors.push_back(std::make_pair(x, y + 2));
	}
	return neighbors;
}

void RandomMaze::GenerateRecursiveBacktrackerMaze() {
	srand(time(NULL));

	if (!backtracker_maze_stack.empty()) {
		int x = backtracker_maze_stack.top().first, y = backtracker_maze_stack.top().second;
		backtracker_maze_stack.pop();

		std::vector<std::pair<int, int>> neighbors = getNeighbors(x, y);
		for (auto& neighbor : neighbors) {
			if (grid[neighbor.second][neighbor.first] == CellState::Obstacle) {
				grid[neighbor.second][neighbor.first] = CellState::Empty;
				grid[(neighbor.second + y) / 2][(neighbor.first + x) / 2] = CellState::Empty;
				backtracker_maze_stack.push(neighbor);
			}
		}
	}
	else {
		finished = true;
	}

}

void RandomMaze::SetUpRecursiveBacktrackerMaze(const sf::Vector2i& starting_point, const sf::Vector2i& ending_point) {
	grid.assign(rows, std::vector<CellState>(cols, CellState::Obstacle));
	finished = false;
	while (!backtracker_maze_stack.empty()) {
		backtracker_maze_stack.pop();
	}
	start = starting_point;
	end = ending_point;
	backtracker_maze_stack.push({ start.x, start.y });
	grid[start.x][start.y] = CellState::Obstacle;
}

void RandomMaze::GenerateRandomMaze() {
	if (current_row_for_random_maze < rows) {
		if (current_col_for_random_maze < cols) {
			if ((rand() % 3) == 0) {
				grid[current_col_for_random_maze][current_row_for_random_maze] = Obstacle;
			}
			else {
				grid[current_col_for_random_maze][current_row_for_random_maze] = Empty;
			}
			current_col_for_random_maze++;
		}
		else {
			current_col_for_random_maze = 0;
			current_row_for_random_maze++;
		}
	}
	else {
		finished = true;
	}
}

std::vector<std::vector<CellState>> RandomMaze::getGrid() {
	return grid;
}

void RandomMaze::SetUpRandomMaze() {
	finished = false;
	current_row_for_random_maze = 0;
	current_col_for_random_maze = 0;
}

bool RandomMaze::getFinished() {
	return finished;
}

void RandomMaze::setGrid(const std::vector<std::vector<CellState>>& replacement_grid) {
	grid = replacement_grid;
}