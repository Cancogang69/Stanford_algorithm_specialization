using DataProcessing;
namespace Knapsack;

public class knap {
    public int value;
    public int weight;
    public knap(int _value, int _weight) {
        value = _value;
        weight = _weight;
    }
    public static knap operator+(knap a, knap b) => new knap(a.value+b.value, a.weight+b.weight);
    public static bool isEqual(knap a, knap b) => a.value==b.value && a.weight == b.weight;
}

public static class KnapProbSolve {
    private static knap findMax(List<knap> list) {
        knap max = new knap(0,0);
        int size = list.Count();
        for(int i=0; i<size; i++) {
            knap node = list[i];
            if(node.value > max.value)
                max = list[i];
        }

        return max;
    }

    private static void maxKnap(List<knap> list, ref List<knap> solList, int knapCapacity, int lastIndex) {
        List<knap> solList1 = solList;
        List<knap> solList2 = new List<knap>();
        int size1 = solList1.Count();
        knap node = list[lastIndex];
        for(int i=0; i<size1; i++) {
            knap newNode = solList1[i] + node;
            if(newNode.weight<=knapCapacity)
                solList2.Add(newNode);
        }

        int size2 = solList2.Count();
        int size = size1+size2;
        List<knap> newSolList = new List<knap>();
        knap gateKeeper = new knap(-1,-1);
        int pointer1=0;
        int pointer2=0;
        while(size-->0) {
            int flag;
            knap newfoe;
            if(pointer1==size1)
                flag = 2;
            else if(pointer2==size2)
                flag = 1;
            else if(solList1[pointer1].weight>solList2[pointer2].weight)
                flag = 2;
            else 
                flag = 1;
            if(flag == 1) {
                newfoe = solList1[pointer1];
                pointer1++;
            } else {
                newfoe = solList2[pointer2];
                pointer2++;
            }

            if(newfoe.weight>gateKeeper.weight && newfoe.value>gateKeeper.value) {
                newSolList.Add(newfoe);
                gateKeeper = newfoe;
            }
        }
        solList = newSolList; 
    }

    public static void FindOptimalSolution(List<knap> list, int knapCapacity) {
        int size = list.Count();
        List<knap> solList = new List<knap>();
        solList.Add(list[0]);
        solList.Add(list[1]);

        for(int i=2; i<size; i++)
            maxKnap(list, ref solList, knapCapacity, i);

        knap champion = solList[solList.Count()-1];
        Console.WriteLine(champion.value + " " + champion.weight);
    }
}