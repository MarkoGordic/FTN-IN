package z11;

import z1.Pravougaonik;


//rezervisana rec extends predstavlja nasledjivanje
public class Kvadar extends GeometrijskoTelo {

	protected Pravougaonik b;
    protected Pravougaonik m;
	
	public Kvadar(double a, double b, double h) {
		this.b = new Pravougaonik(a, b);
      this.m = new Pravougaonik(2 * a + 2 * b, h);
	}

	public double getA() {
		return b.getA();
	}

	public double getB() {
		return b.getB();
	}
	
	public double getH() {
		return m.getB();
	}

	@Override
	public double getZapremina() {
		return b.getPovrsina() * getH();
	}

	@Override
	public double getPovrsina() {
		return 2 * b.getPovrsina() + m.getPovrsina();
	}
	
}
