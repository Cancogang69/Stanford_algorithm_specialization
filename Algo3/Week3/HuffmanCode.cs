namespace HuffmanCode;

//if it's a sub-tree node or root node, value means sum of all its children-node's values
//if it's a leaf node, value means its value
public class tree {
    int value;
    List<int> leftNodes;
    List<int> rightNodes;
    public tree(int _value) {
        value = _value;
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
} 

public static class HuffmanCode {

}