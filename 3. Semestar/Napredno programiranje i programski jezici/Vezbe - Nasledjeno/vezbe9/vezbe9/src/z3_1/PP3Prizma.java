package z3_1;

import z1.Pravougaonik;

public class PP3Prizma {
	private JSTrougao B;
	private Pravougaonik M;
	
	public PP3Prizma(double a, double H) {
		super();
		B = new JSTrougao(a);
		M = new Pravougaonik(H, 3 * a);
	}

	public double getA() {
		return B.getA();
	}
	
	public double getH() {
		return M.getA();
	}

	public double getP() {
		return 2 * B.getP() + M.getP();
	}
	
	public double getV() {
		return B.getP() * getH();
	}

	public static void main(String[] args) {
		JSTrougao jst1 = new JSTrougao(3);
		System.out.println("JST1:\nA: " + jst1.getA() + "\nB: " + jst1.getB() + "\nC: " + jst1.getC());
		jst1.setA(1);
		jst1.setB(2);
		jst1.setC(3);
		System.out.println("JST1:\nA: " + jst1.getA() + "\nB: " + jst1.getB() + "\nC: " + jst1.getC());
		
		PP3Prizma pp3p1 = new PP3Prizma(1, 3);
		System.out.println("PP3P1:\nA: " + pp3p1.getA() + "\nH: " + pp3p1.getH() + "\nP: " + pp3p1.getP() + pp3p1.getH() + "\nV: " + pp3p1.getV());
	}
}
