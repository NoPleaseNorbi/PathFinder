# Main Classes Used in the Program

This is the programming documentation for the PathFinder application written in C++. This documentation can be used alongside the Doxygen documentation, which can be generated using the instructions in the README file.

## Location and Other Important Details

Every file of this program is located inside the PathFinder folder. The program was written in C++ and uses SFML (Simple and Fast Multimedia Library) for window management and graphics rendering. Users have the option to choose between computing algorithms for weighted or unweighted graphs. The application implements various pathfinding algorithms such as Depth-First Search (DFS), Breadth-First Search (BFS), Dijkstra's algorithm, and A* algorithm to cater to different user requirements. Additional information about the program can be found in the MANUAL.pdf attached to the root directory of this project.

## Button Class

The `Button` class is a fundamental component used in the user interface of the application. It provides functionality to create and manage interactive buttons for user interaction. The button class doesn't actually use any functionality, it is just a mere class for a rectangle where we can add text, which will be always in the middle of the rectangle. We also make the ilusion of a real button by changing the color of the button when the user hovers the mouse over the rectangle.

### Constructors

#### `Button()`
- **Description:** Default constructor.
- **Parameters:** None.
- **Initialization:**
  - Initializes the button with default size (100x100 pixels), background color (white), and default text ("button_text").
  
#### `Button(const std::string& button_text, const sf::Vector2f& size, const sf::Color& background_color, const sf::Color& text_color)`
- **Description:** Constructor to initialize button with specified text, size, background color, and text color.
- **Parameters:**
  - `button_text`: The text to display on the button.
  - `size`: The size of the button.
  - `background_color`: The background color of the button.
  - `text_color`: The color of the text on the button.
- **Initialization:**
  - Initializes the button with the provided parameters.

### Member Functions

#### `setFont(const sf::Font& font)`
- **Description:** Set the font for the button's text.
- **Parameters:**
  - `font`: The font to set.

#### `setPosition(const sf::Vector2f& point)`
- **Description:** Set the position of the button.
- **Parameters:**
  - `point`: The position to set.

#### `setBackgroundColor(const sf::Color& color)`
- **Description:** Set the background color of the button.
- **Parameters:**
  - `color`: The color to set.

#### `setHoverColor(const sf::Color& color)`
- **Description:** Set the hover color of the button.
- **Parameters:**
  - `color`: The color to set.

#### `Draw(sf::RenderWindow& window)`
- **Description:** Draw the button to a SFML render window.
- **Parameters:**
  - `window`: The render window to draw to.

#### `MouseOver(const sf::RenderWindow& window) -> bool`
- **Description:** Check if the mouse is over the button. This is important, because than we can change the color of the button based on if the mouse is over the button, using this we can make a simple "real button" effect, so the user feels that the rectangle on which is his/her mouse actually does something, a little bit like in a WinForms application
- **Parameters:**
  - `window`: The render window to check the mouse position against.
- **Returns:** True if the mouse is over the button, otherwise false.

### Private Members
- `button`: The rectangle shape representing the button.
- `text`: The text displayed on the button.
- `_background_color`: The background color of the button.
- `hover_color`: The color of the button when hovered over.


## CellStates enum

This enumeration represents different states of a cell in the PathFinder application, more in depth, these states are used in the grid of the unweighted algorithm page simulation.

### Enum Values

#### `Empty`
- **Description:** Empty cell state, representing an empty space.

#### `Obstacle`
- **Description:** Obstacle cell state, representing an impassable obstacle.

#### `Route`
- **Description:** Route cell state, representing a cell that is part of a route.

#### `RouteHelper`
- **Description:** RouteHelper cell state, representing a cell that is searched through when simulating an algorithm.

## MenuPage Class

This class represents the main menu page of the application. This class uses an enumeration called MenuResult to decide which page to call when the users clicks a button

### Member Functions

#### `Show(sf::RenderWindow& window) -> MenuResult`
- **Description:** Display the main menu page.
- **Parameters:**
  - `window`: The SFML render window to display the menu on.
- **Returns:** The menu result based on user interaction, meaning, based on which button was clicked the user is rerouted to another page of the application  

## RandomMaze Class

This class is responsible for generating random mazes in the application. This class is basically really close to any other path finding simulator class, because this uses the same principle to simulate the maze generation. This class has 2 maze generation algrotihms, the first is just a basic grid generation, which uses just a random function, and with a 33% probability it makes from every empty block an obstacle. The second one is called recursive backtracking algorithm, which is a little bit more sophisticated, and it ensures that it generates an grid, where from every empty cell will be a route to every other empty cell, meaning there will be no isolated empty cells, and also that from the starting node there will be a path to the ending node. The RandomMaze class works like this: The user clicks on the page to generate a maze. We reset everything, and than rather than using while or for loops, I used helper variables, to track where we are at the simulation. After a certain amount of time passed on the page, we call once more the Run function. When the user selects an algorithm to be executed, we at first set up that algorithm, so eveerything works fine, and no undefined behaviour will occur.

