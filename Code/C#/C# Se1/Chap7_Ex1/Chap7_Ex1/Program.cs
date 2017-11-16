using System;
using System.IO;

namespace Chap7_Ex1
{
    class Date
    {
        FileStream fs;
        string fn;

        public Date(string fn)
        {
            this.fn = fn;
        }

        public void Add()
        {
            Console.Clear();
            Console.WriteLine("Option:Add appointment.");
            string d, n, t;
            fs = new FileStream(fn, FileMode.OpenOrCreate, FileAccess.Write);
            StreamWriter w = new StreamWriter(fs);
            w.BaseStream.Seek(0, SeekOrigin.End);
            Console.WriteLine("Please enter the appointment date.(After the form as mm/dd/yy)");
            d = Console.ReadLine();
            Console.WriteLine("Please enter the name of the person to be met.");
            n = Console.ReadLine();
            Console.WriteLine("Please enter the time of appointment.(After the form as HH:MM)");
            t = Console.ReadLine();
            w.WriteLine("{0}\t{1}\t{2}", d, n, t);
            w.Flush();
            w.Close();
            fs.Close();
        }

        public void View()
        {
            Console.Clear();
            Console.WriteLine("Option:View appointment.");
            string info;
            fs = new FileStream(fn, FileMode.OpenOrCreate, FileAccess.Read);
            StreamReader r = new StreamReader(fs);
            r.BaseStream.Seek(0, SeekOrigin.Begin);
            info = r.ReadLine();
            Console.WriteLine("Date\t\tName\tTime");
            while (info != null)
            {
                Console.WriteLine(info);
                info = r.ReadLine();
            }
            r.Close();
            fs.Close();
        }

        public void Search()
        {
            Console.Clear();
            Console.WriteLine("Option:Search.");
            string d, info;
            bool frist = true;
            Console.WriteLine("Please enter the date to be searched.(After the form as mm/dd/yy)");
            d = Console.ReadLine();
            fs = new FileStream(fn, FileMode.OpenOrCreate, FileAccess.Read);
            StreamReader r = new StreamReader(fs);
            r.BaseStream.Seek(0, SeekOrigin.Begin);
            info = r.ReadLine();
            while (info != null)
            {
                if (string.Equals(d, info.Substring(0, 8)))
                {
                    if (frist)
                    {
                        Console.WriteLine("\n\n\nDate\t\tName\tTime");
                        frist = false;
                    }
                    Console.WriteLine(info);
                }
                info = r.ReadLine();
            }
            r.Close();
            fs.Close();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Date d = new Date("Date.txt");
            Console.WriteLine("Enter the option which you want to do.(1/2/3/4)");
            Console.WriteLine("(1)Add appointment;\n(2)View appointment;\n(3)Search;\n(4)Exit.");
            int op = Convert.ToInt32(Console.ReadLine());
            while(op != 4)
            {
                if (op == 1) d.Add();
                else if (op == 2) d.View();
                else if (op == 3) d.Search();
                else Console.WriteLine("Invalid option, please enter a valid one");
                Console.WriteLine("\n\n\nEnter the option which you want to do.(1/2/3/4)");
                Console.WriteLine("(1)Add appointment;\n(2)View appointment;\n(3)Search;\n(4)Exit.");
                op = Convert.ToInt32(Console.ReadLine());
            }
            
        }
    }
}
