#pragma once

#include <vector>
#include <iostream>


#include "PriorityQueue.hpp"

using namespace std;

/*This is the struct for the adjacent vertices for each
vertex in the City. */
struct vertex;

struct Road{
    vertex *v;
    int distance;
};

struct Car{//struct for cars to hold information about cars and their locations.
  double distanceNearest;
  string nearest;
  double chargeDistance;
};


/*this is the struct for each vertex in the City. */
struct vertex{
    string name;
    int prioritization;
    int shortestDistance;
    bool chargingStation;
    bool visited;
    vector<Road> Roads; //stores Roads to adjacent vertices
};

class City{
  public:
    City();
    ~City();
    void addVertex(string cityName);
    void addRoad(string city1, string city2, int distance);
    void displayRoads();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();
    int numVertexes;
    void addCustomer(string startLocation, string endLocation, int sDistance, int priority);
    int shortestDistance(string start, string end);
    double serveCustomer();
    vector<vertex> vertices; //stores vertices

  private:
    vertex *findVertex(string name);
    void BFT_traversal(vertex *v);
    void DFT_traversal(vertex *v);
    PriorityQueue* customerQueue;
    Car myCar;

};
