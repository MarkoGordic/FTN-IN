package skolskiPriborJava;

public class Bojica implements IzracunavanjeCene {
	
	private String serijskiBroj;
	private double cena;
	private String boja;
	private String tip;
	
	public Bojica(String serijskiBroj, double cena, String boja, String tip) {
		super();
		this.serijskiBroj = serijskiBroj;
		this.cena = cena;
		this.boja = boja;
		this.tip = tip;
	}

	public Bojica(Bojica b) {
		serijskiBroj = b.serijskiBroj;
		cena = b.cena;
		boja = b.boja;
		tip = b.tip;
	}

	public String getSerijskiBroj() {
		return serijskiBroj;
	}

	public double getCena() {
		return cena;
	}
	
	@Override
	public boolean akcijskaCena(double procenat) {
		if(procenat <= 0) {
			System.out.println("Neuspesan pokusaj smanjivanja cene!");
			return false;
		}
		
		cena *= 1 - procenat / 100;
		System.out.println("Cena je snizena za " + procenat + "%.");
		
		return true;		
	}

	@Override
	public String toString() {
		return "Bojica [serijskiBroj=" + serijskiBroj + ", cena=" + cena + ", boja=" + boja + ", tip=" + tip + "]";
	}		
}
