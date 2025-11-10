package z4_1;

import z1.Pravougaonik; // koristimo Pravougaonik iz 1. zadatka

public class Kvadar extends GeometrijskoTelo {
	protected Pravougaonik B;
	protected Pravougaonik M;
	
	public Kvadar(double a, double b, double c) {
		super();
		B = new Pravougaonik(a, b);
		M = new Pravougaonik(2 * a + 2 * b, c);
	}
	
	public double getA() {
		return B.getA();
	}
	
	public double getB() {
		return B.getB();
	}
	
	public double getH() {
		return M.getB();
	}
	
	@Override
	public double getP() {
		return 2 * B.getP() + M.getP();
	}

	@Override
	public double getV() {
		return B.getP() * getH();
	}

}
