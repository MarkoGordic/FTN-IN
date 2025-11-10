package z3;

public class Test {

	public static void main(String[] args) {
		Valjak v = new Valjak(2, 4);
		Valjak v1 = new Valjak(v);
		System.out.println("Povrsina valjka je: " + v.getP());
		System.out.println("Zapremina valjka je: " + v.getV());
		System.out.println("Povrsina valjka je: " + v1.getP());
		System.out.println("Zapremina valjka je: " + v1.getV());
	}

}
