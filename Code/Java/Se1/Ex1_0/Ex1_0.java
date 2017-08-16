class Rectangle{
	int Length, Width;
	
	public int getLength()	{return Length;}
	public int getWidth()	{return Width;}
	public void setLength(int a)	{this.Length = a;}
	public void setWidth(int a)		{this.Width = a;}
	public int getArea()	{return Length * Width;}
	public String toString(){
		return "length = " + getLength() + "\nWidth = " + getWidth() + "\nArea = "+ getArea();
	}
}

class Box extends Rectangle{
	int Height;
	public int getHeight()	{return Height;}
	public void setHeight(int a)	{this.Height = a;}
	public int getVolume()	{return getArea() * Height;}
	public String toString(){
		return "height = " + getHeight() + "\nvolume = " + getVolume();
	}
}

public class Ex1_0{
	public static void main(String[] args){
		Rectangle  r = new Rectangle();
		Box b = new Box();
		r.setLength(5);r.setWidth(6);
		System.out.println(r);
		b.setHeight(7);
		System.out.println(b);
	}
}