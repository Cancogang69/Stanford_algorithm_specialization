using Knapsack;
namespace DataProcessing;

public static class Processing {
    public static void ReadData(ref List<knap> list, ref int capacity, string fileName) {
        using(StreamReader data = File.OpenText(fileName)) {
            string? line = data.ReadLine();
            if(line==null) {
                Console.WriteLine("This data file is empty or not exist!");
                return ;
            }

            string[] initNum = line.Split(" ");
            capacity = int.Parse(initNum[0]);
            list = new List<knap>(int.Parse(initNum[1]));
            list.Add(new knap(0,0));
            line = data.ReadLine();
            while(line!=null) {
                string[] nums = line.Split(" ");
                knap newNode = new knap(int.Parse(nums[0]), int.Parse(nums[1]));
                list.Add(newNode);
                line = data.ReadLine();
            }
        }
    }

    private static void swap<type>(ref List<type> list, int pos1, int pos2) {
        type temp = list[pos1];
        list[pos1] = list[pos2];
        list[pos2] = temp;
    }

    private static int Partition(ref List<knap> list, int low, int high) {
        int pivotValue = list[high].weight;

        int i = low - 1;
        for(int j=low; j<high; j++) {
            if(list[j].weight<pivotValue) {
                i++;
                swap(ref list, i, j);
            }
        }

        swap(ref list, i+1, high);
        return i+1;

    }

    private static void QuickSort(ref List<knap> list, int low, int high) {
        if(low<high) {
            int pi = Partition(ref list, low, high);
            QuickSort(ref list, low, pi-1);
            QuickSort(ref list, pi+1, high);
        }
    }

    public static void KnapWeigthSort(ref List<knap> list) {
        int low = 0;
        int high = list.Count() -1;
        QuickSort(ref list, low, high);
    }

    public static void Combing(ref List<knap> list) {
        List<knap> newList = new List<knap>(list.Count());
        newList.Add(list[0]);

        int pointerPos = 0;
        for(int i=1; i<list.Count(); i++, pointerPos++) {
            if(list[i].weight==newList[pointerPos].weight) {
                if(list[i].value > newList[pointerPos].value) {
                    newList[pointerPos].value = list[i].value;
                    pointerPos--;
                }
                else {
                    pointerPos--;
                    continue; 
                }       
            } 
            else
                newList.Add(list[i]);
        }
        list = new List<knap>(newList);
    }
}