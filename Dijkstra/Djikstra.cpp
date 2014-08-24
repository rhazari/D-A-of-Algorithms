#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int count = 100;		//count of the number of nodes to be iterated
int prev[100];

// Function to find the distance between any two nodes
int min_dist(int node1, int node2)
{
	int d;
	if (node1 > node2)
		d = (node1 - node2) + pow((node1-node2+3),2) + 5*node2;
	else
		d = (node2 - node1) + pow((node1-node2+3),2) + 5*node2;
	
	return d;
}

//Function to define the updated array
int *new_arr(int *arr2, int num)
{
	for(int j = 0; j < count; j++)
	{
		if (num == *(arr2+j))
		{
			for(int k = j; k < count; k++)
			{
				*(arr2+k) = *(arr2+k+1);
			}
		}
	}
	count--;		//decreasing the count of the nodes to be iterated
	return arr2;
}

//Prints the shortest path from the source to dest.
void printPath(int dest) {
	if (prev[dest] != -1)
		printPath(prev[dest]);
	cout << dest << "\t";
}

int main()
{
	int shortest[100], w, *arr, total_nodes = 100;
	shortest[0] = 0;
	
	int V[100]; 			//all the 100 nodes

	for (int i = 0; i < total_nodes; i++)
	{
		V[i] = i;
	}
	
	int min_cost = 0;		//the minimum cost path 
	
	int W[100], index = 0;		//All the confirmed nodes		
	W[0] = 0;			//Initializing the 1st confirmed node in array W
	index++;

	arr = new_arr(V,W[0]);
	total_nodes--;
	
	for (int j = 0; j < total_nodes; j++)
	{	
		prev[j] = -1;
		shortest[*(arr+j)] = min_dist(0,*(arr+j));
	}
		
	while (index != 100)
	{
		int ptr;
		int min_distance = 50001;

		for (int u = 0; u < total_nodes; u++)
		{	
			ptr = *(arr+u);
			if ( shortest[ptr] < min_distance)
			{
				
				min_distance = shortest[ptr];
				w = ptr;
			}
		}

		//Adding w to W
		W[index] = w;		//Inserting into the confirmed node list
		index++;		//Index counter for the confirmed node list
		total_nodes--;		//Decrementing the total nodes left to iterate 
		arr = new_arr(arr,w);	//The updated array of unconfirmed nodes
	

		//Update the shortest distance to the remaining vertices
		for(int v = 0; v <total_nodes; v++)
		{
			ptr = *(arr+v);
			if((shortest[w] + min_dist(w,ptr)) < shortest[ptr] )
			{
				shortest[ptr] = shortest[w] + min_dist(w,ptr);
				prev[ptr] = w;
			}
		}

	}

	//Display the results
	cout << "\n";
	cout<<"The shortest cost path from 0 to 99"<<"\n";
	cout<<shortest[99]<<"\n";
	cout<<"\n";
	cout << "Path to 99"<<"\n";
	printPath(99);
	cout << "\n";

	return 0;
	
}


