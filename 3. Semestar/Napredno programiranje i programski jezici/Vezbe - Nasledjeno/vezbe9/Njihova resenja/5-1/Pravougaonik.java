package z31;

public class Pravougaonik implements Figura {

	private double a;
	private double b;
	
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
	
	@Override
	public double getObim() {
		return 2 * (a + b);
	}

	@Override
	public double getPovrsina() {
		return a * b;
	}
}
