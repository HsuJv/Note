using System;
using System.IO;

namespace 作业4
{
    class Program
    {
        static void Main(string[] args)
        {
            FileStream fs = new FileStream(@"P:\demo.txt", FileMode.Create, FileAccess.Write);
            StreamWriter sw = new StreamWriter(fs);
            sw.BaseStream.Seek(0, SeekOrigin.Begin);
            sw.WriteLine("Hello Java");
            sw.Flush();
            sw.Close();
            fs.Close();

            fs = new FileStream(@"P:\demo.txt", FileMode.Open, FileAccess.Read);
            StreamReader sr = new StreamReader(fs);
            sr.BaseStream.Seek(0, SeekOrigin.Begin);
            Console.WriteLine(sr.ReadLine());
            sr.Close();
            fs.Close();
            Console.ReadLine();
        }
    }
}
