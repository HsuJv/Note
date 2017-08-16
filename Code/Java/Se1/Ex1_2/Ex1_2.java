interface Person{
	public abstract int pay();
}

class Assistant implements Person{
	public int base_wage;
	public int hour_wage;
	
	public Assistant(){
		base_wage = 800;
		hour_wage = 25;
	}
	
	public int pay(){
		return base_wage + hour_wage * 15;
	}
}

class Instructor implements Person{
	public int base_wage;
	public int hour_wage;
	
	public Instructor(){
		base_wage = 1000;
		hour_wage = 35;
	}
	
	public int pay(){
		return base_wage + hour_wage * 20;
	}
}

class AssistantProfesson implements Person{
	public int base_wage;
	public int hour_wage;
	
	public AssistantProfesson(){
		base_wage = 1200;
		hour_wage = 40;
	}
	
	public int pay(){
		return base_wage + hour_wage * 25;
	}
}

class Professon implements Person{
	public int base_wage;
	public int hour_wage;
	
	public Professon(){
		base_wage = 1400;
		hour_wage = 50;
	}
	
	public int pay(){
		return base_wage + hour_wage * 30;
	}
}

public class Ex1_2{
	public static void main(String[] args){
		Assistant a = new Assistant();
		Instructor i = new Instructor();
		AssistantProfesson ap = new AssistantProfesson();
		Professon p = new Professon();
		System.out.println("The wage of an Assistant is " + a.pay());
		System.out.println("The wage of an Instructor is " + i.pay());
		System.out.println("The wage of an AssistantProfesson is " + ap.pay());
		System.out.println("The wage of an Professon is " + p.pay());
	}
}