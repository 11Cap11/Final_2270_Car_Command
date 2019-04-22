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

void City::addVertex(string name){
    vertex newCity;
    newCity.name = name;
    vertices.push_back(newCity);
};

void City::addRoad(string v1, string v2, int distance){
    vertex* point1 = findVertex(v1);
    vertex* point2 = findVertex(v2);

    Road road;
    road.distance = distance;
    road.v = point2;

    point1->Roads.push_back(road);
};

void City::displayRoads(){
    for(int v = 0; v < vertices.size(); v++){
        cout << vertices[v].name << "-->";
        for (int i = 0; i < vertices[v].Roads.size(); i++) {
            if(i == 0){
                cout << vertices[v].Roads[i].v->name << " (" << vertices[v].Roads[i].distance << " miles)";
            }
            else{
                cout << "***" << vertices[v].Roads[i].v->name << " (" << vertices[v].Roads[i].distance << " miles)";
            }
        }
        cout << endl;
    }
};

void City::printDFT()
{
    setAllVerticesUnvisited();

    for (int i = 0; i < vertices.size(); i++){
        if (!vertices[i].visited){
            DFT_traversal(&vertices[i]);
        }
    }
};

void City::printBFT(){
    setAllVerticesUnvisited();

    for(int v = 0; v < vertices.size(); v++){
        if(vertices[v].visited == false){
            vertices[v].visited = true;
            BFT_traversal(&vertices[v]);
        }
    }
};

void City::setAllVerticesUnvisited(){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].visited = false;
    }
};

class Compare
{
    public:
        bool operator() (vertex* v1, vertex* v2)
        {
            return v1->shortestDistance>v2->shortestDistance;
        }
};

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

void City::BFT_traversal(vertex* v){
    queue<vertex> Queue;

    v->visited = true;
    Queue.push(*v);

    while(!Queue.empty()){
        v = &Queue.front();
        cout << v->name << " " << endl;


        for (int i = 0; i < v->Roads.size(); i++){
            if (v->Roads[i].v->visited == false){
                v->Roads[i].v->visited = true;
                Queue.push(*(v->Roads[i].v));
            }
        }
        Queue.pop();
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

void City::addCustomer(string startLocation, string endLocation, int priority){
    customerQueue->enqueue(startLocation, endLocation, priority);
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
