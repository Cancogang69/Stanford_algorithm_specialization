namespace HuffmanCode;

//if it's a sub-tree node or root node, value means sum of all its children-node's values
//if it's a leaf node, value means its value
//the first node in each list is the direct child of sub-tree
public class tree {
    public long value;
    public List<long> leftValue;
    public List<long> rightValue;
    public List<tree> leftNodes;
    public List<tree> rightNodes;
    public tree(long _value) {
        value = _value;
        leftNodes = new List<tree>();
        rightNodes = new List<tree>();
        leftValue = new List<long>();
        rightValue = new List<long>();
    }

    private static void Link(ref tree parent, tree child, bool rightChild) {
        if(rightChild) {
            parent.rightNodes.Add(child);
            parent.rightNodes.AddRange(child.leftNodes);
            parent.rightNodes.AddRange(child.rightNodes);

            parent.rightValue.Add(child.value);
            parent.rightValue.AddRange(child.leftValue);
            parent.rightValue.AddRange(child.rightValue);
        }
        else {
            parent.leftNodes.Add(child);
            parent.leftNodes.AddRange(child.leftNodes);
            parent.leftNodes.AddRange(child.rightNodes);

            parent.leftValue.Add(child.value);
            parent.leftValue.AddRange(child.leftValue);
            parent.leftValue.AddRange(child.rightValue);
        }
    }

    public static tree Merge(tree left, tree right) {
        var sum = left.value + right.value;
        tree result = new tree(sum);

        Link(ref result, left, false);
        Link(ref result, right, true);
        return result;
    }
}

public static class DataPreprocess {
    public static void ReadData(ref List<long> list, string fileName) {
        using(StreamReader data = File.OpenText(fileName)) {
            string? number = data.ReadLine();
            while(number!=null) {
                list.Add(long.Parse(number));
                number = data.ReadLine();
            }
        }
    }

    public static void swap<type>(ref List<type> list, int one, int two) {
        type temp = list[one];
        list[one]= list[two];
        list[two]= temp;
    }

    private static int partition(ref List<long> list, int low, int high, bool isDesc) {
        var pivot = list[high];

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

    public static void Sort(ref List<long> list, int low, int high, bool isDesc) {
        if(low<high) {
            var pivot = partition(ref list, low, high, isDesc);
            Sort(ref list, low, pivot-1, isDesc);
            Sort(ref list, pivot+1, high, isDesc);
        }
    }
} 

public static class HuffmanMethod {

    private static int WhichToMerge(ref List<long> list, ref Queue<long> queue) {
        if(queue.Count()==0)
           return 1;
        if(list.Count()==1)
            return 2;

        int lastIndex = list.Count()-1;

        var sum1 = list[lastIndex] + list[lastIndex-1];
        var sum2 = list[lastIndex] + queue.Peek();
        if(sum1 < sum2)
            return 1;
        else
            return 2; 
    }

    private static tree Plant(ref List<tree> forest, ref List<long> forestIndex, long value) {
        int count = forestIndex.Count();
        for(int i=0; i<count; i++)
            if(forestIndex[i]==value)
                return forest[i];
        
        tree sprout = new tree(value);
        forest.Add(sprout);
        forestIndex.Add(value);
        return sprout;
    }

    private static tree rePlant(ref List<tree> forest, ref List<long> forestIndex, long lValue, long rValue) {
        tree left = Plant(ref forest, ref forestIndex, lValue);
        tree right = Plant(ref forest, ref forestIndex, rValue);
        tree sprout = tree.Merge(left, right);

        forest.Add(sprout);
        forestIndex.Add(sprout.value);

        return sprout;
    }

    public static tree encode(List<long> originlist) {
        List<long> list = new List<long>(originlist);
        Queue<long> queue = new Queue<long>();
        List<tree> forest = new List<tree>();
        List<long> forestIndex = new List<long>();

        int count = list.Count();
        while(count!=1) {
            int lSize = list.Count();
            int lastIndex = lSize-1;
            int flag = WhichToMerge(ref list, ref queue);

            if(flag==1) {
                tree sprout = rePlant(ref forest, ref forestIndex, list[lastIndex], list[lastIndex-1]);

                if(lSize>=3 && sprout.value <= list[lastIndex-2]) {
                    list[lastIndex-1]=sprout.value;
                    list.RemoveAt(lastIndex);
                }
                else {
                    queue.Enqueue(sprout.value);
                    list.RemoveRange(lastIndex-1, 2);
                }
            }
            else if(flag==2) {
                tree sprout = rePlant(ref forest, ref forestIndex, list[lastIndex], queue.Dequeue());
                
                if(lSize>=2 && sprout.value <= list[1])
                    list[lastIndex]=sprout.value;
                else {
                    queue.Enqueue(sprout.value);
                    list.RemoveAt(lastIndex);
                }
            }

            lSize = list.Count();
            lastIndex = lSize-1;
            if(lSize==0 || (queue.Count()>0 && queue.Peek()<=list[lSize-1]))
                list.Add(queue.Dequeue());
            
            count = list.Count()+queue.Count();
        } 

        return forest[forest.Count()-1];
    }

    private static int NodeLength(tree bigTree, long value) {
        if(value == bigTree.value)
            return 0;   
        for(int i=0; i<bigTree.leftValue.Count(); i++)
            if(bigTree.leftValue[i]==value) {
                return 1 + NodeLength(bigTree.leftNodes[0], value);
            }
        
        for(int i=0; i<bigTree.rightValue.Count(); i++) 
            if(bigTree.rightValue[i]==value) {
                return 1 + NodeLength(bigTree.rightNodes[0], value);
            }
        
        //this for error detection
        return -1;
    }
    
    public static void  BinaryLength(List<long> list, ref List<long> length, tree huffTree) {
        for(int i=0; i<list.Count(); i++)
            length.Add(NodeLength(huffTree, list[i]));
    }
}