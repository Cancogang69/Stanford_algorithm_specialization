using Clustering;

//Question 1:
string dataSet1 = "DataSet1.txt";
List<edge> graph = new List<edge>();

DataProcess.ReadGraph(ref graph, dataSet1);

//sort edge based on distance
int low = 0;
int high = graph.Count() -1;
DataProcess.EdgeQuickSort(ref graph, low, high);

//create a pointer list 
int[] pointerList = new int[500];
for (int i=0; i<500; i++)
    pointerList[i] = i+1;

// k is the number of cluster to stop fuse
// n is the number of cluster remain so far
int k = 4;
int n = Cluster.UnionCount(ref pointerList);
while(n>k) {
    int node1 = graph[0].node1;
    int node2 = graph[0].node2;

    bool check = !Cluster.UnionCheck(ref pointerList, node1, node2);
    if(check) {
        Cluster.FuseUnion(ref pointerList, node1, node2);
        n--;
    }
    graph.RemoveAt(0);
}

//Remove edge that connects between 2 node in same union
//if that edge connect 2 node from 2 differnce union 
//so that edge is the answer
while(true) {
    int first = 0;
    int node1 = graph[first].node1;
    int node2 = graph[first].node2;
    if(!Cluster.UnionCheck(ref pointerList, node1, node2)) {
        Console.WriteLine("Answer for question 1: " + graph[first].distance);
        break;
    }
    
    graph.RemoveAt(first);
} 

graph.Clear();  




//Question 2
string dataSet2 = "DataSet2.txt";
int hashSize = 100000;
List<List<bitsNode>> bigGraph = new List<List<bitsNode>>(hashSize);
List<int> sortedNode = new List<int>();

//read data 
//bigGraph is a hash table to store node
//sortedNode is a temporary list store value of node for pointer list
DataProcess.ReadBitsGraph(ref bigGraph, ref sortedNode, dataSet2, hashSize);

//sort the sortedNode using QuickSort
int size = sortedNode.Count();
int lowPos = 0;
int highPos = size - 1;
DataProcess.QuickSort(ref sortedNode, lowPos, highPos);


//create union pointer list based on sortedNode list
List<bitsPointer> bitsPointerList = new List<bitsPointer>(size);
for(int i=0; i<size; i++) {
    bitsPointerList.Add(new bitsPointer(sortedNode[i], i));
    int[] pos = DataProcess.FindPosHashList(bigGraph, hashSize, sortedNode[i]);
    bigGraph[pos[0]][pos[1]].pointerPos=i;
}

sortedNode.Clear();

//fuse 2 node in 2 difference union that have 1 bit diference
int bitsUnion = size;
for(int row=0; row<bigGraph.Count(); row++)
    for(int column=0; column<bigGraph[row].Count(); column++) {
        BitCluster.Check1BitDif(ref bigGraph, ref bitsPointerList, row, column, ref bitsUnion, hashSize);
    }

//fuse 2 node in 2 difference union that have 2 bit diference
for(int row=0; row<bigGraph.Count(); row++)
    for(int column=0; column<bigGraph[row].Count(); column++) {
        BitCluster.Check2BitDif(ref bigGraph, ref bitsPointerList, row, column, ref bitsUnion, hashSize);
    }

Console.WriteLine("Answer for question 2: " + bitsUnion);

