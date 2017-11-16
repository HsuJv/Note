using System;

namespace 作业1
{

    class Program
    {

        public int[] delZero(int[] a)
        {
            int n = 0, k = 0;
            int[] na;
            foreach (int i in a) if (i != 0) n++;
            na = new int[n];
            foreach (int i in a) if (i != 0) na[k++] = i;
            return na;
        }

        static void Main(string[] args)
        {
            int[] oldArr = { 1, 3, 4, 5, 0, 0, 6, 6, 0, 5, 4, 7, 6, 7, 0, 5 };
            int[] newArr;
            Program arr = new Program();
            newArr = arr.delZero(oldArr);
            foreach (int i in newArr) Console.WriteLine(i);
            Console.ReadLine();
        }
    }
}
