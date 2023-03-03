#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct NODE
{
    int data;
    NODE* pNext;
};

struct LIST
{
    NODE* pHead;
    NODE* pTail;
};

void CreateEmptyList(LIST& l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

NODE* CreateNode(int x)
{
    NODE* p = new NODE;
    p->data = x;
    p->pNext = NULL;
    return p;
}

void AddTail(LIST& l, int x)
{
    NODE* p = CreateNode(x);
    if(l.pHead==NULL)
    {
        l.pHead=p;
        l.pTail=p;
    }
    else
    {
        l.pTail->pNext=p;
        l.pTail=p;
    }
}

void CreateAdjacencyList(LIST*& l)
{   
    ifstream read("text.txt");
    if (read.is_open() == false)
        return;
    for(int i=0;i<200;i++)
    {
        int n;
        read>>n;
        if(n==i+1)
            read>>n;
        CreateEmptyList(l[i]);
        while(n!=-1)
        {
            AddTail(l[i],n);
            read>>n;
        }
    }
}

void PrintList(LIST l, ofstream& write)
{
    if (l.pHead == NULL)
        return;
    NODE* p = l.pHead;
    while (p != NULL)
    {
        write << p->data << "\t";
        p = p->pNext;
    }

}

void PrintAdjList(int* v, LIST* l, ofstream& write)
{
    for (int i = 0; i < 200; i++)
    {
        write << v[i] << "\t";
        PrintList(l[i], write);
        write << endl;
    }
}

void DeleteNode(LIST& l, int x)
{
    if(l.pHead==NULL)
        return;
    if(l.pHead->data==x)
    {
        l.pHead=l.pHead->pNext;
        return;
    }
    NODE* p = l.pHead;
    NODE* pDel = l.pHead->pNext;
    while(pDel!=NULL)
    {
        if(pDel->data==x)
        {
            p->pNext = pDel->pNext;
            if(p->pNext==NULL)
                l.pTail=p;
            return;
        }
        p = p->pNext;
        pDel = pDel->pNext;
    }
}

void MergeList(LIST& l1, LIST& l2, int v1, int v2, int* v, LIST* l)       
//l1: list nguon, l2: list phu, v1: gia tri giu l1, v2: gia tri giu v2  v: mang dinh, x: vi tri l1
{                                                       
    NODE* p1 = l1.pHead;
    while(p1!=NULL)
    {
        int x1 = p1->data;
        if(x1==v2)
        {
            p1 = p1->pNext;
            DeleteNode(l1, x1);
        }
        else 
        p1 = p1->pNext;
    }

    NODE* p2 = l2.pHead;
    while(p2!=NULL)
    {
        int x2 = p2->data;
        if(x2==v1)
        {
            p2=p2->pNext;
            DeleteNode(l2, x2);
        }
        else
        p2 = p2->pNext;
    }
    l1.pTail->pNext = l2.pHead;
    l1.pTail = l2.pTail;

    NODE* p = l1.pHead;
    while(p!=NULL)
    {
        if(p->data == v1)
        {
            p=p->pNext;
            DeleteNode(l1, v1);
        }
        else if(v[p->data-1]==-1)
        {
            p->data= l[p->data-1].pHead->data;
            p=p->pNext;
        }
        else 
        p=p->pNext;
    }
}

void CleanList(LIST& l1, int m, int* v, LIST* l)
{
    NODE* p = l1.pHead;
    while (p != NULL)
    {
        if (p->data == m)
        {
            p = p->pNext;
            DeleteNode(l1, m);
        }
        else if (v[p->data - 1] == -1)
        {
            if (l[p->data - 1].pHead->data == m)
            {
                int x = p->data;
                p = p->pNext;
                DeleteNode(l1, v[x - 1]);
            }
            else
            {
                p->data = l[p->data - 1].pHead->data;
                p = p->pNext;
            }
        }
        else
            p = p->pNext;
    }
}

int MinimumCut(int* v, LIST*& l, int i)
{
    int n = 200;
    NODE* p1 = l[i].pHead;
    while(p1!=NULL)
    {
        int x = p1->data;
        NODE* p2 = l[x-1].pHead;
        if(v[x-1]==-1)
        {
            p1->data=p2->data;
            p1=p1->pNext;
            continue;
        }
        MergeList(l[i], l[x-1], v[i], v[x-1], v, l);
        v[x-1]=-1;
        CreateEmptyList(l[x-1]);
        AddTail(l[x-1], v[i]);
        p1=p1->pNext;
        ofstream write("text_test.txt");
        PrintAdjList(v, l, write);
        for (int m = 0; m < 200; m++)
        {
            if (v[m] != -1)
                CleanList(l[m], m, v, l);
        }
        int count = 0;
        for (int k = 0; k < n; k++)
            if (v[k] != -1)
                count++;
        if (count == 2)
            break;
    }
    int count = 0;
    for (int i = 0; i < n; i++)
        if (v[i] != -1)
            count++;
    if (count != 2)
        return -1;
    int v1,v2;
    int j=0;
    while(j<n)
    {
        if(v[j]!=-1)
        {
            v1=j++;
            break;
        }
        j++;
    }

    while(j<n)
    {
        if(v[j]!=-1)
        {
            v2=j;
            break;
        }
        j++;
    }
    NODE* p = l[v1].pHead;
    int sum=0;
    while(p!=NULL)
    {
        if(p->data==v[v2])
            sum++;
        p=p->pNext;
    }
    if (sum == 0)
    {
        NODE* p3 = l[v2].pHead;
        sum = 0;
        while (p3 != NULL)
        {
            if (p3->data == v[v1])
                sum++;
            p3 = p3->pNext;
        }
    }
    return sum;
}

int main()
{
    int min = 30;
    ofstream write("answer.txt");
    //for (int i = 0; i < 200; i++)
    //{
        LIST* l = new LIST[200];
        int* v = new int[200];
        for (int j = 0; j < 200; j++)
            v[j] = j + 1;
        CreateAdjacencyList(l);
        int x = MinimumCut(v, l, 5);
        write << x << endl;
        if (min > x)
            min = x;
        delete[] l;
        delete[] v;
    //
    cout<<endl<<min<<endl;
}