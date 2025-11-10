package z3;

public class Valjak {
	private Krug b;
	private Pravougaonik m;
	
	public Valjak(double r, double h) {
		this.b = new Krug(r);
		this.m = new Pravougaonik(b.getO(), h);
	}
	
	public Valjak(Valjak v) {
		this.b = new Krug(v.b);
		this.m = new Pravougaonik(v.m);
	
	}
	public double getR() {
		return b.getR();
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
