namespace IndependentSet;

public static class ISMethod {
    private static long Compare(List<long> maxWISList, int rBorderVertex, int rBVpos) {
        long a1 = maxWISList[rBVpos];
        long a2 = maxWISList[rBVpos-1]+rBorderVertex;

        if(a1>a2)
            return a1;
        else
            return a2;
    }
    public static void FindIndepentSet(List<int> weightList, ref List<long> maxWISList) {
        //init max[0] = 0
        //max[1] = first vertex value
        maxWISList.Add(0);
        maxWISList.Add(weightList[0]);

        //because IS of first vertex is store in max[1]
        //and first vertex is store in weight[0]
        //so we will store IS of vertex i in max[i+1]
        int size = weightList.Count();
        for(int i=1; i<size; i++) {
            maxWISList.Add(Compare(maxWISList, weightList[i], i));
        }
    }

    private static bool isBVInIS(List<long> maxWISList, int rBVpos) {
        if(maxWISList[rBVpos]==maxWISList[rBVpos-1])
            return false;
        else
            return true;
    }

    public static void FindVerticeInIS(List<int> weightList, List<long> maxWISList, ref List<bool> flag) {
        for(int i=0; i<weightList.Count(); i++)
            flag.Add(new bool());
            
        int size = maxWISList.Count();
        for(int i=size-1; i>0; i--) {
            if(isBVInIS(maxWISList, i)) {
                int vPos = i-1;
                flag[vPos] = true;
                i--;
            }
        }
    }
}