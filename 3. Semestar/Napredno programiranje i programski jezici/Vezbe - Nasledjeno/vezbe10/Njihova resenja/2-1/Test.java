package z21;

public class Test {

	public static void main(String[] args) {
		Student s1 = new Student("RA 1/16", "Jovan", "Jovanovic");
		Student s2 = new Student("RA 2/16", "Pera", "Peric");
		Student s3 = new Student("RA 3/16", "Iva", "Ivanic");
		
		System.out.println("\n****************** Testiranje klase Ucionica ******************\n");
		
		Ucionica ucList = new Ucionica();
		
		ucList.dodajStudenta(s1);
		ucList.dodajStudenta(s2);
		ucList.dodajStudenta(s3);
		
		System.out.println(ucList);
		
		ucList.ukloniStudenta(1);
		System.out.println(ucList);
		
 	    try
	    {
	        ucList.ukloniStudenta(5);
	    }
	    catch (Exception e)
	    {
	    	System.out.println("Greska prilikom izbacivanja");
	    	System.out.println(e.getMessage());
	    }		
		
		
		ucList.isprazniUcionicu();
		System.out.println(ucList);
		
		System.out.println("\n****************** Testiranje klase UcionicaMap ******************\n");
		
		UcionicaMap ucMap = new UcionicaMap();
		ucMap.dodajStudenta(s1);
		ucMap.dodajStudenta(s2);
		ucMap.dodajStudenta(s3);
		System.out.println(ucMap);
		
		
        Student s4 = new Student("RA 2/16", "Djordje", "Djordjevic"); // isti broj indeksa kao Pera
        ucMap.dodajStudenta(s4);
		System.out.println(ucMap);
		// zamenjene su vrednosti
		
		
		ucMap.ukloniStudenta("RA 2/16");
		System.out.println(ucMap);
		
		ucMap.isprazniUcionicu();
		System.out.println(ucMap);
		
	}

}
