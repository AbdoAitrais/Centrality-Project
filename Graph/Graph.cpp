//
// Created by abdo on 2/15/2023.
//

#include "Graph.h"

#include <iostream>
#include <queue>

using namespace std;

//**********************************

#define INF INT_MAX

typedef pair<string, double> iPair;


void Graph::betweennessCentrality() {

    // Appliquer Dijkstra sur chaque Node (vertex)
    for (auto i : Nodes)
        dijkstra(i.first);

    for (auto i : Nodes) {
        cout << i.first << "  ==>  " << i.second.betweenness << endl;
    }

}


void Graph::dijkstra(string source) {

    map<string, vector<iPair>> graph;

    for (auto i : Nodes) {
        for (string s : adjacency_list[i.first][0]) {
            pair<string, string> p(i.first, s);
            double length = Edges[p].length;
            graph[i.first].push_back(make_pair(s, length));
        }
    }

    // Create a priority queue to store vertices that are being preprocessed.
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    // Create a map for distances and initialize all distances as infinite (INF).
    map<string, double> dist;
    for (auto i : graph)
        dist[i.first] = INF;

    // Create a map for parents and initialize all parents as #.
    map<string, string> parent;
    for (auto i : graph)
        parent[i.first] = "#";



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
        i.second.degree = adjacency_list[i.first][1].size() + adjacency_list[i.first][0].size();
        //cout << i.second.degree << endl;

//        cout << i.first << " : " << endl;
//        cout << "   InDegree  ==> " << adjacency_list[i.first][1].size() << endl;
//        cout << "   OutDegree ==> " << adjacency_list[i.first][0].size() << endl;
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
    for (const auto& i : Nodes) {
        cout << i.first << " : " << i.second.x << ", " << i.second.y << ", " << i.second.degree << endl;
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

const map<pair<string, string>, Edge> &Graph::getEdges() const {
    return Edges;
}
