package zadatak2;

//ako treba da promenimo naziv
//onda koristimo Desni klik -> Refactor -> Rename i samo izmenimo naziv
//svugde gde treba promeniti on ce promeniti zbog update references

public class Test2 {

	public static void main(String[] args) {
		CDDisk cd1 = new CDDisk();
		CDDisk cd2 = new CDDisk(5, "pjesma", "pevac");
		
		cd1.setId(2);
		cd1.setIzvodjac("tose");
		cd1.setNaziv("nisam nado");
		
		System.out.println(cd1); // ako tostring nije redefinisan vraca nam neki hes kod
		
		System.out.println(cd2.getId());
		System.out.println(cd2.getIzvodjac());
		System.out.println(cd2.getNaziv());
		
		XCDStorage x = new XCDStorage();
		x.dodaj(cd1);
		x.dodaj(cd2);
		System.out.println("Izbacen el id = 2: \n" + x.izbaci(2));
		System.out.println("Pronadjeni disk id = 343: \n" + x.pronadji(343));
		System.out.println("Pronadjeni disk id = 5: \n" + x.pronadji(5));
		
		System.out.println(x);
		x.isprazni();
		System.out.println(x);
		
		XCDStorageMap m = new XCDStorageMap();
		m.dodaj(cd1);
		m.dodaj(cd2);
		System.out.println(m.izbaci(2));
		
		System.out.println(m.pronadji(2));
		
		System.out.println(m);
		m.isprazni();
		System.out.println(m);
	}

}
