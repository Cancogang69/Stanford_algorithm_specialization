﻿using HuffmanCode;

string dataSet1 = "DataSet1.txt";
List<int> originList = new List<int>();

DataPreprocess.ReadData(ref originList, dataSet1);

Console.WriteLine("Read data done!");

int low = 0;
int high = originList.Count()-1;
DataPreprocess.Sort(ref originList, low, high);

Console.WriteLine("Sorting done!");

List<int> huffList = new List<int>(originList);

tree huffTree = HuffmanMethod.encode(ref huffList);

Console.WriteLine("encoding done!");

List<int> length = new List<int>();

 
