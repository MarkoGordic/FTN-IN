package novogodisnja_rasveta;

public class Lampion implements Popravka {
	private int sifra;
	private String boja;
	private boolean ispravan;
	private double cena;
	
	public Lampion(int sifra, String boja, double cena, boolean ispravan) {
		super();
		this.sifra = sifra;
		this.boja = boja;
		this.cena = cena;
		this.ispravan = ispravan;
	}

	public Lampion(Lampion l) {
		super();
		this.sifra = l.sifra;
		this.boja = l.boja;
		this.cena = l.cena;
		this.ispravan = l.ispravan;
	}

	public double getCena() {
		return cena;
	}

	public void setCena(double cena) {
		this.cena = cena;
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
		String str = "------ Lampion ------\n";
		str += "Sifra = " + sifra;
		str += "\nBoja = " + boja;
		str += "\nIspravan = ";
		if (ispravan)
			str += "ISPRAVAN";
		else
			str += "NEISPRAVAN";
		str += "\nCena = " + cena;
		str += "\n------------------------";
		return str;
	}

}
