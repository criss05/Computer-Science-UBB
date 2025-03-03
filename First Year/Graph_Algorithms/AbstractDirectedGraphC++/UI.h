#pragma once
#include "Graph.h"


class UI {
private:
    Graph graph{};
    Graph copy_graph{};

public:
    UI() {};
    void print_menu();
    void start();
    void read_form_file();
    void random_graph();
    void number_vertices();
    void find_if_edge();
    void in_degree();
    void out_degree();
    void print_outbounds();
    void print_inbounds();
    void give_cost();
    void modify_cost();
    void add_edge();
    void remove_edge();
    void add_vertex();
    void remove_vertex();
    void copy_the_graph();
    void print_graph(Graph& graph);
    void print_edges();
    void save_to_file();
};