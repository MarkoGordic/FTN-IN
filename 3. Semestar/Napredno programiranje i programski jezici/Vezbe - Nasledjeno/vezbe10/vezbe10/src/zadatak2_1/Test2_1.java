package zadatak2_1;

public class Test2_1 {

	public static void main(String[] args) {
		Student s1 = new Student("RA 1/16", "Jovan", "Jovanovic");
		Student s2 = new Student("RA 2/16", "Pera", "Peric");
		Student s3 = new Student("RA 3/16", "Iva", "Ivanic");
		
		System.out.println("\n****************** Testiranje klase Ucionica ******************\n");
		
		Ucionica ucList = new Ucionica();
		
		ucList.dodaj(s1);
		ucList.dodaj(s2);
		ucList.dodaj(s3);
		
		System.out.println(ucList);
		
		ucList.ukloni(1);
		System.out.println(ucList);
		
 	    try
	    {
	        ucList.ukloni(5);
	    }
	    catch (Exception e)
	    {
	    	System.out.println("Greska prilikom izbacivanja");
	    	System.out.println(e.getMessage());
	    }		
		
		
		ucList.isprazni();
		System.out.println(ucList);
		
		System.out.println("\n****************** Testiranje klase UcionicaMap ******************\n");
		
		UcionicaMap ucMap = new UcionicaMap();
		ucMap.dodaj(s1);
		ucMap.dodaj(s2);
		ucMap.dodaj(s3);
		System.out.println(ucMap);
		
		
        Student s4 = new Student("RA 2/16", "Djordje", "Djordjevic"); // isti broj indeksa kao Pera
        ucMap.dodaj(s4);
		System.out.println(ucMap);
		// zamenjene su vrednosti
		
		
		ucMap.obrisi("RA 2/16");
		System.out.println(ucMap);
		
		ucMap.isprazni();
		System.out.println(ucMap);

	}

}
