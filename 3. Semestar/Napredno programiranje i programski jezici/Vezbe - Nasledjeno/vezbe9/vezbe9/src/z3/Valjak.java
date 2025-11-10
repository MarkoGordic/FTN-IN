package z3;

import z1.Krug;
import z1.Pravougaonik;

public class Valjak {

	private Krug B;
	private Pravougaonik M;
	
	public Valjak(Valjak v) {
		super();
		B = v.B;
		M = v.M;
	}

	public Valjak(double r, double H) {
		super();
		B = new Krug(r);
		M = new Pravougaonik(H, 2 * r * Math.PI);
	}

	double getR() {
		return B.getR();
	}
	
	double getH() {
		return M.getA();
	}
	
	double getV() {
		return B.getP() * getH();
	}
	
	double getP() {
		return 2 * B.getP() + M.getP();
	}

	public static void main(String[] args) {
		Valjak v1 = new Valjak(3, 4);
		Valjak v2 = new Valjak(v1);
		
		System.out.println("V1:\nR: " + v1.getR() + "\nH: " + v1.getH() + "\nP: " + v1.getP() + "\nV: " + v1.getV());
		
		System.out.println("V2:\nR: " + v2.getR() + "\nH: " + v2.getH() + "\nP: " + v2.getP() + "\nV: " + v2.getV());
	}

}
