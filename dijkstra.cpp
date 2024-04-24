// A C++ program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph

#include <limits.h>
#include <stdio.h>
#include <random>
#include <ctime>
#include <iostream>

// Number of vertices in the graph
#define N 1250

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value as the bigges int value available
	int min = INT_MAX, min_index;

	for (int v = 0; v < N; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance
// array (not used becuse our program isn't interactive
// and it will disrupt our time measures)
void printSolution(int dist[], int n, int src)
{
	printf("Vertex Distance from Source \n");
	std::cout << "\t Sorce vertice: " << src << std::endl;
	for (int i = 0; i < N; i++)
		printf("\t%d \t\t\t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int graph[N][N], int src)
{
	int dist[N]; // The output array. dist[i] will hold the
		     // shortest
		     // distance from src to i

	bool sptSet[N]; // sptSet[i] will be true if vertex i is
			// included in shortest
			// path tree or shortest distance from src to i is
			// finalized

			// Initialize all distances as INFINITE and stpSet[] as
			// false
	for (int i = 0; i < N; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < N - 1; count++) {
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to
		// src in the first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < N; v++)

			// Update dist[v] only if is not in sptSet,
			// there is an edge from u to v, and total
			// weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v]
					&& dist[u] != INT_MAX
					&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	//printSolution(dist, N, src);
}

// Fills our arra-graph with values
void fillArray(int arr[N][N]){

	// Seed the random number generator for unique values each time
	srand(time(0));

	int z;	// chance for a cell of array to be zero

	// Generate random positive numbers and set diagonal elements to 0
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j] = rand() % 101;  // Generate a number from 0 to 100 (inclusive)
			z = rand() % 100;	// Generates a number to z
			if (z > 1 && i != 0) arr[i][j] = 0; 	// In 99 times out of 100 (randomly) sets zero to array cell
			if (i == j) {
				arr[i][j] = 0;  // Set diagonal elements to 0
			}
		}
		// Makes our array symmetrical
		for (int j = 0; j < N; j++){
			arr[j][i] = arr[i][j];
		}
	}

	// Prints array to command line
	/*	
		for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
		std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
		}
		*/	   
}

int main()
{
	// Graph for testing
	/*int graph[N][N] = {
	  { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	  { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	  { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	  { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	  { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	  { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	  { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
	  { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	  { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
	  */

	//Do algorithm more than one time for better measure
	for (int i = 0; i < 10; i++){
		int graph[N][N];
		fillArray(graph);

		for (int j = 0; j < N - 1; j++){
			dijkstra(graph, j);
		}
	}
	return 0;
}
