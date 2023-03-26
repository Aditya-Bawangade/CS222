// Aditya Rajesh Bawangade
// 2103111
// 
// Assignment 7
#include<iostream>
#include<stdio.h>
#include<vector>
// using namespace std for convinience
using namespace std;
//Creating a class Node for storing the vertex distance pair in the Min Heap
class Node{
		// private data members
        int vertex;
        int distance;
	// public data members
    public:
		// intializing the default constructor
        Node(){}
		// initializing constructor
        Node(int v, int d){
            vertex = v;
            distance = d;
        }
		// initialising the destructor
        ~Node(){}
		// Comparison function for comparison between nodes for Min heap
        bool compare(Node b){
            return (this->distance < b.distance);
        }
		// function to get the distance
        int getDistance(){
            return this->distance;
        }
		// function to get the vertex
        int getVertex(){
            return this->vertex;
        }
		// function to print the distance
        void PrintDistance(){
            printf("%d", distance);
        }
		// Function to print the vertex
        void PrintVertex(){
            printf("%d", vertex);
        }
		// Function to update the distance
        void updateDistance(int d){
            this->distance = d;
        }

};
// creating a min heap for using in the dijkstra's algorithm
class MinHeap{
	// private data members 
        Node *arr;
        int maxsize;
        int currentsize;
    public:
	// initialising the constructor
        MinHeap(int ms){
            currentsize = 0;
            maxsize = ms;
            arr = new Node[ms];
        }
		// intializing the copy constructor as we have a dynamically allocated array, the default constructor won't do
        MinHeap(const MinHeap& other){
            maxsize = other.maxsize;
            currentsize = other.currentsize;
            arr = new Node[maxsize];
            for(int i = 0 ; i < maxsize ; i++){
                arr[i] = other.arr[i];
            }
        }
		// Destructor
        ~MinHeap(){
            delete[] arr;
        }
		// function for pushing the node to minhea[]
        void push(Node a){
            if(currentsize == maxsize){
                printf("Cannot push any more elements! MinHeap is full:");
                return;
            }
            currentsize++;
            int i = currentsize -1 ;
            arr[i] = a;
			// maintaining the heap property 
            while(i != 0 && arr[i].compare(arr[(i-1)/2])){
                Node trash = arr[i];
                arr[i] = arr[(i-1)/2];
                arr[(i-1)/2] = trash;
                i = (i-1)/2;
            }
            return;
        }
		// For printing the distance array of the Minheap's Nodes
        void PrintDistanceArr(){
            if(currentsize == 0){
                cout<<"null";
                return;
            }
            for(int i = 0 ; i < currentsize ; i++){
                arr[i].PrintDistance();
                printf(" ");
            }
            return;
        }
		// For printing the Vertices of the Minheap's Nodes
        void PrintVertexArr(){
            if(currentsize == 0){
                cout<<"null";
                return;
            }
            for(int i = 0 ; i < currentsize ; i++){
                arr[i].PrintVertex();
                printf(" ");
            }
            return;
        }
		// A function to get the lowest node in the Min heap
        Node getTop(){
            Node trash = arr[0];
            return trash;
        }
		// Minheapify function to maintiain the heap property
        void Minheapify(int i){
            int l = 2*i+1;
            int r = 2*i+2;
            int smallest = i;
            if(l < currentsize && arr[l].compare(arr[smallest])){
                smallest = l;
            }
            if(r < currentsize && arr[r].compare(arr[smallest])){
                smallest = r;
            }
            if(smallest != i){
                Node temp = arr[i];
                arr[i] = arr[smallest];
                arr[smallest] = temp;
                Minheapify(smallest);
            }
        }
		// A function to check if the node already exists
        bool nodeExists(Node a){
            int v = a.getVertex();
            for(int i = 0 ; i < currentsize ; i++){
                if(arr[i].getVertex() == v){
                    return true;
                }
            }
            return false;
        }
		// A function to update the Node distance;
        void updateNodeDist(Node &a){
            bool flag = nodeExists(a);
            if(flag==0){
                return;
            }
            int v = a.getVertex();
            int d = a.getDistance();
            for(int i = 0 ; i < currentsize ; i++){
                if(arr[i].getVertex() == v){
                    arr[i].updateDistance(d);
                    while(i!=0 && arr[i].compare(arr[(i-1)/2])){
                        Node trash = arr[i];
                        arr[i] = arr[(i-1)/2];
                        arr[(i-1)/2] = trash;
                        i = (i-1)/2;
                    }
                }
                return;
            }


        }
		// Function to check whether the Minheap is empty or not
        bool empty(){
            if(currentsize > 0){
                return false;
            }
            return true;
        }
		// Function to pop the smallest node from the heap
        void pop(){
            if(currentsize == 0){
                return;
            }
            if(currentsize == 1){
                currentsize--;
                return;
            }
            arr[0] = arr[currentsize - 1];
            currentsize--;
            int i = 0;
            Minheapify(i);
            return;
        }
};