### Member Variables

- `rows`: Number of rows in the maze.
- `cols`: Number of columns in the maze.
- `grid`: Grid representing the maze.
- `finished`: Flag indicating if maze generation is finished.
- `current_row_for_random_maze`: Current row during random maze generation.
- `current_col_for_random_maze`: Current column during random maze generation.
- `backtracker_maze_stack`: Stack used for backtracking in maze generation.
- `start`: Start position in the maze.
- `end`: End position in the maze.

### Member Functions

#### `RandomMaze(const int& rows_number, const int& cols_number)`
- **Description:** Constructor to initialize the RandomMaze object with specified dimensions.
- **Parameters:**
  - `rows_number`: The number of rows in the maze.
  - `cols_number`: The number of columns in the maze.

#### `getNeighbors(const int& x, const int& y) -> std::vector<std::pair<int, int>>`
- **Description:** Get neighboring cells of a given cell.
- **Parameters:**
  - `x`: The x-coordinate of the cell.
  - `y`: The y-coordinate of the cell.
- **Returns:** A vector of neighboring cells.

#### `GenerateRecursiveBacktrackerMaze()`
- **Description:** Generate a maze using the recursive backtracker algorithm.

#### `SetUpRecursiveBacktrackerMaze(const sf::Vector2i& starting_point, const sf::Vector2i& ending_point)`
- **Description:** Set up the simulation using the recursive backtracker algorithm.
- **Parameters:**
  - `starting_point`: The starting point of the maze.
  - `ending_point`: The ending point of the maze.

#### `GenerateRandomMaze()`
- **Description:** Generate a random maze, which uses just a basic random function.

#### `SetUpRandomMaze()`
- **Description:** Set up a random maze.

#### `setGrid(const std::vector<std::vector<CellState>>& replacement_grid)`
- **Description:** Set the grid of the maze.
- **Parameters:**
  - `replacement_grid`: The grid to replace the current maze grid with.

#### `getFinished() -> bool`
- **Description:** Check if maze generation is finished.
- **Returns:** True if maze generation is finished, otherwise false.

#### `getGrid() -> std::vector<std::vector<CellState>>`
- **Description:** Get the grid representing the maze.
- **Returns:** The grid representing the maze.

## UnweightedAlgorithmsPage Class

This class is responsible for displaying the unweighted algorithms page in the application. This page works like this: The obstacles are representing the grid, where the algorithms will run. Then the initialization of the buttons happens in the code. I made it so in the enumeration for the cell state I didn't include the starting node and the ending node, so that I don't have to rewrite the checking code a lot times, so there is no state for the these nodes, these are have implicit definitions inside the code. Based on the mouseover we decide which button was pressed, and start an algorithm. Than the checking of dragging is implemented in the code. If the user holds the S key, than using the mouse it can be repositioned. Also using the E key, the ending node can be repoistioned. I didn't need error checking for this, because the user cannot get out of the bounds of the grid. After the algortihms finished, we write to the page the grid. This is inside a while loop which ensures that the updates are in real-time

### Member Variables

- `obstacles`: Grid representing obstacles in the maze.

### Member Functions

#### `ResetGridAfterAlgorithm()`
- **Description:** Reset the grid after running an algorithm, meaning it resets the magenta colored cells to white.

#### `ResetGrid()`
- **Description:** Reset the grid to initial state.

#### `Display(sf::RenderWindow& window)`
- **Description:** Display the unweighted algorithms page.
- **Parameters:**
  - `window`: The SFML render window to display the page on.

## UnweightedGraph Class

This class represents an unweighted graph and implements 5 algorithms for it. This class also uses the principle of after a certain time the algorithm runs one step, so in this way we can get the "simulation" feel of the application. This class also uses helper data structures which have to be initialized and stored inside the class for the simulation to work perfectly without interruption. The priority queues use my custom function struct, which is used because I am using sf::Vector2i data structure inside these queues.

### Member Variables

- `finished`: Flag indicating if an algorithm has finished.
- `start`: Start point of the graph.
- `end`: End point of the graph.
- `column_size`: Number of columns in the grid.
- `row_size`: Number of rows in the grid.
- `vertices`: Grid representing the vertices of the graph.
- `distances`: Matrix of distances between vertices.
- `visited`: Matrix indicating visited vertices.
- `bfs_queue`: Queue for Breadth First Search.
- `dfs_stack`: Stack for Depth First Search.
- `dijkstra_priority_queue`: Priority queue for Dijkstra's algorithm.
- `astar_priority_queue`: Priority queue for A* algorithm.
- `gbfs_priority_queue`: Priority queue for Greedy Best-First Search algorithm.

