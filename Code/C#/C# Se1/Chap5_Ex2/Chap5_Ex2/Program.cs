using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Chap5_Ex2
{
    abstract class Pic
    {
        public abstract void Draw();
    }

    class Line : Pic
    {
        public override void Draw()
        {
            Console.WriteLine("I'm a Line.");
        }
    }

    class Circle : Pic
    {
        public override void Draw()
        {
            Console.WriteLine("I'm a Circle.");
        }
    }

    class Square : Pic
    {
        public override void Draw()
        {
            Console.WriteLine("I'm a Square.");
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            Line l = new Line();
            Circle c = new Circle();
            Square s = new Square();
            l.Draw();
            c.Draw();
            s.Draw();
            Console.ReadLine();
        }
    }
}