struct neighborList // structure of a node in the adjacency list
{
	int neighborIndex;		   // index of the neighbor
	int weight;				   // weight of the edge
	struct neighborList *next; // next pointer
};

class graph
{
	int vCount;				// vertex count
	int **adjMatrix;		// adjacency matrix
	neighborList **adjList; // adjacency list
	int edgeCount;			// edge count
	int superSource;		// source vertex for Dijkstra's Algorithm
	int *predListDijkstra;	// predecessor list from Dijkstra's Algorithm
	int **predListFW;		// predecessor list from Floyd-Warshall Algorithm

	int *distListDijkstra; // distance details from Dijkstra's Algorithm
	int **distListFW;	   // distance details from FW Algorithm

public:
	graph(int vertexCount)
	{
		vCount = vertexCount;
		edgeCount = 0;
		allocateMem();
	}

	void allocateMem() // allocates memory for the necessary data structures
	{
		adjMatrix = new int *[vCount];
		adjList = new neighborList *[vCount];
		for (int i = 0; i < vCount; i++)
		{
			adjMatrix[i] = new int[vCount];
			adjList[i] = NULL;
		}

		predListDijkstra = new int[vCount];
		distListDijkstra = new int[vCount];
		predListFW = new int *[vCount];
		distListFW = new int *[vCount];
		for (int i = 0; i < vCount; i++)
		{
			predListFW[i] = new int[vCount];
			distListFW[i] = new int[vCount];
		}
	}
	void readAdjMatrix(FILE *fp) // reads adjacency matrix from the file
	{
		for (int i = 0; i < vCount; i++)
			for (int j = 0; j < vCount; j++)
				fscanf(fp, "%d", &adjMatrix[i][j]);
	}

	void printAdjMatrix() // prints adjacency matrix
	{
		for (int i = 0; i < vCount; i++)
		{	//printing the list using nested loops
			for (int j = 0; j < vCount; j++)
			{	
				printf("%d", adjMatrix[i][j]);
				printf(" ");
			}
			printf("\n");
		}
	}
	void loadAdjList() // set up the adjacency list
	{	
		
		for (int k = 0; k < vCount; k++)
		{	//initializing the list with row numbered heads of the neighborlists
			neighborList* trash;
			trash = new neighborList;
			trash->neighborIndex = k+1;
			trash->weight = 0;
			trash->next = NULL;
			adjList[k] = trash;
			
		}
		for (int i = 0; i < vCount; i++)
		{
			for (int j = 0; j < vCount; j++)
			{
				if (adjMatrix[i][j] != 0)
				{	//creating a new object
					neighborList *temp;
					temp = new neighborList;
					temp->next = NULL;
					temp->neighborIndex = j + 1;
					temp->weight = adjMatrix[i][j];
					//iterating through the list
					neighborList* it = adjList[i];
					while(it->next != NULL){
						it = it->next;
					}
					//appending to the list
					it->next = temp;
					
				}
			}
		}
	}

	void printAdjList() // prints the adjacency list
	{	
		//printing the adjacency list using nested for loops
		for (int i = 0; i < vCount; i++)
		{	
			cout<<adjList[i]->neighborIndex<<"->";
			neighborList *temp = adjList[i];
			// printing the lists corresponding to the indices
			while (temp != NULL)
			{
				cout << "("<<temp->neighborIndex <<","<< temp->weight<<")->";
				temp = temp->next;
			}
			cout<<"NULL";
			cout << "\n";
			
		}
	}

	int countEdge() // count the number of edges in the graph
	{
		for (int i = 0; i < vCount; i++)
		{
			for (int j = 0; j < vCount; j++)
			{	//counting the edges for non-zero values in the adj matrix
				if (adjMatrix[i][j] != 0)
				{
					edgeCount++;
				}
			}
			
		}
		return edgeCount;
	}