### Member Functions

#### `UnweightedGraph(const std::vector<std::vector<CellState>>& vertices_of_the_graph, const sf::Vector2i& starting_point, const sf::Vector2i& ending_point)`
- **Description:** Constructor to initialize the unweighted graph with vertices, starting point, and ending point.

#### `RunBFS()`
- **Description:** Runs the Breadth First Search algorithm after the setup. This is called after the interval defined in the main page ellapsed.

#### `RunDFS()`
- **Description:** Runs the Depth First Search algorithm after the setup. This is called after the interval defined in the main page ellapsed.

#### `RunDijkstra()`
- **Description:** Runs the Dijkstra's algorithm after the setup. This is called after the interval defined in the main page ellapsed.

#### `RunAStar()`
- **Description:** Runs the A* algorithm after the setup. This is called after the interval defined in the main page ellapsed.

#### `RunGBFS()`
- **Description:** Runs the Greedy Best-First Search algorithm after the setup. This is called after the interval defined in the main page ellapsed.

#### `SetUpBFS()`
- **Description:** When the user wants to simulate this algorithm, first set up Breadth First Search algorithm.

#### `SetUpDFS()`
- **Description:** When the user wants to simulate this algorithm, first set up Depth First Search algorithm.

#### `SetUpDijkstra()`
- **Description:** When the user wants to simulate this algorithm, first set up Dijkstra's algorithm.

#### `SetUpAStar()`
- **Description:** When the user wants to simulate this algorithm, first set up A* algorithm.

#### `SetUpGBFS()`
- **Description:** When the user wants to simulate this algorithm, first set up Greedy Best-First Search algorithm.

#### `ResetAlgorithm()`
- **Description:** Resets the finished flag, and also the starting end ending nodes, resets the distances and vertices vectors.

#### `TraceShortestPath() -> std::vector<std::vector<CellState>>`
- **Description:** Trace the path from the starting node to the end based on chaning the colors of the cells in the path.

#### `CheckCellValidity(const int& row, const int& col) -> bool`
- **Description:** Check if a cell is available next to the given cell.
- **Parameters:**
  - `row`: The row of the cell.
  - `col`: The column of the cell.
- **Returns:** True if the cell is valid, otherwise false.

#### `getVertices() -> std::vector<std::vector<CellState>>`
- **Description:** Get the grid representing the vertices of the graph.
- **Returns:** The grid representing the vertices.

#### `getFinished() -> bool`
- **Description:** Check if an algorithm has finished.
- **Returns:** True if the algorithm has finished, otherwise false.

#### `setStart(const sf::Vector2i& starting_point)`
- **Description:** Set the starting point of the graph.
- **Parameters:**
  - `starting_point`: The starting point to set.

#### `setEnd(const sf::Vector2i& ending_point)`
- **Description:** Set the ending point of the graph.
- **Parameters:**
  - `ending_point`: The ending point to set.

#### `setObstacles(const std::vector<std::vector<CellState>>& obstacles)`
- **Description:** Set the obstacles on the graph.
- **Parameters:**
  - `obstacles`: The obstacles to set.

## WeightedAlgorithmsPage Class

This class is responsible for displaying the weighted algorithms page in the application. Users can interact with this page to visualize and run various weighted graph algorithms. The page consists of a frame, where the user can draw circles, which represent the vertices of a graph. These vertices are numbered from 0, and these numbers are automatically added to the vertex. The user can add edges, if they click on a button, this button will turn cyan, and than clicking another button will trigger another page, where the user can define the weight of the edge. Buttons are provided for selecting and running different algorithms on the graph. The user can also "deselect" a vertex if they selected it, becuase than they are unable to add a vertex, just make an edge between two vertices. The user can deselect a vertex selected using the right mouse button. The code structure is close to the `UnweightedAlgorithmsPage`. We define the buttons and custom components such as the graph frame, which is a frame to limit the user to make vertices only inside the frame. After that we always check if a vertex is selected, than we wait for another one to be selected, if not, than we potentially wait for a right mouse click, to reset the selecting of a vertex. We always make calulcations in this page, so we calculate the positions of the vertex, the text, the triangle which show the direction of the edge and so on.

### Member Functions

#### `Display(sf::RenderWindow& window)`
- **Description:** Displays the weighted algorithms page.
- **Parameters:**
  - `window`: The SFML render window to display the page on.

### Helper Functions

