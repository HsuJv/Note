#include "../h/extGraph.h"
#include <string.h>

int main()
{
	int control = 1; 
	int w = 1; 
	int *d, *path; 
	int n, m; 
	cout << "Please input the number of the city:" << endl; 
	cin >> n; 
	cout << "Please input the number of the flight:" << endl; 
	cin >> m; 
	
	d = new int[n]; 
	path = new int[n];

	extLGraph<int> el(n); 
	int u, v; 
	for(int i = 0; i < m; i++)
	{
		cout << "Please input the start point and end point of the " << i+1 << " flight:" << endl; 
		cin >> u >> v; 
		cout << el.insert(u, v, w) << endl; 
	}
	
	while(control)
	{
		for (int i = 0; i < n; i++) d[i] = INF;
		memset(path, 0, sizeof(path));
		cout << "Please input the start and destination of you travel:"; 
		cin >> u >> v; 
		el.dijkstra(u, d, path); 
		
		if(d[v] != 0 && d[v] < INF)
		{	
			cout << "The length of the route that takes the least transition is:" << d[v] << endl; 
			cout << "And the route is:"; 
			int *p = new int [d[v]]; 
			int t = path[v]; 
			for(int i = 0; i < d[v]; i++){
				p[i] = t; 
				t = path[t]; 
			}
			for(int i = d[v]-1; i >= 0; i--){
				cout << " " << p[i]; 
			}
			cout << " " << v; 
		}
		else
			cout << "Between the two places is no route! or The start and end is same!"; 
		cout << endl << endl << "Enter 1 to continue or 0 to exit."; 
		cin >> control; 
	}
	return 0; 
} 
