package z1;

public class Test1 {

	public static void main(String[] args) {
		Pravougaonik p1 = new Pravougaonik(3, 4);
		Pravougaonik p2 = new Pravougaonik(p1);
		
		System.out.println("P1:\nA: " + p1.getA() + "\nB: " + p1.getB() + "\nP: " + p1.getP() + "\nO: " + p1.getO());
		p2.setA(5);
		p2.setB(5);
		System.out.println("P2:\nA: " + p2.getA() + "\nB: " + p2.getB() + "\nP: " + p2.getP() + "\nO: " + p2.getO());
		
		Krug k1 = new Krug(4);
		Krug k2 = new Krug(k1);
		
		System.out.println("K1:\nR: " + k1.getR() + "\nP: " + k1.getP() + "\nO: " + k1.getO());
		k2.setR(5);
		System.out.println("K2:\nR: " + k2.getR() + "\nP: " + k2.getP() + "\nO: " + k2.getO());
	}

}
