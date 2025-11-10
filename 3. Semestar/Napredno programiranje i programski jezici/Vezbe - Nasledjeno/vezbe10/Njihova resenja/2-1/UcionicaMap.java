package z21;

import java.util.HashMap;

public class UcionicaMap {
	private HashMap<String, Student> studenti = new HashMap<String, Student>();
	private int kapacitet = 5;
	
	public void dodajStudenta(Student s){
		if(studenti.size() < kapacitet)
			studenti.put(s.getIndeks(), s);
        // ako doda studenta koji ima isti indeks vrednosti ce se zameniti
	}

    // Kod ove strukture se ne pristupa, pa ni ne izbacuje, preko indeksa. To nije namena.
    // Pristup se radi preko kljuca
	public void ukloniStudenta(String indeks){
		studenti.remove(indeks);
	}
	
	public void isprazniUcionicu(){
		studenti.clear();
	}
	
	@Override
	public String toString() {
		return "UcionicaMap: studenti = " + studenti ;
	}
}