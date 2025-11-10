package zadatak2;

public class CDDisk {
	private int id;
	private String naziv;
	private String izvodjac;

	public CDDisk(int id, String naziv, String izvodjac) {
		super();
		this.id = id;
		this.naziv = naziv;
		this.izvodjac = izvodjac;
	}

	public CDDisk() {
		super();
		this.id = 0;
		this.naziv = "milojica";
		this.izvodjac = "mile";
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
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

	@Override
	public String toString() {
		String str = "--- CDDisk ---";
		str += "\nid: " + id;
		str += "\nnaziv: " + naziv;
		str += "\nizvodjac: " + izvodjac + "\n";
		return str;
		
		// ili ga samo ovako vratimo :)
		//return "--- CDDisk ---\nid=" + id + "\nNaziv: " + naziv + "\nIzvodjac: " + izvodjac;
	}
}
