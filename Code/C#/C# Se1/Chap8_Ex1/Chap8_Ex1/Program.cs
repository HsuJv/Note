using System;

namespace Chap8_Ex1
{
    class TicketLimit
    {
        static void Main(string[] args)
        {
            TicketOrder t = new TicketOrder(10);
            Console.WriteLine("Do you want to order any tickets?(Y/N)");
            string op = Console.ReadLine();
            while (op != "Y" && op != "N")
            {
                Console.WriteLine("Invalid parameter. Please enter 'Y' or 'N'");
                op = Console.ReadLine();
            }
            if (op == "Y")
            {
                Console.WriteLine("Please enter how many tickets do you want to order.");
                int i = Convert.ToInt32(Console.ReadLine());
                try
                {
                    t.Order(i);
                }
                catch (TicketLimtException e)
                {
                    Console.WriteLine("TicketLimetException: {0}", e);
                }
            }
            Console.ReadLine();
        }
    }

    public class TicketLimtException : ApplicationException
    {
        public TicketLimtException(string message): base(message)
        {
        }
    }

    public class TicketOrder
    {
        int tl;

        public TicketOrder(int n)
        {
            tl = n;
        }

        public void Order(int n)
        {
            if (n > tl)
                throw (new TicketLimtException("Out of ticket limit!"));
            else
                Console.WriteLine("Order successed.");
        }
    }
}