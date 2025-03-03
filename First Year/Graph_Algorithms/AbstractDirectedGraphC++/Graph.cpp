#include "Graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <sstream>


Graph::Graph(int n){
	length = n;
	for (int i = 0; i < length; ++i) {
		din[i] = {};
		dout[i] = {};
	}
}

void Graph::add_vertex(int vertex){
	if (is_vertex(vertex)) {
		throw invalid_argument("Vertex already exists!");
	}
	din[vertex] = {};
	dout[vertex] = {};
	++length;
}

bool Graph::is_vertex(int vertex){
	return (din.find(vertex) != din.end()) && (dout.find(vertex) != dout.end());
}

void Graph::add_edge(int vertex1, int vertex2, int cost){
	if (is_edge(vertex1, vertex2)) {
		throw invalid_argument("Edge already exists!");
	}
	din[vertex2].push_back(vertex1);
	dout[vertex1].push_back(vertex2);
	dcost[make_pair(vertex1, vertex2)] = cost;
}

bool Graph::is_edge(int vertex1, int vertex2){
	if (!is_vertex(vertex1) || !is_vertex(vertex2)) {
		throw invalid_argument("One of the vertices does not exist!");
	}
	for (int v : dout[vertex1]) {
		if (v == vertex2) {
			return true;
		}
	}
	return false;
}

void Graph::remove_vertex(int vertex){
	if (!is_vertex(vertex)) {
		throw invalid_argument("Vertex does not exist!");
	}
	for (int vertex2 : parse_vertex_out(vertex)) {
		auto it = dcost.find(make_pair(vertex, vertex2));
		if (it != dcost.end()) {
			dcost.erase(it);
		}
		din[vertex2].erase(remove(din[vertex2].begin(), din[vertex2].end(), vertex), din[vertex2].end());
	}
	for (int vertex1 : parse_vertex_in(vertex)) {
		auto it = dcost.find(make_pair(vertex1, vertex));
		if (it != dcost.end()) {
			dcost.erase(it);
		}
		dout[vertex1].erase(remove(dout[vertex1].begin(), dout[vertex1].end(), vertex), dout[vertex1].end());
	}
	din.erase(vertex);
	dout.erase(vertex);
	--length;
}

void Graph::remove_edge(int vertex1, int vertex2){
	if (!is_edge(vertex1, vertex2)) {
		throw invalid_argument("Edge does not exist!");
	}
	dout[vertex1].erase(remove(dout[vertex1].begin(), dout[vertex1].end(), vertex2), dout[vertex1].end());
	din[vertex2].erase(remove(din[vertex2].begin(), din[vertex2].end(), vertex1), din[vertex2].end());
	dcost.erase(make_pair(vertex1, vertex2));
}

int Graph::get_number_vertices(){
	return length;
}

int Graph::get_number_edges(){
	return length;
}

int Graph::get_cost(int vertex1, int vertex2){
	if (!is_edge(vertex1, vertex2)) {
		throw invalid_argument("Edge does not exist!");
	}
	return dcost[make_pair(vertex1, vertex2)];
}

void Graph::modify_cost(int vertex1, int vertex2, int new_cost){
	if (!is_edge(vertex1, vertex2)) {
		throw invalid_argument("Edge does not exist!");
	}
	dcost[make_pair(vertex1, vertex2)] = new_cost;
}

