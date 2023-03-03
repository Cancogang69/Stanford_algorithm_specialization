using System.Text.RegularExpressions;
namespace Clustering;

public class edge {
    public int node1 {get; set;}
    public int node2 {get; set;}
    public int distance {get; set;}
    public edge(int _node1, int _node2, int _distance) {
        node1 = _node1;
        node2 = _node2;
        distance = _distance;
    }
}

public class bitsPointer {
    public int value {get; set;}
    public int leaderPos {get; set;}
    public bitsPointer(int _value, int _leaderPos) {
        value = _value;
        leaderPos = _leaderPos;
    }
}

public class bitsNode {
    public int value {get; set;}
    public int pointerPos {get; set;}
    public bitsNode(int _value) {
        value = _value;
    }
}

public static class DataProcess {
    public static void MatrixListInit<type>(ref List<List<type>> matrix, int size) {
        for(int i=0; i<size; i++)
            matrix.Add(new List<type>());
    }

    public static int BinToDec(char[] bits, int size) {
        int dec = 0;
        for(int i=size-1, power=1; i>=0; i--, power*=2)
            if(bits[i]=='1')
                dec+= power;

        return dec;
    }

    public static char[] DecToBin(int dec, int size) {
        char[] bits = new char[size];

        for(int i= size-1; dec != 0; i--, dec/=2) {
            int bit = dec%2;
            if(bit==1)
                bits[i] = '1';
            else
                bits[i] = '0';
        }

        return bits;
    }

    public static int Hash(int hashSize, int number) { 
        return number%hashSize;
    }

    public static int[] FindPosHashList(List<List<bitsNode>> graph, int hashSize, int number) {
        int[] pos = new int[2];
        pos[0] = Hash(hashSize, number);
        for(int i=0; i< graph[pos[0]].Count(); i++)
            if(graph[pos[0]][i].value == number) {
                pos[1] = i;
                return pos;
            }

        int[] error = {-1, -1};
        return error;
    }

    public static char[] RemoveWhitespace(this string input) {
        string result = new string(input.ToCharArray().Where(c => !char.IsWhiteSpace(c)).ToArray());
        return result.ToCharArray();
    }

    public static void ReadBitsGraph(ref List<List<bitsNode>> graph, ref List<int> node, string FileName, int hashSize) {
        MatrixListInit(ref graph, hashSize);

        using(StreamReader data = File.OpenText(FileName)) {
            string? line = data.ReadLine();

            while(line!=null) {
                char[] bits = RemoveWhitespace(line);
                bitsNode newNode = new bitsNode(BinToDec(bits, 24));
                
                if(FindPosHashList(graph, hashSize, newNode.value)[1]==-1) {
                    graph[Hash(hashSize, newNode.value)].Add(newNode);
                    node.Add(newNode.value);
                }
                
                line = data.ReadLine();
            }
        }
    }

    public static void ReadGraph(ref List<edge> graph, string FileName) {
        using(StreamReader data = File.OpenText(FileName)) {
            string? line = data.ReadLine();

            while(line!=null) {
                string[] number = line.Split(' ');
                int node1 = int.Parse(number[0]);
                int node2 = int.Parse(number[1]);
                int distance = int.Parse(number[2]);
                graph.Add(new edge(node1, node2, distance));
                line = data.ReadLine();
            }
        }
    }

    public static void swap<type>(ref List<type> arr, int pos1, int pos2) {
        type temp = arr[pos1];
        arr[pos1] = arr[pos2];
        arr[pos2] = temp;
    }

    static private int EdgePartition(ref List<edge> graph, int high, int low) {
        int pivot = graph[high].distance;

        //i is the position that right next to pivot
        int i = low - 1;

        //j use to scan through list
        for(int j=low; j<=high-1; j++) {
            if(graph[j].distance < pivot) {
                i++;
                swap(ref graph, i, j);
            }
        }

        swap(ref graph, i+1, high);
        return i+1;
    }

    public static void EdgeQuickSort(ref List<edge> graph, int low, int high) {
        if(low<high) {
            int pi = EdgePartition(ref graph, high, low);
            EdgeQuickSort(ref graph, low, pi-1);
            EdgeQuickSort(ref graph, pi+1, high);
        }
    }

    static private int Partition(ref List<int> graph, int high, int low) {
        int pivot = graph[high];

        //i is the position that right next to pivot
        int i = low - 1;

        //j use to scan through list
        for(int j=low; j<=high-1; j++) {
            if(graph[j] < pivot) {
                i++;
                swap(ref graph, i, j);
            }
        }

        swap(ref graph, i+1, high);
        return i+1;
    }

    public static void QuickSort(ref List<int> graph, int low, int high) {
        if(low<high) {
            int pi = Partition(ref graph, high, low);
            QuickSort(ref graph, low, pi-1);
            QuickSort(ref graph, pi+1, high);
        }
    }

}

