//
// Created by abdo on 2/15/2023.
//

#ifndef CENTRALITY_GRAPH_H
#define CENTRALITY_GRAPH_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef struct
{
    string id;
    double x;
    double y;
    int betweenness;

}Node;

typedef struct
{
    double length;
}Edge;

class Graph
{
public:
    Graph();
    virtual ~Graph();
    void add_node(Node N);
    void add_edge(string from, string to);
    void add_edge_data(string from, string to, Edge edge);
    void printNodes();
    void printEdges();
    void print(string);
    void degreeCentrality();
    void dijkstra(string source);
    void betweennessCentrality();

private:
    //** Les nodes sont identifiés par une chaine de caractéres
    map<string, Node> Nodes; // La liste des nodes
    map<string, vector<string>[2]> adjacency_list; // La liste des successeurs et precedesseurs pour chaque node
    map<pair<string, string>, Edge> Edges; // La liste des arcs
};

#endif //CENTRALITY_GRAPH_H
