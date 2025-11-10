package z31;

public class Test {

	public static void main(String[] args) {
		TeloA a = new TeloA(2, 2, 4, 2, 8);
		
		System.out.println("Povrsina telaA je: " + a.getP());
		System.out.println("Zapremina telaA je: " + a.getV());
		
		TeloB b = new TeloB(2);
		
		System.out.println("Povrsina telaB je: " + b.getP());
		System.out.println("Zapremina telaB je: " + b.getV());

	}
	
}
