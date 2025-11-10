package zadatak2_1;

import java.util.HashMap;

public class UcionicaMap {
	private HashMap<String, Student> studenti = new HashMap<String, Student>();
	private int kapacitet = 5;
	
	public boolean dodaj(Student s) {
		if (studenti.size() >= kapacitet) {
			return false;
		}
		studenti.put(s.getIndeks(), s); // ako doda studenta koji ima isti indeks vrednosti ce se zameniti
		return true;
	}
	
	// Kod ove strukture se ne pristupa, pa ni ne izbacuje, preko indeksa. To nije namena.
    // Pristup se radi preko kljuca
	public Student obrisi(String indeks) {
		return studenti.remove(indeks);
	}
	
	public void isprazni() {
		studenti.clear();
	}

	@Override
	public String toString() {
		String str = "*** UCIONICAMAP ***\n";
		if (studenti.isEmpty()) {
			str += "ucionica je prazna!";
			return str;
		}
		for (Student s : studenti.values()) {
			str += s + "\n";
		}
		return str;
	}
}
