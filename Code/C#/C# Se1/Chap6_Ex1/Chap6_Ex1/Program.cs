using System;

namespace Chap6_Ex1
{
    class Height
    {
        int Inches, Feet;
        
        public Height(int f = 0, int i = 0)
        {
            Inches = i;
            Feet = f;
        }

        public static Height operator +(Height a, Height b)
        {
            Height c = new Height();
            c.Inches = (a.Inches + b.Inches) % 12;
            c.Feet = a.Feet + b.Feet + (a.Inches + b.Inches) / 12;
            return c;
        }
        public void display()
        {
            Console.Write("{0} feet {1} inch(es)", Feet, Inches);
        }

    }

    class Program
    {
        public int inputPosInt()
        {
            int a;
            a = Convert.ToInt32(Console.ReadLine());
            while (a < 0)
            {
                Console.WriteLine("Invid data, please retry.");
                a = Convert.ToInt32(Console.ReadLine());
            }
            return a;
        }

        static void Main(string[] args)
        {
            Program p = new Program();
            int f, i;
            Console.WriteLine("Enter the two height follow the form 'a feet b inches', You need to input a and b.");
            f = p.inputPosInt();
            i = p.inputPosInt();
            Height h1 = new Height(f, i);
            f = p.inputPosInt();
            i = p.inputPosInt();
            Height h2 = new Height(f, i);
            Height h3 = h1 + h2;
            h1.display();
            Console.Write(" plus ");
            h2.display();
            Console.Write(" is ");
            h3.display();
            Console.WriteLine();
            Console.ReadLine();
        }
    }
}
