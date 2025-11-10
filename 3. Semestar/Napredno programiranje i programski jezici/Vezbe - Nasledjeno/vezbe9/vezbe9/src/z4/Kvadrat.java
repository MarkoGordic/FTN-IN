package z4;

public class Kvadrat extends Pravougaonik {
	public Kvadrat(double a) {
		super(a ,a); // super poziva konstruktor od Pravougaonik
	}
	
	@Override
	public void setA(double a) {
		super.setA(a);
		super.setB(a);
		
		// moze i ovako
		// this.a = a;
		// this.b = b;
	}

	@Override
	public void setB(double b) {
		super.setA(b);
		super.setB(b);
	}
	
	@Override
	public String toString() {
		return "Kvadrat: a = " + a;
	}
}
