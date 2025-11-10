package novogodisnji_paketic;

public class NovogodisnjiPaketic extends Pakovanje {
	private String opis;
	private String namenjen;
	private boolean spakovan;
	private int minimalanUzrast;
	private boolean zasluzen;
	private boolean spremanZaIsporuku;
	
	public NovogodisnjiPaketic(String opis, String namenjen, boolean spakovan, int minimalanUzrast, boolean zasluzen, boolean spremanZaIsporuku) {
		super();
		this.opis = opis;
		this.namenjen = namenjen;
		this.spakovan = spakovan;
		this.minimalanUzrast = minimalanUzrast;
		this.zasluzen = zasluzen;
		this.spremanZaIsporuku = spremanZaIsporuku;
	}

	public String getOpis() {
		return opis;
	}

	public void setOpis(String opis) {
		this.opis = opis;
	}

	public boolean isSpremanZaIsporuku() {
		return spremanZaIsporuku;
	}

	public void setSpremanZaIsporuku(boolean spremanZaIsporuku) {
		this.spremanZaIsporuku = spremanZaIsporuku;
	}

	public String getNamenjen() {
		return namenjen;
	}

	public boolean isSpakovan() {
		return spakovan;
	}

	public int getMinimalanUzrast() {
		return minimalanUzrast;
	}

	@Override
	public boolean spakuj() {
		if (!zasluzen || spakovan) {
			return false;
		}
		else if ((namenjen.equals("za decaka") || namenjen.equals("za devojcicu")) && minimalanUzrast > 2) {
			System.out.println("Novogodisnji paketic je uspesno spakovan.");
			spakovan = true;
			return true;
		}
		return false;
	}

	@Override
	public String toString() {
		String zasluzio = new String();
		String spakovano = new String();
		String spreman = new String();
		if (zasluzen) {
			zasluzio = "zasluzeno";
		}
		else {
			zasluzio = "nezasluzeno";
		}
		if (spakovan) {
			spakovano = "spakovano";
		}
		else {
			spakovano = "nespakovano";
		}
		if (spremanZaIsporuku) {
			spreman = "spreman";
		}
		else {
			spreman = "nespreman";
		}
		
		String str = "------ NovogodisnjiPaketic ------";
		str += "\nopis: " + opis;
		str += "\nnamenjen: " + namenjen;
		str += "\nspakovan: " + spakovano;
		str += "\nminimalanUzrast: " + minimalanUzrast;
		str += "\nzasluzen: " + zasluzio;
		str += "\nspremanZaIsporuku: " + spreman;
		str += "\n---------------------------------";
		return str;
	}
}
