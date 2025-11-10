package zadatak2;

import java.util.ArrayList;

public class XCDStorage {
	private ArrayList<CDDisk> arhiva; // vid genericke klase
	// napravili smo samo referencu na tu listu, u konstruktoru cemo napraviti novu
	// listu
	// ako ne uradimo to u konstruktoru, imacemo null pointer exception jer je
	// default vrednost za referenec upravo null

	public XCDStorage() {
		super();
		arhiva = new ArrayList<CDDisk>(); // mada ih mozemo odmah inicijalizovati bez ovoga u konstruktoru vec gore kod
											// polja (vazi za listu i za mapu)
	}

	// ako ne napisemo nista onda je to package ili default kako nazivaju
	public boolean dodaj(CDDisk cd) {
		for (int i = 0; i < arhiva.size(); i++) {
			if (arhiva.get(i).getId() == cd.getId()) {
				return false;
			}
		}
		return arhiva.add(cd); // mozemo slati i na neki indeks koji mi zelimo
	}

	public CDDisk izbaci(int id) {
		for (int i = 0; i < arhiva.size(); i++) {
			if (arhiva.get(i).getId() == id) {
				return arhiva.remove(i); // moze i da se prosledi objekat ali tad vraca boolean
			}
		}
		// mogli bismo i foreach ali bismo koristili drugu metodu
		// ako se naglasi da treba po indeksu ili po id da se brise onda ne sme
		// foreach!!!
		return null;
	}

	public CDDisk pronadji(int id) {
		for (int i = 0; i < arhiva.size(); i++) {
			if (arhiva.get(i).getId() == id) {
				return arhiva.get(i);
			}
		}
		// moze i ovako
		/*
		 * for (CDDisk cd : arhiva) { if (cd.getId() == id) { return cd; } }
		 */
		return null;
	}

	public void isprazni() {
		arhiva.clear();
	}

	@Override
	public String toString() {
		String str = "*** XCDStorage ***\n";
		if (arhiva.isEmpty()) {
			str += "Arhiva je prazna!";
			return str;
		}
		// for (int i = 0; i < arhiva.size(); i++) { ret += arhiva.get(i); ret += "\n"; }
		// malko je brze da koristimo nesto sto je kao for each koji ide element po element iz liste
		// koristimo ga za kolekcije
		for (CDDisk cd : arhiva) {
			str += cd + "\n";
		}
		return str;
	}
}
