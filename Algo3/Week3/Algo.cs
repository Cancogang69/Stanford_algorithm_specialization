using HuffmanCode;

string dataSet1 = "DataSet1.txt";
List<int> originList = new List<int>();

DataPreprocess.ReadData(ref originList, dataSet1);

Console.WriteLine("Read data done!");
