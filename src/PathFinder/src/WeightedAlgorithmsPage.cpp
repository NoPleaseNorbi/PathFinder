#include "../headers/WeightedAlgorithmsPage.hpp"
#include "../headers/WeightedGraph.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define PI 3.14159265

enum class AlgorithmPicked { // Enum for the algorithms, to see which one is picked
    None,
    Dijkstra,
    BFS,
    Bellman_Ford,
    DFS
};

float CalculateAngle(const sf::Vector2f& start, const sf::Vector2f& end) {
    return atan2(end.y - start.y, end.x - start.x) * 180 / PI; // Calculation for the triangle angle
}

// Page for getting the edge weight
int WeightedPage::getEdgeWeight(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile(PROJECT_SOURCE_DIR + std::string("/monoregular.ttf"))) {
        std::cerr << "Font not found" << std::endl;
        return 0;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString("Enter edge weight (integer) and press Enter:");

    sf::Text input_text;
    input_text.setFont(font);
    input_text.setCharacterSize(24);
    input_text.setFillColor(sf::Color::White);

    input_text.setPosition(text.getPosition().x + text.getLocalBounds().width + 10, text.getPosition().y);
    
    std::string input_string;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !input_string.empty()) {
                    input_string.pop_back();
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    try {
                        return std::stoi(input_string);
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Invalid input. Please enter an integer." << std::endl;
                    }
                }
                else if (event.text.unicode < 128) {
                    input_string += event.text.unicode;
                }
                input_text.setString(input_string);
            }
        }

        window.clear(sf::Color(0, 34, 77));
        window.draw(text);
        window.draw(input_text);
        window.display();
    }

    return 0;
}

