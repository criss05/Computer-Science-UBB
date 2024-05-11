#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <sstream>
#include <random>
#include "UI.h"

using namespace std;

void UI::print_menu(){
    cout << "0. Read the graph from file\n"
        << "1. Random Graph.\n"
        << "2. Get the number of vertices.\n"
        << "3. Display the set of vertices.\n"
        << "4. Find if there is an edge from a vertex to another.\n"
        << "5. Get the in degree for a vertex.\n"
        << "6. Get the out degree for a vertex.\n"
        << "7. Display the outbound edges of a vertex.\n"
        << "8. Display the inbound edges of a vertex.\n"
        << "9. Retrieve the cost of an edge.\n"
        << "10. Modify the cost of an edge.\n"
        << "11. Add edge to graph.\n"
        << "12. Remove edge from graph.\n"
        << "13. Add vertex to graph.\n"
        << "14. Remove vertex from graph.\n"
        << "15. Copy Graph.\n"
        << "16. Print copy Graph.\n"
        << "17. Print the whole graph.\n"
        << "18. Print edges.\n"
        << "19. Save Graph to file.\n"
        << "20. Exit.\n";
}

void UI::start(){
    while (true) {
        try {
            print_menu();
            int option;
            cout << "Please choose an option: ";
            cin >> option;
            switch (option) {
            case 0:
                read_form_file();
                break;
            case 1:
                random_graph();
                break;
            case 2:
                number_vertices();
                break;
            case 3:
                cout << "Vertices: ";
                for (int v : graph.parse_vertices()) {
                    cout << v << " ";
                }
                cout << endl;
                break;
            case 4:
                find_if_edge();
                break;
            case 5:
                in_degree();
                break;
            case 6:
                out_degree();
                break;
            case 7:
                print_outbounds();
                break;
            case 8:
                print_inbounds();
                break;
            case 9:
                give_cost();
                break;
            case 10:
                modify_cost();
                break;
            case 11:
                add_edge();
                break;
            case 12:
                remove_edge();
                break;
            case 13:
                add_vertex();
                break;
            case 14:
                remove_vertex();
                break;
            case 15:
                copy_the_graph();
                break;
            case 16:
                print_graph(copy_graph);
                break;
            case 17:
                print_graph(graph);
                break;
            case 18:
                print_edges();
                break;
            case 19:
                save_to_file();
                break;
            case 20:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid input!" << endl;
                break;
            }
        }
        catch (const exception& error) {
            cerr << error.what() << endl;
        }
    }
}

void UI::read_form_file(){
    graph = Graph();
    string file_name;
    cout << "Give the file name: ";
    cin >> file_name;
    graph.load_graph_from_file(file_name);
}

void UI::random_graph(){
    int n, m;
    cout << "Please give the number of vertices: ";
    cin >> n;
    cout << "Please give the number of edges: ";
    cin >> m;
    graph = Graph(n);
    if (m > n * (n - 1) + n) {
        m = n * (n - 1) + n;
        cout << "Cannot create a graph like this. Number of vertices is: " << m << endl;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n - 1);
    while (m) {
        int vertex1 = dis(gen);
        int vertex2 = dis(gen);
        int vertex_cost = uniform_int_distribution<>(1, 200)(gen);
        if (!graph.is_edge(vertex1, vertex2)) {
            graph.add_edge(vertex1, vertex2, vertex_cost);
            m--;
        }
    }
}

void UI::number_vertices(){
    cout << "Number of vertices is: " << graph.get_number_vertices() << endl;
}

void UI::find_if_edge(){
    int vertex1, vertex2;
    cout << "Please give the first vertex: ";
    cin >> vertex1;
    cout << "Please give the second vertex: ";
    cin >> vertex2;
    if (graph.is_edge(vertex1, vertex2)) {
        cout << "There exists an edge from " << vertex1 << " to " << vertex2 << endl;
    }
    else {
        cout << "There is no an edge from " << vertex1 << " to " << vertex2 << endl;
    }
}

