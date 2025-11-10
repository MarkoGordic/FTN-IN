package z21;

public class Student {
	
	private String indeks, ime, prezime;

	public Student(String indeks, String ime, String prezime) {
		this.indeks = indeks;
		this.ime = ime;
		this.prezime = prezime;
	}

	public String getIndeks() {
		return indeks;
	}

	public String getIme() {
		return ime;
	}

	public String getPrezime() {
		return prezime;
	}

	public void setIndeks(String indeks) {
		this.indeks = indeks;
	}

	public void setIme(String ime) {
		this.ime = ime;
	}

	public void setPrezime(String prezime) {
		this.prezime = prezime;
	}

	@Override
	public String toString() {
		return "Student [indeks = " + indeks + ", ime = " + ime + ", prezime = " + prezime + "]";
	}

}
