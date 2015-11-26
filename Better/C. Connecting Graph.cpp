// problem 
// http://codeforces.com/gym/100814/problem/C

/* 
								C. Connecting Graph
							time limit per test6 seconds
							memory limit per test1024 megabytes
							inputstandard input
							outputstandard output
	Alex is known to be very clever, but Walter does not believe that. In order to test Alex, he invented a new game. He 
gave Alex n nodes, and a list of queries. Walter then gives Alex one query every second, there are two types of queries:

1 U V means: adding an undirected edge between nodes u and v.

2 U V means: what was the earliest time (query index) when u and v became connected? 2 nodes are connected if there is a path of edges 
between them. Alex can solve this problem easily, but he is too busy now, so he is asking for your help.

Input
The first line contains an integer T, the number of test cases. Each test case begins with a line containing two integers (1 ≤ n, m ≤ 105), 
the number of nodes and queries, respectively. Then there are m lines, each line represents a query and contains three integers, type, u 
and v ( , 1 ≤ u, v ≤ n)

Output
For each query of type 2, print one line with one integer, the answer to the query. If the 2 nodes in the query are not connected, print -1.

Sample test(s) 
input
1
4 5
1 1 2
2 1 2
1 2 3
2 1 3
2 1 4
output
1
3
-1
Note
Warning: large Input/Output data, be careful with certain languages.
*/


// solution 
/* 
	Here we will use DSU, and for each node simply keep time when it was connected with its parent. When we have some query, we will find least 
	common ancestor of both nodes and check which connection was done later and that's the answer.

*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

typedef long long ll;
 
 
 void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
 }
 
 // returns root of subtree node is in
 int getroot(int node,vector<int> &p){
	while(node != p[node]){
		node = p[node];
	}
	return node;	
 }
 
 // updates connection as DSU does, and keeps connection time
void update(int time,int u,int v,vector<int> &p,vector<int> &h,vector<int> &t){
	
	int ru = getroot(u,p);
	int rv = getroot(v,p);	
	
	if(ru == rv) return;
	
	if(h[ru] > h[rv]) swap(ru,rv);
		
	p[ru] = rv;
	h[rv] = max(h[rv],h[ru]+1);
	t[ru] = time;
}

// returns some ancestor a of u, where parent of a is 'parent'
int getnode(int parent, int u,vector<int> &p){
	while(p[u] != parent && p[u] != u) u = p[u];
	
	return u;
}

// find least commong ancestor, and return later connection,
// or return -1 if common ancestor doesn't exist
int query(int u,int v,vector<int> &p,vector<int> &h,vector<int> &t)
{
		
	int ru = getroot(u,p);
	int rv = getroot(v,p);
	
	if(ru != rv) return -1;
	
	int nodeu = getnode(u,v,p);
	if(p[nodeu] == u) return t[nodeu];
	
	int nodev = getnode(v,u,p);
	if(p[nodev] == v) return t[nodev];
	
	while(u != p[u]){
		int node = getnode(p[u],v,p);
		if(p[node] == p[u]) return max(t[node],t[u]);
		u = p[u];
	}
	
	return 0;
}

int main(){
	
	
	
	int t;
	cin >> t;
	
	for(int q = 0; q < t; q++){
		int n,m;
		scanf("%d%d",&n,&m);
		
		// data for parents, for heights (p,h DSU staff)
		// data for connection times (t)
		vector<int> p(n+1),h(n+1),t(n+1);
		
		for(int i = 1; i <= n; i++){
			p[i] = i;
			h[i] = 1;
		}
		
		for(int i = 0; i < m; i++){
			int type,u,v;
			scanf("%d%d%d",&type,&u,&v);
			if(type == 1){
				update(i+1,u,v,p,h,t);	// update datas
			} else printf("%d\n", query(u,v,p,h,t));	// calculate result for query
		}
	}
	
	return 0;
}