#### `getEdgeWeight(sf::RenderWindow& window) -> int`
- **Description:** Prompts the user to enter the weight of an edge. This is another SFML page.
- **Parameters:**
  - `window`: The SFML render window to display the input dialog.
- **Returns:** The weight of the edge entered by the user.

## WeightedGraph Class

This class represents a weighted graph and provides functionalities to run various algorithms on it. The algorithms are implemented to execute in steps, providing a simulation feel to the application. The class utilizes helper data structures internally to help the simulation feel of the algorithms. Priority queues are employed with a custom function struct to handle vertex comparisons, which is need because I used `sf::Vector2i` data structure. The graphics are already set, so we don't need to worry about the positioning, angle, length or any property of any of the graphics used in the graph.

### Member Variables

- `adjacency_list`: An unordered map representing the adjacency list of the graph.
- `vertices`: Vector of graphical representations of vertices in the graph.
- `vertex_numbers`: Vector of texts representing vertex numbers.
- `edges`: Vector of graphical representations of edges in the graph.
- `edge_weights`: Vector of texts representing edge weights.
- `edge_going_to_signaling_triangles`: Vector of graphical representations of triangles indicating edge directions.
- `visited`: Vector indicating visited nodes during algorithm execution.
- `distances`: Vector storing distances of nodes from each other during algorithm execution.
- `parents`: Vector storing parents of each node during algorithm execution.
- `finished`: Flag indicating if an algorithm has finished.
- `bellman_curr_vertex`: Current vertex during Bellman-Ford algorithm execution.
- `bellman_curr_edge`: Current edge during Bellman-Ford algorithm execution.
- `bfs_queue`: Queue for Breadth First Search.
- `dfs_stack`: Stack for Depth First Search.
- `dijkstra_priority_queue`: Priority queue for Dijkstra's algorithm.

### Member Functions

#### `WeightedGraph()`
- **Description:** Default constructor to initialize WeightedGraph object.

#### `AddEdge(const int& from, const int& to, const int& weight, const sf::VertexArray& edge, const sf::Text& weight_graphics)`
- **Description:** Add an edge to the graph.
- **Parameters:**
  - `from`: The source vertex of the edge.
  - `to`: The destination vertex of the edge.
  - `weight`: The weight of the edge.
  - `edge`: Graphics representing the edge.
  - `weight_graphics`: Text graphics representing the weight of the edge.

#### `getAdjacencyList(const int& vertex) -> std::vector<std::pair<int, int>>`
- **Description:** Get the adjacency list of a vertex.
- **Parameters:**
  - `vertex`: The vertex whose adjacency list is to be retrieved.
- **Returns:** The adjacency list of the vertex.

#### `Clear()`
- **Description:** Clear the vectors containing graph elements.

#### `AddVertex(const sf::CircleShape& vertex, const sf::Text& vertex_number)`
- **Description:** Add a vertex to the graph.
- **Parameters:**
  - `vertex`: Graphics representing the vertex.
  - `vertex_number`: Text representing the number of the vertex.

#### `ChangeVertexColor(const sf::Color& color, const int& index)`
- **Description:** Change color of a vertex.
- **Parameters:**
  - `color`: The color to set.
  - `index`: The index of the vertex.

#### `getVertices() -> std::vector<sf::CircleShape>`
- **Description:** Get the vertices of the graph.
- **Returns:** Vector of vertices.

#### `Draw(sf::RenderWindow& window)`
- **Description:** Draw the graph on a given render window.
- **Parameters:**
  - `window`: The render window to draw the graph on.

#### `AddTriangle(const sf::ConvexShape& triangle)`
- **Description:** Add a signaling triangle to indicate direction of an edge.
- **Parameters:**
  - `triangle`: Graphics representing the triangle.

#### `RunDijkstra()`
- **Description:** Run Dijkstra's algorithm.

#### `RunBFS()`
- **Description:** Run Breadth First Search algorithm.

#### `RunDFS()`
- **Description:** Run Depth First Search algorithm.

#### `RunBellmanFord()`
- **Description:** Run Bellman-Ford algorithm.

#### `SetUpDijkstra()`
- **Description:** Set up Dijkstra's algorithm.

#### `SetUpBFS()`
- **Description:** Set up Breadth First Search algorithm.

#### `SetUpDFS()`
- **Description:** Set up Depth First Search algorithm.

#### `SetUpBellmanFord()`
- **Description:** Set up Bellman-Ford algorithm.

#### `TracePath()`
- **Description:** Trace the shortest path found by the algorithm.

#### `Reset()`
- **Description:** Reset the graph and algorithm states.

#### `getFinished() -> bool`
- **Description:** Check if an algorithm has finished.
- **Returns:** True if the algorithm has finished, otherwise false.


## External Dependencies
- SFML