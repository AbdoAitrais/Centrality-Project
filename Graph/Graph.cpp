//
// Created by abdo on 2/15/2023.
//

#include "Graph.h"

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

//**********************************

#define INF INT_MAX

typedef pair<string, double> iPair;


void Graph::betweennessCentrality() {

    map<string, vector<iPair>> graph;

    for (auto i : Nodes) {
        for (string s : adjacency_list[i.first][0]) {
            pair<string, string> p(i.first, s);
            double length = Edges[p].length;
            graph[i.first].push_back(make_pair(s, length));
        }
    }

    // Appliquer Dijkstra sur chaque Node (vertex)
    int j = 10;
    for (auto i : Nodes) {
        if (!(j--))
            break;
        dijkstra(i.first, graph);
    }


    /*dijkstra("42439210", graph);
    dijkstra("42431019", graph);
    dijkstra("42437312", graph);*/

    for (auto i : Nodes) {
        cout << i.first << "  ==>  " << i.second.betweenness << endl;
    }

}


void Graph::dijkstra(string source, map<string, vector<iPair>> graph) {

    // Create a priority queue to store vertices that are being preprocessed.
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    // Create a map for distances and initialize all distances as infinite (INF).
    map<string, double> dist;
    // Create a map for parents and initialize all parents
    map<string, string> parent;

    for (auto i : graph) {
        dist[i.first] = INF;
        parent[i.first] = "#";
    }

    // Insert source itself in priority queue and initialize its distance as 0.
    pq.push(make_pair(source, 0));
    dist[source] = 0;

    // Loop until priority queue becomes empty.
    while (!pq.empty()) {
        // Extract the minimum distance vertex from priority queue.
        string u = pq.top().first;
        pq.pop();

        // Traverse through all adjacent vertices of u and update their distance from source.
        for (auto& neighbor : graph[u]) {
            string v = neighbor.first;
            double length = neighbor.second;

            // If there is shorter path to v through u.
            if (dist[v] > dist[u] + length) {
                // Update distance of v and push it into the priority queue.
                dist[v] = dist[u] + length;
                parent[v] = u;
                pq.push(make_pair(v, dist[v]));
            }
        }
    }

    for (auto i : parent)
        if (i.second != "#")
            Nodes[i.first].betweenness++;

}




//***********************************

// Function to compute the dot product of two vectors
double dot_product(map<string, double> m1, map<string, double> m2) {
    double result = 0;
    auto it_m1 = m1.cbegin();
    auto it_m2 = m2.cbegin();
    while (it_m1 != m1.end() && it_m2 != m2.end()) {
        result += it_m1->second * it_m2->second;
        ++it_m1;
        ++it_m2;
    }
    return result;
}

// Function to normalize a vector
void normalize(map<string, double>& m) {
    double sum = 0;
    for (auto i : m) {
        sum += pow(i.second, 2);
    }
    double norm = sqrt(sum);
    for (auto& i : m) {
        i.second /= norm;
    }
}



// Function to compute eigenvector centrality
void Graph::eigenvector_centrality() {
    // Initialize the centrality vector with random values
    map<string, double> centrality;

    for (auto i : Nodes)
        centrality[i.first] = 1.0;

    // Set the convergence tolerance and maximum number of iterations
    double tolerance = 0.01;
    int max_iterations = 100;

    // Iteratively update the centrality vector using the power iteration method
    for (int i = 0; i < max_iterations; i++) {
        map<string, double> new_centrality;
        for (auto j : Nodes) {
            double sum = 0;
            for (auto k : adjacency_list[j.first][0]) {
                sum += centrality[k];
            }
            for (auto k : adjacency_list[j.first][1]) {
                sum += centrality[k];
            }
            new_centrality[j.first] = sum;
        }
        normalize(new_centrality);
        if (fabs(dot_product(new_centrality, centrality) - 1) < tolerance) {
            break;
        }
        centrality = new_centrality;
    }

    //return centrality;
    for (auto i : centrality)
        Nodes[i.first].eigenvector = i.second;

    for (auto i : Nodes)
        cout << i.first << "==>" << i.second.eigenvector << endl;
}





//**********************************

Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}


/*Graph::Graph(int num_vertices)
{
    adjacency_list.resize(num_vertices);
}*/

void Graph::add_node(Node N)
{
    Nodes[N.id] = N;
}

void Graph::add_edge(string fromID, string toID)
{
    adjacency_list[fromID][0].push_back(toID);
    adjacency_list[toID][1].push_back(fromID);
}


void Graph::add_edge_data(string fromID, string toID, Edge edge)
{
    pair<string, string> p = { fromID, toID };
    Edges[p]= edge;
}


void Graph::printEdges()
{
    for (auto i : Edges) {
        cout << i.first.first << " --- " << i.first.second << " ==> " << i.second.length << endl;
    }
}

void Graph::degreeCentrality()
{
    for (auto& i : Nodes) {
        cout << i.first << " : " << endl;
        i.second.degree = adjacency_list[i.first][0].size() + adjacency_list[i.first][1].size();
    }
}



/*void Graph::print()
{
    for (int i = 0; i < adjacency_list.size(); ++i)
     {
         for (int j = 0; j < num_vertices; ++j)
        {
            cout << i << " " << j << ": ";
            for (Content C : adjacency_list[i][j]) {
                //cout << C << " ";
                cout << C.x << " " << C.y << endl;
            }
            cout << "\n";
        }
     }
}*/


void Graph::printNodes()
{
    for (auto i : Nodes) {
        cout << i.first << " : " << i.second.x << ", " << i.second.y << endl;
    }
}

void Graph::print(string id)
{
    for (int i = 0; i < adjacency_list[id][0].size(); i++)
        cout << adjacency_list[id][0][i] << endl;
}

const map<string, Node> &Graph::getNodes() const {
    return Nodes;
}

const map<string, vector<string>[2]> &Graph::getAdjacencyList() const {
    return adjacency_list;
}
