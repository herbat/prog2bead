#pragma once
#include <string>
using namespace std;

class Pipe {
    int capacity;
    bool on;
    string start;
    string end;
    string name;
    
public:
    Pipe(){};
    Pipe(string _name, int _cap, const string _start, const string _end):
           name(_name), capacity(_cap), start(_start), end(_end){
        on = false;
    };
    string getName(){
        return name;
    }
    string getStart(){
        return start;
    }
    string getEnd(){
        return end;
    }
    bool isOn(){
        return on;
    }
    int getCap(){
        return capacity;
    }
    void switchTo(bool _on){
        on = _on;
    }
    void switchDirection(){
        swap(start, end);
    }
    
};


