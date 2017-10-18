// Raul Martinez
// raul.martinez01@utrgv.edu

#include <iostream>
#include <string>
#include <fstream>
#include "directedGraph.h"

using namespace std;

int main()
{
	directedGraph graph;
	int weight = 0;
	int matrix[n][n] = { 5, 8, 3, 3, 3, 2, 4, 9, 3, 3, 2, 8, 2, 2, 7, 1 };

	// adds vertices
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			graph.addVertex(matrix[r][c], weight, r, c);

			++weight;
		}
	}

	// prints out input graph
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << " ";
		}

		cout << endl;
	}

	cout << endl;

	// solves rocky
	graph.rocky(matrix);

	return 0;
}