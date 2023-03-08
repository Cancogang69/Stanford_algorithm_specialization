namespace HuffmanCode;

//if it's a sub-tree node or root node, value means sum of all its children-node's values
//if it's a leaf node, value means its value
//the first node in each list is the direct child of sub-tree
public class tree {
    public int value;
    public List<int> leftValue;
    public List<int> rightValue;
    public List<tree> leftNodes;
    public List<tree> rightNodes;
    public tree(int _value) {
        value = _value;
        leftNodes = new List<tree>();
        rightNodes = new List<tree>();
        leftValue = new List<int>();
        rightValue = new List<int>();
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
        int sum = left.value + right.value;
        tree result = new tree(sum);

        Link(ref result, left, false);
        Link(ref result, right, true);
        return result;
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

    public static void swap<type>(ref List<type> list, int one, int two) {
        type temp = list[one];
        list[one]= list[two];
        list[two]= temp;
    }

    private static int partition(ref List<int> list, int low, int high) {
        int pivot = list[high];

        //i is index of the left element of pivot
        int i = low-1;
        for(int j=low; j<high; j++)
            if (list[j]<pivot) {
                i++;
                swap(ref list, i, j);
            }

        swap(ref list, i+1, high);
        return i+1;  
    }

    public static void Sort(ref List<int> list, int low, int high) {
        if(low<high) {
            int pivot = partition(ref list, low, high);
            Sort(ref list, low, pivot-1);
            Sort(ref list, pivot+1, high);
        }
    }
} 

public static class HuffmanMethod {

    private static int WhichToMerge(ref List<int> list, ref Queue<int> queue) {
        if(queue.Count()==0)
           return 1;
        if(list.Count()==1)
            return 2;

        int sum1 = list[0] + list[1];
        int sum2 = list[0] + queue.Peek();
        if(sum1 < sum2)
            return 1;
        else
            return 2; 
    }

    private static tree Plant(ref List<tree> forest, ref List<int> forestIndex, int value) {
        int count = forestIndex.Count();
        for(int i=0; i<count; i++)
            if(forestIndex[i]==value)
                return forest[i];
        
        tree sprout = new tree(value);
        forest.Add(sprout);
        forestIndex.Add(value);
        return sprout;
    }

    private static tree rePlant(ref List<tree> forest, ref List<int> forestIndex, int lValue, int rValue) {
        tree left = Plant(ref forest, ref forestIndex, lValue);
        tree right = Plant(ref forest, ref forestIndex, rValue);
        tree sprout = tree.Merge(left, right);

        forest.Add(sprout);
        forestIndex.Add(sprout.value);

        return sprout;
    }

    public static tree encode(ref List<int> list) {
        Queue<int> queue = new Queue<int>();
        List<tree> forest = new List<tree>();
        List<int> forestIndex = new List<int>();

        int count = list.Count();
        while(count!=1) {

            int flag = WhichToMerge(ref list, ref queue);

            if(flag==1) {
                tree sprout = rePlant(ref forest, ref forestIndex, list[0], list[1]);

                if(sprout.value <= list[2]) {
                    list[1]=sprout.value;
                    list.RemoveAt(0);
                }
                else {
                    queue.Enqueue(sprout.value);
                    list.RemoveRange(0, 2);
                }
            }
            else if(flag==2) {
                tree sprout = rePlant(ref forest, ref forestIndex, list[0], queue.Dequeue());
                
                if(sprout.value <= list[1])
                    list[0]=sprout.value;
                else {
                    queue.Enqueue(sprout.value);
                    list.RemoveAt(0);
                }
            }
            
            count = list.Count();
        } 

        count = list.Count()+queue.Count();
        while(count!=1) {
            tree sprout = rePlant(ref forest, ref forestIndex, list[0], queue.Dequeue());
            queue.Enqueue(sprout.value);
            list[0] = queue.Dequeue();
            count = list.Count() + queue.Count();
        }

        return forest[forest.Count()-1];
    }

    private static int NodeLength(tree bigTree, int value) {
        for(int i=0; i<bigTree.lef)
    }
    
    public static void  BinaryLength(List<int> list, List<int> length, tree huffTree) {
        for(int i=0; i<list.Count(); i++) {
            
        }
    }
}