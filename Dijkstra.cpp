//simulate and implement Dijkstra algorithm for shortest path routing

#include<iostream>
#include<iomanip>
using namespace std;

int miniDist(int distance[], bool Tset[]) // finding minimum distance
{
    int minimum=INT_MAX,ind;
              
    for(int k=0;k<6;k++) 
    {
        if(Tset[k]==false && distance[k]<=minimum)      
        {
            minimum=distance[k];
            ind=k;
        }
    }
    return ind;
}

void DijkstraAlgo(int graph[10][10],int src, int size) // adjacency matrix 
{
    int distance[10]; // // array to calculate the minimum distance for each node                             
    bool Tset[10];// boolean array to mark visited and unvisited for each node
    
     
    for(int k = 0; k<size; k++)
    {
        distance[k] = INT_MAX;
        Tset[k] = false;    
    }
    
    distance[src] = 0;   // Source vertex distance is set 0               
    
    for(int k = 0; k<6; k++)                           
    {
        int m=miniDist(distance,Tset); 
        Tset[m]=true;
        for(int k = 0; k<6; k++)                  
        {
            // updating the distance of neighbouring vertex
            if(!Tset[k] && graph[m][k] && distance[m]!=INT_MAX && distance[m]+graph[m][k]<distance[k])
                distance[k]=distance[m]+graph[m][k];
        }
    }
    cout<<"Vertex\t\tDistance from source vertex"<<endl;
    for(int k = 0; k<6; k++)                      
    { 
        char str=65+k; 
        cout<<str<<"\t\t\t"<<distance[k]<<endl;
    }
}

void input(int A[10][10], int size){
	cout<<"-> Enter the graph here : "<<endl;
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			cin>>A[i][j];
		}
	}	 
}

int main()
{
	cout<<endl<<"\t ** IMPLEMENTING DIJKSTRA ALGORITHM ** "<<endl<<endl;
	int size;
	cout<<"-> Enter the size of the graph : ";
	cin>>size;
	int graph[10][10];
	input(graph, size);
    DijkstraAlgo(graph,0, size);
    return 0;                           
}

