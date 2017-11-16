using System;

namespace chap2_Ex9
{
    class main
    {
        static void Main(string[] args)
        {
            int n;
            bool leap = false;
            Console.WriteLine("Enter a number that represents year:");
            n = Convert.ToInt32(Console.ReadLine());
            if (n % 400 == 0 || (n % 4 == 0 && n % 100 != 0)) leap = true;
            if (leap) Console.WriteLine("{0} is a leap year", n);
            else Console.WriteLine("{0} is not a leap year", n);
            Console.ReadLine();
        }
    }
}
