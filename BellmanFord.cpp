#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void BellmannFord(vector<vector<int>> edges, int source, int v){
    vector<int> ans(v);
    for(int i = 0 ; i < v; i++){
        ans[i] = 99999;
    }
    ans[source] = 0;
    for(int i = 0 ; i < v-1; i++){
        for(int a = 0 ; a < edges.size() ; a++){
                int u = edges[a][0];
                int v = edges[a][1];
                int wt = edges[a][2];
                if(ans[u] != 99999 && ans[u] + wt < ans[v]){
                    ans[v] = ans[u] + wt;
                }
        }
    }
    for(int a = 0 ; a < edges.size() ; a++){
                int u = edges[a][0];
                int v = edges[a][1];
                int wt = edges[a][2];
                if(ans[u] != 99999 && ans[u] + wt < ans[v]){
                    printf("There is a negative edge 🙄😏😣");
                    return;
                }
        }

   for(int i = 0; i < ans.size() ; i++){
        cout<<ans[i]<<" ";
    }
}
void BF(int edges[][3], int source, int E, int V){
    int ans[V];
    for(int i = 0 ; i < V ; i++){
        ans[i] = 1e9;
    }
    ans[source] = 0;
    for(int i = 0 ; i < V-1 ; i++){
        for(int j = 0 ; j < E; j++){
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];
            if(ans[u]!=1e9 && ans[u] + wt < ans[v]){
                ans[v] = ans[u] + wt;
            }
        }
    }
    
    for(int j = 0 ; j < E; j++){
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];
            if(ans[u]!=1e9 && ans[u] + wt < ans[v]){
                printf("There is a negative edege!🥱😫");
                return;
            }
    }
    for(int i = 0 ; i < V ; i++){
        printf("%d ", ans[i]);
    }
    
}
int main(){
    int gp[][3] = {{0,1,-1},{0,2,4},{1,2,3},{1,3,2},{1,4,2},{3,2,5},{3,1,1},{4,3,-3}};
    BF(gp,0,8,5);
    return 0;
}