//
// Created by abdo on 2/15/2023.
//

#ifndef CENTRALITY_GRAPH_H
#define CENTRALITY_GRAPH_H

#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef struct
{
    string id;
    double x;
    double y;
    int degree;
    int betweenness;
    double eigenvector;

}Node;

typedef struct
{
    double length;
}Edge;

using namespace std;

typedef pair<string, double> iPair;

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
    void dijkstra(string source, map<string, vector<iPair>> graph);
    void betweennessCentrality();
    void eigenvector_centrality();

    const map<string, Node> &getNodes() const;

    const map<string, vector<string>[2]> &getAdjacencyList() const;

private:
    //** Les nodes sont identifi�s par une chaine de caract�res
    map<string, Node> Nodes; // La liste des nodes
    map<string, vector<string>[2]> adjacency_list; // La liste des successeurs et precedesseurs pour chaque node
    map<pair<string, string>, Edge> Edges; // La liste des arcs
};


#endif //CENTRALITY_GRAPH_H
