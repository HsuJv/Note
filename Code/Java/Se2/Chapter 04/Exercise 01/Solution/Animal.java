
package chapter04;

import java.util.LinkedList;

public class Animal 
{
    LinkedList name;
    
    public Animal()
    {
        name = new LinkedList();
        name.add("ELEPHANT");
        name.add("TIGER");
        name.add("BUFFALO");
        name.add("GIRAFFE");
        name.add("LEOPARD");
    }
    
    public LinkedList getAnimal()
    {
        return name;
    }
    
    public String toString()
    {
        return "Animal";
    }
 
    
}
