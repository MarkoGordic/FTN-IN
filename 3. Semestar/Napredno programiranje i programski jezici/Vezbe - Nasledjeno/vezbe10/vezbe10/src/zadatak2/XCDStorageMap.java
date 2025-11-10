package zadatak2;

import java.util.HashMap;

public class XCDStorageMap {
	private HashMap<Integer, CDDisk> arhiva; // umesto prostog tipa, mora klasa koja predstavlja taj prosti tip
	
	public XCDStorageMap() {
		super();
		arhiva = new HashMap<Integer, CDDisk>();
	}
	
	public boolean dodaj(CDDisk cd) {
		if (arhiva.containsKey(cd.getId())) {
			return false; // verovatno nece traziti kolizije vec samo da proverimo da li vec postoji objekat takvog id-a i onda ne dodajemo ako postoji vec
		}
		arhiva.put(cd.getId(), cd); // put vraca prethodnu vrednost povezanu sa tim kljucem pre nego sto smo je zgazili
		return true; // sigurno ce put biti dobar pa mozemo vratiti true
	}
	
	public CDDisk izbaci(int id) {
		/*if (arhiva.containsKey(id)) {
			return arhiva.remove(id);
		}
		return null;*/
		// dovoljno je ovo
		return arhiva.remove(id); // remove takodje vraca prethodnu vrednost, bas kao i put
	}
	
	public CDDisk pronadji(int id) {
		return arhiva.get(id); // get cita objekat i vraca ga
	}
	
	public void isprazni() {
		arhiva.clear();
	}

	@Override
	public String toString() {
		String str = "*** XCDStorageMAP ***\n";
		if (arhiva.isEmpty()) {
			str += "Arhiva je prazna!";
			return str;
		}
		for (CDDisk cd : arhiva.values()) {
			// moramo preko foreach jer klasicno iteriranje ne moze
			// sa .values citamo samo vrednosti bez kljuceva
			str += cd + "\n";
		}
		return str;
	}
}
