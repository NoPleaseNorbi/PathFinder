#include "../headers/WeightedGraph.hpp"

#include <iostream>
#include <climits>

WeightedGraph::WeightedGraph() {
	finished = false;
	bellman_curr_edge = 0;
	bellman_curr_vertex = 0;
}

void WeightedGraph::AddEdge(const int& from, const int& to, const int& weight, const sf::VertexArray& edge, const sf::Text& weight_graphics) {
	adjacency_list[from].push_back({ to, weight });
	edges.push_back(edge);
	edge_weights.push_back(weight_graphics);
}

std::vector<std::pair<int, int>> WeightedGraph::getAdjacencyList(const int& vertex) {
	return adjacency_list[vertex];
}

void WeightedGraph::Clear() {
	finished = false;
	distances.clear();
	parents.clear();
	adjacency_list.clear();
	vertices.clear();
	vertex_numbers.clear();
	edges.clear();
	edge_weights.clear();
	edge_going_to_signaling_triangles.clear();
}

void WeightedGraph::AddVertex(const sf::CircleShape& vertex, const sf::Text& vertex_number) {
	vertices.push_back(vertex);
	vertex_numbers.push_back(vertex_number);
}

void WeightedGraph::ChangeVertexColor(const sf::Color& color, const int& index) {
	vertices[index].setFillColor(color);
}

std::vector<sf::CircleShape> WeightedGraph::getVertices() {
	return vertices;
}

void WeightedGraph::Draw(sf::RenderWindow& window) {
	for (size_t i = 0; i < edges.size(); ++i) {
		window.draw(edges[i]);
		window.draw(edge_weights[i]);
	}
	for (const auto& vertex : vertices) {
		window.draw(vertex);
	}
	for (const auto& vertex_number : vertex_numbers) {
		window.draw(vertex_number);
	}
	for (const auto& triangle : edge_going_to_signaling_triangles) {
		window.draw(triangle);
	}
}

void WeightedGraph::AddTriangle(const sf::ConvexShape& triangle) {
	edge_going_to_signaling_triangles.push_back(triangle);
}

void WeightedGraph::RunDijkstra() {
	if (finished) {
		return;
	}
	if (!dijkstra_priority_queue.empty()) {
		int distance = dijkstra_priority_queue.top().first;
		int vertex = dijkstra_priority_queue.top().second;
		vertices[vertex].setFillColor(sf::Color::Magenta);
		dijkstra_priority_queue.pop();

		if (distance > distances[vertex]) return;

		for (auto edge : adjacency_list[vertex]) {
			int next_vertex = edge.first;
			int edge_weight = edge.second;

			if (distances[vertex] + edge_weight < distances[next_vertex]) {
				distances[next_vertex] = distances[vertex] + edge_weight;
				parents[next_vertex] = vertex;
				dijkstra_priority_queue.push({ distances[next_vertex], next_vertex });
			}
		}
	}
	else {
		finished = true;
	}
}

bool WeightedGraph::getFinished() {
	return finished;
}

void WeightedGraph::SetUpDijkstra() {
	Reset();
	while (!dijkstra_priority_queue.empty()) {
		dijkstra_priority_queue.pop();
	}
	dijkstra_priority_queue.push(std::make_pair(0, 0));
}

void WeightedGraph::RunBFS() {
	if (finished) {
		return;
	}
	if (!bfs_queue.empty()) {
		int vertex = bfs_queue.front();
		bfs_queue.pop();
		vertices[vertex].setFillColor(sf::Color::Magenta);

		for (auto edge : adjacency_list[vertex]) {
			int next_vertex = edge.first;
			if (!visited[next_vertex]) {
				visited[next_vertex] = true;
				bfs_queue.push(next_vertex);
				parents[next_vertex] = vertex;
			}
		}
	}
	else {
		finished = true;
	}
}

void WeightedGraph::SetUpBFS() {
	Reset();
	while (!bfs_queue.empty()) {
		bfs_queue.pop();
	}
	bfs_queue.push(0);
}

void WeightedGraph::RunDFS() {
	if (finished) {
		return;
	}
	if (!dfs_stack.empty()) {
		int vertex = dfs_stack.top();
		dfs_stack.pop();
		vertices[vertex].setFillColor(sf::Color::Magenta);

		for (auto edge : adjacency_list[vertex]) {
			int next_vertex = edge.first;
			if (!visited[next_vertex]) {
				visited[next_vertex] = true;
				dfs_stack.push(next_vertex);
				parents[next_vertex] = vertex;
			}
		}
	}
	else {
		finished = true;
	}
}

void WeightedGraph::SetUpDFS() {
	Reset();
	while (!dfs_stack.empty()) {
		dfs_stack.pop();
	}
	dfs_stack.push(0);
	
}

void WeightedGraph::RunBellmanFord() {
	if (finished) {
		return;
	}
	if (bellman_curr_vertex < vertices.size()) {
		if (bellman_curr_edge < adjacency_list[bellman_curr_vertex].size()) {
			int u = bellman_curr_vertex;
			int v = adjacency_list[u][bellman_curr_edge].first;
			int weight = adjacency_list[u][bellman_curr_edge].second;
			if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
				distances[v] = distances[u] + weight;
				parents[v] = u;
				vertices[v].setFillColor(sf::Color::Magenta);
			}

			bellman_curr_edge++;
		}
		else {
			
			bellman_curr_vertex++;
			bellman_curr_edge = 0;
		}
	}
	else {
		for (const auto& item : adjacency_list) {
			int u = item.first;
			for (const auto& edge : item.second) {
				int v = edge.first;
				int weight = edge.second;
				if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
					std::cout << "Graph contains negative weight cycle" << std::endl;
					vertices[v].setFillColor(sf::Color::Red);
					finished = true;
					return;
				}
			}
		}

		finished = true;
	}
}

void WeightedGraph::SetUpBellmanFord() {
	Reset();
	bellman_curr_vertex = 0;
	bellman_curr_edge = 0;
}

void WeightedGraph::TracePath() {
	finished = false;
	int destination = vertices.size() - 1;

	if (destination == -1) {
		std::cerr << "The graph was empty" << std::endl;
		return;
	}
	if (parents[destination] == -1) {
		std::cout << "No path from source to destination exists." << std::endl;
		return;
	}

	for (int v = destination; v != -1; v = parents[v]) {
		vertices[v].setFillColor(sf::Color::Yellow);
	}
	vertices[0].setFillColor(sf::Color::Green);
	vertices[vertices.size() - 1].setFillColor(sf::Color::Red);
}

void WeightedGraph::Reset() {
	finished = false;
	for (size_t i = 0; i < vertices.size(); ++i) {
		vertices[i].setFillColor(sf::Color::White);
	}
	if (vertices.size() == 0) {
		finished = true;
		return;
	}
	visited.clear();
	parents.clear();
	parents.resize(vertices.size(), -1);
	distances.resize(vertices.size(), INT16_MAX);
	distances[0] = 0;
	visited.resize(vertices.size(), false);
	visited[0] = true;
}