	void runDijkstra(int startVertex) // Run Dijkstra's Algorithm with the given startVertex and load the associated data structures with necessary information
	{	
		
		MinHeap Qq(81);
		for(int i = 0 ; i < vCount ; i++){
			distListDijkstra[i] = INT16_MAX;
		}
		distListDijkstra[startVertex-1] = 0;
		predListDijkstra[startVertex-1] = 0;
        Node trash(startVertex-1,0);
		Qq.push(trash); //Syntax of pair<distance of vertex from source, vertex>

		while(!Qq.empty()){
            Node temp = Qq.getTop();
            
			int v = temp.getVertex();
			int d = temp.getDistance();

			Qq.pop();

            
			for(int i = 0 ; i < vCount ; i++){
				if(adjMatrix[v][i] != 0){
					int w = adjMatrix[v][i];
					if(d+w<distListDijkstra[i]){
						distListDijkstra[i] = d+w;
						predListDijkstra[i] = v+1;
                        Node temp2(i,d+w);

                        Qq.push(temp2);

					}
				}	
			} 
            
		}
		cout<<"The shortest path from vertex "<<superSource<<" to all the other vertices are as follows: ";
		for(int i = 0 ; i < vCount ; i++){
			cout<<predListDijkstra[i]<<" ";
		}
		
	}
	void runFW() // Run Floyd-Warshall Algorithm and fill in the associated data structures with necessary information
	{
		for(int i = 0 ; i < vCount ; i++){
			for(int j = 0 ; j < vCount ; j++){
				if(adjMatrix[i][j] == 0 && (i!=j)){
					distListFW[i][j] = INT16_MAX;
				}
				else{
					distListFW[i][j] = adjMatrix[i][j];
					}
				if(i==j){
					predListFW[i][j] = 0;
					continue;
				}
				predListFW[i][j] = i+1;
			}
		}
		// 
		for(int k = 0 ; k < vCount ; k++){
			for(int i = 0 ; i < vCount ; i++){
				for(int j = 0 ; j < vCount ; j++){
					if(distListFW[i][j] > distListFW[i][k] + distListFW[k][j]   ){
						distListFW[i][j] = distListFW[i][k] + distListFW[k][j];
						predListFW[i][j] = predListFW[k][j];
					}
				}
			}
		}
		for(int i = 0 ; i < vCount ; i++){
			for(int j = 0 ; j < vCount ; j++){
				cout<< distListFW[i][j]<<" ";
			}
			cout<<endl;
		}
		return;
		
	}
	void printDijkstraPathTo(int targetVertex) /*superSource->......->tergetVertex     lengthOfPath*/
	{	
		runDijkstra(superSource);
		vector<int> ans;
		ans.push_back(targetVertex);
		targetVertex = targetVertex - 1;
		int i = targetVertex;
		while(i<=vCount){
			if(predListDijkstra[i]==superSource){
				ans.push_back(predListDijkstra[i]);
				break;
			}
			ans.push_back(predListDijkstra[i]);
			i = predListDijkstra[i] - 1;
			
		}
		for(int j= ans.size() - 1;j >= 0 ;j--){
			if(j==0){
				cout<<ans[j];
				break;
			}
			cout<<ans[j]<<"->";
		}
		cout<<"  Weight of the path: "<<distListDijkstra[targetVertex];
		return;
	}
	void printFWPathBetween(int sourceVertex, int targetVertex) /*sourceVertex->......->targetVertex     lengthOfPath*/
	{
		runFW();
		vector<int> ans;
		ans.push_back(targetVertex);
		targetVertex--;
		sourceVertex--;
		int i = targetVertex;
		
		while(i<=vCount){
			if(predListFW[sourceVertex][i] == sourceVertex+1){
				ans.push_back(predListFW[sourceVertex][i]);
				break;
			}
			ans.push_back(predListFW[sourceVertex][i]);
			i = predListFW[sourceVertex][i] - 1;
		}
		for(int j= ans.size() - 1;j >= 0 ;j--){
			if(j==0){
				cout<<ans[j];
				break;
			}
			cout<<ans[j]<<"->";
		}
		cout<<" Weight of the path is: "<<distListFW[sourceVertex][targetVertex];
		return;

	}
	void SetSource(int source){
		superSource = source;
	}
	void testDijkstra(){
		while(true){
			int a;
			cout<<"Please enter the target vertex for the shortest path from the source or press 101 to exit: ";
			cin>> a;
			int b = a;
			if(b==101){
				break;
			}
			printDijkstraPathTo(b);
			cout<<"\n";
		}
	}
	void testFW(){
		while(true){
			int a; int b;
			cout<<"Enter the source and the target vertices seperated by a space or enter 101 in both fields to exit: ";
			cin>>a>>b;
			
			int c = a;
			int d = b;
			if(c==101 && d==101){
				break;
			}
			printFWPathBetween(c,d);
			cout<<"\n";
		}
	}

} *myGraph;

int main(int argc, char **argv)
{
	int vertexCount;
	int source = 1;
	FILE *fp = fopen(argv[1], "r");
	fscanf(fp, "%d", &vertexCount);
	myGraph = new graph(vertexCount); // initialize vertex count from the file
	myGraph->readAdjMatrix(fp);
	fclose(fp);
	printf("There are %d edges in the graph \n", myGraph->countEdge());
	myGraph->SetSource(source);
	myGraph->printAdjMatrix();
	myGraph->loadAdjList();
	printf("The adjacency list representation is as follows:\n");
	myGraph->printAdjList();
	int choice;
	while(true){
		printf("Please enter 1 for testing Dijkstra's algorithm or 2 for testing Floyd Warshall Algorithm or enter 101 to exit: ");
		cin>>choice;
		int a = choice;
		if(a == 1){
			myGraph->testDijkstra();
		}
		if(a == 2){
			myGraph->testFW();
		}
		if(a == 101){
			break;
		}
	}
	
}

