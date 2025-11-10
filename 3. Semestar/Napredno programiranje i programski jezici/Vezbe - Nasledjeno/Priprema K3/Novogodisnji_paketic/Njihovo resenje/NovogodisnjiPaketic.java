package paketic;

public class NovogodisnjiPaketic extends Pakovanje {
	
	private String opis;
	private String namenjen; //za decaka, za devojcicu
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

	public int getMinimalanUzrast() {
		return minimalanUzrast;
	}
	
	public String getOpis() {
		return opis;
	}
	
	public String getNamenjen() {
		return namenjen;
	}

	public boolean isSpakovan() {
		return spakovan;
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

	@Override
	public boolean spakuj() {
		if(!zasluzen || spakovan)
			return false;
		
		if((namenjen.equals("za decaka") || namenjen.equals("za devojcicu")) && minimalanUzrast > 2) {
			spakovan = true;
			System.out.println("Novogodisnji paketic je uspesno spakovan.");
			return true;
		}
			
		return false;
	}

	@Override
	public String toString() {
		String s, z, szi;
		
		if(spakovan)
			s = "spakovan";
		else
			s = "nije spakovan";
		
		if(zasluzen)
			z = "zasluzen";
		else
			z = "nije zasluzen";
		
		if(spremanZaIsporuku)
			szi = "spreman za isporuku";
		else
			szi = "nije spreman za isporuku";
		
		return "Novogodisnji paketic [opis=" + opis + 
				", namenjen=" + namenjen + 
				", spakovan=" + s +
				", minimalanUzrast=" + minimalanUzrast +
				", zasluzen=" + z +
				", spremanZaIsporuku=" + szi + "]";
	}
	
}
