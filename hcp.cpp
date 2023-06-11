#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

#define EDGES 128

struct EdgesAndWeight {
    char Edge1;                                                                                     //O(1)
    char Edge2;                                                                                     //O(1)
    int weight;                                                                                     //O(1)
};
struct EdgesAndTime {
    char Edge;                                                                                      //O(1)
    int DeliveryTime_t;                                                                             //O(1)
};

void FindHamiltonianCircuit(vector<pair<char, int>> graph[], vector<bool>& visited, vector<char>& path, char v, int& minWeight, int totalWeight, vector<char>& minPath, EdgesAndTime* t, int numVer, int PathSize) {
    //O(N!)

    if (path.size() == PathSize) {                                                                  //O(1)
        for (auto& p : graph[v]) {        
            
            //O(N) N is size of graph
            if (totalWeight < minWeight) {      
            
                //O(1)
                minPath = path;      
                                            //O(1)
                minWeight = totalWeight;                                                            //O(1)
            }
        }
        return;                                                                                     //O(1)
    }
    for (auto& p : graph[v]) {                                                                      //O(N) N is size of graph
        if (!visited[v]) {                                                                          //O(1)
            visited[v] = true;                                                                      //O(1)
            path.emplace_back(v);                                                                   //O(1)
            int deliveryTime = 0;                                                                   //O(1)

            for (int i = 0; i <= numVer; i++) {                                                   //O(N) N is number of vertices
                if (p.first == t[i].Edge) {                                                         //O(1)
                    deliveryTime = t[i].DeliveryTime_t;                                             //O(1)
                }
            }

            FindHamiltonianCircuit(graph, visited, path, p.first, minWeight, totalWeight + p.second + deliveryTime, minPath, t, numVer, PathSize);
            visited[v] = false;                                                                     //O(1)
            path.pop_back();                                                                        //O(1)
        }
    }
}

void addEdge(vector<pair<char, int>> graph[], char Edge1, char Edge2, int weight) {                 //O(1)
    graph[Edge1].emplace_back(make_pair(Edge2, weight));                                            //O(1)
    graph[Edge2].emplace_back(make_pair(Edge1, weight));                                            //O(1)
}

