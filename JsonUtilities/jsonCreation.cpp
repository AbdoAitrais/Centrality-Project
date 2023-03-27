//
// Created by abdo on 3/25/2023.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "../Graph/Graph.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


using namespace rapidjson;



void createJsonFile(map<string,Node> nodes) {

    // Create a RapidJSON document to hold the GeoJSON data
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    // Create a RapidJSON array to hold the GeoJSON features
    Value features(kArrayType);

    // Loop through each node and create a GeoJSON feature for it
    for (const auto& node : nodes) {
        // Create a RapidJSON object for the feature
        Value feature(kObjectType);

        // Create a RapidJSON object for the geometry
        Value geometry(kObjectType);
        geometry.AddMember("type", "Point", allocator);
        Value coordinates(kArrayType);
        coordinates.PushBack(node.second.y, allocator);
        coordinates.PushBack(node.second.x, allocator);
        geometry.AddMember("coordinates", coordinates, allocator);

        // Create a RapidJSON object for the properties
        Value properties(kObjectType);
        properties.AddMember("id", Value().SetString(node.second.id.c_str(), node.second.id.length(), document.GetAllocator()), document.GetAllocator());
        properties.AddMember("degree", node.second.degree, allocator);
        properties.AddMember("eigenvector", node.second.eigenvector, allocator);

        // Add the geometry and properties to the feature
        feature.AddMember("type", "Feature", allocator);
        feature.AddMember("geometry", geometry, allocator);
        feature.AddMember("properties", properties, allocator);

        // Add the feature to the array
        features.PushBack(feature, allocator);
    }

    // Add the features array to the document
    document.AddMember("type", "FeatureCollection", allocator);
    document.AddMember("features", features, allocator);

    // Write the GeoJSON to a file
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    std::ofstream outfile("city_graph.geojson");
    outfile << buffer.GetString();
    outfile.close();

}

//void createJsonFileWithEdges(Graph graph){
//    // Load your node and edge data into vectors of Node and Edge structs
//    map<string, Node> nodes = graph.getNodes();
//    map<pair<string, string>, Edge> edges = graph.getEdges();
//
//
//    // Create a RapidJSON document to hold the GeoJSON data
//    Document document;
//    document.SetObject();
//    Document::AllocatorType& allocator = document.GetAllocator();
//
//    // Create a RapidJSON array to hold the GeoJSON features
//    Value features(kArrayType);
//
//    // Loop through each node and create a GeoJSON feature for it
//    for (const auto& node : nodes) {
//        // Create a RapidJSON object for the feature
//        Value feature(kObjectType);
//
//        // Create a RapidJSON object for the geometry
//        Value geometry(kObjectType);
//        geometry.AddMember("type", "Point", allocator);
//        Value coordinates(kArrayType);
//        coordinates.PushBack(node.lng, allocator);
//        coordinates.PushBack(node.lat, allocator);
//        geometry.AddMember("coordinates", coordinates, allocator);
//
//        // Create a RapidJSON object for the properties
//        Value properties(kObjectType);
//        properties.AddMember("id", node.id.c_str(), allocator);
//        properties.AddMember("degree", node.degree, allocator);
//        properties.AddMember("betweenness", node.betweenness, allocator);
//
//        // Add the geometry and properties to the feature
//        feature.AddMember("type", "Feature", allocator);
//        feature.AddMember("geometry", geometry, allocator);
//        feature.AddMember("properties", properties, allocator);
//
//        // Add the feature to the array
//        features.PushBack(feature, allocator);
//    }
//
//    // Loop through each edge and create a GeoJSON feature for it
//    for (const auto& edge : edges) {
//        // Look up the source and target node coordinates
//        auto source_coordinates = nodes[edge.first.first];
//        auto target_coordinates = nodes[edge.first.second];
//
//        // Create a RapidJSON object for the feature
//        Value feature(kObjectType);
//
//        // Create a RapidJSON object for the geometry
//        Value geometry(kObjectType);
//        geometry.AddMember("type", "LineString", allocator);
//        Value coordinates(kArrayType);
//        coordinates.PushBack(source_coordinates.first, allocator);
//        coordinates.PushBack(source_coordinates.second, allocator);
//        coordinates.PushBack(target_coordinates.first, allocator);
//        coordinates.PushBack(target_coordinates.second, allocator);
//        geometry.AddMember("coordinates", coordinates, allocator);
//        // Create a RapidJSON object for the properties
//        Value properties(kObjectType);
//        properties.AddMember("id", edge.id.c_str(), allocator);
//        properties.AddMember("weight", edge.weight, allocator);
//
//        // Add the geometry and properties to the feature
//        feature.AddMember("type", "Feature", allocator);
//        feature.AddMember("geometry", geometry, allocator);
//        feature.AddMember("properties", properties, allocator);
//
//        // Add the feature to the array
//        features.PushBack(feature, allocator);
//    }
//
//    // Add the features array to the document
//    document.AddMember("type", "FeatureCollection", allocator);
//    document.AddMember("features", features, allocator);
//
//    // Convert the document to a string and write it to a file
//    StringBuffer buffer;
//    Writer<StringBuffer> writer(buffer);
//    document.Accept(writer);
//
//    std::ofstream outfile("city_graph.geojson");
//    outfile << buffer.GetString();
//    outfile.close();
//
//}