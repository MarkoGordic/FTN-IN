package pripremaK3;

public class Lampion implements Popravka {

	private int sifra;
	private String boja;
	private boolean ispravan;
	private double cena;

	public Lampion(int sifra, String boja, boolean ispravan, double cena) {
		super();
		this.sifra = sifra;
		this.boja = boja;
		this.ispravan = ispravan;
		this.cena = cena;
	}

	public Lampion(Lampion l) {
		sifra = l.sifra;
		boja = l.boja;
		ispravan = l.ispravan;
		cena = l.cena;
	}

	public int getSifra() {
		return sifra;
	}

	public String getBoja() {
		return boja;
	}

	public boolean isIspravan() {
		return ispravan;
	}

	public double getCena() {
		return cena;
	}

	public void setCena(double cena) {
		this.cena = cena;
	}

	@Override
	public boolean popravi() {
		if (!ispravan) {
			ispravan = true;
			return true;
		}

		return false;
	}

	@Override
	public String toString() {
		String i;
		if (ispravan)
			i = "ispravan";
		else
			i = "neispravan";

		String ret = "----- Lampion -----\n";
		ret += "Sifra = " + sifra + "\n";
		ret += "Boja = " + boja + "\n";
		ret += "Ispravan = " + i + "\n";
		ret += "Cena = " + cena + "\n";
		ret += "-------------------";
		return ret;

	}
}
