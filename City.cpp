#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>


#include "PriorityQueue.hpp"
#include "City.hpp"


using namespace std;

// -- Public:

City::City(){
};

City::~City(){
};

/**
* addVertex: adds a vertex to the graph as a new city
* parameter: name of the city to be added
**/
void City::addVertex(string name){
    vertex newCity; // creating a new vertex object for the new city
    newCity.name = name; // setting the new vertex's name to the string passed as a parameter
    vertices.push_back(newCity); // pushing back the new city into the vector of vertices
};

/**
* addRoad: adds a road (edge) with a specified distance between two vertices
* parameters: two strings specifying the two vertices between which the road is going
* and the distance of the aforementioned road
**/
void City::addRoad(string v1, string v2, int distance){
    vertex* point1 = findVertex(v1); // finding the first vertex by name
    vertex* point2 = findVertex(v2); // finding the second vertex by name

    Road road; // creating a new road object
    road.distance = distance; // setting the distance of the road to the parameter
    road.v = point2; // setting the vertex of the road to the second vertex

    point1->Roads.push_back(road); // pushing back the new road into the vector of roads from point 1
};

/**
* displayRoads: displays the inputted roads
* parameters: none
**/
void City::displayRoads(){
    for(int v = 0; v < vertices.size(); v++){ // traversing the vertices of the city
        cout << vertices[v].name << "-->"; // displaying the name of each vertex
        for (int i = 0; i < vertices[v].Roads.size(); i++) { // traversing the roads at each vertex
            if(i == 0){ // printing the roads in a similar fashion to that of assignment 9
                cout << vertices[v].Roads[i].v->name << " (" << vertices[v].Roads[i].distance << " miles)";
            }
            else{
                cout << "***" << vertices[v].Roads[i].v->name << " (" << vertices[v].Roads[i].distance << " miles)";
            }
        }
        cout << endl;
    }
};

/**
* printDFT: prints a depth first traversal of the city graph
* parameters: none
**/
void City::printDFT()
{
    setAllVerticesUnvisited(); // sets all vertices unvisited as the function name suggests

    for (int i = 0; i < vertices.size(); i++){ // for loop traversing the vertices
        if (!vertices[i].visited){ // if the vertex is unvisisted
            DFT_traversal(&vertices[i]); // recursive call of the current vertex to continue the DFT
        }
    }
};

/**
* printBFT: prints a breadth first traversal of the city graph
* parameters: none
**/
void City::printBFT(){
    setAllVerticesUnvisited(); // sets all vertices unvisited as the function name suggests

    for(int v = 0; v < vertices.size(); v++){ // for loop traversing the vertices
        if(vertices[v].visited == false){ // if the vertex is unvisited
            vertices[v].visited = true; // setting the visited boolean at the vertex to true
            BFT_traversal(&vertices[v]); // recursively calling BFT traversal from the current vertex
        }
    }
};

/**
* setAllVerticesUnvisited: sets all vertices in the graph to unvisited
* parameters: none
**/
void City::setAllVerticesUnvisited(){
    for (int i = 0; i < vertices.size(); i++) { // for loop traversing all vertices in the graph
        vertices[i].visited = false; // setting the visited boolean at each vertex to false
    }
};

/** Class to compare the shortest distance between 
two vertices and the current position**/
class Compare
{
    public:
        bool operator() (vertex* v1, vertex* v2)
        {
            return v1->shortestDistance>v2->shortestDistance; // comparing the two vertices and comparing which has the larger distance
        }
};

/**
* shortestDistance: finds the shortest distance between two points passed in as parameters
* parameters: two strings representing the starting and ending points
**/
int City::shortestDistance(string start, string end)
{
    //Create a priority queue
    priority_queue<vertex*, vector<vertex*>, Compare> pq;

    //Set the initial distance and visited
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name == start){
            vertices[i].shortestDistance = 0;
            pq.push(&vertices[i]);
        }else{
            vertices[i].shortestDistance=100000;
        }
        vertices[i].visited=false;
    }

    //Till my queue is not empty
    while(pq.size() >0){
        //Get the first element (As this is a priority queue the top will be the next closed element, wait, why is that?)
        vertex* current= pq.top();
        //Mark it as visited or done as this is the next closest element!
        current->visited=true;
        //Remove from the queue
        pq.pop();
        //For all the edges
        for(int i=0;i<current->Roads.size();i++){
            //If they are not already solved
            if(current->Roads[i].v->visited==false){
                //If the new distance I found to the node is actually smaller than the old distance I had
                if(current->Roads[i].v->shortestDistance > current->shortestDistance+ current->Roads[i].distance){
                    //Update it
                    current->Roads[i].v->shortestDistance = current->shortestDistance + current->Roads[i].distance;
                }
                //Enqueue the vertex
                pq.push(current->Roads[i].v);

            }
        }
    }
    //Lets print everything
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name == end){
            return vertices[i].shortestDistance;
        }
    }
}


// -- Private:

vertex* City::findVertex(string name){
    for(int v = 0; v < vertices.size(); v++){
        if(vertices[v].name == name){
            return &vertices[v];
        }
    }
    return nullptr;
};

/**
* BFT_traversal: function to perform a breadth first traversal
* parameter: a vertex to start the traversal from
**/
void City::BFT_traversal(vertex* v){
    queue<vertex> Queue; // initializing a queue of vertices

    v->visited = true; // setting visited to true for each vertex as we get to it
    Queue.push(*v); // pushing the vertex into the queue

    while(!Queue.empty()){
        v = &Queue.front(); // while the queue is not empty, set v equal to the front of the queue
        cout << v->name << " " << endl; // printing the name of the vertex


        for (int i = 0; i < v->Roads.size(); i++){ // traversing the number of roads
            if (v->Roads[i].v->visited == false){ // if the road has not already been visited
                v->Roads[i].v->visited = true; // set the roads' visited boolean to true
                Queue.push(*(v->Roads[i].v)); // pushing into the roads of the vertex we are currently at
            }
        }
        Queue.pop(); // popping from the queue
    }
};


void City::DFT_traversal(vertex *v){
    v->visited = true;
    cout << v->name << endl;
    for (int i = 0; i < v->Roads.size(); i++){
        if (!v->Roads[i].v->visited){
            DFT_traversal(v->Roads[i].v);
        }
    }
};

void City::addCustomer(string startLocation, string endLocation, int sDistance, int priority){
    int distance = sDistance + shortestDistance(startLocation, endLocation);
    customerQueue->enqueue(startLocation, endLocation, distance, priority);
};

double City::serveCustomer(){
    if(customerQueue->isEmpty()){
        return 0.0;
    }
    double pricePerDist = 1.25 + (0.25 * (customerQueue->peek().priority));
    int distance = customerQueue->peek().distanceToTravel;
    double tripPrice = pricePerDist*distance;
    if((myCar.chargeDistance+3) <= distance){
        myCar.chargeDistance = 20;
        tripPrice = tripPrice - 2.0;
    }
    myCar.chargeDistance = myCar.chargeDistance - distance;
    myCar.nearest = customerQueue->peek().endLocation;
    customerQueue->dequeue();
    return tripPrice;
};
