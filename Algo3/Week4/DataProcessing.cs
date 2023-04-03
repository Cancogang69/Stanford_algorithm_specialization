using Knapsack;
namespace DataProcessing;

public static class Processing {
    public static bool ReadData(ref List<knap> list, ref int capacity, string fileName) {
        bool flag = File.Exists(fileName);
        if(flag == false) {
            Console.WriteLine("Data file is not exist!");
            return false;
        }
        using(StreamReader data = File.OpenText(fileName)) {
            string? line = data.ReadLine();
            
            if(line==null) {
                Console.WriteLine("This data file is empty!");
                return false;
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
        return flag;
    }

    public static void WriteData(List<knap> list) {
        using(StreamWriter data = new StreamWriter("sortList.txt")) {
            for(int i=0; i<list.Count(); i++)
                data.WriteLine(list[i].value + " " + list[i].weight);
        }
    }
}