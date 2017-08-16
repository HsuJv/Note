package chapter06;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class Task implements Runnable {

    String taskname;

    public Task(String name) {
        taskname = name;
    }

    public void run() {
        System.out.println("The task name is - " + taskname);
        if (taskname.equals("Display 1 to 10")) {
            System.out.println("Thread A starts");
            for (int i = 1; i <= 10; i++) {
                System.out.println("Thread A in for loop, i = " + i);
            }
            System.out.println("Thread A exits");

           
            
        } else if (taskname.equals("Display 11 to 20")) {
            System.out.println("Thread B starts");
            for (int i = 11; i <= 20; i++) 
            {
                System.out.println("Thread B in for loop, i = " + i);
            }
            System.out.println("Thread B exits");
        }
    }
}
class TaskExecutor {
    public static void main(String a[]) {
        Task task1 = new Task("Display 1 to 10");
        Task task2 = new Task("Display 11 to 20");
        ExecutorService threadexecutor = Executors.newCachedThreadPool();
        System.out.println("Executor started");
        try {
        threadexecutor.execute(task1);
        threadexecutor.execute(task2);
        }
        finally
        {
        threadexecutor.shutdown();
        }
        
        }
}
