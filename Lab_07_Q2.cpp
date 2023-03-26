// Aditya Rajesh Bawangade 
// 2103111
// including header file for convinience
#include <bits/stdc++.h>
// using namespace std for convinience;
using namespace std;
int main(){
    // getting the user inputs
    string name;
    cout<<"Enter the filename: ";
    cin>>name;
    int vertexCount;
    cout<<"Enter the number of vertices you want in the graph: ";
    cin>> vertexCount;
    float p;
    cout<<"Enter a valid probability value for having an edge between any two vertices: ";
    cin>>p;
    int prob = p*100;
  
   
    int lim = vertexCount;
    // opening the file
    fstream myfile(name);
    
        for(int i = 0 ; i < lim; i++){
            for(int j = 0 ; j < lim ; j++){
                float a = float(rand()%100);
                // writing a 1 only when random number is less than the prob value
                if(a<prob){
                    myfile<<1<<" ";
                }
                // else writing 0
                else if(a>=prob){
                    myfile<<0<<" ";
                }
            }
            myfile<<"\n";
        }
        // closing the file;
    myfile.close();
    return 0;
}