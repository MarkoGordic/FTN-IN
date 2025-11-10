package z3_1;

public class JSTrougao {
	private double a;
	private double b;
	private double c;
	
	public JSTrougao(double a) {
		super();
		this.a = a;
		this.b = a;
		this.c = a;
	}

	public double getA() {
		return a;
	}

	public void setA(double a) {
		this.a = a;
		this.b = a;
		this.c = a;
	}

	public double getB() {
		return b;
	}

	public void setB(double b) {
		this.a = b;
		this.b = b;
		this.c = b;
	}

	public double getC() {
		return c;
	}

	public void setC(double c) {
		this.a = c;
		this.b = c;
		this.c = c;
	}
	
	public double getP() {
		return Math.pow(a, 2) * Math.sqrt(3) / 4;
	}
	
	public double getO() {
		return a + b + c;
	}
}
