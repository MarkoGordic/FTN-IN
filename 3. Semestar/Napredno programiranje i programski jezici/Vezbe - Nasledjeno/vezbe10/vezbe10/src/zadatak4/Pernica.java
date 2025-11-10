package zadatak4;

import java.util.HashMap;

public class Pernica {
	private HashMap<String, Bojica> bojice;
	private int raspolozivoMesta = 5;
	
	public Pernica() {
		super();
		bojice = new HashMap<String, Bojica>();
	}
	
	public boolean dodaj(Bojica bojica) {
		if (bojice.containsKey(bojica.getSerijskiBroj()) || bojice.size() >= raspolozivoMesta) {
			return false;
		}
		bojice.put(bojica.getSerijskiBroj(), bojica);
		return true;
	}
	
	public int prebroj(double cena) {
		int broj = 0;
		for (Bojica b : bojice.values()) {
			if (b.getCena() > cena ) {
				broj++;
			}
		}
		return broj;
	}
	
	@Override
	public String toString() {
		String str = "*** Pernica ***\n";
		if (bojice.isEmpty()) {
			str += "Prazna pernica!\n";
			return str;
		}
		for (Bojica b : bojice.values()) {
			str += b;
			str += "\n";
		}
		return str;
	}

	public static void main(String[] args) {
		Bojica b1 = new Bojica("101", 56, "CRVENA", "DRVENA");
		Bojica b2 = new Bojica(b1);
		Bojica b3 = new Bojica("150", 21, "PLAVA", "DRVENA");
		
		b3.akcijskaCena(10);
		System.out.println(b3);
		
		b1.akcijskaCena(0);
		System.out.println(b1);
		
		Pernica p1 = new Pernica();
		p1.dodaj(b3);
		p1.dodaj(b3);
		p1.dodaj(b3);
		p1.dodaj(b2);
		p1.dodaj(b1);
		
		System.out.println(p1);
		
		System.out.println("Broj bojica skupljih od 25 dinara: " + p1.prebroj(25));
	}

}
