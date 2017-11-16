using System;
using System.Data;

namespace Chap5_Ex1
{
    interface Area
    {
        double calcArea(double r);
    }

    interface Volume
    {
        double calcVolume(double a, double b, double c);
    }

    class Program : Area, Volume
    {
        public double calcVolume(double a, double b, double c)
        {
            return a * b * c;
        }

        public double calcArea(double r)
        {
            return r * r * Math.PI;
        }

        public double inputPosDouble()
        {
            double a;
            a = Convert.ToDouble(Console.ReadLine());
            while (a < 0)
            {
                Console.WriteLine("Invid data, please retry.");
                a = Convert.ToDouble(Console.ReadLine());
            }
            return a;
        }

        static void Main(string[] args)
        {
            double r, a, b, c;
            Program i = new Program();
            Console.WriteLine("Enter the radii of a circle:");
            r = i.inputPosDouble();
            Console.WriteLine("Enter the length of three sides of a cube:");
            a = i.inputPosDouble();
            b = i.inputPosDouble();
            c = i.inputPosDouble();
            Console.WriteLine("The area of this circle is {0}.", Math.Round(i.calcArea(r), 2));
            Console.WriteLine("The volume of this cube is {0}.", Math.Round(i.calcVolume(a, b, c), 2));
            Console.ReadLine();
        }
    }
}