void WeightedPage::Display(sf::RenderWindow& window) {
    constexpr int vertex_size = 30;

    AlgorithmPicked algorithm_picker;
    algorithm_picker = AlgorithmPicked::None;

    sf::Clock timer;
    
    int selected_vertex = -1; // Helper variable to store the selected vertex from which are the edge to be drawn
    const float step_interval = 1.0f; // The step interval for the timer

    WeightedGraph graph;

    // The frame of the graphs where the user can draw circles
    sf::RectangleShape graph_frame;
    graph_frame.setSize(sf::Vector2f(window.getSize().x - 20, (window.getSize().y / 2) - 20));
    graph_frame.setFillColor(sf::Color::White);
    graph_frame.setPosition(10, 10);
    graph_frame.setOutlineThickness(2);
    graph_frame.setOutlineColor(sf::Color::Black);
	
    
    sf::Font font;
	if (!font.loadFromFile(PROJECT_SOURCE_DIR + std::string("/monoregular.ttf"))) {
		std::cerr << "Failed to load font" << std::endl;
		return;
	}

    // Set up for the buttons
    Button reset_button("Reset graph", { 300, 100 }, sf::Color(255, 32, 78), sf::Color::White);
    reset_button.setFont(font);
    reset_button.setPosition({ 350, 800 });
    reset_button.setHoverColor(sf::Color(158, 28, 33));

    Button dijkstra_button("Dijkstra", { 300, 80 }, sf::Color(255, 32, 78), sf::Color::White);
    dijkstra_button.setHoverColor(sf::Color(160, 21, 62));
    dijkstra_button.setFont(font);
    dijkstra_button.setPosition({ 150, 550 });

    Button bfs_button("BFS", { 300, 80 }, sf::Color(255, 32, 78), sf::Color::White);
    bfs_button.setHoverColor(sf::Color(160, 21, 62));
    bfs_button.setFont(font);
    bfs_button.setPosition({ 550, 550 });

    Button dfs_button("DFS", { 300, 80 }, sf::Color(255, 32, 78), sf::Color::White);
    dfs_button.setHoverColor(sf::Color(160, 21, 62));
    dfs_button.setFont(font);
    dfs_button.setPosition({ 150, 670 });
    
    Button bellman_ford_button("Bellman-Ford", { 300, 80 }, sf::Color(255, 32, 78), sf::Color::White);
    bellman_ford_button.setHoverColor(sf::Color(160, 21, 62));
    bellman_ford_button.setFont(font);
    bellman_ford_button.setPosition({ 550, 670 });


    while (window.isOpen()) {
        sf::Time elapsed = timer.getElapsedTime();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (reset_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    graph.Clear();
                    selected_vertex = -1;
                    algorithm_picker = AlgorithmPicked::None;
                }
            }
            else if (dijkstra_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    graph.SetUpDijkstra();
                    algorithm_picker = AlgorithmPicked::Dijkstra;
                }
            }
            else if (bfs_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    graph.SetUpBFS();
                    algorithm_picker = AlgorithmPicked::BFS;
                }
            }
            else if (dfs_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    graph.SetUpDFS();
                    algorithm_picker = AlgorithmPicked::DFS;
                }
            }
            else if (bellman_ford_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    graph.SetUpBellmanFord();
                    algorithm_picker = AlgorithmPicked::Bellman_Ford;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    bool vertex_clicked = false;
                    for (int i = 0; i < graph.getVertices().size(); ++i) {
                        if (graph.getVertices()[i].getGlobalBounds().contains(position.x, position.y)) {
                            graph.Reset();
                            vertex_clicked = true;
                            if (selected_vertex == -1) {
                                // If currently we don't have a selected vertex
                                graph.ChangeVertexColor(sf::Color::Cyan, i);
                                selected_vertex = i;
                            }
                            else {
                                // Else make an edge between the selected vertices
                                int weight = getEdgeWeight(window);
                                sf::VertexArray edge(sf::LinesStrip, 3);
                                edge[0].position = graph.getVertices()[selected_vertex].getPosition() + sf::Vector2f(vertex_size, vertex_size);
                                edge[1].position = graph.getVertices()[i].getPosition() + sf::Vector2f(vertex_size, vertex_size);
                                edge[2].position = graph.getVertices()[selected_vertex].getPosition() + sf::Vector2f(vertex_size, vertex_size);
                                edge[0].color = sf::Color::Black;
                                edge[1].color = sf::Color::Black;
                                edge[2].color = sf::Color::Black;

                                float angle = CalculateAngle(graph.getVertices()[selected_vertex].getPosition() + sf::Vector2f(30, 30), graph.getVertices()[i].getPosition() + sf::Vector2f(30, 30));

                                // The edge weight
                                sf::Text weight_text;
                                weight_text.setFont(font);
                                weight_text.setCharacterSize(20);
                                weight_text.setFillColor(sf::Color::Black);
                                weight_text.setString(std::to_string(weight)); 
                                weight_text.setPosition((graph.getVertices()[selected_vertex].getPosition() + graph.getVertices()[i].getPosition()) / 2.f);

                                // The triangle indicating the direction of the edge
                                sf::ConvexShape triangle(3);
                                triangle.setPoint(0, sf::Vector2f(-5, -5));
                                triangle.setPoint(1, sf::Vector2f(-5, 5));
                                triangle.setPoint(2, sf::Vector2f(10, 0));
                                triangle.setFillColor(sf::Color::Black);
                                triangle.setRotation(angle);


                                // The position of the direction triangle
                                float triangle_distance_before_vertex = -40.0f;
                                sf::Vector2f triangle_position = graph.getVertices()[i].getPosition() + sf::Vector2f(vertex_size, vertex_size);
                                triangle_position.x += triangle_distance_before_vertex * cos(angle * PI / 180);
                                triangle_position.y += triangle_distance_before_vertex * sin(angle * PI / 180);
                                triangle.setPosition(triangle_position);

                                graph.AddTriangle(triangle);

                                graph.ChangeVertexColor(sf::Color::White, selected_vertex);

                                graph.AddEdge(selected_vertex, i, weight, edge, weight_text);

                                selected_vertex = -1;
                            }
                            break;
                        }
                    }
                    if (!vertex_clicked && selected_vertex == -1 && graph_frame.getGlobalBounds().contains(position.x, position.y)) {
                        graph.Reset();
                        
                        // Draw a vertex inside the graph frame
                        sf::CircleShape vertex(vertex_size);
                        vertex.setFillColor(sf::Color::White);
                        vertex.setOutlineThickness(3);
                        vertex.setOutlineColor(sf::Color::Black);
                        vertex.setPosition(position.x - vertex_size, position.y - vertex_size);

                        // Draw the vertex number
                        sf::Text vertex_number;
                        vertex_number.setFont(font);
                        vertex_number.setString(std::to_string(graph.getVertices().size()));
                        vertex_number.setCharacterSize(40);
                        vertex_number.setFillColor(sf::Color::Black);
                        vertex_number.setPosition(vertex.getPosition().x + vertex.getLocalBounds().width / 2.f - vertex_size / 2, vertex.getPosition().y + vertex.getLocalBounds().height / 2.f - vertex_size);

                        graph.AddVertex(vertex, vertex_number);
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    // Reset the vertex selected
                    if (selected_vertex != -1) {
                        graph.ChangeVertexColor(sf::Color::White, selected_vertex);
                    }
                    selected_vertex = -1;
                }
            }
        }

        // Based on what algorithm is picked start a simulation
        if (elapsed.asSeconds() >= step_interval && algorithm_picker != AlgorithmPicked::None) {
            switch (algorithm_picker) {
            case AlgorithmPicked::Dijkstra:
                graph.RunDijkstra();
                break;
            case AlgorithmPicked::BFS:
                graph.RunBFS();
                break;
            case AlgorithmPicked::Bellman_Ford:
                graph.RunBellmanFord();
                break;
            case AlgorithmPicked::DFS:
                graph.RunDFS();
                break;
            }
            timer.restart();
        }

        // If the simulation finished show the path from the source to the ending node
        if (graph.getFinished() && (algorithm_picker != AlgorithmPicked::None)) {
            graph.TracePath();
            algorithm_picker = AlgorithmPicked::None;
        }

        // Display the components to the page
        window.clear(sf::Color(0, 34, 77));
        window.draw(graph_frame);
        dijkstra_button.Draw(window);
        bfs_button.Draw(window);
        dfs_button.Draw(window);
        bellman_ford_button.Draw(window);
        graph.Draw(window);
        reset_button.Draw(window);
        window.display();
    }

}
