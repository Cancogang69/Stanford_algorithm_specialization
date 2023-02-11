using System;
using System.IO;

namespace Prim;

public class vertex
{
    public int this_vertex;
    public int outgoing_vertex;
    public int length;
    public vertex(int _this_vertex, int _outgoing_vertex, int _length)
    {
        this_vertex= _this_vertex;
        outgoing_vertex = _outgoing_vertex;
        length = _length;
    }
}

public static class MinHeap
{
    private static void swap<type>(ref List<type> Arr, int position_1, int position_2)
    {
        type temp = Arr[position_1];
        Arr[position_1] = Arr[position_2];
        Arr[position_2] = temp; 
    }

    public static bool Heapify(ref List<vertex> vertices, int parent, int left_child, int right_child, ref int next_pos)
    {
        int smallest = parent;
        
        if(vertices[smallest].length > vertices[left_child].length)
        {
            smallest = left_child;
            next_pos = left_child;
        }

        if(vertices[smallest].length > vertices[right_child].length)
        {
            smallest = right_child;
            next_pos = right_child;
        }
        
        if(smallest==parent)
            return false;

        swap<vertex>(ref vertices, parent, smallest);
        return true;
    }

    public static void Insert(ref List<vertex> vertices, vertex new_value)
    {
        vertices.Add(new_value);

        int heap_size = vertices.Count-1;
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
            bool can_we_stop = !Heapify(ref vertices, parent, left_child, right_child,ref dummy);

            if(can_we_stop)
                break;

            parent = (parent-1)/2;
        }
    }

    public static void DeleteMinValue(ref List<vertex> vertices)
    {
        int heap_size = vertices.Count-1;
        swap<vertex>(ref vertices, 0, heap_size);
        vertices.RemoveAt(heap_size);

        heap_size = vertices.Count-1;
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
            
            int smallest = parent;
            bool can_we_stop = !Heapify(ref vertices, parent, left_child, right_child, ref smallest);

            if(can_we_stop)
                break;

            parent = smallest;
        }
    }
}

public static class Prim
{
    public static void ReadDataGraph(ref List<vertex>[] Graph, string file_name, int size)
    {
        for(int i=0; i<size; i++)
            Graph[i] = new List<vertex>();

        using(StreamReader data = File.OpenText(file_name))
        {
            string? line = data.ReadLine();

            while(line != null)
            {
                string[] number = line.Split(' ');
                int vertex1 = int.Parse(number[0]);
                int vertex2 = int.Parse(number[1]);
                int length = int.Parse(number[2]);
                vertex new_vertex1 = new vertex(vertex1, vertex2, length);
                vertex new_vertex2 = new vertex(vertex2, vertex1, length);
                Graph[vertex1-1].Add(new_vertex1);
                Graph[vertex2-1].Add(new_vertex2);
                line = data.ReadLine();
            }
        }
    }

    static void VertexToHeap(ref List<vertex> vertices, ref List<vertex> heap, int this_vertex)
    {
        foreach(vertex node in vertices)
        {
            if(node.outgoing_vertex==this_vertex)
                continue;
            MinHeap.Insert(ref heap, node);
        }
        
        vertices.Clear();
    }

    private static bool are_we_done(bool[] spanning_tree)
    {
        foreach(bool node in spanning_tree)
            if(node == false)
                return false;

        return true;
    }

    public static long PrimAlgo(List<vertex>[] Graph, bool[] spanning_tree, int start_node)
    {
        long result = 0;
        List<vertex> vertex_heap = new List<vertex>();

        int dummy = 0;                                      //it's the begin and we dont need to check here
        VertexToHeap(ref Graph[start_node], ref vertex_heap, dummy);
        spanning_tree[start_node]=true;

        while(true)
        {
            int outgoing_vertex = vertex_heap[0].outgoing_vertex;
            int this_vertex = vertex_heap[0].this_vertex;
            if(spanning_tree[this_vertex-1]==true && spanning_tree[outgoing_vertex-1]==false)
            {
                result+= vertex_heap[0].length;
                spanning_tree[outgoing_vertex-1]=true;
            }

            if(are_we_done(spanning_tree))
                break;
            MinHeap.DeleteMinValue(ref vertex_heap);
            VertexToHeap(ref Graph[outgoing_vertex-1], ref vertex_heap, this_vertex);
        }

        return result; 
    }
}
