package skolskiPriborJava;

import java.util.HashMap;

public class Pernica {

	private HashMap<String, Bojica> bojice;
	private int raspolozivoMesta = 5;
	
	public Pernica() {
		super();
		bojice = new HashMap<String, Bojica>();
	}
	
	public boolean dodaj(Bojica b) {
		if(bojice.containsKey(b.getSerijskiBroj()))
			return false;
		
		if(bojice.size() < raspolozivoMesta) {
			bojice.put(b.getSerijskiBroj(), b);
			return true;
		}
		
		return false;
	}
	
	public int prebroj(double cena) {
		int brojac = 0;
		
		for(Bojica b : bojice.values()) 
			if(b.getCena() > cena)
				brojac++;
		
		return brojac;
	}

	@Override
	public String toString() {
		if(bojice.size() == 0)
			return "\nPernica je prazna!";
		
		String s = "\nU pernici se nalaze sledece bojice:\n";
		for(Bojica b : bojice.values())
			s += b + "\n";
		
		return s;
	}
	
	public static void main(String[] args) {
		Bojica b1 = new Bojica("123abc", 23.9, "drvena", "zelena");
		Bojica b2 = new Bojica("456mnk", 57.4, "vostana", "plava");
		Bojica b3 = new Bojica("789edf", 45.6, "drvena", "zuta");
		Bojica b4 = new Bojica("035sdv", 68.3, "vostana", "bela");
		Bojica b = new Bojica(b1);
		
		System.out.println(b);
		b.akcijskaCena(7);
		System.out.println(b);
		
		Pernica p = new Pernica();
		
		p.dodaj(b1);
		p.dodaj(b2);
		p.dodaj(b3);
		p.dodaj(b4);
		System.out.println(p.toString());
	
		System.out.println("broj bojica sa cenom vecom od zadate: " + p.prebroj(50.5));
	}
}
