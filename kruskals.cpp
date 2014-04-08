#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <stack>
#include <queue>
  
using namespace std;
double elapsed_secs = 0;
int cnt=0;	//counter to stop after all vertices get 6 edges
typedef vector<vector <int> > mat;

struct data {
	int x,y,w;
};
/////////////////////////////////////////////////Disjoint Sets//////////////////////////////////////////////////////
class set {
private:
	int dad[5000];
	int rank[5000];
public:
	void makeset(int);
	void myunion(int,int);
	int myfind(int);
};

void set :: makeset(int p) {
	dad[p] = -1;
	rank[p] = 0;
}

void set :: myunion(int p,int q) {

	if(rank[p] < rank[q]){
		dad[p] = q;}
	else if(rank[p] > rank[q]){
		dad[q] = p;}
	if(rank[p] == rank[q]){
		dad[q] = p;
		rank[p] = rank[q] + 1;}
}

int set :: myfind(int p) {
	int w = p;
	stack<int> mystack;
	while (dad[w] != -1) {
		mystack.push(w);
		w=dad[w];
	}
	while(!mystack.empty()) {
		int u = mystack.top();
		mystack.pop();
		dad[u] = w;
	}
	return w;
} 	

//////////////////////////////////////////////////Graph generation///////////////////////////////////////////////////////	
class graph {
private:
	mat matrix;
public:
	void makegraph(int&);
	void addedge(int *degcnt, int from, int to, int weight, vector<data> &das1,int deg);
	void display(int&);
	void tree(int from, int to, int weight);
	void bfs(int n, int s, int t);
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

void graph :: tree(int from, int to, int weight) {
	matrix[from][to] = weight;
	matrix[to][from] = weight;
}

void graph :: bfs(int n, int s, int t) {
	
	int cost[n];
	int path[n];
	bool visited[n];
    for(int i = 0; i < n; i++)
        {visited[i] = false;	
        cost[i] = 0;}
    queue<int> queue;
	cost[s] = 99999;
    visited[s] = true;
    queue.push(s);

    while(!queue.empty())
    {
        s = queue.front();
        queue.pop();
        for(int y = 0; y <n; y++)
        {
			if(matrix[s][y]!=0 && !visited[y] && cost[s]!=0 && cost[y]<min(matrix[s][y],cost[s])) {
					cost[y] = min(cost[s],matrix[s][y]);
					visited[y] = true;
					queue.push(y);
        	}
		}
    }
	cout << "max bandwidth: " << cost[t] << "\n";
}

void graph :: addedge(int *degcnt, int from, int to, int weight, vector<data> &das1, int deg) {
	
	if(degcnt[from]<deg && degcnt[to]<deg)
	{
		if(matrix[from][to]==0 && matrix[to][from]==0)
		{
			das1.push_back(data());
			das1[cnt].x = from;
			das1[cnt].y = to;
			das1[cnt].w = weight;
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

////////////////////////////////////////////////////////Heap Structure////////////////////////////////////////////////////////
class Heap {
public:
    Heap();
    ~Heap();
    void insert(data element);
    data deletemax();
    void print();
    int size() { return heap.size(); }
private:
    int left(int parent);
    int right(int parent);
    int parent(int child);
    void heapifyup(int index);
    void heapifydown(int index);
    void heapify();
private:
    vector<data> heap;
};

Heap::Heap()
{
}

Heap::~Heap()
{
}

void Heap::insert(data d)
{
    heap.push_back(d);
    heapifyup(heap.size() - 1);
}

data Heap::deletemax()
{ 
    data max = heap.front();
    heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapifydown(0);
    return max;
}

void Heap::print()
{
    vector<data>::iterator pos = heap.begin();
    cout << "Heap = ";
    while ( pos != heap.end() ) {
		cout << (*pos).x << "<->" << (*pos).y << "w:"<<(*pos).w << "\t";
        ++pos;
    }
    cout << endl;
}

void Heap::heapifyup(int index)
{    
    while ( ( index > 0 ) && ( parent(index) >= 0 ) &&
            ( heap[parent(index)].w < heap[index].w ) )
    {
        data tmp = heap[parent(index)];
        heap[parent(index)] = heap[index];
        heap[index] = tmp;
        index = parent(index);
    }
}

void Heap::heapifydown(int index)
{     
    int child = left(index);
    if ( ( child > 0 ) && ( right(index) > 0 ) &&
         ( heap[child].w < heap[right(index)].w ) )
    {
        child = right(index);
    }
    if ( heap[child].w > heap[index].w )
    {
        data tmp = heap[index];
        heap[index] = heap[child];
        heap[child] = tmp;
        heapifydown(child);
    }
}

void Heap::heapify()
{
    int index1 = heap.size()-1;
    int index;
    while(index1>0){
    index = index1;
    while ( ( index > 0 ) && ( parent(index) >= 0 ) &&
            ( heap[parent(index)].w < heap[index].w ) )
    {
        data tmp = heap[parent(index)];
        heap[parent(index)] = heap[index];
        heap[index] = tmp;
        index = parent(index);
    }
    index1--;
    }
}

int Heap::left(int parent)
{
    int i = 2*parent + 1;
    return ( i < heap.size() ) ? i : -1;
}

int Heap::right(int parent)
{
    int i = 2*parent + 2;
    return ( i < heap.size() ) ? i : -1;
}

int Heap::parent(int child)
{
    if (child != 0)
    {
	int i = ((child-1)/2);
        return i;
    }
    return -1;
}

/////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////////////////
int main() {
	int n=5000, deg,rel;
	int t = time(NULL);
	srand(t);
	graph g;
	cout << "\nEnter the degree for the graph(6 or 1000): ";
	cin >> deg;
	cout << "\n";
	if(deg==1000) {rel=200;}
	else{rel=2;}
	vector<data> das1(30000);
	int degcnt[n];
    memset(degcnt,0,sizeof(degcnt)+1); //initialize degcnt array to all 0s
	int *p;
	p = &degcnt[0];
	g.makegraph(n);
	
	int u,v,w,c=0;
	while(cnt<=((n*(deg/2))-rel))
	{
		u = rand()%n;
		v = rand()%n;
		if(u!=v){
			w = (rand()%15000)+1;
			g.addedge(p,u,v,w,das1,deg);
		}
	}
	cout << "graph generated" << "\n";

	vector<data> store;
	set myset;
	
	///////////////////////////////////////Kruskal's Algorithm/////////////////////////////////////////////////
	clock_t begin = clock();
	for(int z = 0;z <= n;z++)
	{
		myset.makeset(z);
	}
	Heap* myheap = new Heap();
	for(int i = 0;i < cnt;i++)
    {	
    	myheap->insert(das1[i]);
    }
    int count=0;    
    for(int zz = 0;zz < cnt;zz++)
    {
		data d = myheap->deletemax();
		if(myset.myfind(d.x) != myset.myfind(d.y)) {
			count++;
			store.push_back(d);
			myset.myunion(d.x,d.y);
			if(count == (n-1)){break;}
			}
	}		
	clock_t end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	graph g1;
	g1.makegraph(n);
	for(int t=0;t<count;t++)
	{
		g1.tree(store[t].x,store[t].y,store[t].w);
	}
	cout << endl;
	int sr = rand()%n;
	int ds = rand()%n;
	if(ds==sr)
		{ds = ds + 1;}
	cout << "source: " << 100 << "\n" << "Destination: " << ds << "\n";
	g1.bfs(n,100,ds);
	cout << "Time elapsed for running the Kruskal's Algorithm: " << elapsed_secs << "secs" << endl << endl;
	
}
	
