#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Pipe.cpp"
#include "Container.cpp"

using namespace std;

const int MAX = 20;
const string fileURL =  "/Users/atus/Documents/schoolprog/prog2bead/prog2bead/test.txt";//to be replaced with actual fileURL
const string fileURL2 =  "/Users/atus/Documents/schoolprog/prog2bead/prog2bead/test2.txt";

vector<vector<double>> createflowmatrix(map<string, Container> containers, map<string, Pipe> pipes);
double step (map<string, Container> containers, map<string, Pipe> pipes,  vector<vector<double>> flowmatrix, double time);

int main(int argc, const char * argv[]) {
    map<string, Container> containers;
    map<string, Pipe> pipes;
    
    int cap, amt;
    double time = 0;
    string line;
    char name [MAX], start [MAX], end[MAX], cont[MAX], command[MAX];
    ifstream initFile(fileURL);
    ifstream initFile2(fileURL2);
    
    //INITIAL STATE--------------------------------------------------
    
    while(getline(initFile, line)){//get containers
        if(line == "-") break;
        sscanf(line.c_str(), "%s %d", name, &cap);
        containers.emplace(name, Container(name, cap));
    }
    
    while(getline(initFile, line)){//get pipes
        sscanf(line.c_str(), "%s %d %s %s", name, &cap, start, end);
        if(containers.find(start) == containers.end() || containers.find(end) == containers.end()) break;
        pipes.emplace(name, Pipe(name, cap, start, end));
        containers[start].addPipe(&pipes[name]);
    }
    
    while(getline(initFile2, line)){
        sscanf(line.c_str(), "%s %s %d", name, cont, &amt);
        if(containers.find(cont) == containers.end()) break;
        if(containers[cont].getCap() < amt) continue;
        containers[cont].addMaterial(name, amt);
    }
    
    //---------------------------------------------------------------
    
    //COMMAND SECTION------------------------------------------------
    
    while(scanf("%s", command)){
        if(strcmp(command, "step")) {
            time = step(containers, pipes, createflowmatrix(containers, pipes), time);
        } else if (strcmp(command, "off") && pipes.find(name) == pipes.end()) {
            scanf("%s", name);
            pipes[name].switchTo(false);
        } else if (strcmp(command, "clean") && containers.find(name) == containers.end()) {
            scanf("%s", name);
            containers[name].clean();
        } else if (strcmp(command, "on") && pipes.find(name) == pipes.end() && containers.find(end) == containers.end()) {
            scanf("%s %s", name, end);
            if(pipes[name].getEnd() == end)
                pipes[name].switchTo(true);//just open it
            
            else if(pipes[name].getStart() == end)
                containers[pipes[name].getEnd()].flowTo(end);//reverse direction and open it
            
            else { cout << "Bad command" << endl; continue; }// bad command so skip
        } else {
            cout << "Bad command" << endl;
            continue;
        }
        
    }
    
    //---------------------------------------------------------------
    
    //ITERATIONS-----------------------------------------------------
    //---------------------------------------------------------------
    
    //vector<string> path = findpath(containers, "A", "B", * new vector<string>);
    //cout << path[0] << endl;
    return 0;
}

vector<vector<double>> createflowmatrix(map<string, Container> containers, map<string, Pipe> pipes) {
    vector<vector<double>> flowmatrix;
    vector<double> flows;
    for(auto c : containers) {
        map<string, Pipe * > cpipes = c.second.getPipes();
        for (auto p : pipes) {
            if(!(cpipes.find(p.second.getName()) == cpipes.end())){//if the pipe is connected to the container
                if (p.second.isOn()) {//and it is on
                    if (p.second.getStart() == c.first)
                         flows.push_back(-p.second.getCap());//and cont is source, then negative
                    else flows.push_back(p.second.getCap());//if not source, then end, which means positive
                } else flows.push_back(0);
            } else flows.push_back(0);
        }
        flowmatrix.push_back(flows);
    }
    return flowmatrix;
}

double step (map<string, Container> containers, map<string, Pipe> pipes,  vector<vector<double>> flowmatrix, double time) {
    
    vector<double> sum;
    double t_temp = 1-time;
    int keresett = 0;//ahol update kell a flowban
    
    for(auto c : containers) {//
        int tsum = 0;
        
        for(auto p : c.second.getPipes())
            tsum += p.second->getCap();
        
        sum.push_back(tsum);
    }
    
    int count;
    for(auto c : containers) {
        
        if(sum[count] != 0) {
            if(sum[count] > 0 && t_temp*sum[count] > c.second.getLeftVolume()) {//ha megtelőben van, akkor számoljuk újra az időt
                t_temp = (c.second.getLeftVolume())/sum[count];
                keresett = count;
            } else if(t_temp*sum[count] > (0 - c.second.getAmt())) {
                t_temp = (0-c.second.getAmt())/sum[count];
                keresett = count;
            }
        }
        count++;
    }
    
    count = 0;
    for(auto c : containers) {
        c.second.addAmount(sum[count]*t_temp);
        count++;
    }
    
}

