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
    // Load your graph data into a vector of Node structs

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
        coordinates.PushBack(node.second.x, allocator);
        coordinates.PushBack(node.second.y, allocator);
        geometry.AddMember("coordinates", coordinates, allocator);

        // Create a RapidJSON object for the properties
        Value properties(kObjectType);
        properties.AddMember("id", Value().SetString(node.second.id.c_str(), node.second.id.length(), document.GetAllocator()), document.GetAllocator());
        //properties.AddMember("degree", node.second., allocator);
        properties.AddMember("betweenness", node.second.betweenness, allocator);

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
