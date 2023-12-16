/*
- Luís Henrique Dantas - 13782369
*/

#include <iostream>
#include <bits/stdc++.h>
#include <climits>

#define VIS 1
#define NAOVIS 0
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
};


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int nv;
    int u, v, w;

    cin >> nv;

    Graph Circuit(nv);

    //connect vertices
    int i;
    cin >> i;

    for(; i > 0; i--){
        cin >> u >> v >> w;
        Circuit.connect(u,v,w);
    }
    
    cout << Circuit.MST();

    return 0;
}