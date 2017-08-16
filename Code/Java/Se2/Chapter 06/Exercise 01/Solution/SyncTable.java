package chapter06;
public class SyncTable {

    void print(int num) {
        synchronized (this) {
            Thread t = Thread.currentThread();
            String name = t.getName();
            System.out.println("Table created by " + name);
            for (int i = 1; i <= 10; i++) {
                System.out.println(num * i);
                try {
                t.sleep(1000);
                }
                catch(Exception e)
                {
                System.out.println("Interrupted");
                
                }
                }
        }
    }
}
class Thread1 extends Thread {
    SyncTable t;
    Thread1(SyncTable t) {
        this.t = t;
    }
    public void run() {
        t.print(2);
    }
}
class Thread2 extends Thread {
    SyncTable t;
    Thread2(SyncTable t) {
        this.t = t;
    }
    public void run() {
        t.print(4);
    }
}
class ShowTable {
    public static void main(String args[]) {
        SyncTable obj = new SyncTable();
        Thread1 newthread1 = new Thread1(obj);
        newthread1.setName("Thread1");
        Thread2 newthread2 = new Thread2(obj);
        newthread2.setName("Thread2");
        newthread1.start();
        newthread2.start();
    }
}