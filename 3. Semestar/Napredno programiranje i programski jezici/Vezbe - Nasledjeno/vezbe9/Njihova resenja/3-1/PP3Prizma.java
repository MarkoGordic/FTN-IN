package z4;

import z3.Pravougaonik;

public class PP3Prizma {
	private JSTrougao b;
	private Pravougaonik m;
	
	public PP3Prizma(double a, double h) {
		this.b = new JSTrougao(a);
		this.m = new Pravougaonik(b.getO(), h);
	}
	
	public double getA() {
		return b.getA();
	}
	
	public double getH() {
		return m.getB();
	}
	
	public double getP() {
		return 2 * b.getP() + m.getP();
	}
	
	public double getV() {
		return b.getP() * getH();
	}

}
