package z2;

public class CDDisk {

	private String naziv;
	private String izvodjac;
	private int id;
	
	public CDDisk() {
		naziv = "nepoznat";
		izvodjac = new String("nepoznat");
		id = -1;
	}
	
	public CDDisk(int id, String naziv, String izvodjac) {
		this.id = id;
		this.naziv = naziv;
		this.izvodjac = izvodjac;
	}

	public String getNaziv() {
		return naziv;
	}

	public void setNaziv(String naziv) {
		this.naziv = naziv;
	}

	public String getIzvodjac() {
		return izvodjac;
	}

	public void setIzvodjac(String izvodjac) {
		this.izvodjac = izvodjac;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String toString() {
		return "CD [" + id + ", " + naziv + ", " + izvodjac + " ]";
	}

}
