package z21;

import java.util.ArrayList;

public class Ucionica {
	private ArrayList<Student> studenti = new ArrayList<Student>();
	private int kapacitet = 5;
	
	public void dodajStudenta(Student s){
		if(studenti.size() < kapacitet){
			studenti.add(s);
		}
	}

	// izbacivanje preko indeksa
	public void ukloniStudenta(int i){
		studenti.remove(i);
	}
	
	public void isprazniUcionicu(){
		studenti.clear();
	}

	@Override
	public String toString() {
		if (studenti.size() == 0)
			return "Ucionica je prazna";
		
		return "Ucionica: studenti = " + studenti;
	}
	
}
