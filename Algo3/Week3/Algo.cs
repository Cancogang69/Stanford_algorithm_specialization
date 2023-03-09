using HuffmanCode;

string dataSet1 = "DataSet1.txt";
List<long> originList = new List<long>();
DataPreprocess.ReadData(ref originList, dataSet1);

int low = 0;
int high = originList.Count()-1;
DataPreprocess.Sort(ref originList, low, high, true);

tree huffTree = HuffmanMethod.encode(originList);

List<long> lengthList = new List<long>();
HuffmanMethod.BinaryLength(originList, ref lengthList, huffTree);

DataPreprocess.Sort(ref lengthList, low, high, true);

Console.WriteLine("maxium length: " + lengthList[0]);
Console.WriteLine("minium length: " + lengthList[lengthList.Count()-1]);

 
