/*
- Luís Henrique Dantas - 13782369
*/

#include <iostream>
#include <bits/stdc++.h>
#include <climits>
#include <stack>
#include <ranges>

#define NIL -1
#define INF INT_MAX

using namespace std;

typedef pair<int, int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;

class UnionFind{
    private:
        vector<int> p;
        vector<int> rank;

    public:
        UnionFind(int n){
            rank.assign(n, 0); p.assign(n, 0);
            for(int i = 0; i < n; i++)
                p[i] = i;
        }

        int findSet(int i){
            if(p[i] != i)
                p[i] = findSet(p[i]);
            return p[i];
        }

        bool isSameSet(int i, int j){
            return (findSet(i) == findSet(j));
        }

        void unionSet(int i, int j){
            if(!isSameSet(i, j)){
                int x = findSet(i);
                int y = findSet(j);

                if(rank[x] > rank[y])
                    p[y] = x;
                else{
                    p[x] = y;
                    if(rank[x] == rank[y])
                        rank[x] = rank[y] + 1;
                }
            }
        }
};

class Graph{
    private:   
        vector<vii> AdjList;
        bool directed;
        int numVertices;

        void FindSSC(int vertex, int sccs[], int disc[], int low[], bool stackControl[], stack<int> *processed){
            static int time = 0;

            //initialize values
            disc[vertex] = ++time;
            low[vertex] = time;
            stackControl[vertex] = true;
            processed->push(vertex);
            

            //go through vertices
            for(ii i: AdjList[vertex]){
                int adjVertex = i.first;

                if(disc[adjVertex] == NIL){
                    FindSSC(adjVertex, sccs, disc, low, stackControl, processed);
                    low[vertex] = min(low[vertex], low[adjVertex]);
                }
                else if(stackControl[adjVertex])
                    low[vertex] = min(low[vertex], disc[adjVertex]);
            }

            //when the head node of SCC is found, pop the SCC
            int popped = 0;
            static int sccCounter = 1;

            if(low[vertex] == disc[vertex]){
                //remove from stack until we find vertex
                while(true){
                    popped = processed->top();
                    processed->pop();
                    stackControl[popped] = false;
                    sccs[popped] = sccCounter;

                    if(popped == vertex) break;
                }
                sccs[0] = sccCounter;
                sccCounter++;
            }
        }

    public:
        Graph(int nv, bool directed = false){
            numVertices = nv;
            this->directed = directed;
            AdjList.assign(nv+1, vii());
        }

        bool connect(int u, int v, int w = 0){
            AdjList[u].push_back(ii(v, w));
            if(!(this->directed))
                AdjList[v].push_back(ii(u, w));
            return true;
        }

        long long MST(){
            long long treeWeight = 0;

            UnionFind disjSets(numVertices);

            //vector of <weight, <u,v>>
            vector<iii> edges;

            //fill auxiliar vector "edges"
            int iCounter = 0;
            for(auto i: AdjList){
                for(auto j: AdjList[iCounter]){
                    edges.push_back(make_pair(j.second, ii(iCounter, j.first)));
                }
                iCounter++;
            }

            //sort vector by weight
            sort(edges.begin(), edges.end());

            //kruskal algorithm
            int selectedEdges = 0;

            vector<iii>::iterator it;
            for(it = edges.begin(); it!=edges.end(); it++){
                int w = it->first;
                int u = it->second.first;
                int v = it->second.second;

                //these account for the graph offset (there is no vertice 0)
                int uSet = disjSets.findSet(u-1); 
                int vSet = disjSets.findSet(v-1);

                if(uSet != vSet){
                    selectedEdges++;
                    treeWeight += w;
                    disjSets.unionSet(uSet, vSet);
                    if(selectedEdges == numVertices - 1) return treeWeight;
                }
            }

            return -1;
        }

        int* SCC(){
            //discovery time of vertices
            int *disc = new int[numVertices+1];
            //least discovery time
            int *low = new int[numVertices+1];
            //connected ancestors
            stack<int> *processed = new stack<int>();
            //stores if vertice is in stack
            bool *stackControl = new bool[numVertices+1];
            //stores SCCs, index 0 stores the number of SCCs
            int *sccs = new int[numVertices+1];

            for(int i = 1; i<=numVertices; i++){
                disc[i] = NIL;
                low[i] = NIL;
                sccs[i] = NIL;
                stackControl[i] = false;
            }

            for(int i = 1; i <= numVertices; i++)
                if(disc[i] == NIL){
                    FindSSC(i, sccs, disc, low, stackControl, processed);
                }

            return sccs;
        }
};


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int nv;
    int u, v;

    cin >> nv;

    Graph Circuit(nv, true);

    //connect vertices
    int i;
    cin >> i;

    for(; i > 0; i--){
        cin >> u >> v;
        Circuit.connect(u,v);
    }
    
    int *components = Circuit.SCC();

    //print solution
    int temp[nv+1] = {0};
    int counter = 1;

    cout << components[0] << "\n";
    for(int i = 1; i <= nv; i++){
        if(temp[components[i]] == 0) 
            temp[components[i]] = counter++;
        cout << temp[components[i]] << " ";
    }

    return 0;
}