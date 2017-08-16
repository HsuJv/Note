
package chapter01;

import java.util.Random;


public class StaticInnerClassDemo {
    public static class Pair{
            private int first;
            private int last;
          public Pair(int f, int s)  {
              first = f;
              last=s;
          }
          public int getFirst(){
              return first;
          }
          public int getLast(){
              return last;
          }
        }
        public static Pair minmax(int values[]){
            
            int min=2147483647;
            int max=-2147483648;
            for(int v:values){
                if(min>v)
                    min=v;
                if(max<v)
                    max=v;
            }
            return new Pair(min,max);
        }
    public static void main(String args[]){
        Random r=new Random();
        int d[]=new int[20];
        for(int i=0;i<d.length;i++){
            d[i]=r.nextInt(100);
            System.out.println(d[i]);
        }
            
        StaticInnerClassDemo.Pair p=StaticInnerClassDemo.minmax(d);
        System.out.println("min = "+p.getFirst());
        System.out.println("max = "+p.getLast());
        
        
    }
}
