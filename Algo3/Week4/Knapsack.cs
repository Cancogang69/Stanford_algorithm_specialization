namespace Knapsack;

public class knap {
    public int value;
    public int weight;
    public knap(int _value, int _weight) {
        value = _value;
        weight = _weight;
    }

    public static knap operator +(knap a, knap b) 
    => new knap(a.value+b.value, a.weight+b.weight);
}

public static class KnapProbSolve {

    public static void OptimalSolution(List<knap> list, ref List<knap> solList, int knapCapacity, int pos) {
        int n1Pos = pos-1;
        if(solList.Count()-1 < n1Pos)
            OptimalSolution(list, ref solList, knapCapacity, n1Pos);
        
        int newCapacity = knapCapacity - list[pos].weight;
        knap newNode = null;
        for(int i=n1Pos; i>=0; i--)
            if(solList[i].weight<=newCapacity) {
                newNode = list[pos] + solList[i];
                break;
            }

        if(newNode.value > solList[n1Pos].value)
            solList.Add(newNode);
        else
            solList.Add(solList[n1Pos]);
    }
}