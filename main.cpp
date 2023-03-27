
#include <iostream>
#include "Graph/Graph.cpp"
#include "JsonUtilities/jsonCreation.cpp"
#include<boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
using namespace std;
#include<boost/property_tree/xml_parser.hpp>
#include<boost/foreach.hpp>
#define XML_PATH "C:/Users/abdo/Desktop/ILISI/ILISI 2/S2/IOT Atelier/manhatten.xml"
#define ATTR_SET "<xmlattr>"

int main()
{
    ptree pt;
    read_xml(XML_PATH, pt);
    string strTmp;
    //auto root = pt.get_child("graphml.graph");
    //Graph
    Graph G;

    for (auto& node : pt.get_child("graphml.graph")) {
        if (node.first == "node") {
            Node N;
            N.betweenness = 0;
            std::string node_id = node.second.get<std::string>("<xmlattr>.id");
            //std::cout << "Node ID: " << node_id << std::endl;
            N.id = node_id;
            for (auto& data : node.second) {
                if (data.first == "data") {
                    std::string key = data.second.get<std::string>("<xmlattr>.key");
                    std::string value = data.second.data();
                    if (key == "d3") {
                        //std::cout << "\t" << key << ": " << value << std::endl;
                        N.y = stod(value);
                    }
                    else if (key == "d4") {
                        //std::cout << "\t" << key << ": " << value << std::endl;
                        N.x = stod(value);
                    }
                    else break;
                }
            }
            //cout << N.id << endl;
            G.add_node(N);
        }
        if (node.first == "edge") {
            Edge edge;
            std::string source = node.second.get<std::string>("<xmlattr>.source");
            std::string target = node.second.get<std::string>("<xmlattr>.target");
            //std::cout << "Source: " << source << " || Target: " << target << std::endl;
            for (auto& data : node.second) {
                if (data.first == "data") {
                    std::string key = data.second.get<std::string>("<xmlattr>.key");
                    std::string value = data.second.data();
                    //std::cout << "\t" << key << ": " << value << std::
                    if (key == "d9") {
                        edge.length = stod(value);
                        break;
                    }
                }
            }
            G.add_edge(source, target);
            G.add_edge_data(source, target, edge);
        }
        //G.printNodes();
    }
    //G.printNodes();
    //G.print("42429217");
    G.degreeCentrality();
//    G.printEdges();
    //G.dijkstra("42428604");
    //G.betweennessCentrality();
    G.eigenvector_centrality();
    createJsonFile(G.getNodes());
}
