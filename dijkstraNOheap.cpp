#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <ctime>
#include <cstdlib>
 
using namespace std;

int cnt=0;	//counter to stop after all vertices get 6 edges
typedef vector<vector <int> > mat;

class graph {
private:
	mat matrix;
public:
	void makegraph(int&);
	void addedge(int *degcnt, int from, int to, int weight);
	void display(int&);
	int maxwt(int cost[], bool set[], int n);
	void algo(int src, int dst, int n);
};

void graph :: makegraph(int& n) {
	int i,j;
	for (i=0;i<n;i++) {
    		vector<int> row; // Create an empty row
    		for (j=0;j<n;j++) {	
        		row.push_back(0); // Add an element (column) to the row
    		}
    		matrix.push_back(row); // Add the row to the main vector
	}
}

void graph :: addedge(int *degcnt, int from, int to, int weight) {
	if(degcnt[from]<6 && degcnt[to]<6) //change 6 to 1000 for 1000 degree graph
	{
		if(matrix[from][to]==0 && matrix[to][from]==0)
		{
			matrix[from][to] = weight;
			matrix[to][from] = weight;
			degcnt[from]++; //degcnt array gets incremented in the corresponding position
			degcnt[to]++;
			cnt++;
		}
		else
			return;
	}
	else
		return;
}

void graph :: display(int& n) {
	int i,j;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			cout << " -> " << matrix[i][j];
		}
		cout << "\n";
	}
	
}


int graph :: maxwt(int cost[], bool set[], int n) {
	int max = 0;
	int index;
	for(int v=0;v<n;v++)
	{
		if(set[v] == false && cost[v] >= max)
		{
			max = cost[v];
			index = v;
		}
	}
	return index;
}

void graph :: algo(int src, int dst, int n)
{
	int cost[n];
	bool set[n];
	int path[n];
	int i;
	for(i=0;i<n;i++)
	{
		cost[i] = 0;
		set[i] = false;
	}
	cost[src]=999999;
	for (int count=0;count<n;count++)
	{
		int u = maxwt(cost,set,n);
		set[u] = true;
		path[count] = u;
		int v;
		                 
		for(v=0;v<n;v++)
		{
			if(!set[v] && matrix[v][u]!=0 && cost[u]!=0 && cost[v]<min(matrix[v][u],cost[u]))
				{cost[v] = min(cost[u],matrix[v][u]);
				set[v] = false;}
		}
	}
}

int main()
{
	int n;
	int t = time(NULL);
	srand(t);
	graph g;
	cout << "\nEnter the number of vertices:";
	cin >> n;

	int degcnt[n];
    memset(degcnt,0,sizeof(degcnt)+1); //initialize degcnt array to all 0s
	int *p;
	p = &degcnt[0];
	g.makegraph(n);
	//cout << "\nGraph generated";
	int u,v,w;
	while(cnt<=((n*3)-2)) //For 100 degree graph, change 3 to 500 and 2 to 100 for relaxing.
	{	
		u = rand()%n;
		v = rand()%n;
		if(u!=v){
			w = rand()%15000+1;
			g.addedge(p,u,v,w);
		}
	}
	//cout << "\n";
	//cout << "\nEdges added\n"; 
	//g.display(n); //remove comments to display the graph
	
	int sr = rand()%n;
	int ds = rand()%n;
	clock_t begin = clock();
	g.algo(sr,ds,n);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << "secs" << endl;
	//cout << "Max bandwidth from source node calculated\n";

return 0;
}
