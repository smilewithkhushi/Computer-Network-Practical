#include<iostream>
#include<iomanip>
using namespace std;

int findMinVertex(int distance[], bool Tset[], int size) // finding minimum distance
{
    int minVertex=-1;

    for(int k=0;k<size;k++) 
    {
        if(Tset[k]==false && (minVertex==-1 || distance[k]<distance[minVertex]))      
        {
            minVertex=distance[k];
        }
    }
    return minVertex;
}

void DijkstraAlgo(int graph[100][100],int src, int size) // adjacency matrix 
{
    int distance[size]; // // array to calculate the minimum distance for each node                             
    bool visited[size];// boolean array to mark visited and unvisited for each node
     
    for(int k = 0; k<size; k++)
    {
        distance[k] = INT_MAX;
        visited[k] = false;    
    }//set all the values suitably
    
    distance[src] = 0;   // Source vertex distance is set 0               
    
    for(int k = 0; k<size-1; k++){
        int minVertex=findMinVertex(distance, visited, size); //minimum distance / vertex
        visited[minVertex]=true;

        for(int j = 0; j<size; j++)                  
        {
            if (graph[minVertex][j]!=0 && !visited[j]){
                int dist= distance[minVertex]+graph[minVertex][j];
                if (dist<distance[j]){
                    distance[j]=dist;
                }
            }
            // updating the distance of neighbouring vertex
        }
    }
    
    cout<<"Vertex\t\tDistance from source vertex"<<endl;
    for(int k = 0; k<size; k++){ 
        char str=65+k; 
        cout<<str<<"\t\t"<<distance[k]<<endl;
    }
}


void input(int A[100][100], int size){
	cout<<"-> Enter the Adjacency Matrix for the graph here : "<<endl;
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			cin>>A[i][j];
		}
	}	 
}

int main()
{
	cout << endl<< "\t ** PROGRAM TO IMPLEMENT DIJKSTRA ALGORITHM  ** " << endl << endl;
    int size;
	cout<<"-> Enter the size of the graph : ";
	cin>>size;
	int graph[100][100];
	input(graph, size);
    DijkstraAlgo(graph,0, size);
    return 0;                           
}