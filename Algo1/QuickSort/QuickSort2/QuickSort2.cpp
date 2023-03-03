#include <iostream>

using namespace std;

void QuickSort(int*& arr, int l, int r, unsigned long long& sum);
void Partition(int*& arr, int l, int& pivot, int r, unsigned long long& sum);


int main()
{
	const int num = 10000;
	unsigned long long sum = 0;
	int* arr = new int[num];
	for (int i = 0; i < num; i++)
		cin >> arr[i];
	QuickSort(arr, 0, num - 1, sum);
	/*for (int i = 0; i < num; i++)
		cout << arr[i] << " ";*/
	cout << sum;
}

void Partition(int*& arr, int l, int& pivot, int r, unsigned long long& sum)
{
	int p = arr[pivot];
	int i = r-1;
	int j = i;
	for (; j >= l; j--, sum++)
		if (arr[j] > p)
		{
			swap(arr[i], arr[j]);
			i--;
		}
	swap(arr[i + 1], arr[r]);
	pivot = i + 1;
}

void QuickSort(int*& arr, int l, int r, unsigned long long& sum)
{
	if (l >= r)
		return;
	int p = r;
	Partition(arr, l, p, r, sum);
	QuickSort(arr, l, p - 1, sum);
	QuickSort(arr, p + 1, r, sum);
}