
package chapter04;

import java.util.LinkedList;


public class Fruit 
{
    LinkedList name;
    
    public Fruit()
    {
        name = new LinkedList();
        name.add("MANGO");
        name.add("APPLE");
        name.add("GRAPES");
        name.add("PINEAPPLE");
        name.add("GUAVA");
    }
    
    public LinkedList getFruit()
    {
        return name;
    }
    
    public String toString()
    {
        return "Fruit";
    }
 
    
}
