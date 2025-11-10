package z1;

public class Test {

	// izvrsavanje programa krece od main metode
	public static void main(String[] args) {

		// promenljive p1 i p2 su reference na objekat klase Pravougaonik
		Pravougaonik p1 = new Pravougaonik(3, 4);
		Pravougaonik p2 = new Pravougaonik(p1);

		System.out.println("Obim pravougaonika p je: " + p1.getO() + 
				"\nPovrsina pravougaonika p je: " + p1.getP());
		System.out.println("\nObim pravougaonika p2 je: " + p2.getO() + 
				"\nPovrsina pravougaonika p2 je: " + p2.getP());
		
		Krug k = new Krug(5);
		System.out.println("\nObim kruga je: " + k.getO() + 
				"\nPovrsina kruga je: " + k.getP());
		
	}

}
