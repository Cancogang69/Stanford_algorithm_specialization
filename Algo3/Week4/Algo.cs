using Knapsack;
using DataProcessing;

//string dataSet1 = "DataSet1.txt";
string dataSet1 = "test2.txt";
int knapCapacity1 = 0;
List<knap> knapList1 = new List<knap>();

bool flag = Processing.ReadData(ref knapList1, ref knapCapacity1, dataSet1);
//Processing.WriteData(knapList);
if(flag)
    KnapProbSolve.FindOptimalSolution(knapList1, knapCapacity1);

string dataSet2 = "DataSet2.txt";
int knapCapacity2 = 0;
List<knap> knapList2 = new List<knap>();
flag = Processing.ReadData(ref knapList2, ref knapCapacity2, dataSet2);

if(flag)
    KnapProbSolve.FindOptimalSolution(knapList2, knapCapacity2);
