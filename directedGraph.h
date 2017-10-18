// Raul Martinez
// raul.martinez01@utrgv.edu

#include <iostream>
#include <stack>
#include <cmath>
#include <ctime>
#include "minHeap.h"

using namespace std;

const int n = 4;

class directedGraph
{
private:
	class vertex;
	class edge;

	class vertex
	{
	public:
		int data;
		int index;
		vector<edge> adjList;
		vertex * pred;
		double weight;
		
		int row;
		int col;
		bool path;

		vertex(int x)
		{
			data = x;
			weight = 0;
			pred = NULL;
			path = false;
		}
	};
	class edge
	{
	public:
		vertex * start;
		vertex * end;
		double weight;
		edge(vertex * v, vertex * u, double w)
		{
			start = v;
			end = u;
			weight = w;
		}
		edge() {}
	};

	vector<vertex*> vertexList;
	int cost;


public:
	~directedGraph()
	{
		//free all the (dynamically allocated) vertices.
		for (vector<vertex*>::iterator itr = vertexList.begin(); itr != vertexList.end(); itr++)
		{
			delete (*itr);
		}
	}

	//add a new vertex with data value x, weight, row, and column to the graph
	void addVertex(int x, int w, int r, int c)
	{
		vertexList.push_back(new vertex(w));
		vertexList[vertexList.size() - 1]->weight = x;
		vertexList[vertexList.size() - 1]->row = r;
		vertexList[vertexList.size() - 1]->col = c;
	}

	//add a directed edge going from x to y
	void addDirectedEdge(int x, int y, double w)
	{
		vertex * v = vertexList[x];
		vertex * u = vertexList[y];

		edge e(v, u, w);
		v->adjList.push_back(e);
	}

	//add an edge going from x to y; (BOTH SDES)
	void addEdge(int x, int y, double w)
	{
		addDirectedEdge(x, y, w);
		addDirectedEdge(y, x, w);
	}

	// Runs the Dijkstra alogrithm
	void dijkstra(vertex * start)
	{
		minHeap<vertex*> mh;

		// set weights from all vertices to INFINITY
		for (int i = 0; i < vertexList.size(); i++)
		{
			vertexList[i]->weight=INFINITY;
			vertexList[i]->pred = NULL;
		}

		start->weight = 0;

		// Insert vertices into minHeap
		for (vector<vertex*>::iterator itr = vertexList.begin(); itr != vertexList.end(); itr++)
		{
			mh.insert((*itr));
		}

		// Relax edges using minHeap
		while (!mh.empty())
		{
			vertex * v = mh.extractMin();

			for (vector<edge>::iterator itr = v->adjList.begin(); itr != v->adjList.end(); itr++)
			{
				relax(*itr, mh);
			}
		}
	}

	void relax(edge e, minHeap<vertex*> &mh)
	{
		vertex * v = e.start;
		vertex * u = e.end;
		if (v->weight + e.weight < u->weight)
		{
			u->weight = v->weight + e.weight;
			u->pred = v;
			mh.fix(u);
		}
	}

	void shortestPath(int matrix[n][n])
	{
		int x;
		int y = n * n;
		int i = 0;
		stack<vertex*> s;
		int j;
		vertex * v = vertexList[0];
		
		addVertex(y);
		v = vertexList[y];
		
		while (i < y)
		{
			addDirectedEdge(y, i, 0);
			i = i + n;
		}
		
		dijkstra(v);

		x = n - 1;
		vertex * u = vertexList[x];
		while (x < y)
		{
			if (vertexList[x]->weight < u->weight)
				u = vertexList[x];

			x+= n;
		}

		vertex * vv = vertexList[v->data];
		vertex * uu = vertexList[u->data];
		cost = uu->data;

		vv->path = true;

		while (vv->data != uu->data)
		{
			s.push(uu);
			uu->path = true;
			uu = uu->pred;
		}

		for (int i = 0, j = 1; i < n*n; i++)
		{
			if (vertexList[i]->path == true)
				cout << 'o' << " ";
			else
				cout << 'x' << " ";
			
			if (j % n == 0)
			{
				cout << endl;
				j = 1;
			}
			else
				++j;
		}
	}

	void connect(int matrix[n][n])
	{
		int x = n * n;
		vertex * a;

		for (int i = 0; i < vertexList.size(); i++)
		{
			a = vertexList[i];


			int p;
			int totalWeight;
			vertex * connector = NULL;

			// connect up
			p = a->data - 1;
			if (p >= 0 && p < x)
				connector = vertexList[p];
			if (a->col != 0 && matrix[a->row][a->col - 1] == connector->weight)
			{
				totalWeight = abs(a->weight - connector->weight);
				addDirectedEdge(a->data, p, totalWeight);
			}

			// connect down
			p = a->data + 1;
			if (p >= 0 && p < x)
				connector = vertexList[p];
			if (a->col + 1 != n && matrix[a->row][a->col + 1] == connector->weight)
			{
				totalWeight = abs(a->weight - connector->weight);
				addDirectedEdge(a->data, p, totalWeight);
			}
			
			// connect left
			p = a->data - n;
			if (p >= 0 && p < x)
				connector = vertexList[p];
			if (a->row != 0 && matrix[a->row - 1][a->col] == connector->weight)
			{
				totalWeight = abs(a->weight - connector->weight);
				addDirectedEdge(a->data, p, totalWeight);
			}

			// connect right
			p = a->data + n;
			if (p >= 0 && p < x)
				connector = vertexList[p];
			if (a->row + 1 != n && matrix[a->row + 1][a->col] == connector->weight)
			{
				totalWeight = abs(a->weight - connector->weight);
				addDirectedEdge(a->data, p, totalWeight);
			}

			// connect up-left
			p = a->data - 1 - n;
			if (p >= 0 && p < x)
				connector = vertexList[p];
			if (a->row != 0 && a->col != 0 && matrix[a->row - 1][a->col - 1] == connector->weight)
			{
				totalWeight = abs(a->weight - connector->weight);
				addDirectedEdge(a->data, p, totalWeight);
			}

			// connect up-right
			p = a->data + 1 - n;
			if (p >= 0 && p < x)
				connector = vertexList[p];
			if (a->row != 0 && a->col + 1 != n && matrix[a->row - 1][a->col + 1] == connector->weight)
			{
				totalWeight = abs(a->weight - connector->weight);
				addDirectedEdge(a->data, p, totalWeight);
			}

			// connect down-left
			p = a->data + n - 1;
			if (p >= 0 && p < x)
				connector = vertexList[p];
			if (a->row + 1 != n && a->col != 0 && matrix[a->row + 1][a->col - 1] == connector->weight)
			{
				totalWeight = abs(a->weight - connector->weight);
				addDirectedEdge(a->data, p, totalWeight);
			}

			// connect down-right
			p = a->data + n + 1;
			if (p >= 0 && p < x)
				connector = vertexList[p];
			if (a->row + 1 != n && a->col + 1 != n && matrix[a->row + 1][a->col + 1] == connector->weight)
			{
				totalWeight = abs(a->weight - connector->weight);
				addDirectedEdge(a->data, p, totalWeight);
			}
		}
	}

	void rocky(int matrix[n][n])
	{
		clock_t startTime = clock();
		connect(matrix);
		shortestPath(matrix);
		clock_t endTime = clock();

		cout << "Elapsed time:" << (endTime - startTime) / (double) CLOCKS_PER_SEC << " sec." << endl;

	}
};