void UI::in_degree(){
    int vertex;
    cout << "Please give the vertex: ";
    cin >> vertex;
    cout << "The in degree of " << vertex << " is: " << graph.in_degree(vertex) << endl;
}

void UI::out_degree(){
    int vertex;
    cout << "Please give the vertex: ";
    cin >> vertex;
    cout << "The out degree of " << vertex << " is: " << graph.out_degree(vertex) << endl;
}

void UI::print_outbounds(){
    int vertex;
    cout << "Please give the vertex: ";
    cin >> vertex;
    cout << "Outbounds: ";
    for (auto& edge : graph.parse_outbound_edges(vertex)) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;
}

void UI::print_inbounds(){
    int vertex;
    cout << "Please give the vertex: ";
    cin >> vertex;
    cout << "Inbounds: ";
    for (auto& edge : graph.parse_inbound_edges(vertex)) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;
}

void UI::give_cost(){
    int vertex1, vertex2;
    cout << "Please give the first vertex: ";
    cin >> vertex1;
    cout << "Please give the second vertex: ";
    cin >> vertex2;
    cout << "The cost of the edge (" << vertex1 << ", " << vertex2 << ") is " << graph.get_cost(vertex1, vertex2) << endl;
}

void UI::modify_cost(){
    int vertex1, vertex2, new_cost;
    cout << "Please give the first vertex: ";
    cin >> vertex1;
    cout << "Please give the second vertex: ";
    cin >> vertex2;
    cout << "Please give the cost: ";
    cin >> new_cost;
    graph.modify_cost(vertex1, vertex2, new_cost);
}

void UI::add_edge(){
    int vertex1, vertex2, cost;
    cout << "Give the first vertex: ";
    cin >> vertex1;
    cout << "Give the second vertex: ";
    cin >> vertex2;
    cout << "Give the cost: ";
    cin >> cost;
    graph.add_edge(vertex1, vertex2, cost);
}

void UI::remove_edge(){
    int vertex1, vertex2;
    cout << "Give the first vertex: ";
    cin >> vertex1;
    cout << "Give the second vertex: ";
    cin >> vertex2;
    graph.remove_edge(vertex1, vertex2);
}

void UI::add_vertex(){
    int vertex;
    cout << "Give a vertex: ";
    cin >> vertex;
    graph.add_vertex(vertex);
}

void UI::remove_vertex(){
    int vertex;
    cout << "Give the vertex: ";
    cin >> vertex;
    graph.remove_vertex(vertex);
}

void UI::copy_the_graph(){

    copy_graph = Graph();
    for (int vertex : graph.parse_vertices()) {
        copy_graph.add_vertex(vertex);
    }
    for (auto& edge : graph.parse_edges()) {
        copy_graph.add_edge(edge.first.first, edge.first.second, edge.second);
    }
    cout << "Graph was copied!" << endl;
}

void UI::print_graph(Graph& graph){
    cout << "Outbound: " << endl;
    for (int vertex1 : graph.parse_vertices()) {
        cout << vertex1 << ": ";
        for (int vertex2 : graph.parse_vertex_out(vertex1)) {
            cout << vertex2 << " ";
        }
        cout << endl;
    }
    cout << "Inbound: " << endl;
    for (int vertex1 : graph.parse_vertices()) {
        cout << vertex1 << ": ";
        for (int vertex2 : graph.parse_vertex_in(vertex1)) {
            cout << vertex2 << " ";
        }
        cout << endl;
    }
}

void UI::print_edges(){
    for (auto& edge : graph.parse_edges()) {
        cout << "(" << edge.first.first << ", " << edge.first.second << ") : " << edge.second << endl;
    }
}

void UI::save_to_file(){
    string file_name;
    cout << "Give the file name: ";
    cin >> file_name;
    graph.save_graph_to_file(file_name);
}
