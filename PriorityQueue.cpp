#include "PriorityQueue.hpp"
#include <limits.h>
#include <string>
#include <iostream>

using namespace std;

int getParent(int index){
    return ((index-1)/2);
};

int getLeftChild(int index){
    return ((2*index) + 1);
};

int getRightChild(int index){
    return ((2*index) + 2);
};

void swap(Customer* a, Customer* b){
    Customer temp = *a;
    *a = *b;
    *b = temp;
    return;
};

PriorityQueue::PriorityQueue(int queueSize){
    maxQueueSize = queueSize;
    currentQueueSize = 0;
    priorityQueue = new Customer[queueSize];
};

PriorityQueue::~PriorityQueue()
{
    delete[] priorityQueue;
};

void PriorityQueue::enqueue(string _startLocation, string _endLocation, int _distance, int _priority){
    Customer add;
    add.startLocation = _startLocation;
    add.endLocation = _endLocation;
    add.distanceToTravel = _distance;
    add.priority = _priority;

    if(currentQueueSize == maxQueueSize)
    {
        cout << "Heap full, cannot enqueue" << endl;
        return;
    }

    currentQueueSize++;

    int index = currentQueueSize - 1;

    priorityQueue[index] = add;

    repairUpward(index);
};

void PriorityQueue::dequeue(){
    if(currentQueueSize <= 0)
    {
      cout << "Heap empty, cannot dequeue" << endl;
      return;
    }

    if(currentQueueSize == 1)
    {
      currentQueueSize--;
      return;
    }

    priorityQueue[0] = priorityQueue[currentQueueSize - 1];
    repairDownward(0);
    currentQueueSize--;
    return;
};

Customer PriorityQueue::peek(){
  if(!isEmpty())
  {
    return priorityQueue[0];
  }

  cout << "Heap empty, nothing to peek" << endl;
  return Customer{};
};

bool PriorityQueue::isFull(){
    if(currentQueueSize == maxQueueSize)
    {
      return true;
    }

    return false;
};


bool PriorityQueue::isEmpty(){
    if(currentQueueSize == 0)
    {
      return true;
    }
    return false;
};

    //private:

void PriorityQueue::repairUpward(int nodeIndex){
    while(nodeIndex != 0 && priorityQueue[getParent(nodeIndex)].distanceToTravel > priorityQueue[nodeIndex].distanceToTravel)
    {
        swap(&priorityQueue[nodeIndex], &priorityQueue[getParent(nodeIndex)]);
        nodeIndex = getParent(nodeIndex);
    }

    if(priorityQueue[getParent(nodeIndex)].distanceToTravel == priorityQueue[nodeIndex].distanceToTravel)
    {
        if(priorityQueue[getParent(nodeIndex)].priority > priorityQueue[nodeIndex].priority)
        {
            swap(&priorityQueue[nodeIndex], &priorityQueue[getParent(nodeIndex)]);
        }
    }
};

void PriorityQueue::repairDownward(int nodeIndex){
    int l = getLeftChild(nodeIndex);
    int r = getRightChild(nodeIndex);
    int smallest = nodeIndex;

    if(l < currentQueueSize && priorityQueue[l].distanceToTravel < priorityQueue[r].distanceToTravel)
    {
      smallest = l;
    }

    if(r < currentQueueSize && priorityQueue[r].distanceToTravel < priorityQueue[smallest].distanceToTravel)
    {
      smallest = r;
    }

    if(smallest != nodeIndex)
    {
      swap(&priorityQueue[nodeIndex], &priorityQueue[smallest]);
      repairDownward(smallest);
    }
};
