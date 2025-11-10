package z1;

public class Test {

	public static void main(String[] args) {
		Test t = new Test();
		t.testiraj();
	}
	
	private void testiraj() {
		Pravougaonik p = new Pravougaonik(2, 3);
		Kvadrat kv = new Kvadrat(3);
		Krug k = new Krug(4);
		
		ispisiPovrsinu(p);
		ispisiPovrsinu(kv);
		ispisiPovrsinu(k);
	}
		
	private void ispisiPovrsinu(GeometrijskaFigura g) {
		//getPovrsina - pozvace se prava metoda jer su sve metode u javi virtuelne
		System.out.println(g);
		System.out.println("Povrsina je: " + g.getPovrsina());
		System.out.println();
	}

}
