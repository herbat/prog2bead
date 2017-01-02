#pragma once
#include <string>
#include <map>
#include "Pipe.hpp"

using namespace std;

typedef struct m{
    
    string name;
    int amount;
    
} Material;

class Container {
    string name;
    bool isClean;
    bool isEmpty;
    Material material;
    
public:
    int capacity;
    map<string, Pipe *> pipes;
    Container(){};
    Container(string _name, int _cap) : name(_name), capacity(_cap){};
    void addPipe(Pipe * pipe){
        pipes.emplace(pipe->name, pipe);
    }
    void addMaterial(string name, int amount){
        this->material = Material{name, amount};
    }
};
