using HuffmanCode;

string dataSet1 = "DataSet1.txt";
List<int> originList = new List<int>();

DataPreprocess.ReadData(ref originList, dataSet1);

Console.WriteLine("Read data done!");

int low = 0;
int high = originList.Count()-1;
DataPreprocess.Sort(ref originList, low, high);

Console.WriteLine("Sorting done!");