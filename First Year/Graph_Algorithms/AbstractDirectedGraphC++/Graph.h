#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;


class Graph {
private:
    int length;
    map<int, vector<int>> din;
    map<int, vector<int>> dout;
    map<pair<int, int>, int> dcost;

public:
    Graph(int n = 0);
    void add_vertex(int vertex);
    bool is_vertex(int vertex);
    void add_edge(int vertex1, int vertex2, int cost);
    bool is_edge(int vertex1, int vertex2);
    void remove_vertex(int vertex);
    void remove_edge(int vertex1, int vertex2);
    int get_number_vertices();
    int get_number_edges();
    int get_cost(int vertex1, int vertex2);
    void modify_cost(int vertex1, int vertex2, int new_cost);
    void load_graph_from_file(const string& file_name);
    void save_graph_to_file(const string& file_name);
    vector<int> parse_vertices();
    vector<int> parse_vertex_in(int vertex);
    vector<int> parse_vertex_out(int vertex);
    int in_degree(int vertex);
    int out_degree(int vertex);
    vector<pair<int, int>> parse_outbound_edges(int vertex1);
    vector<pair<int, int>> parse_inbound_edges(int vertex2);
    vector<pair<pair<int, int>, int>> parse_edges();
};
