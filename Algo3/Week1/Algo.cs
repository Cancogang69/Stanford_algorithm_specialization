using System;
using System.IO;
using JobSchedule;
using Prim;

namespace week2
{

    class Program
    {
        static void Main(string[] args)
        {
            //Difference completion time
            List<Job> jobs = new List<Job>();
            string data_name = "data_set_1.txt";
            //data_name = "test_data_set.txt";
            int parameter = 1;                                      //1: parameter = difference
            JobSchedule.JobSchedule.ReadDataSchedule(ref jobs, data_name, parameter);
            long dif_completion_time = JobSchedule.JobSchedule.DCompletionTime(jobs);
            Console.WriteLine(dif_completion_time);
            jobs.Clear();

            //Ration completion time
            jobs = new List<Job>();
            data_name = "data_set_1.txt";
            //data_name = "test_data_set.txt";
            parameter = 2;                                          //2: parameter = ratio
            JobSchedule.JobSchedule.ReadDataSchedule(ref jobs, data_name, parameter);
            double ratio_completion_time = JobSchedule.JobSchedule.RCompletionTime(jobs);
            Console.WriteLine(ratio_completion_time);
            jobs.Clear(); 

            //Prim's algo
            int size = 500;
            bool[] spanning_tree = new bool[size];
            List<vertex>[] Graph = new List<vertex>[size];
            string data_name_2 = "data_set_2.txt";
            //data_name_2 = "test_data_set_2.txt";
            int seed = 5;

            Prim.Prim.ReadDataGraph(ref Graph, data_name_2, size);
            long minimum_spanning_tree = Prim.Prim.PrimAlgo(Graph, spanning_tree, seed);
            Console.WriteLine(minimum_spanning_tree);
        }
    }
}