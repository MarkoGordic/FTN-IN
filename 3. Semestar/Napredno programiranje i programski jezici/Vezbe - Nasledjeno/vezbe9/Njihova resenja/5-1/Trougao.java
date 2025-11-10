package z31;

public class Trougao implements Figura {
	
	private double a, b, c;

	public Trougao(double a, double b, double c) {
		this.a = a;
		this.b = b;
		this.c = c;
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

	public double getC() {
		return c;
	}

	public void setC(double c) {
		this.c = c;
	}
	
	@Override
	public double getObim() {
		return a + b + c;
	}

	@Override
	public double getPovrsina() {
		double s = getObim() / 2;
        return Math.sqrt(s * ((s - a) * (s - b) * (s - c)));
	}

}
