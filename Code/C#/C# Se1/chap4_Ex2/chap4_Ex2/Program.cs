using System;

namespace chap4_Ex2
{
    class main
    {
        static void Main(string[] args)
        {
            int n, min, max;
            int[] arr;
            Console.WriteLine("The number of array: ");
            n = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Enter the array:");
            arr = new int[n];
            for (int i = 0; i < n; i++)
                arr[i] = Convert.ToInt32(Console.ReadLine());
            max = min = arr[0];
            foreach (int i in arr)
            {
                if (max < i) max = i;
                if (min > i) min = i;
            }
            Console.WriteLine("The maximun is {0}, and the minimun is {1}.", max, min);
            Console.ReadLine();
        }
    }
}
