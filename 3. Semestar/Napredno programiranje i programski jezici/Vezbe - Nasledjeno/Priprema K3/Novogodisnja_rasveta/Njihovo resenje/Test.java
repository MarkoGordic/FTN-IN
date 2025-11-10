package pripremaK3;

public class Test {

	public static void main(String[] args) {
		/* ************** Testiranje klase Lampion ************** */
		System.out.println("Testiranje klase Lampion:");
		Lampion l1 = new Lampion(123, "plava", true, 1123.44);
		Lampion l2 = new Lampion(456, "zuta", true, 1421.98);
		Lampion l3 = new Lampion(789, "crvena", true, 856.35);
		Lampion l4 = new Lampion(101, "crvena", true, 2245.23);
		Lampion l5 = new Lampion(452, "plava", true, 2097.04);
		Lampion l6 = new Lampion(894, "zuta", false, 2941.12);
		Lampion l7 = new Lampion(679, "plava", true, 1750.59);
		Lampion l = new Lampion(l7);
		l.getBoja();
		l.getCena();
		l.getSifra();
		l.isIspravan();
		l.setCena(10);
		l.popravi();
		System.out.println(l);
		System.out.println();

		/* ******** Testiranje klase Novogodisnja rasveta ******** */
		System.out.println("Testiranje klase NovogodisnjaRasveta:");

		NovogodisnjaRasveta nr = new NovogodisnjaRasveta();
		System.out.println(nr);

		nr.dodaj(l1);
		nr.dodaj(l2);
		nr.dodaj(l3);
		nr.dodaj(l4);
		nr.dodaj(l5);
		nr.dodaj(l6);
		nr.dodaj(l7);
		System.out.println(nr);

		Lampion trazeniLampion = nr.pronadji(1199.99, "crna");
		if (trazeniLampion != null)
			System.out.println("Trazeni lampion: " + trazeniLampion.toString() + "\n");
		else
			System.out.println("Ne postoji trazeni lampion!\n");

		// trazeniLampion.toString(); //da nismo imali proveru desio bi se
		// NullPointerException

		System.out.println(nr.postaviAkciju());
		System.out.println(nr);
	}
}