void Graph::load_graph_from_file(const string& file_name){
	ifstream file(file_name);
	if (!file.is_open()) {
		throw runtime_error("File not found!");
	}

	string line;
	getline(file, line);
	istringstream iss(line);
	int vertex1, vertex2, cost;
	int n, m;
	if (!(iss >> vertex1 >> vertex2 >> cost)) { // Two vertices on the first line
		iss >> n >> m;
		while (getline(file, line)) {
			istringstream iss(line);
			iss >> vertex1 >> vertex2 >> cost;
			if (!is_vertex(vertex1))
				add_vertex(vertex1);
			if (!is_vertex(vertex2))
				add_vertex(vertex2);
			add_edge(vertex1, vertex2, cost);
		}
		for (int vertex = 0; vertex < this->length; vertex++)
			if (is_vertex(vertex) == false)
				add_vertex(vertex);
	}
	else { // Three values on the first line
		iss >> vertex1 >> vertex2 >> cost;
		cout << vertex1 << " " << vertex2 << " " << cost;
		if (vertex2 == -1) {
			add_vertex(vertex1);
		}
		else {
			if (!is_vertex(vertex1))
				add_vertex(vertex1);
			if (!is_vertex(vertex2))
				add_vertex(vertex2);
			add_edge(vertex1, vertex2, cost);
		}
		while (getline(file, line)) {
			istringstream iss(line);
			iss >> vertex1 >> vertex2 >> cost;
			cout << vertex1 << " " << vertex2 << " " << cost;
			if (vertex2 == -1) {
				add_vertex(vertex1);
			}
			else {
				if (!is_vertex(vertex1))
					add_vertex(vertex1);
				if (!is_vertex(vertex2))
					add_vertex(vertex2);
				add_edge(vertex1, vertex2, cost);
			}
		}
	}

	file.close();
}

void Graph::save_graph_to_file(const string& file_name){
	ofstream file(file_name);
	if (!file.is_open()) {
		throw runtime_error("Unable to open file for writing!");
	}

	bool found = false;
	for (auto& i : dout)
		if (i.second.empty() && din[i.first].empty())
			found = true;

	if (found) {
		for (auto& i : dout) {
			if (i.second.empty() && din[i.first].empty()) {
				file << i.first << " -1 -1\n";
			}
			else {
				for (int vertex2 : i.second) {
					int cost = dcost[{i.first, vertex2}];
					file << i.first << " " << vertex2 << " " << cost << "\n";
				}
			}
		}
	}
	else {
		file << length << " " << get_number_edges() << "\n";
		for (auto& i : dcost) {
			int vertex1 = i.first.first;
			int vertex2 = i.first.second;
			file << vertex1 << " " << vertex2 << " " << i.second << "\n";
		}
	}

	file.close();
}

vector<int> Graph::parse_vertices(){
	 vector<int> vertices;
        for (auto& entry : din) {
            vertices.push_back(entry.first);
        }
        return vertices;
}

vector<int> Graph::parse_vertex_in(int vertex){
	if (!is_vertex(vertex)) {
		throw invalid_argument("Vertex does not exist!");
	}
	return din[vertex];
}

vector<int> Graph::parse_vertex_out(int vertex){
	if (!is_vertex(vertex)) {
		throw invalid_argument("Vertex does not exist!");
	}
	return dout[vertex];
}

int Graph::in_degree(int vertex){
	if (!is_vertex(vertex)) {
		throw invalid_argument("Vertex does not exist!");
	}
	return din[vertex].size();
}

int Graph::out_degree(int vertex){
	if (!is_vertex(vertex)) {
		throw invalid_argument("Vertex does not exist!");
	}
	return dout[vertex].size();
}

vector<pair<int, int>> Graph::parse_outbound_edges(int vertex1){
	if (!is_vertex(vertex1)) {
		throw invalid_argument("Vertex does not exist!");
	}
	vector<pair<int, int>> edges;
	for (int vertex2 : parse_vertex_out(vertex1)) {
		edges.push_back(make_pair(vertex1, vertex2));
	}
	return edges;
}

vector<pair<int, int>> Graph::parse_inbound_edges(int vertex2){
	if (!is_vertex(vertex2)) {
		throw invalid_argument("Vertex does not exist!");
	}
	vector<pair<int, int>> edges;
	for (int vertex1 : parse_vertex_in(vertex2)) {
		edges.push_back(make_pair(vertex1, vertex2));
	}
	return edges;
}

vector<pair<pair<int, int>, int>> Graph::parse_edges(){
	vector<pair<pair<int, int>, int>> edges;
	for (auto& entry : dcost) {
		edges.push_back(make_pair(entry.first, entry.second));
	}
	return edges;
}
