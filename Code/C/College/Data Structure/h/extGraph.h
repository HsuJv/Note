#ifndef EXT_GRAPH_H
#define EXT_GRAPH_H

#ifndef GRAPH_H

#include "graph.h"

#endif // GRAPH_H

#ifndef QUEUE_H

#include "queue.h"

#endif // QUEUE_H

#ifndef LIMITS_H
#define LIMITS_H

#include <limits.h>

#endif // LIMITS_H


#define INF INT_MAX-100

template <class T>
class extMGraph: public mGraph<T>
{
public:
	extMGraph(int mSize, const T& noEdg): mGraph<T>(mSize, noEdg){	}
	void dfs(){
		bool* visited = new bool [this->n];
		for (int i = 0; i < this->n; i++) visited[i] = false;
		for (int i = 0; i < this->n; i++)
			if (!visited[i]) dfs(i, visited);
		delete[] visited;
	}
	void bfs(){
		bool* visited = new bool [this->n];
		for (int i = 0; i < this->n; i++) visited[i] = false;
		for (int i = 0; i < this->n; i++)
			if (!visited[i]) bfs(i, visited);
		delete[] visited;
	}
	int choose(int *d, bool *s){
		int minpos; T min;
		min = INF; minpos = -1;
		for (int i = 0; i < this->n ; i++)
			if (d[i] <= min && !s[i]){
				min = d[i];
				minpos = i;
			}
		return minpos;
	}
	void dijkstra(int v, T* d, int* path){
		if (v<0 || v>this->n-1) throw;
		bool *s = new bool [this->n];
		for (int i = 0; i < this->n; i++){
			s[i] = false;
			d[i] = this->a[v][i];
			if (i!=v && d[i]<INF) path[i] = v;
			else path[i] = -1;
		}
		s[v] = true; d[v] = 0;
		for (int i = 0; i < this->n; i++){
			int k = choose(d, s);
			s[k] = true;
			for (int w = 0; w < this->n; w++)
				if (!s[w] && d[k]+this->a[k][w] < d[w]){
					d[w] = d[k] + this->a[k][w];
					path[w] = k;
				}
		}
	}
protected:
	void dfs(int v, bool* visited){
		visited[v] = true;
		cout << " " << v;
		for (int i = 0; i < this->n; i++)
			if (this->a[v][i] != this->noEdge && !visited[i]) dfs(i, visited);
	}
	void bfs(int v, bool* visited){
		seqQueue<int> q(this->n);
		visited[v] = true;
		cout << " " << v;
		q.enQueue(v);
		while(!q.isEmpty()) {
		    q.getFront(v);q.deQueue();
		    for (int i = 0; i < this->n; i++)
		    	if (this->a[v][i]!=this->noEdge && !visited[i]){
		    		visited[i] = true;
		    		cout << " " << i;
		    		q.enQueue(i);
		    	}		
		}
	}
	
};

template <class T>
class extLGraph: public lGraph<T>
{
public:
	extLGraph(int mSize): lGraph<T>(mSize){ }
	void dfs(){
		bool* visited = new bool [this->n];
		for (int i = 0; i < this->n; i++) visited[i] = false;
		for (int i = 0; i < this->n; i++)
			if (!visited[i]) dfs(i, visited);
		delete[] visited;
	}
	void bfs(){
		bool* visited = new bool [this->n];
		for (int i = 0; i < this->n; i++) visited[i] = false;
		for (int i = 0; i < this->n; i++)
			if (!visited[i]) bfs(i, visited);
		delete[] visited;
	}
	int choose(int *d, bool *s){
		int minpos; T min;
		min = INF; minpos = -1;
		for (int i = 0; i < this->n ; i++)
			if (d[i] <= min && !s[i]){
				min = d[i];
				minpos = i;
			}
		return minpos;
	}
	void dijkstra(int v, T* d, int* path){
		if (v<0 || v>this->n-1) throw;
		bool *s = new bool [this->n];
		for (int i = 0; i < this->n; i++)
			s[i] = false;
		for (eNode<T> *w = this->a[v]; w != NULL; w = w->nextArc){
			d[w->adjVex] = w->w;
			path[w->adjVex] = v;
		}
		path[v] = -1;
		s[v] = true; d[v] = 0;
		for (int i = 1; i < this->n; i++){
			int k;
			k = choose(d, s);
			s[k] = true;
			for (eNode<T> *w = this->a[k]; w != NULL; w = w->nextArc)
				if (!s[w->adjVex] && d[k]+w->w < d[w->adjVex]){
					d[w->adjVex] = d[k] + w->w;
					path[w->adjVex] = k;
				}
		}
	}
protected:
	void dfs(int v, bool* visited){
		visited[v] = true;
		cout << " " << v;
		for (eNode<T> *w = this->a[v]; w != NULL; w = w->nextArc)
			if (!visited[w->adjVex]) dfs(w->adjVex, visited);
	}
	void bfs(int v, bool* visited){
		seqQueue<int> q(this->n);
		visited[v] = true;
		cout << " " << v;
		q.enQueue(v);
		while(!q.isEmpty()) {
		    q.getFront(v);q.deQueue();
		    for (eNode<T> *w = this->a[v]; w != NULL; w = w->nextArc)
		    	if (!visited[w->adjVex]){
		    		visited[w->adjVex] = true;
		    		cout << " " << w->adjVex;
		    		q.enQueue(w->adjVex);
		    	}		
		}
	}
	
};

#endif // EXT_GRAPH_H