public static class Cluster {
    private static int FindUnion(ref int[] pointerList, int node) {
        int unionLeader = node;

        //if node and its pointer are equal then it's the union leader
        while(unionLeader != pointerList[unionLeader-1]) 
            unionLeader = pointerList[unionLeader-1];

        //replace old unionLeader with new unionLeader
        pointerList[node-1] = unionLeader;

        return unionLeader;
    }

    //check if 2 node in same union
    public static bool UnionCheck(ref int[] pointerList, int node1, int node2) {
        if(FindUnion(ref pointerList, node1) == FindUnion(ref pointerList, node2))
            return true;
        else
            return false;
    }
    
    public static void FuseUnion(ref int[] pointerList, int node1, int node2) {
        int newUnionLeader = FindUnion(ref pointerList, node1);
        int loser = FindUnion(ref pointerList, node2);
        pointerList[loser-1] = newUnionLeader; 
    }

    public static int UnionCount(ref int[] pointerList) {
        List<int> leaderGroup = new List<int>();
        for(int i = 0; i<500; i++ ) {
            int unionLeader = FindUnion(ref pointerList, pointerList[i]);

            bool check = false;
            for(int j = 0; j<leaderGroup.Count(); j++) 
                if(unionLeader == leaderGroup[j]) {
                    check = true;
                    break;
                }

            if(check)
                continue;
            leaderGroup.Add(unionLeader);
        }

        return leaderGroup.Count();
    }
}

public static class BitCluster {
    
    private static int FindUnion(ref List<List<bitsNode>> graph, ref List<bitsPointer> list, 
                                 int hashSize, int number) {
        int[] pos = DataProcess.FindPosHashList(graph, hashSize, number);

        //pos[0] equal -1 mean node aren't in the graph
        if(pos[0]==-1)
            return -1;

        int valuePos = graph[pos[0]][pos[1]].pointerPos;
        int leaderPos = list[valuePos].leaderPos;

        //this variant are used to replace unionLeader
        int rePos = valuePos;

        //if value and unionLeader are equal then it's the union leader
        while(valuePos != leaderPos) {
            valuePos = leaderPos;
            leaderPos = list[valuePos].leaderPos;
        }

        //replace old unionLeader with new unionLeader
        list[rePos].leaderPos = leaderPos;

        return valuePos;
    }
    public static int UnionCheck(List<List<bitsNode>> graph, ref List<bitsPointer> list, 
                                 int hashSize, int num1, int num2) {
        int leader1 = FindUnion(ref graph, ref list, hashSize, num1);
        int leader2 = FindUnion(ref graph, ref list, hashSize, num2);
        
        // leader1 or leader2 equal -1 mean the node aren't in graph
        if(leader1 ==-1 || leader2==-1)
            return -1;
        // leader1 == leader2 mean they in the same union
        if(leader1 == leader2)
            return 1;
        else
            return 0;
    }

    public static void FuseUnion(List<List<bitsNode>> graph, ref List<bitsPointer> list, 
                                 int hashSize, int num1, int num2) {
        int newLeaderPos = FindUnion(ref graph, ref list, hashSize, num1);
        int loserPos = FindUnion(ref graph, ref list, hashSize, num2);

        list[loserPos].leaderPos = newLeaderPos;
    }

    private static void replaceBit(char[] bits, ref char[] difBits, int pos) {
        if(bits[pos]=='0')
            difBits[pos]='1';
        else
            difBits[pos]='0';
    }

    public static void Check1BitDif(ref List<List<bitsNode>> graph, ref List<bitsPointer> list, 
                                    int row, int column, ref int bitsUnion, int hashSize) {
        int bitsSize = 24;
        int value = graph[row][column].value;
        char[] bits = DataProcess.DecToBin(value, bitsSize);

        for(int i=0; i<bitsSize; i++) {
            char[] oneBitDif = new char[bitsSize];
            Array.Copy(bits, oneBitDif, bitsSize);

            replaceBit(bits, ref oneBitDif, i);

            int newFoe = DataProcess.BinToDec(oneBitDif, bitsSize);
            if(UnionCheck(graph, ref list, hashSize, value, newFoe) == 0) {
                FuseUnion(graph, ref list, hashSize, value, newFoe);
                bitsUnion--;
            }
        }
    }

    public static void Check2BitDif(ref List<List<bitsNode>> graph, ref List<bitsPointer> list, 
                                    int row, int column, ref int bitsUnion, int hashSize) {
        int bitsSize = 24;
        int value = graph[row][column].value;
        char[] bits = DataProcess.DecToBin(value, bitsSize);

        for(int distance=1; distance<bitsSize; distance++) {
            char[] twoBitDif = new char[bitsSize];
            for(int loop=0; loop+distance<bitsSize; loop++) {
                Array.Copy(bits, twoBitDif, bitsSize);
                replaceBit(bits, ref twoBitDif, loop);
                replaceBit(bits, ref twoBitDif, loop+distance);

                int newFoe = DataProcess.BinToDec(twoBitDif, bitsSize);
                if(UnionCheck(graph, ref list, hashSize, value, newFoe) == 0) {
                    FuseUnion(graph, ref list, hashSize, value, newFoe);
                    bitsUnion--;
                }  
            }
        }
    }
}
