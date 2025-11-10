package z5_1;

public class TeloA {
	private Pravougaonik ad;
	private Pravougaonik ah;
	private Pravougaonik dh;
	private Pravougaonik cd;
	private Trougao abc;
	
	public TeloA(double a, double b, double c, double d, double h) {
		super();
		ad = new Pravougaonik(a, d);
		ah = new Pravougaonik(a, h);
		dh = new Pravougaonik(d, h);
		cd = new Pravougaonik(c, d);
		abc = new Trougao(a, b, c);
	}

	public double getP() {
		return ad.getP() + 2 * ah.getP() + 2 * dh.getP()+ 2 * cd.getP() + 2 * abc.getP();
	}
	
	public double getV() {
		return ad.getP() * ah.getB() + abc.getP() * cd.getB();
	}
	
	@Override
	public String toString() {
		String str = "TeloA:\n";
		str += "a: " + abc.getA();
		str += "\nb: " + abc.getB();
		str += "\nc: " + abc.getC();
		str += "\nd: " + dh.getA();
		str += "\nh: " + dh.getB();
		return str;
	}
}
