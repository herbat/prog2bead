#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Pipe.hpp"

using namespace std;

typedef struct m{
    
    string name;
    double amount;
    
} Material;

class Container {
    string name;
    bool clean;
    bool empty;
    Material material;
    int capacity;
    map<string, Pipe *> pipes;
    
public:
    Container(){};
    Container(string _name, int _cap) : name(_name), capacity(_cap){
        empty = true;
        clean = true;
    };
    int getCap(){
        return capacity;
    }
    
    bool isEmpty(){
        return empty;
    }
    
    double getAmt(){
        return material.amount;
    }
    
    string getMaterial(){
        return material.name;
    }
    
    double getLeftVolume(){
        return empty ? capacity : capacity - material.amount;
    }
    
    string getName(){
        return name;
    }
    
    map<string, Pipe *> getPipes(){
        return pipes;
    }
    
    void addPipe(Pipe * pipe){
        pipes.emplace(pipe->getName(), pipe);
    }
    
    void addMaterial(string name, double amount){
        material = Material{name, amount};
        empty = false;
        clean = false;
    }
    
    void addAmount(double amount) {
        material.amount += amount;
    }
    
    void cleanIt(){
        if(clean) return;
        for (auto i : pipes){
            i.second->switchTo(false);
            cout << "off" << i.second->getName() << endl;
        }
        clean = true;
    }
    
    void flowTo(string dest){
        for (auto i : pipes){
            if(i.second->getStart() == dest) i.second->switchDirection();
            if (i.second->getEnd() == dest) i.second->switchTo(true);
        }
    }
};
