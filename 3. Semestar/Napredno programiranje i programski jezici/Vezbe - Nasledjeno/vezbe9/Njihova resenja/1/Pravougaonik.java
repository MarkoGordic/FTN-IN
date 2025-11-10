package z1;

public class Pravougaonik {
	private double a;
	private double b;
	
	public Pravougaonik(double a, double b) {
		//this je referenca na objekat nad kojim se poziva metoda (ne postoje pokazivaci)
		this.a = a;
		this.b = b;
	}
	
	public Pravougaonik(Pravougaonik p) {
		this.a = p.a;
		this.b = p.b;
	}
	
	public double getA() {
		return a;
	}
	
	public void setA(double a) {
		this.a = a;
	}
	
	public double getB() {
		return b;
	}
	
	public void setB(double b) {
		this.b = b;
	}
	
	public double getO() {
		return 2*a + 2*b;
	}
	
	public double getP() {
		return a * b;
	}
	

}
