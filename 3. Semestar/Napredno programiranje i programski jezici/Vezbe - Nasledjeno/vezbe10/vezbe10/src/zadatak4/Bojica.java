package zadatak4;

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
		super();
		this.serijskiBroj = b.serijskiBroj;
		this.cena = b.cena;
		this.boja = b.boja;
		this.tip = b.tip;
	}

	public String getSerijskiBroj() {
		return serijskiBroj;
	}

	public double getCena() {
		return cena;
	}

	@Override
	public boolean akcijskaCena(double popust) {
		if (popust <= 0) {
			System.out.println("Neuspesan pokusaj smanjivanja cene!");
			return false;
		}
		cena -= cena * (popust / 100);
		System.out.println("Cena je snizena za " + popust +" %.");
		return true;
	}

	@Override
	public String toString() {
		String str = "--- BOJICA ---\n";
		str += "serijski broj: " + serijskiBroj + "\n";
		str += "cena: " + cena + "\n";
		str += "boja: " + boja + "\n";
		str += "tip: " + tip + "\n";
		str += "--------------";
		return str;
	}
}
