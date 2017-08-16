
package chapter04;

import java.util.LinkedList;


public class Country  
{
   LinkedList name;
    
    public Country()
    {
        name = new LinkedList();
        name.add("AUSTRIA");
        name.add("CANADA");
        name.add("BAHRAIN");
        name.add("JAPAN");
        name.add("SYRIA");
    }
    
    public LinkedList getCountry()
    {
        return name;
    }
    
    public String toString()
    {
        return "Country";
    }
    
}
