package pripremaK3;

import java.util.ArrayList;
import java.util.Scanner;

public class NovogodisnjaRasveta {

	private int kapacitet = 5; // inicijalizacija moze ili ovde ili u konstrukotru
	private ArrayList<Lampion> lampioni = new ArrayList<Lampion>(); // inicijalizacija moze ili ovde ili u konstrukotru

	public NovogodisnjaRasveta() {
		super();
	}

	public boolean dodaj(Lampion noviLampion) {
		if (lampioni.size() >= kapacitet || !noviLampion.isIspravan())
			return false;

		for (Lampion l : lampioni)
			if (l.getSifra() == noviLampion.getSifra())
				return false;

		return lampioni.add(noviLampion);
	}

	public Lampion pronadji(double cena, String boja) {
		for (Lampion l : lampioni)
			if (l.getCena() > cena && l.getBoja().equals(boja)) // mora equals poredimo sadrzaj stringova, ne adrese
				return l;

		return null;
	}

	public boolean postaviAkciju() {
		if (lampioni.size() == 0)
			return false;

		System.out.println("Molimo vas unesite akcijsku cenu:");
		Scanner sc = new Scanner(System.in);
		String uneto = sc.nextLine();
		sc.close();

		try {
			int novaCena = Integer.parseInt(uneto);
			Lampion maks = lampioni.get(0);
			for (int i = 1; i < lampioni.size(); i++) { // i je na pocetku 1 da ne uporedjujeno lampion na indksu 0 sa
														// samim sobom
				if (lampioni.get(i).getCena() > maks.getCena()) {
					maks = lampioni.get(i);
				}
			}
			if (novaCena < maks.getCena()) {
				maks.setCena(novaCena);
				return true;
			}
			return false;

		} catch (NumberFormatException nfe) {
			return false;
		}

	}

	@Override
	public String toString() {
		if (lampioni.isEmpty())
			return "Lista lampiona je prazna!";

		String s = "U listi se nalaze sledeci lampioni:\n";
		for (Lampion l : lampioni)
			s += l + "\n";

		return s;
	}
}
