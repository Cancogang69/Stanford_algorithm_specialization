#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct NODE {
	int info;
	NODE* pNext;
};

struct LIST {
	NODE* pHead;
	NODE* pTail;
};

NODE* CreateNode(int x) {
	NODE* p;
	p = new NODE;
	p->info = x;
	p->pNext = NULL;
	return p;
}
void AddTail(LIST& L, NODE* p) {
	if (L.pHead == NULL) {
		L.pHead = p;
		L.pTail = L.pHead;
	}
	else {
		L.pTail->pNext = p;
		L.pTail = p;
	}
}

void CreateEmptyList(LIST& L) {
	L.pHead = NULL;
	L.pTail = NULL;
}

void CreateList(LIST& L) {
	NODE* p;
	while (true) 
	{
		int x;
		cin >> x;
		if (x == -1)
			break;
		p = CreateNode(x);
		AddTail(L, p);
	}
}

void Merge_Partition(LIST& l, LIST& l1, LIST& l2 , int n)
{
	CreateEmptyList(l1);
	CreateEmptyList(l2);
	if (l.pHead == NULL)
		return;
	for (int i = 0; i<n/2; i++)
	{
		if (l.pHead == NULL)
			break;
		AddTail(l1, l.pHead);
		l.pHead = l.pHead->pNext;
	}
	while (l.pHead != NULL)
	{
		AddTail(l2, l.pHead);
		l.pHead = l.pHead->pNext;
	}
	if (l1.pHead != NULL)
		l1.pTail->pNext = NULL;
	if (l2.pHead != NULL)
		l2.pTail->pNext = NULL;
}

void Merge_2_Sorted_LL(LIST& l, LIST& l1, LIST& l2, unsigned long long& sum)
{
	CreateEmptyList(l);
	while (l1.pHead != NULL && l2.pHead != NULL)
	{
		if (l1.pHead->info < l2.pHead->info)
		{
			AddTail(l, l1.pHead);
			l1.pHead = l1.pHead->pNext;
		}
		else
		{
			NODE* temp = l1.pHead;
			while (temp != NULL)
			{
				sum++;
				temp = temp->pNext;
			}
			AddTail(l, l2.pHead);
			l2.pHead = l2.pHead->pNext;
		}
	}
	while (l1.pHead != NULL)
	{
		AddTail(l, l1.pHead);
		l1.pHead = l1.pHead->pNext;
	}
	while (l2.pHead != NULL)
	{
		AddTail(l, l2.pHead);
		l2.pHead = l2.pHead->pNext;
	}
}

void mergesort_ascending(LIST& l, int n, unsigned long long& sum)
{
	if (l.pHead == NULL || l.pHead->pNext == NULL)
		return;
	LIST l1, l2;
	CreateEmptyList(l1);
	CreateEmptyList(l2);
	Merge_Partition(l, l1, l2 , n);
	mergesort_ascending(l1, n / 2, sum);
	mergesort_ascending(l2, n / 2 + 1, sum);
	Merge_2_Sorted_LL(l, l1, l2, sum);
}

int length(NODE* p) {
	int i = 0;
	while (p) {
		i++;
		p = p->pNext;
	}
	return i;
}

void PrintList(NODE* p) {
	if (p == NULL)
		cout << "Empty List.";
	else {
		cout << length(p) << endl;
		while (p) {
			cout << p->info << " ";
			p = p->pNext;
		}
	}
}

int main() {
	LIST L;
	CreateEmptyList(L);

	CreateList(L);
	int n;
	cin >> n;
	unsigned long long sum = 0;
	mergesort_ascending(L, n, sum);
	cout << endl << sum;
	return 0;
}