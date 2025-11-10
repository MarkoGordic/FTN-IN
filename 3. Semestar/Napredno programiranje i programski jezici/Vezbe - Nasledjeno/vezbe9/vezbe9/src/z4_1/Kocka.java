package z4_1;

public class Kocka extends Kvadar {

	public Kocka(double a) {
		super(a, a, a);
	}
	
	public static void main(String[] args) {
		Kvadar kv1 = new Kvadar(1, 2, 3);
		System.out.println("KVADAR");
		System.out.println("A: " + kv1.getA());
		System.out.println("B: " + kv1.getB());
		System.out.println("H: " + kv1.getH());
		System.out.println("P: " + kv1.getP());
		System.out.println("V: " + kv1.getV());
		
		Kocka ko1 = new Kocka(3);
		System.out.println("KOCKA");
		System.out.println("A: " + ko1.getA());
		System.out.println("B: " + ko1.getB());
		System.out.println("H: " + ko1.getH());
		System.out.println("P: " + ko1.getP());
		System.out.println("V: " + ko1.getV());
	}
}
