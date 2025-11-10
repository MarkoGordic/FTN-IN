package zadatak2_1;

import java.util.ArrayList;

public class Ucionica {
	private ArrayList<Student> studenti = new ArrayList<Student>();
	private int kapacitet = 5;
	
	// oni su isli sa stavom da sve bude void
	public boolean dodaj(Student s) {
		if (studenti.size() >= kapacitet) {
			return false;
		}
		return studenti.add(s);
	}
	
	public Student ukloni(int i) {
		return studenti.remove(i);
	}
	
	public void isprazni() {
		studenti.clear();
	}

	@Override
	public String toString() {
		String str = "*** UCIONICA ***\n";
		if (studenti.isEmpty()) {
			str += "ucionica je prazna!";
			return str;
		}
		for (Student s : studenti) {
			str += s + "\n";
		}
		return str;
		// po njima samo
		// return "Ucionica: studenti = " + studenti;
	}
}
