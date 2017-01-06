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
void step();

int main(int argc, const char * argv[]) {
    map<string, Container> containers;
    map<string, Pipe> pipes;
    
    int cap, amt;
    string line;
    char name [MAX], start [MAX], end[MAX], cont[MAX], command[MAX];
    ifstream initFile(fileURL);
    ifstream initFile2(fileURL2);
    
    //INITIAL STATE--------------------------------------------------
    
    while(getline(initFile, line)){//get containers
        if(line == "- ") break;
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
        cout << name << " " << amt;
        if(containers.find(cont) == containers.end()) break;
        if(containers[cont].getCap() < amt) continue;
        containers[cont].addMaterial(name, amt);
    }
    
    //---------------------------------------------------------------
    
    //COMMAND SECTION------------------------------------------------
    
    while(scanf("%s %s %s", command, name, end)){
        if(strcmp(command, "step")) {
            step();
        } else if (strcmp(command, "off") && pipes.find(name) == pipes.end()) {
            pipes[name].switchTo(false);
        } else if (strcmp(command, "clean") && containers.find(name) == containers.end()) {
            containers[name].clean();
        } else if (strcmp(command, "on") && pipes.find(name) == pipes.end() && containers.find(end) == containers.end()) {
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
                    if (p.second.getStart() == c.second.getName())
                         flows.push_back(-p.second.getCap());//and cont is source, then negative
                    else flows.push_back(p.second.getCap());//if not source, then end, which means positive
                } else flows.push_back(0);
            } else flows.push_back(0);
        }
        flowmatrix.push_back(flows);
    }
    return flowmatrix;
}

void step (map<string, Container> containers, map<string, Pipe> pipes,  vector<vector<double>> flowmatrix, double time)
{
    
    vector<double> sum;
    double t_temp = 1-time;
    int keresett = 0;//ahol update kell a flowban
    
    for(auto c : containers) {//
        int tsum = 0;
        
        for(auto p : c.second.getPipes())
            tsum += p.second->getCap();
        
        sum.push_back(tsum);
    }
    
    for(int i=0; graf.tartalyok.size(); i++)
    {
        if(sum[i] != 0)
        {
            if(sum[i]>0 && t_temp > (graf.tartalyok[i]->V - graf.tartalyok[i]->V_nedv)/sum[i]) {t_temp = (graf.tartalyok[i]->V - graf.tartalyok[i]->V_nedv)/sum[i]; keresett = i;}
            if(sum[i]<0 && t_temp > (0 - graf.tartalyok[i]->V_nedv)/sum[i]) {t_temp = (0 - graf.tartalyok[i]->V_nedv)/sum[i]; keresett = i;}
        }
    }
    if(t+t_temp == 1)
    {
        for(int i=0 ;i <graf.tartalyok.size();i++)
        {
            graf.tartalyok[i]->V_nedv += sum[i]*t_temp;
        }
        return;
    }
    
    else
    {
        for(int i = 0; i < graf.tartalyok.size();i++)
        {
            graf.tartalyok[i]->V_nedv += sum[i]*t_temp;
        }
    }
    double poz[graf.csovek.size()];
    int alfa = 1;
    double sumt = sum[keresett];
    
    if(sum[keresett]<0)
    {
        alfa = -1;
    }
    for(int i=0; i<graf.csovek.size();i++)
    {
        if(flowmatrix[keresett][i]*alfa > 0)
        {
            poz[i]=flowmatrix[keresett][i];
            sumt = sumt-poz[i];
        }
    }
    if(sumt == 0)
    {
        for (int i=0; i<graf.csovek.size();i++)
            
        {
            if(flowmatrix[keresett][i] != 0)
            {
                if( graf.csovek[i].tar1 == graf.tartalyok[keresett]->nev_tart)
                {
                    
                    for(int j=0; j<graf.tartalyok.size();j++)
                    {
                        if(graf.tartalyok[j]->nev_tart == graf.csovek[i].tar2)
                        {
                            flowmatrix[keresett][i]=0;
                            flowmatrix[j][i]=0;
                        }
                    }
                }
                else
                {
                    for(int j=0; j<graf.tartalyok.size();j++)
                    {
                        if(graf.tartalyok[j]->nev_tart == graf.csovek[i].tar1)
                        {
                            flowmatrix[keresett][i]=0;
                            flowmatrix[j][i]=0;
                        }
                    }
                }
            }
        }
        step(graf, flowmatrix, t+t_temp);
    }
    else
    {  alfa = 1;
        double sumt2;
        vector<double>index;
        
        if (sumt < 0)    alfa=-1;
        
        for(int i= 0; i< graf.csovek.size(); i++)
        {
            if ( flowmatrix[keresett][i]*alfa > 0 )
            {
                sumt2=+flowmatrix[keresett][i];
                index.push_back(i);
                
            }
        }
        
        for(int i=0; i<index.size();i++)
        {
            if (graf.csovek[index[i]].tar1 == graf.tartalyok[keresett]->nev_tart)
            {
                for (int j=0; j<graf.tartalyok.size();j++)
                {
                    if(graf.csovek[index[i]].tar2 == graf.tartalyok[j]->nev_tart)
                    {
                        flowmatrix[keresett][index[i]]*=(sumt2-sum[keresett])/sumt2;
                        flowmatrix[j][index[i]]*=(sumt2-sum[keresett])/sumt2;
                    }
                }
            }
        }
        step(graf,flowmatrix,t+t_temp);
    }
    
}



//vector<string> findpath(map<string, Container> containers, string start, string end,vector<string> path){
//    // The set of nodes already evaluated.
//    closedSet := {}
//    // The set of currently discovered nodes still to be evaluated.
//    // Initially, only the start node is known.
//    openSet := {start}
//    // For each node, which node it can most efficiently be reached from.
//    // If a node can be reached from many nodes, cameFrom will eventually contain the
//    // most efficient previous step.
//    cameFrom := the empty map
//    
//    // For each node, the cost of getting from the start node to that node.
//    gScore := map with default value of Infinity
//    // The cost of going from start to start is zero.
//    gScore[start] := 0
//    // For each node, the total cost of getting from the start node to the goal
//    // by passing by that node. That value is partly known, partly heuristic.
//    fScore := map with default value of Infinity
//    // For the first node, that value is completely heuristic.
//    fScore[start] := heuristic_cost_estimate(start, goal)
//    
//    while openSet is not empty {
//        current := the node in openSet having the lowest fScore[] value
//        if current = goal
//            return reconstruct_path(cameFrom, current);
//            
//        openSet.Remove(current)
//        closedSet.Add(current)
//        for each neighbor of current {
//            if neighbor in closedSet
//                continue		// Ignore the neighbor which is already evaluated.
//            // The distance from start to a neighbor
//            tentative_gScore := gScore[current] + dist_between(current, neighbor)
//            if neighbor not in openSet	// Discover a new node
//                openSet.Add(neighbor)
//            else if tentative_gScore >= gScore[neighbor]
//                continue		// This is not a better path.
//                            
//            // This path is the best until now. Record it!
//            cameFrom[neighbor] := current
//            gScore[neighbor] := tentative_gScore
//            fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
//        }
//        return failure
//                            
//        function reconstruct_path(cameFrom, current)
//            total_path := [current]
//                            while current in cameFrom.Keys:
//                                current := cameFrom[current]
//                                total_path.append(current)
//                                return total_path
//}
//
