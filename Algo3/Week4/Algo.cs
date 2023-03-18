using Knapsack;
using DataProcessing;

//string dataSet1 = "DataSet1.txt";
string dataSet1 = "test.txt";
int knapCapacity = 0;
List<knap> knapList = null;

Processing.ReadData(ref knapList, ref knapCapacity, dataSet1);

Processing.KnapWeigthSort(ref knapList);

Processing.Combing(ref knapList);

List<knap> solutionList = new List<knap>(knapList.Count());
solutionList.Add(new knap(0, 0));
solutionList.Add(knapList[1]);
int lastIndex = knapList.Count()-1;
KnapProbSolve.OptimalSolution(knapList, ref solutionList, knapCapacity, lastIndex);
Console.WriteLine(solutionList[lastIndex].value);
Console.WriteLine(solutionList[lastIndex].weight); 

