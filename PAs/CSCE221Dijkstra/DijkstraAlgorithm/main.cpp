#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int main(int argc, const char * argv[]) {
    cout << "Filename of graph to load: ";
    cout << endl;

    // TODO: next five code snippets
    // Snippet 1: read filename and open file
    string filename = "";
    cin >> filename;
    fstream stream;
    istringstream ISS;
    stream.open(filename);
    if(!stream.is_open())
    {
        cout << "Error unable to open file" << endl;
        return 0;
    }

    string line = "";
    // Snippet 2: get number graph size
    int numberOfVertices = 0;
    int numberOfEdges = 0;
    getline(stream, line);
    ISS.str(line);
    ISS >> numberOfVertices;
    ISS >> numberOfEdges;

    
    int vertex = 0;
    int edge = 0;
    float weight = 0;

    int startVertex = 0;
    int endVertex = 0;
    // Snippet 3: create graph
    Graph* graph = new Graph();
    
    while (!stream.eof())
    {
        getline(stream, line);
        ISS.clear();
        ISS.str(line);
        
        ISS >> vertex; //first values is the vertex
        ISS >> edge; //second value is the edge
        if(!(ISS >> weight)) // if we're at the last line where there's no weight just the start and end vertices copy the vertex and edge values else input weight value
        {
            
            startVertex = vertex;
            endVertex = edge;
        }
        else
        {
            // Snippet 4: read edges
            
            graph->insertEdge(vertex, edge, weight);
        }
    }

    stream.close();
    
    
    // Snippet 5: read start and end of path
    //graph->print();
    cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;
    

    vector<Vertex*> path = graph->shortestPath(startVertex, endVertex);

    // TODO: call shortest path on your graph for the sstart and end verices and save result to path
    
    for (auto i : path) { // this is a for-each loop
        cout << i->label << " ";
    }
    // cout endline at very end
    cout << endl;
    return 0;
}
