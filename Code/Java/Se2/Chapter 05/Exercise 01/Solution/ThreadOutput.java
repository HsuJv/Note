package chapter05;
class ThreadA extends Thread {
    public void run() {
        System.out.println("Thread A starts");
        for (int i = 1; i <= 10; i++) {
            System.out.println("Thread A in for loop, i = " + i);
        }
        System.out.println("Thread A exits");

        System.out.println("Thread A sleeping for 5 seconds");
        try {
            this.sleep(5000);
        } catch (InterruptedException e) {
            System.out.println("Exception caught:" + e);
        }
    }
}
class ThreadB extends Thread {
    public void run() {
        System.out.println("Thread B starts");
        for (int i = 1; i <= 10; i++) {
            System.out.println("Thread B in for loop, i = " + i);
        }
        System.out.println("Thread B exits");

        System.out.println("Thread B sleeping for 5 seconds");
        try {
            this.sleep(5000);
        } catch (InterruptedException e) {
            System.out.println("Exception caught:" + e);
        }
    }
}
public class ThreadOutput {
    public static void main(String[] args) {
        ThreadA objA = new ThreadA();
        objA.start();

        try {
            objA.join();
        } catch (InterruptedException e) {
            System.out.println(e);
        }
        
        ThreadB objB = new ThreadB();
        objB.start();
        try {
            objB.join();
        } catch (InterruptedException e) {
            System.out.println(e);
        }

       
        System.out.println("Exit from the main thread");
    }
}