namespace DataProcessing;

public static class Processing {
    public static void ReadData(ref List<int> list, string fileName) {
        using(StreamReader data = File.OpenText(fileName)) {
            string? number = data.ReadLine();
            while(number!=null) {
                list.Add(int.Parse(number));
                number = data.ReadLine();
            }
        }
    }

    public static void swap<type>(ref List<type> list, int one, int two) {
        type temp = list[one];
        list[one]= list[two];
        list[two]= temp;
    }

    private static int partition(ref List<int> list, int low, int high, bool isDesc) {
        int pivot = list[high];

        //i is index of the neighbor element of pivot
        int i = low-1;
        for(int j=low; j<high; j++)
            if (list[j]>pivot==isDesc) {
                i++;
                swap(ref list, i, j);
            }

        swap(ref list, i+1, high);
        return i+1;  
    }

    public static void Sort(ref List<int> list, int low, int high, bool isDesc) {
        if(low<high) {
            var pivot = partition(ref list, low, high, isDesc);
            Sort(ref list, low, pivot-1, isDesc);
            Sort(ref list, pivot+1, high, isDesc);
        }
    }
}