int main() {

    vector<pair<char, int>> graph[EDGES];                                                           //O(1)
    int NumOfFiles = 1, numVer = 0, TimeToBeat = 0;                                               //O(1)
    while (true) {                                                                                  //O(N)   N is number of files
        ifstream file("P2_test" + to_string(NumOfFiles) + ".txt");                                  //O(N)

        if (!file.is_open()) {                                                                      //O(1)    
            break;                                                                                  //O(1)
        }
        numVer = -1;                                                                              //O(1)
        string line;                                                                                //O(1)
        int gCount = 0, tCount = 0, sizeOfGraphData = 0;                                            //O(1)
        EdgesAndWeight* g = new EdgesAndWeight;                                                     //O(1)
        EdgesAndTime* t = new EdgesAndTime;                                                         //O(1)
        while (getline(file, line)) {                                                               //O(N) N is number of lines
            if (line[0] == 'V') {                                                                   //O(1)
                for (int i = 0; i < line.size(); ++i) {                                             //O(N) N is line size
                    if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z')) { //O(1)
                        numVer++;                                                                 //O(1)
                    }
                }
            }

            if (line[0] == 'E') {                                                                   //O(1)
                for (int i = 0; i < line.size(); i++) {                                             //O(N) N is line size
                    if (line[i] == '(' || line[i] == ')') {                                         //O(1)
                        sizeOfGraphData++;                                                          //O(1)
                    }
                }
                sizeOfGraphData /= 2;                                                               //O(1)
                g = new EdgesAndWeight[sizeOfGraphData];
                for (int i = 0; i < line.size(); i++) {                                             //O(N) N is line size
                    if (line[i] == '(') {                                                           //O(1)
                        g[gCount].Edge1 = line[i + 1];                                              //O(1)
                        g[gCount].Edge2 = line[i + 3];                                              //O(1)
                        i += 4;                                                                     //O(1)
                        gCount++;                                                                   //O(1)
                    }
                }
            }
            if (line[0] == 'W') {                                                                   //O(1)
                gCount = 0;                                                                         //O(1)
                string num = "";                                                                    //O(1)
                for (int i = 0; i <= line.size(); i++) {                                            //O(N) N is line size
                    if (line[i] >= '0' && line[i] <= '9') {                                         //O(1)
                        if (line[i] != ',' || line[i] != '}') {                                     //O(1)
                            num += line[i];                                                         //O(1)
                        }
                    }
                    else {
                        if (num != "") {                                                            //O(1)
                            int temp = stoi(num);                                                   //O(1)
                            g[gCount].weight = temp;                                                //O(1)
                            gCount++;                                                               //O(1)
                        }
                        num = "";                                                                   //O(1)
                    }
                }
            }
            if (line[0] == 't') {
                t = new EdgesAndTime[numVer - 1];                                                 //O(1)
                tCount = 0;                                                                         //O(1)
                string num = "";                                                                    //O(1)
                for (int i = 0; i <= line.size(); i++) {                                            //O(N) N is line size
                    if (line[i] == '(') {                                                           //O(1)
                        t[tCount].Edge = line[i + 1];                                               //O(1)
                    }
                    if (line[i] >= '0' && line[i] <= '9') {                                         //O(1)
                        if (line[i] != ',' || line[i] != '=') {                                     //O(1)
                            num += line[i];                                                         //O(1)
                        }
                    }
                    else {
                        if (num != "") {                                                            //O(1)
                            t[tCount].DeliveryTime_t = stoi(num);                                   //O(1)
                            tCount++;                                                               //O(1)
                        }
                        num = "";                                                                   //O(1)
                    }
                }
            }
            if (line[0] == 'T') {
                string num = "";                                                                    //O(1)
                for (int i = 0; i <= line.size(); i++) {                                            //O(N) N is length of line
                    if (line[i] >= '0' && line[i] <= '9') {
                        if (line[i] != ',' || line[i] != '=') {                                     //O(1)
                            num += line[i];                                                         //O(1)
                        }
                    }
                    else {
                        if (num != "") {                                                            //O(1)
                            TimeToBeat = stoi(num);                                                 //O(1)
                        }
                        num = "";                                                                   //O(1)
                    }
                }
            }
        }

        for (int i = 0; i < sizeOfGraphData;i++) {                                                  //O(N) N is size of graph
            addEdge(graph, g[i].Edge1, g[i].Edge2, g[i].weight);                                    //O(1)
        }

        vector<bool> visited(EDGES, false);                                                         //O(1)
        vector<char> path;                                                                          //O(1)
        vector<char> minPath;                                                                       //O(1)
        int minWeight = INT_MAX, totalWeight = 0;                                                   //O(1)

        FindHamiltonianCircuit(graph, visited, path, g[0].Edge1, minWeight, totalWeight, minPath, t, numVer - 1, numVer); //O(1)

        if (minWeight <= TimeToBeat) {                                                              //O(1)
            cout << "For Test Case " << NumOfFiles << "\nHamiltonian Circuit: ";                    //O(1)
            for (char i : minPath)                                                                  //O(N) N is size of path
                cout << i << " ";                                                                   //O(1)
            cout << minPath[0] << endl;                                                             //O(1)
            cout << "Weight: " << minWeight << endl;                                                //O(1)
        }
        else {
            cout << "For Test Case " << NumOfFiles << "\nNO FEASIBLE CIRCUIT" << endl;              //O(1)
        }

        file.close();                                                                               //O(1)
        NumOfFiles++;                                                                               //O(1)
        cout << endl;                                                                               //O(1)
    }
    return 0;
}

