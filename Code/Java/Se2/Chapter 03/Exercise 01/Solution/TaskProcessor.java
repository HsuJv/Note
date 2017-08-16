package chapter03;

public class TaskProcessor<X> 
{
    private X value;

    public TaskProcessor(X v) 
    {
        value = v;
    }

    public X getTaskP() 
    {
        return value;
    }
}
