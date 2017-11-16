using System;


namespace 作业3
{
    class point
    {
        private double x, y;

        public double X
        {
            get { return x; }
            set { x = value; }
        }

        public double Y
        {
            get { return y; }
            set { y = value; }
        }
    }

    class circle:point
    {
        public circle(double x, double y)
        {
            this.X = x;
            this.Y = y;
        }

        public double Radius()
        {
            return Math.Sqrt(X * X + Y * Y);
        }

        public double calArea(double r)
        {
            return Math.PI * Math.Pow(r, 2);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            circle c = new circle(2, 2);
            Console.WriteLine("The area of this circle is {0}.", Math.Round(c.calArea(c.Radius()), 2));
            Console.ReadLine();
        }
    }
}
