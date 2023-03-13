namespace HuffmanCode;

//if it's a sub-tree node or root node, value means sum of all its children-node's values
//if it's a leaf node, value means its value
public class tree {
    public long value;
    public tree? lChild;
    public tree? rChild;
    public tree(long _value) {
        value = _value;
        lChild = null;
        rChild = null;
    }

    private static void Link(ref tree parent, tree child, bool rightChild) {
        if(rightChild)
            parent.rChild = child;
        else 
            parent.lChild = child;
    }

    public static tree Merge(tree left, tree right) {
        var sum = left.value + right.value;
        tree result = new tree(sum);

        Link(ref result, left, false);
        Link(ref result, right, true);
        return result;
    }

    public static bool isLeaf(tree _tree) {
        if(_tree.lChild==null)
            return true;
        
        return false;
    }
} 

public static class HuffmanMethod {

    private static int WhichToMerge(List<long> list, Queue<long> queue) {
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
        
        return new tree(value);
    }

    private static tree rePlant(ref List<tree> forest, ref List<long> forestIndex, long lValue, long rValue) {
        tree left = Plant(ref forest, ref forestIndex, lValue);
        tree right = Plant(ref forest, ref forestIndex, rValue);
        tree sprout = tree.Merge(left, right);

        forest.Add(sprout);
        forestIndex.Add(sprout.value);

        return sprout;
    }

    public static tree encode(List<int> originlist) {
        List<long> list = new List<long>();
        for(int i=0; i<originlist.Count(); i++)
            list.Add((long) originlist[i]);
        Queue<long> queue = new Queue<long>();
        List<tree> forest = new List<tree>();
        List<long> forestIndex = new List<long>();

        int count = list.Count();
        while(count!=1) {
            int lSize = list.Count();
            int lastIndex = lSize-1;
            int flag = WhichToMerge(list, queue);

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
                
                if(lSize>=2 && sprout.value <= list[lastIndex-1])
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
    
    public static void BinaryLength(ref List<int> lengthList, tree huffTree, int lenght) {
        if(tree.isLeaf(huffTree.lChild))
            lengthList.Add(lenght);
        else
            BinaryLength(ref lengthList, huffTree.lChild, lenght+1);

        if(tree.isLeaf(huffTree.rChild))
            lengthList.Add(lenght);
        else
            BinaryLength(ref lengthList, huffTree.rChild, lenght+1);
        
        return;
    }
}