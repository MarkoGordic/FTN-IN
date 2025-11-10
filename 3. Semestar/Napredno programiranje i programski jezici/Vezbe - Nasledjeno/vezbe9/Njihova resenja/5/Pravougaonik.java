package z3;

//rezervisana rec implements predstavlja implementaciju interfejsa
public class Pravougaonik implements GeometrijskaFigura {

	protected double a;
	protected double b;
	
	public Pravougaonik(double a, double b) {
		this.a = a;
		this.b = b;
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
	
	//anotacija @Override oznacava da je metoda nasledjena
	//ukoliko postoji anotacija a mi nismo napisali dobro prototip metode kompajler javlja gresku
	//moze i da se ne navede
	@Override
	public double getObim() {
		return 2 * (a + b);
	}

	@Override
	public double getPovrsina() {
		return a * b;
	}
	
	@Override
	public String toString() {
		return "Pravougaonik(a=" + a + ", b=" + b + ")";
	}
}
