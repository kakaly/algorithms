#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <ctime>
#include <cstdlib>
 
using namespace std;

int cnt=0;	//counter to stop after all vertices get 6 edges
typedef vector<vector <int> > mat;

//////////////////////////////////////////////Graph generation///////////////////////////////////////////////

class graph {
private:
	mat matrix;
public:
	void makegraph(int&);
	void addedge(int *degcnt, int from, int to, int weight,int deg);
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

void graph :: addedge(int *degcnt, int from, int to, int weight, int deg) {
	if(degcnt[from]<deg && degcnt[to]<deg) //change 6 to 1000 for 1000 degree graph
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

///////////////////////////////////////Dijkstra's algorithm///////////////////////////////////////////////////////////

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
	cout << "max bandwidth: " << cost[dst] << "\n";
}

//////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////

int main()
{
	int n=5000, deg,rel;
	int t = time(NULL);
	srand(t);
	graph g;
	cout << "\nEnter the degree for the graph(6 or 1000): ";
	cin >> deg;
	cout << "\n";
	if(deg==1000) {rel=200;}
	else{rel=2;}

	int degcnt[n];
    memset(degcnt,0,sizeof(degcnt)+1); //initialize degcnt array to all 0s
	int *p;
	p = &degcnt[0];
	g.makegraph(n);
	int u,v,w;
	while(cnt<=((n*(deg/2))-rel))
	{	
		u = rand()%n;
		v = rand()%n;
		if(u!=v){
			w = rand()%15000+1;
			g.addedge(p,u,v,w,deg);
		}
	}
	int sr = rand()%n;
	int ds = rand()%n;
	cout << "source: " << sr << "\n" << "Destination: " << ds << "\n";
	clock_t begin = clock();
	g.algo(sr,ds,n);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time elapsed for running the Kruskal's Algorithm: " << elapsed_secs << "secs" << endl << endl;

return 0;
}
