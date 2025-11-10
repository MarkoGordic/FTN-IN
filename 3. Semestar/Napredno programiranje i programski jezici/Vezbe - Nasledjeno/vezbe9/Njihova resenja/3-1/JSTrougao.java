package z4;

public class JSTrougao {
	private double a;	
	
	public JSTrougao(double a) {
		this.a = a;
	}
	
	public JSTrougao(JSTrougao t) {
		this.a = t.a;
	}

	public double getA() {
		return a;
	}

	public void setA(double a) {
		this.a = a;
	}

	public double getO() {
		return a * 3;
	}
	
	public double getP() {
		double s = getO() / 2;
		return Math.sqrt(s * Math.pow((s - a), 3));
	}

}
