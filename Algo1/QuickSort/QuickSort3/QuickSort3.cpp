#include <iostream>

using namespace std;

void QuickSort(int*& arr, int l, int r, unsigned long long& sum);
void Partition(int*& arr, int l, int& pivot, int r, unsigned long long& sum);
void FindMedian(int& low, int& mid, int& high);


int main()
{
	const int num = 10;
	unsigned long long sum = 0;
	int* arr = new int[num];
	for (int i = 0; i < num; i++)
		cin >> arr[i];
	QuickSort(arr, 0, num - 1, sum);
	for (int i = 0; i < num; i++)
		cout << arr[i] << " ";
	//cout << sum;
}

void FindMedian(int& low, int& mid, int& high)
{
	if (high < low)
		swap(high, low);
	if (high < mid)
		swap(high, mid);
	if (mid < low)
		swap(mid, low);
}

void Partition(int*& arr, int l, int& pivot, int r, unsigned long long& sum)
{
	FindMedian(arr[l], arr[pivot], arr[r]);
	if (pivot != 0)
		swap(arr[l], arr[pivot]);
	int p = arr[l];
	int i = l + 1;
	int j = i;
	for (; j <= r; j++)
		if (arr[j] < p)
		{
			swap(arr[i], arr[j]);
			i++;
		}
	swap(arr[i - 1], arr[l]);
	pivot = i - 1;
}

void QuickSort(int*& arr, int l, int r, unsigned long long& sum)
{
	if (l >= r)
		return;
	int p = (l+r)/2;
	Partition(arr, l, p, r, sum);
	for (int i = 0; i <= r; i++)
		cout << arr[i] << " ";
	cout << endl;
	QuickSort(arr, l, p - 1, sum);
	QuickSort(arr, p + 1, r, sum);
}