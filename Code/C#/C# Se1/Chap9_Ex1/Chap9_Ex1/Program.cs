using System;
using System.Threading;

namespace Chap9_Ex1
{
    public class Vehicle
    {
        private int id, v, toTollBooth;
        Random ran = new Random();
        private static TollBooth toll = new TollBooth();
        public Vehicle(int id)
        {
            this.id = id;
            for (int i = 0; i < id+1; i++)
            {
                v = ran.Next(10, 30);
            }
            toTollBooth = ran.Next(5, 13) * v;
            Console.WriteLine("Vehicle {0} has started its journey, it travels at the speed of {1}, and it is {2} miles away from the toll booth.\n", this.id, this.v, this.toTollBooth);
        }

        public void exec()
        {
            travel(toTollBooth / v);
            toll.useToll(this);
        }

        public int getVehicleId()
        {
            return id;
        }

        public void travel(int time)
        {
            Thread.Sleep(time * 1000);
            Console.WriteLine("Time {0} : Vehicle {1} arrives the toll booth.", Simulate.time, this.id);
        }
    }

    public class TollBooth
    {
        public void useToll(Vehicle vehicle)
        {
            Monitor.Enter(this);
            Console.WriteLine("Time {0} : Vehicle {1} enters the toll booth...", Simulate.time, vehicle.getVehicleId());
            Thread.Sleep(2000);
            Console.WriteLine("Time {0} : Vehicle {1} has exited the toll booth.", Simulate.time, vehicle.getVehicleId());
            Monitor.Exit(this);
        }
    }

    public class Simulate
    {
        public static int time = 0;
        public static void Main(string[] args)
        {
            int noOfVehicles = 5;
            Vehicle[] Vehicles = new Vehicle[noOfVehicles];
            Thread[] th = new Thread[noOfVehicles];
            for(int i = 0; i < noOfVehicles; i++)
            {
                Vehicles[i] = new Vehicle(i);
                th[i] = new Thread(new ThreadStart(Vehicles[i].exec));
            }
            for(int i = 0; i < noOfVehicles; i++)
            {
                th[i].Start();
            }
            for (int i = 0; i < 25; i++)
            {
                Thread.Sleep(1000);
                time++;
            }
            Console.WriteLine("All vehicle has passed the toll booth.");
            Console.ReadLine();
        }
    }
}
