#include "../headers/UnweightedAlgorithmsPage.hpp"
#include "../headers/Button.hpp"
#include "../headers/UnweightedGraph.hpp"
#include "../headers/RandomMaze.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

const int GRID_SIZE = 25; // Number of cells in each row/column
const int CELL_SIZE = 25; // Size of each cell in pixels

const int OFFSET = 20; // Offset of the grid from the edge of the window

enum class AlgorithmPicked {
    None,
    BFS,
    DFS,
    Dijkstra,
    AStar,
    GBFS,
    RandomMaze,
    RandomBacktrackerMaze
};

void UnweightedAlgorithmsPage::ResetGridAfterAlgorithm() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (obstacles[i][j] != Obstacle) {
                obstacles[i][j] = Empty;
            }
        }
    }
}

void UnweightedAlgorithmsPage::ResetGrid() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            obstacles[i][j] = Empty;
        }
    }
}

void UnweightedAlgorithmsPage::Display(sf::RenderWindow& window) {
    AlgorithmPicked algoritm_picker;
    algoritm_picker = AlgorithmPicked::None;
    
    sf::Clock timer; // The time for the algorithms
    constexpr float step_interval = 0.03f; // The time between a tick in any algorithm
    
    sf::Font font;
    if (!font.loadFromFile(PROJECT_SOURCE_DIR + std::string("/monoregular.ttf"))) {
        std::cerr << "Font not found" << std::endl;
        return;
    }

    std::vector<std::vector<sf::RectangleShape>> grid(GRID_SIZE, std::vector<sf::RectangleShape>(GRID_SIZE));
    obstacles.resize(GRID_SIZE, std::vector<CellState>(GRID_SIZE, Empty));
    
    sf::Vector2i start(0, 0);
    sf::Vector2i end(GRID_SIZE - 1, GRID_SIZE - 1);
    
    UnweightedGraph graph(obstacles, start, end);
    RandomMaze random_maze(GRID_SIZE, GRID_SIZE);

    // Set up of the buttons
    Button reset_button("Reset grid", { 350, 100 }, sf::Color(255, 32, 78), sf::Color::White);
    reset_button.setHoverColor(sf::Color(158, 28, 33));
    reset_button.setFont(font);
    reset_button.setPosition({ 325, 680 });

    Button random_maze_button("Random maze", { 300, 70 }, sf::Color(255, 32, 78), sf::Color::White);
    random_maze_button.setHoverColor(sf::Color(160, 21, 62));
    random_maze_button.setFont(font);
    random_maze_button.setPosition({ 350, 800 });

    Button recursive_backtracker_maze_button("Recursive maze", { 300, 70 }, sf::Color(255, 32, 78), sf::Color::White);
    recursive_backtracker_maze_button.setHoverColor(sf::Color(160, 21, 62));
    recursive_backtracker_maze_button.setFont(font);
    recursive_backtracker_maze_button.setPosition({ 350, 900 });

    Button bfs_button("BFS", { 300, 70 }, sf::Color(255, 32, 78), sf::Color::White);
    bfs_button.setHoverColor(sf::Color(160, 21, 62));
    bfs_button.setFont(font);
    bfs_button.setPosition({ 680, 20 });

    Button dfs_button("DFS", { 300, 70 }, sf::Color(255, 32, 78), sf::Color::White);
    dfs_button.setHoverColor(sf::Color(160, 21, 62));
    dfs_button.setFont(font);
    dfs_button.setPosition({ 680, 110 });

    Button dijkstra_button("Dijkstra", { 300, 70 }, sf::Color(255, 32, 78), sf::Color::White);
    dijkstra_button.setHoverColor(sf::Color(160, 21, 62));
    dijkstra_button.setFont(font);
    dijkstra_button.setPosition({ 680, 200 });

    Button a_star_button("A Star", { 300, 70 }, sf::Color(255, 32, 78), sf::Color::White);
    a_star_button.setHoverColor(sf::Color(160, 21, 62));
    a_star_button.setFont(font);
    a_star_button.setPosition({ 680, 290 });

    Button gbfs_button("GBFS", { 300, 70 }, sf::Color(255, 32, 78), sf::Color::White);
    gbfs_button.setHoverColor(sf::Color(160, 21, 62));
    gbfs_button.setFont(font);
    gbfs_button.setPosition({ 680, 380 });

    // Initializing the grid for later use, setting the positions
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            grid[i][j].setPosition(OFFSET + i * CELL_SIZE, OFFSET + j * CELL_SIZE);
            grid[i][j].setOutlineThickness(1);
            grid[i][j].setOutlineColor(sf::Color::Black);
        }
    }

    // The helper booleans for the drawing of objects when the mouse is dragging
    bool is_left_dragging = false;
    bool is_right_dragging = false;
    bool is_start_key_held = false;
    bool is_end_key_held = false;

    int last_x_coordinate = -1, last_y_coordinate = -1; // The coordinates of the last point clicked on the grid 

    // Set up the window
    while (window.isOpen()) {
        sf::Time elapsed = timer.getElapsedTime();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (bfs_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    algoritm_picker = AlgorithmPicked::BFS;
                    ResetGridAfterAlgorithm();
                    graph.setObstacles(obstacles);
                    graph.SetUpBFS();
                }
            }
            else if (dfs_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    algoritm_picker = AlgorithmPicked::DFS;
                    ResetGridAfterAlgorithm();
                    graph.setObstacles(obstacles);
                    graph.SetUpDFS();
                }
            }
            else if (dijkstra_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    algoritm_picker = AlgorithmPicked::Dijkstra;
                    ResetGridAfterAlgorithm();
                    graph.setObstacles(obstacles);
                    graph.SetUpDijkstra();
                }
            }
            else if (a_star_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    algoritm_picker = AlgorithmPicked::AStar;
                    ResetGridAfterAlgorithm();
                    graph.setObstacles(obstacles);
                    graph.SetUpAStar();
                }
            }
            else if (gbfs_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    algoritm_picker = AlgorithmPicked::GBFS;
                    ResetGridAfterAlgorithm();
                    graph.setObstacles(obstacles);
                    graph.SetUpGBFS();
                }
            }
            else if (reset_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    ResetGrid();
                    graph.ResetAlgorithm();
                    graph.setObstacles(obstacles);
                    algoritm_picker = AlgorithmPicked::None;
                }
            }
            else if (random_maze_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
                    algoritm_picker = AlgorithmPicked::RandomMaze;
                    ResetGrid();
                    random_maze.setGrid(obstacles);
                    random_maze.SetUpRandomMaze();
                }
            }
            else if (recursive_backtracker_maze_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    algoritm_picker = AlgorithmPicked::RandomBacktrackerMaze;
                    ResetGrid();
                    random_maze.setGrid(obstacles);
                    random_maze.SetUpRecursiveBacktrackerMaze(start, end);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                is_left_dragging = true;
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                is_left_dragging = false;
                last_x_coordinate = -1;
                last_y_coordinate = -1;
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                is_right_dragging = true;
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
                is_right_dragging = false;
                last_x_coordinate = -1;
                last_y_coordinate = -1;
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) {
                    is_start_key_held = true;
                }
                else if (event.key.code == sf::Keyboard::E) {
                    is_end_key_held = true;
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::S) {
                    is_start_key_held = false;
                }
                else if (event.key.code == sf::Keyboard::E) {
                    is_end_key_held = false;
                }
            }
        }

        // Handle mouse drag to color cells
        if (is_left_dragging) {
            int mouse_x_coordinate = sf::Mouse::getPosition(window).x;
            int mouse_y_coordinate = sf::Mouse::getPosition(window).y;

            int cell_x_coordinate = (mouse_x_coordinate - OFFSET) / CELL_SIZE;
            int cell_y_coordinate = (mouse_y_coordinate - OFFSET) / CELL_SIZE;
            

            if (is_start_key_held) {
                if (cell_x_coordinate >= 0 && cell_x_coordinate < GRID_SIZE && cell_y_coordinate >= 0 && cell_y_coordinate < GRID_SIZE) {
                    start.x = cell_x_coordinate;
                    start.y = cell_y_coordinate;
                    graph.setStart(start); // Resetting the start in the grid
                    graph.ResetAlgorithm(); // Reset the algorithm so it doesn't cause any undefined behaviour
                    algoritm_picker = AlgorithmPicked::None;
                }
            }

            else if (is_end_key_held) {
                if (cell_x_coordinate >= 0 && cell_x_coordinate < GRID_SIZE && cell_y_coordinate >= 0 && cell_y_coordinate < GRID_SIZE) {
                    end.x = cell_x_coordinate;
                    end.y = cell_y_coordinate;
                    graph.setEnd(end); // Resetting the end in the grid
                    graph.ResetAlgorithm(); // Reset the algorithm so it doesn't cause any undefined behaviour
                    algoritm_picker = AlgorithmPicked::None;
                }
            }
            else if (cell_x_coordinate >= 0 && cell_x_coordinate < GRID_SIZE && cell_y_coordinate >= 0 && cell_y_coordinate < GRID_SIZE) {
                if (last_x_coordinate == -1 || last_x_coordinate != cell_x_coordinate || last_y_coordinate != cell_y_coordinate) {
                    obstacles[cell_x_coordinate][cell_y_coordinate] = Obstacle;
                    graph.ResetAlgorithm();
                    graph.setObstacles(obstacles);
                    algoritm_picker = AlgorithmPicked::None;
                    last_x_coordinate = cell_x_coordinate;
                    last_y_coordinate = cell_y_coordinate;
                }
            }   
        }
        else if (is_right_dragging) {
            int mouse_x_coordinate = sf::Mouse::getPosition(window).x;
            int mouse_y_coordinate = sf::Mouse::getPosition(window).y;

            int cell_x_coordinate = (mouse_x_coordinate - OFFSET) / CELL_SIZE;
            int cell_y_coordinate = (mouse_y_coordinate - OFFSET) / CELL_SIZE;
            if (cell_x_coordinate >= 0 && cell_x_coordinate < GRID_SIZE && cell_y_coordinate >= 0 && cell_y_coordinate < GRID_SIZE) {
                if (last_x_coordinate == -1 || last_x_coordinate != cell_x_coordinate || last_y_coordinate != cell_y_coordinate) {
                    obstacles[cell_x_coordinate][cell_y_coordinate] = Empty;
                    graph.ResetAlgorithm();
                    graph.setObstacles(obstacles);
                    last_x_coordinate = cell_x_coordinate;
                    last_y_coordinate = cell_y_coordinate;
                }
            }
        }
        // Starting an algorithm based on the algorithm picked
        if (elapsed.asSeconds() >= step_interval && algoritm_picker != AlgorithmPicked::None) {
            switch (algoritm_picker) {
            case AlgorithmPicked::BFS:
                graph.RunBFS();
                break;
            case AlgorithmPicked::DFS:
                graph.RunDFS();
                break;
            case AlgorithmPicked::Dijkstra:
                graph.RunDijkstra();
                break;
            case AlgorithmPicked::AStar:
                graph.RunAStar();
                break;
            case AlgorithmPicked::GBFS:
                graph.RunGBFS();
                break;
            case AlgorithmPicked::RandomMaze:
                random_maze.GenerateRandomMaze();
                break;
            case AlgorithmPicked::RandomBacktrackerMaze:
                random_maze.GenerateRecursiveBacktrackerMaze();
            }
            if (algoritm_picker == AlgorithmPicked::RandomMaze || algoritm_picker == AlgorithmPicked::RandomBacktrackerMaze) {
                obstacles = random_maze.getGrid();
            }
            else {
                obstacles = graph.getVertices();
            }
            timer.restart();
        }

        // Get the path from source to the ending node if the algorithm finished
        if (graph.getFinished()) {
            obstacles = graph.TraceShortestPath();
            algoritm_picker = AlgorithmPicked::None;
            graph.ResetAlgorithm();
        }

        // Reset the algorithm if the maze generation finished
        if (random_maze.getFinished()) {
            algoritm_picker = AlgorithmPicked::None;
        }

        // Render the window
        window.clear(sf::Color(0, 34, 77));
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (sf::Vector2i(i, j) == start) {
                    grid[i][j].setFillColor(sf::Color(38, 186, 30));
                }
                else if (sf::Vector2i(i, j) == end) {
                    grid[i][j].setFillColor(sf::Color::Red);
                }
                else if (obstacles[i][j] == Obstacle) {
                    grid[i][j].setFillColor(sf::Color::Black); // Obstacle
                }
                else if (obstacles[i][j] == Empty) {
                    grid[i][j].setFillColor(sf::Color::White); // Empty
                }
                else if (obstacles[i][j] == Route) {
                    grid[i][j].setFillColor(sf::Color::Yellow);
                }
                else if (obstacles[i][j] == RouteHelper) {
                    grid[i][j].setFillColor(sf::Color::Magenta);
                }
                window.draw(grid[i][j]);
            }
        }
        bfs_button.Draw(window);
        dfs_button.Draw(window);
        reset_button.Draw(window);
        random_maze_button.Draw(window);
        recursive_backtracker_maze_button.Draw(window);
        dijkstra_button.Draw(window);
        a_star_button.Draw(window);
        gbfs_button.Draw(window);
        window.display();
    }
}
