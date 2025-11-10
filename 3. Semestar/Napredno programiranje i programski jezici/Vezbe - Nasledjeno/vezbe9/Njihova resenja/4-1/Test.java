package z11;

public class Test {

	public static void main(String[] args) {
		Test t = new Test();
		t.testiraj();
	}
	
	private void testiraj() {
		Kvadar p = new Kvadar(2, 3, 4);
		Kocka kv = new Kocka(4);
		
		ispisi(p);
		ispisi(kv);
	}
		
	private void ispisi(GeometrijskoTelo g) {
		System.out.println("Zapremina je: " + g.getZapremina());
		System.out.println("Povrsina je: " + g.getPovrsina());
		System.out.println();
	}


}
