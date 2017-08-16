#include "../h/extGraph.h"

#define noedge INT_MAX

int main()
{
	int w = 1;
	
	mGraph<int> m(4, noedge);
	cout << m.insert(0, 1, w) << endl;
	cout << m.vertices() << endl;
	if(m.exist(0, 1))
		cout << "Edge <0, 1> exists." << endl;
		
	lGraph<int> l(4);
	cout << l.insert(1, 3, w) << endl;
	cout << l.vertices() << endl;
	if(l.exist(1, 3))
		cout << "Edge <1, 3> exists." << endl;	
	
	extMGraph<int> em(7, noedge);
	cout << em.insert(0, 1, w) << endl;
	cout << em.insert(1, 2, w) << endl;
	cout << em.insert(1, 3, w) << endl;
	cout << em.insert(2, 0, w) << endl;
	cout << em.insert(3, 0, w) << endl;
	cout << em.insert(3, 2, w) << endl;
	cout << em.insert(4, 5, w) << endl;
	cout << em.insert(4, 6, w) << endl;
	cout << em.insert(5, 1, w) << endl;
	cout << em.insert(6, 3, w) << endl;
	cout << em.insert(6, 5, w) << endl;
	cout << "DFS: ";
	em.dfs();
	cout << endl;
	cout << "BFS: ";
	em.bfs();
	return 0;
} 
