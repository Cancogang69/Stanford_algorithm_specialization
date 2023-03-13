using DataProcessing;
using HuffmanCode;
using IndependentSet;

//Question 1 and 2
string dataSet1 = "DataSet1.txt";
List<int> huffList = new List<int>();
Processing.ReadData(ref huffList, dataSet1);

int low = 0;
int high = huffList.Count()-1;
Processing.Sort(ref huffList, low, high, true);

tree huffTree = HuffmanMethod.encode(huffList);

List<int> lengthList = new List<int>();
int length = 1;
HuffmanMethod.BinaryLength(ref lengthList, huffTree, length);

Processing.Sort(ref lengthList, low, high, true);

Console.WriteLine("maxium length: " + lengthList[0]);
Console.WriteLine("minium length: " + lengthList[lengthList.Count()-1]);

huffList.Clear();
lengthList.Clear();

//Question 3
string dataSet2 = "DataSet2.txt";
//string dataSet2 = "TestDataSet2.txt";
List<int> weightList = new List<int>();
Processing.ReadData(ref weightList, dataSet2);

List<long> maxWISList = new List<long>();
ISMethod.FindIndepentSet(weightList, ref maxWISList);

List<bool> isInIS = new List<bool>();
ISMethod.FindVerticeInIS(weightList, maxWISList, ref isInIS);

string questionSet = "Question3Vertices.txt";
List<int> qVertices = new List<int>();
Processing.ReadData(ref qVertices, questionSet);

for(int i=0; i<qVertices.Count(); i++)
    if(isInIS[qVertices[i]-1])
        Console.Write("1");
    else 
        Console.Write("0");

Console.WriteLine();




 
