using System;

namespace 作业2
{
    class Program
    {

        static void Main(string[] args)
        {
            int n;
            int[] arr;
            Console.WriteLine("The number of array: ");
            n = Convert.ToInt32(Console.ReadLine());
            arr = new int[n];
            for (int i = 0; i < n; i++)
                arr[i] = Convert.ToInt32(Console.ReadLine());
            for (int i = 0; i < n/2; i++)
            {
                int temp = arr[i];
                arr[i] = arr[n-1 - i];
                arr[n - 1 - i] = temp; 
            }
            foreach (int i in arr) Console.Write("{0} ", i);
            Console.WriteLine();
            Console.Read();
        }
    }
}
