/*
- Luís Henrique Giorgetti Dantas - 13782369
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <unordered_set>
#include <cstdint>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;

#define INFINITY INT_MAX

// Fill Matrix with value
void MatrixSet(vector<vector<long long>>& matrix, int initialValue = 0){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            matrix[i][j] = initialValue;
        }
    }
}

//returns true if ith bit in subset is set to 1
bool inSubset(long long subset, int i){
    return ((subset & (static_cast<long long>(1) << i)) != 0);
}

class Graph{
    private:   
        vector<vii> AdjList;
        bool directed;
        int numVertices;

        // Setup MEMO table for TSP
        void Setup(vector<vector<long long>>& MEMO, int start){

            for(int i = 1; i < MEMO.size(); i++){
                if(i == start) continue;

                MEMO[i][1 << start | 1 << i] = getDistance(start, i);   // 1 << start: sets the start node bit to 1 on the path
                                                                        // 1 << i: sets the ith bit to 1 on the path
                                                                        // Essentially, 1 << start | 1 << i represents the path going through only those 2 nodes
                                                                        // Example: start = 1, i = 2 : 
                                                                        //          (1 << 1 | 1 << 2) = 110 (in binary)
                                                                        //          that means that the nodes 1 and 2 are visited in the path
            }

        }

        // Auxiliar function to generate subpaths with a specified number os visited nodes (bits set to 1)
        void recursiveGeneration(long long subpath, int at, int visits, unordered_set<long long>& subpaths) {
            //if subpath has no visited nodes
            if (visits == 0)
                subpaths.insert(subpath);
            else {
                
                for (int i = at; i <= this->numVertices; i++) {
                    // Switch ith bit
                    subpath = subpath | (static_cast<long long>(1) << i);

                    recursiveGeneration(subpath, i + 1, visits - 1, subpaths);

                    // Backtrack, and switch ith bit
                    subpath = subpath & ~(static_cast<long long>(1) << i);
                }
            }
        }


        // Generates subpaths with a specified number os visited nodes (bits set to 1)
        // Returns subpaths in a set
        unordered_set<long long> generateSubsets(int visits){
            unordered_set<long long> subpaths;
            
            recursiveGeneration(0, 1, visits, subpaths);
    
            return subpaths;
        }

        void SolveMEMO(vector<vector<long long>>& MEMO, int start){
            //Each number's binary representation is a path
            unordered_set<long long> paths;

            //for each number of nodes in path
            for(int i = 3; i <= this->numVertices; i++){

                //for each subpath generated
                for(long long subpath: generateSubsets(i)){

                    //if start node is not in subpath, subpath is invalid
                    if(!inSubset(subpath, start)) continue;

                    //evaluate possible next nodes 
                    for(int next = 1; next <= this->numVertices; next++){

                        //if next node is not part of subset
                        if(next == start || !inSubset(subpath, next)) continue;

                        long long state = subpath ^ (static_cast<long long>(1) << next);    //path excluding node being evaluated as next 
                        long long minDistance = INFINITY;

                        //for possible end nodes
                        for(int end = 1; end <= this->numVertices; end++){
                            if(end == start || end == next || !inSubset(subpath, end))  continue;

                            long long newDistance = MEMO[end][state] + getDistance(end,next);

                            if(newDistance < minDistance)
                                minDistance = newDistance;

                        }
        
                        MEMO[next][subpath] = minDistance;
                    }
                }
            }
        }

        // Returns the shortest distance for a complete path, or -1 if not possible
        long long findMinCost(vector<vector<long long>> MEMO){
            //complete path is a path where, for every vertex i of the graph, the ith bit is set to 1
            long long completePath = (1 << this->numVertices+1) - 2;

            long long minDistance = INFINITY;

            //for all possible end nodes for a full path, check the shortest way to reach the node
            for(int i = 1; i <= this->numVertices; i++){
                
                if(MEMO[i][completePath] < minDistance)
                    minDistance = MEMO[i][completePath];
            }

            //if possible return the distance, else return -1
            return ((minDistance < INFINITY) ? minDistance:-1);
        }

    public:
        Graph(int nv, bool directed = false){
            numVertices = nv;
            this->directed = directed;
            AdjList.assign(nv+1, vii());
        }

        bool connect(int u, int v, int w){
            AdjList[u].push_back(ii(v, w));
            if(!(this->directed))
                AdjList[v].push_back(ii(u, w));
            return true;
        }

        long long getDistance(int u, int v){
            for(ii uv: AdjList[u]){
                if(uv.first == v) return uv.second;
            }

            return INFINITY;
        }

        long long TSP(int start = 1){
            //2D array MEMO for DP
            /*
            i = end node of path
            j = path (look at binary representation) EX: 14 is the path 1110, or "path going through nodes 1, 2 and 3"
            */
            vector<vector<long long>> MEMO(this->numVertices+1, vector<long long>(pow(2,this->numVertices+1)));

            //Fill MEMO with INFINITY
            MatrixSet(MEMO, INFINITY);

            //Calculate distance for nodes adjacent to start node
            Setup(MEMO, start);

            //Solve the TSP Problem, filling MEMO table with the shortest distance for each path
            SolveMEMO(MEMO, start);

            //Return the shortest distance for a complete path
            return findMinCost(MEMO);

        }

};


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int nv, na;
    int u, v, w;

    cin >> nv >> na;

    Graph Lakes(nv);

    //connect vertices

    for(int i = 0; i < na; i++){
        cin >> u >> v >> w;
        Lakes.connect(u,v,w);
    }

    //Solve TSP on Lakes Graph
    cout << Lakes.TSP();

    return 0;
}