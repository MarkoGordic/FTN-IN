package z2;

public class Test {

	public static void main(String[] args) {
		Test t = new Test();
		
		t.testirajCDDisk();
		t.testirajXCDStorage();
		t.testirajXCDStorageMap();
		t.testirajIzmenu();
	}
	
	private void testirajCDDisk() {
		System.out.println("\n****************** Testiranje klase CDDisk ******************\n");
		
		CDDisk d1 = new CDDisk(1, "Novi disk", "Pevac hitova");
		CDDisk d2 = new CDDisk(2, "Hitovi", "Pevac");
			
		System.out.println(d1);
		System.out.println(d2);
	}
	
	private void testirajXCDStorage() {
		System.out.println("\n****************** Testiranje klase XCDStorage ******************\n");
		
		XCDStorage cds = new XCDStorage();
		System.out.println(cds);
		
		CDDisk d1 = new CDDisk(1, "Stari disk", "Orkestar");
		CDDisk d2 = new CDDisk(2, "Novi disk", "Orkestar");
		
		cds.add(d1);
		cds.add(d2);
		System.out.println(cds);
		
		CDDisk nadjen = cds.find(1);
		if(nadjen != null) 
			System.out.println("Nadjen disk: " + nadjen);

		CDDisk removed = cds.remove(2);
		if(removed != null) 
			System.out.println("Uklonjen disk: " + removed);
		
	}
		
	private void testirajXCDStorageMap() {
		System.out.println("\n****************** Testiranje klase XCDStorageMap ******************\n");
		
		XCDStorageMap cds = new XCDStorageMap();
		System.out.println(cds);
		
		CDDisk d1 = new CDDisk(1, "Stari disk", "Orkestar");
		CDDisk d2 = new CDDisk(2, "Novi disk", "Orkestar");
		
		cds.add(d1);
		cds.add(d2);
		System.out.println(cds);
		
		CDDisk nadjen = cds.find(1);
		if(nadjen != null) 
			System.out.println("Nadjen disk: " + nadjen);

		CDDisk removed = cds.remove(2);
		if(removed != null) 
			System.out.println("Uklonjen disk: " + removed);
		
	}
	
	private void testirajIzmenu() {
		System.out.println("\n****************** Testiranje izmene nakon dodavanja ******************\n");
		
		CDDisk d1 = new CDDisk(1, "Stari disk", "Orkestar");
		CDDisk d2 = new CDDisk(2, "Novi disk", "Orkestar");
		XCDStorage cds = new XCDStorage();
		cds.add(d1);
		cds.add(d2);
		XCDStorageMap cdsm = new XCDStorageMap();
		cdsm.add(d1);
		cdsm.add(d2);

		System.out.println(cds);
		System.out.println(cdsm);
		
		d2.setId(1);
		
		System.out.println(cds);
		System.out.println(cdsm);
		
        // id vrednosti nece vise biti jedinstvene

        // Pogotovo kod struktura koje koriste hash funkcije za identifikaciju treba voditi racuna da li to zelimo
		// Izbegavati; nije ta namena
	}

}
