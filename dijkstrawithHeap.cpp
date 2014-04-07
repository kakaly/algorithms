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
	vector<int> heap;
public:
	void makegraph(int&);
	void addedge(int *degcnt, int from, int to, int weight);
	void display(int&);
	void algo(int src, int dst, int n);
	
	void insert(int element,int cost[]);
    	int extractmax(int cost[]);
    	int size() { return heap.size(); }
    	int left(int parent);
    	int right(int parent);
    	int parent(int child);
    	void heapifyup(int index,int cost[]);
    	void heapifydown(int index,int cost[]);
		void heapupdate(int cost[], int adjust);
};

void graph::insert(int element,int cost[])
{
    heap.push_back(element);
    heapifyup(heap.size() - 1,cost);
}

int graph::extractmax(int cost[])
{
    int max = heap.front();
    heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapifydown(0,cost);
    return max;
}

void graph::heapifyup(int index,int cost[])
{    
    while ( ( index > 0 ) && ( parent(index) >= 0 ) &&
            ( cost[heap[parent(index)]] < cost[heap[index]] ) )
    {
        int tmp = heap[parent(index)];
        heap[parent(index)] = heap[index];
        heap[index] = tmp;
        index = parent(index);
    }
}

void graph::heapifydown(int index,int cost[])
{     
    int child = left(index);
    if ( ( child > 0 ) && ( right(index) > 0 ) &&
         ( cost[heap[child]] < cost[heap[right(index)]] ) )
    {
        child = right(index);
    }
    if (child>0 && cost[heap[child]] > cost[heap[index]])
    {
        int tmp = heap[index];
        heap[index] = heap[child];
        heap[child] = tmp;
        heapifydown(child,cost);
    }
}

void graph::heapupdate(int cost[], int adjust)
{
	int j=0;
    for(int i=0;i<heap.size();i++) {
		j=i;
		if(heap[i]==adjust)
		break;
	}
	if(cost[heap[j]]>cost[heap[parent(j)]])
	{
		heapifyup(j,cost);
	}
	else if(cost[heap[j]]<cost[heap[left(j)]] || cost[heap[j]]<cost[heap[right(j)]]) 
	{
		heapifydown(j,cost);
	}
}

int graph::left(int parent)
{
    int i = 2*parent + 1;
    return ( i < heap.size() ) ? i : -1;
}

int graph::right(int parent)
{
    int i = 2*parent + 2;
    return ( i < heap.size() ) ? i : -1;
}

int graph::parent(int child)
{
    if (child != 0)
    {
	int i = ((child-1)/2);
        return i;
    }
    return -1;
}

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
	if(degcnt[from]<6 && degcnt[to]<6) //change it to 1000 for degree 1000 graph
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

void graph :: algo(int src, int dst, int n)
{
	int cost[n];
	int path[n];
	bool set[n];
	int i;
	//initialize single source shortest path
	for(i=0;i<n;i++)
	{
		cost[i] = 0;
		set[i] = false;	
	}
	cost[src]=999999;
	
	//insert into the priority queue
	for(i=0;i<n;i++)
	{
		insert(i,cost);
	}
	int c=0;
	
	//loop till queue is empty
	while(heap.size()!=0)
	{	
		int u = extractmax(cost);
		set[u] = true;
		path[c] = u;
		int v;
		for(v=0;v<n;v++)
		{
			if(!set[v] && matrix[v][u]!=0 && cost[u]!=0 && cost[v]<min(matrix[v][u],cost[u]))
			
			{
				cost[v] = min(cost[u],matrix[v][u]);
				set[v] = false;
				heapifyup(v,cost);
			}
		}
		c++;
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
	//cout << "\nEdges added\n";
	//g.display(n); //remove comments to display the graph
	
	int sr = rand()%n;
	int ds = rand()%n;
	clock_t begin = clock();
	g.algo(0,ds,n);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << "secs" << endl;
	//cout << "Max bandwidth from source node calculated\n";
return 0;
}
