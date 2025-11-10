package zadatak2_1;

public class Student {
	private String indeks;
	private String ime;
	private String prezime;
	public Student(String indeks, String ime, String prezime) {
		super();
		this.indeks = indeks;
		this.ime = ime;
		this.prezime = prezime;
	}
	@Override
	public String toString() {
		String str = "--- STUDENT ---\n";
		str += "indeks: " + indeks;
		str += "\nime: " + ime;
		str += "\nprezime: " + prezime;
		str += "\n-------------";
		return str;
	}
	public String getIndeks() {
		return indeks;
	}
	public void setIndeks(String indeks) {
		this.indeks = indeks;
	}
	public String getIme() {
		return ime;
	}
	public void setIme(String ime) {
		this.ime = ime;
	}
	public String getPrezime() {
		return prezime;
	}
	public void setPrezime(String prezime) {
		this.prezime = prezime;
	}
}
