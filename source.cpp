//the solution

#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#define INFINITY 99999
using namespace std;
const int siiize = 200;
int c;
string str;
void dijkstra(int G[siiize][siiize], int n, int startnode, int endnode);
int numVertices()
{
	int num = 0;
	int x;
	ifstream inputfile;
	inputfile.open(str);
	while (inputfile >> x)
	{
		num++;
	}
	num = sqrt(num);
	inputfile.close();

	return num;
}
//////////////////
void printPath(int path[][siiize], int v, int u)
{

	if (path[v][u] == v)
		return;

	printPath(path, v, path[v][u]);
	cout << path[v][u] << " ";
}

//////////////
void printSolution(int cost[siiize][siiize], int path[siiize][siiize], int v, int u)
{


	if (u != v && path[v][u] != -1)
	{

		if (v > c || u > c) {
			cout << "soory,you shoud input two vertix exist in array \n";
			return;
		}
		else
		{
			cout << "Shortest Path from  " << v << "  to  " << u << "  = " << cost[v][u]
				<< endl << "the path is :  ( " << v << " ";
		}
		printPath(path, v, u);
		cout << u << " )" << endl;
	}
	else if (u == v) {
		cout << "shortest path from vertix " << cost[v][u] << " to itself is 0"<<endl<<"the path is 0 ";
	}
	else cout << "Shortest Path from  " << v << "  to  " << u << " =  0" << endl<<" the path is : 0";
}

//////////////
void FloydWarshell(int adjMatrix[][siiize], int startnode, int endnode)
{
	int cost[siiize][siiize], path[siiize][siiize];

	for (int v = 0; v < c; v++)
	{
		for (int u = 0; u < c; u++)
		{

			cost[v][u] = adjMatrix[v][u];

			if (v == u)
				path[v][u] = 0;
			else if (cost[v][u] != 0)
				path[v][u] = v;
			else
				path[v][u] = -1;
		}
	}

	for (int k = 0; k < c; k++)
	{
		for (int v = 0; v < c; v++)
		{
			for (int u = 0; u < c; u++)
			{

				if (cost[v][k] != 0 && cost[k][u] != 0
					&& cost[v][k] + cost[k][u] < cost[v][u])
				{
					cost[v][u] = cost[v][k] + cost[k][u];
					path[v][u] = path[k][u];
				}
			}

			if (cost[v][v] < 0)
			{
				cout << "Negative Weight Cycle Found!!";
				return;
			}
		}
	}

	printSolution(cost, path, startnode, endnode);
}

void dijkstra(int G[siiize][siiize], int startnode, int endnode) {
	int cost[siiize][siiize], distance[siiize], pred[siiize];
	int visited[siiize], count, mindistance, nextnode, i, j;
	for (i = 0;i < c;i++)
		for (j = 0;j < c;j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];
	for (i = 0;i < c;i++) {
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	while (count < c - 1) {
		mindistance = INFINITY;
		for (i = 0;i < c;i++)
			if (distance[i] < mindistance && !visited[i]) {
				mindistance = distance[i];
				nextnode = i;
			}
		visited[nextnode] = 1;
		for (i = 0;i < c;i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i] < distance[i]) {
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}

	if (endnode != startnode) {
		cout << "\nshortest path from  " << startnode << " to  " << endnode << "  =  " << distance[endnode];
		cout << "\nPath =  " << endnode;
		j = endnode;
		do {
			j = pred[j];
			cout << "<-" << j;
		} while (j != startnode);
	}
}
int main()
{
	cout << "input the name of file \n";
	cin >> str;
	c = numVertices();
	int choose;
	int m[siiize][siiize];
	int x;
	ifstream inpfile;
	inpfile.open(str);
	for (int i = 0;i < c;i++)
		for (int j = 0;j < c;j++)
		{
			inpfile >> m[i][j];
		}
	inpfile.close();
	do {
		int what_alg;
		cout << "choose algorithm\n  1.floyd\n  2.dijeksta\n";
		cin >> what_alg;
		int startnode, endnode;
		cout << "input 2 virtices" << endl;
		cin >> startnode >> endnode;
		if (what_alg == 1)

		{
			FloydWarshell(m, startnode, endnode);
		}
		else if (what_alg == 2)
		{
			dijkstra(m, startnode, endnode);
		}
		else
			cout << "wrong choice \n";
		cout << endl << "do you want complete the program : 1.yes 2.no \n";
		cin >> choose;
	} while (choose == 1);

	system("pause");
	return 0;
}
