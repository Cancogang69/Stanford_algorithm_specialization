using System.IO;

namespace JobSchedule;
public class Job 
{
    public int weight;
    public int length;

    public Job(int _weight, int _length)
    {
        weight = _weight;
        length = _length;
    }
    
    public int Differences()
    {
        return weight - length;
    }

    public double Ratio()
    {
        return (double) weight/length;
    }
}

public static class MaxHeap
{
    public static void swap<type>(ref List<type> Arr, int position_1, int position_2)
    {
        type temp = Arr[position_1];
        Arr[position_1] = Arr[position_2];
        Arr[position_2] = temp; 
    }

    public static bool Heapify(ref List<Job> jobs, int parent, int left_child, int right_child, ref int next_pos, int parameter)
    {
        int largest = parent;
        dynamic pm = 0;
        if(parameter==1)
            pm = jobs[largest].Differences()-jobs[left_child].Differences();
        else
            pm = jobs[largest].Ratio()-jobs[left_child].Ratio();
        
        
        if(pm<0)
        {
            largest = left_child;
            next_pos = left_child;
        }
        else if(pm==0 && jobs[largest].weight<jobs[left_child].weight)
        {
            largest = left_child;
            next_pos = left_child;
        }
        
        if(parameter==1)
            pm = jobs[largest].Differences()-jobs[right_child].Differences();
        else
            pm = jobs[largest].Ratio()-jobs[right_child].Ratio();
        
        if(pm<0)
        {
            largest = right_child;
            next_pos = right_child;
        }
        else if(pm==0 && jobs[largest].weight<jobs[right_child].weight)
        {
            largest = right_child;
            next_pos = right_child;
        }
        
        if(largest==parent)
            return false;

        swap(ref jobs, parent, largest);
        return true;
    }

    public static void Insert(ref List<Job> jobs, Job new_value, int parameter)
    {
        jobs.Add(new_value);

        int heap_size = jobs.Count-1;
        int parent = (heap_size-1)/2;
        while(true)
        {
            if(parent < 0)
                return;

            int left_child = parent*2+1; 
            int right_child = parent*2+2;

            if(left_child>heap_size)
                return;
            if(right_child>heap_size)
                right_child=parent;
            
            int dummy = 0;
            bool can_we_stop = !Heapify(ref jobs, parent, left_child, right_child,ref dummy, parameter);

            if(can_we_stop)
                break;

            parent = (parent-1)/2;
        }
    }

    public static void DeleteMaxValue(ref List<Job> jobs, int parameter)
    {
        int heap_size = jobs.Count-1;
        swap<Job>(ref jobs, 0, heap_size);
        jobs.RemoveAt(heap_size);

        heap_size = jobs.Count-1;
        int parent = 0;
        while(true)
        {
            if(parent >= heap_size)
                return;

            int left_child = parent*2+1;
            int right_child = parent*2+2;

            if(left_child>heap_size)
                return;
            if(right_child>heap_size)
                right_child=parent;
            
            int largest = parent;
            bool can_we_stop = !Heapify(ref jobs, parent, left_child, right_child, ref largest, parameter);

            if(can_we_stop)
                break;

            parent = largest;
        }
    }
}

public static class JobSchedule
{
    public static void ReadDataSchedule(ref List<Job> jobs, string file_name, int parameter)
    {
        using(TextReader data = File.OpenText(file_name))
        {
            string? line = data.ReadLine();
            while(line != null)
            {
                string[] bits = line.Split(' ');
                Job new_Job = new Job(0,0);
                new_Job.weight = int.Parse(bits[0]);
                new_Job.length = int.Parse(bits[1]);
                MaxHeap.Insert(ref jobs, new_Job, parameter);
                line = data.ReadLine();
            }
        }
    }

    public static long DCompletionTime(List<Job> jobs)
    {
        long completion_time = 0;
        long time = 0;

        while(true)
        {
            
            time += (long) jobs[0].length;
            completion_time+= (long) (jobs[0].weight*time);
            
            if(jobs.Count==1)
                break;
            MaxHeap.DeleteMaxValue(ref jobs, 1);
        }

        return completion_time;
    }

    public static double RCompletionTime(List<Job> jobs)
    {
        double completion_time = 0;
        double time = 0;

        while(true)
        {
            time += (double) jobs[0].length;
            completion_time+= (double) (jobs[0].weight*time);
            
            if(jobs.Count==1)
                break;
            MaxHeap.DeleteMaxValue(ref jobs, 2);
        }   
        return completion_time;
    }
}
