namespace HuffmanCode;

//if it's a sub-tree node or root node, value means sum of all its children-node's values
//if it's a leaf node, value means its value
public class tree {
    int value;
    List<tree> leftNodes;
    List<tree> rightNodes;
    public tree(int _value) {
        value = _value;
        leftNodes = new List<tree>();
        rightNodes = new List<tree>();
    }
}

public static class DataPreprocess {
    public static void ReadData(ref List<int> list, string fileName) {
        using(StreamReader data = File.OpenText(fileName)) {
            string? number = data.ReadLine();
            while(number!=null) {
                list.Add(int.Parse(number));
                number = data.ReadLine();
            }
        }
    }

    public static void swap<T>(ref List<T> list, int one, int two) {
        T temp = list[one];
        list[one]= list[two];
        list[two]= temp;
    }

    private static int partition(ref List<int> list, int low, int high) {
        int pivot = list[high];

        //i is index of the left element of pivot
        int i = low-1;
        for(int j=low; j<high-1; j++) {
            if (list[j]<pivot) {
                i++;
                swap(ref list, i, j);
            }
        }
        swap(ref list, i+1, high);
        return i+1;  
    }

    public static void Sort(ref List<int> list, int low, int high) {
        if(low<high) {
            int pivot = partition(ref list, low, high);
            Sort(ref list, pivot+1, high);
            Sort(ref list, low, pivot-1);
        }
    }
} 

public static class HuffmanMethod {

}