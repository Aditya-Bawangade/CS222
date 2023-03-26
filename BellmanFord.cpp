#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void BellmannFord(vector<vector<int>> gp, int source){
    vector<int> ans(gp.size());
    for(int i = 0 ; i < gp.size(); i++){
        ans[i] = 99999;
    }
    ans[source] = 0;
    
    for(int i = 0 ; i < ans.size(); i++){
        for(int a = 0 ; a < ans.size() ; a++){
            for(int b = 0 ; b < ans.size() ; b++){
                if(ans[a] + gp[a][b] < ans[b]){
                    ans[b] = ans[a] + gp[a][b];
                }
            }
          
        }
    }
   for(int i = 0; i < ans.size() ; i++){
        cout<<ans[i]<<" ";
    }
}
int main(){
    vector<vector<int>> gp = {{0, 2, 4, 5, 3},{4, 0, 1, 9, 1},{1, 2, 0, 3, 8},{4, 8, 9, 0, 5},{1, 1, 5, 8, 0}};
    
    BellmannFord(gp,3);
    return 0;
}