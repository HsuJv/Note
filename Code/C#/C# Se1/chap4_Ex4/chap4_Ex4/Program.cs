using System;

namespace chap4_Ex4
{
    struct item
    {
        enum items { Women, Men, Girls, Boys, Babies };
        items cata;
        string name;
        int price, amount;
        public item(string s, int t, int n, int p)
        {
            name = s;
            amount = n;
            price = p;
            cata = (items)t;
        }

        public void print_info()
        {
            Console.WriteLine("{0}:\t{1}\t{2}\t{3}", cata, name, amount, price);
        }
    }

    class main
    {
        static void Main(string[] args)
        {
            item[] g;
            int n;
            Console.WriteLine("Enter the number of the kinds of items:");
            n = Convert.ToInt32(Console.ReadLine());
            g = new item[n];
            Console.Write("Enter more details.You may use number 0, 1, 2, 3, 4");
            Console.WriteLine(" to represent catagrory 'Women', 'Men', 'Girls', 'Boys', 'Babies'.");
            for (int i = 0; i < n; i++)
            {
                string name;
                int price, amount, cata;
                Console.WriteLine("Item {0}:", i + 1);
                Console.Write("Cata: ");
                cata = Convert.ToInt32(Console.ReadLine());
                Console.Write("Name: ");
                name = Convert.ToString(Console.ReadLine());
                Console.Write("Amount: ");
                amount = Convert.ToInt32(Console.ReadLine());
                Console.Write("Price: ");
                price = Convert.ToInt32(Console.ReadLine());
                g[i] = new item(name, cata, amount, price);
                Console.WriteLine();
                
            }
            Console.WriteLine("\n\n\nSummary:");
            Console.WriteLine("{0}:\t{1}\t{2}\t{3}", "Cata", "Name", "Amount", "Price");
            for (int i = 0; i < n; i++)
                g[i].print_info();
            Console.ReadLine();
        }
    }
}
