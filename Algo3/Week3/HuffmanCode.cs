namespace HuffmanCode;

//if it's a sub-tree node or root node, value means sum of all its children-node's values
//if it's a leaf node, value means its value
public class Tree {
    long value;
    List<int> leftNodes;
    List<int> rightNodes;
}

public static class DataPreprocess {
    public static void ReadData(string fileName) {
        int sum = 0;
        using(StreamReader data = File.OpenText(fileName)) {
            string? number = data.ReadLine();
            sum += int.Parse(number);
        }
        
        Console.WriteLine(sum);
    }
} 

public static class HuffmanCode {

}