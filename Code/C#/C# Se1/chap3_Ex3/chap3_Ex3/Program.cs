using System;

namespace chap3_Ex3
{
    class main
    {
        static int n;
        static long fact(int n)
        {
            if (n == 1) return 1;
            return n * fact(n - 1);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Enter a integer which is between 1 to 20:");
            n = Convert.ToInt32(Console.ReadLine());
            while (n < 1 || n > 20)
            {
                Console.WriteLine("Illegal data!\nPlease enter another number:");
                n = Convert.ToInt32(Console.ReadLine());
            }
            Console.WriteLine("The factorial of {0} is {1}.", n, fact(n));
            Console.ReadLine();
        }
    }
}
