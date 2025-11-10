package paketic;

import java.util.ArrayList;
import java.util.HashMap;

public class DedaMraz {

	private HashMap<String, NovogodisnjiPaketic> novogodisnjiPaketici;

	public DedaMraz() {
		this.novogodisnjiPaketici = new HashMap<String, NovogodisnjiPaketic>();
	}

	public boolean pripremiZaIsporuku(NovogodisnjiPaketic np, String o) {
		if (np.spakuj()) {
			np.setOpis(o);
			np.setSpremanZaIsporuku(true);
			System.out.println("Novogodisnji paketic je spreman za isporuku.");
			return true;
		}

		return false;
	}

	public boolean dodaj(NovogodisnjiPaketic novogodisnjiPaketic) {
		if (!novogodisnjiPaketic.isSpremanZaIsporuku())
			return false;

		String kljuc = novogodisnjiPaketic.getOpis().substring(0, 3) + ":" + novogodisnjiPaketic.getMinimalanUzrast();

		if (novogodisnjiPaketici.containsKey(kljuc))
			return false;

		novogodisnjiPaketici.put(kljuc, novogodisnjiPaketic);
		return true;
	}

	public NovogodisnjiPaketic izbaci(String opis, int minUzrast) {
		String kljuc = opis.substring(0, 3) + ":" + minUzrast;
		return novogodisnjiPaketici.remove(kljuc);
	}

	public double prosecniMinimalniUzrast() {
		double suma = 0;
		for (NovogodisnjiPaketic np : novogodisnjiPaketici.values()) {
			suma += np.getMinimalanUzrast();
		}
		return suma / novogodisnjiPaketici.size();
	}

	public ArrayList<String> sifrujNamenjen() {
		ArrayList<String> ret = new ArrayList<String>();
		for (NovogodisnjiPaketic np : novogodisnjiPaketici.values()) {
			String sifra = np.getOpis();
			sifra = sifra.trim();
			sifra = sifra.toUpperCase();
			if (sifra.length() > 5) {
				char poslednji = sifra.charAt(sifra.length()-1);
				char prvi = sifra.charAt(0);
	            sifra = poslednji + sifra.substring(1, sifra.length() - 1) + prvi;
			} else {
				sifra.replace("a", "e");
				sifra.replace("e", "i");
				sifra.replace("i", "o");
			}
			ret.add(sifra);
		}
		return ret;
	}

	@Override
	public String toString() {
		String str = "";

		str += "---------------------------- DEDA MRAZ ----------------------------\n";

		if (novogodisnjiPaketici.isEmpty())
			str += "Vreca Deda Mraza je trenutno prazna!\n";
		else {
			for (NovogodisnjiPaketic np : novogodisnjiPaketici.values())
				str += np + "\n";
		}

		str += "-------------------------------------------------------------------";

		return str;
	}

	public static void main(String[] args) {
		NovogodisnjiPaketic np1 = new NovogodisnjiPaketic("nestoo", "za decaka", false, 3, true, false);
		NovogodisnjiPaketic np2 = new NovogodisnjiPaketic("opisNeki", "za devojcicu", false, 4, true, false);
		NovogodisnjiPaketic np3 = new NovogodisnjiPaketic("iOvoJeOpis", "za decaka", false, 2, true, false);
		NovogodisnjiPaketic np4 = new NovogodisnjiPaketic("LaLaLa", "za devojcicu", false, 3, true, false);
		NovogodisnjiPaketic np5 = new NovogodisnjiPaketic("Zima", "za decaka", false, 5, true, false);
		NovogodisnjiPaketic np6 = new NovogodisnjiPaketic("ZimskaCarolija", "za devojcicu", false, 1, true, false);
		np1.getMinimalanUzrast();
		np1.getNamenjen();
		np1.getOpis();
		np1.isSpakovan();
		np1.isSpremanZaIsporuku();
		np1.setOpis("ho-ho-ho");
		np1.setSpremanZaIsporuku(false);
		np1.spakuj();
		System.out.println(np1);

		DedaMraz dm = new DedaMraz();

		System.out.println(dm);

		dm.pripremiZaIsporuku(np1, "vozic");
		dm.pripremiZaIsporuku(np2, "barbika");
		dm.pripremiZaIsporuku(np3, "lego kockice");
		dm.pripremiZaIsporuku(np4, "bratz lutka");
		dm.pripremiZaIsporuku(np5, "dinosaurus");
		dm.pripremiZaIsporuku(np6, "plisani meda");

		dm.dodaj(np1);
		dm.dodaj(np2);
		dm.dodaj(np3);
		dm.dodaj(np4);
		dm.dodaj(np5);
		dm.dodaj(np6);
		dm.dodaj(np5);

		System.out.println(dm);

		dm.izbaci("bratz lutka", 3);
		System.out.println(dm);

		System.out.println("Prosecni minimalni uzrast je: " + dm.prosecniMinimalniUzrast());
	
		System.out.println(dm.sifrujNamenjen());
	}
}
