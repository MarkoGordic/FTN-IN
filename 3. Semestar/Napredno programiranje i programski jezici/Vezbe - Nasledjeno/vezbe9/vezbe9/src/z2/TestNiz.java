package z2;

import z1.Pravougaonik;

public class TestNiz {
	// staticke metode su pandan slobodnim funkcijama u c++, mislim nesto kao
	public static Pravougaonik NajvecaPovrsina(Pravougaonik[] pravougaonici) {
		if (pravougaonici.length < 0) {
			return null;
		}
		Pravougaonik najveci = pravougaonici[0];
		for (int i = 1; i < pravougaonici.length; i++) {
			if (pravougaonici[i].getP() > najveci.getP()) {
				najveci = pravougaonici[i];
			}
		}
		return najveci;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		// nacini pravljenja niza
		// int nizInt[] = new int[5]; // takodje bi trebalo ovo inicijalizovati kasnije
		int nizInt2[] = new int[] {1, 2, 3, 4};
		for (int i = 0; i < nizInt2.length; i++) {
			System.out.println("nizInt2[" + i + "]: " + nizInt2[i]);
		}
	
		double nizDouble[] = new double[] {1.4, Math.PI, Math.E};
		for (int i = 0; i < nizDouble.length; i++) {
			System.out.println("nizDouble[" + i + "]: " + nizDouble[i]);
		}
	
		Pravougaonik p1 = new Pravougaonik(3, 4);
		Pravougaonik p2 = new Pravougaonik(4, 5);
		Pravougaonik p3 = new Pravougaonik(4, 4);
		Pravougaonik p4 = new Pravougaonik(p3);
		Pravougaonik nizPravougaonik[] = new Pravougaonik[3];
		nizPravougaonik[0] = p1;
		nizPravougaonik[1] = p2;
		nizPravougaonik[2] = p3;
		nizPravougaonik[3] = p4;

		for (int i = 0; i < nizPravougaonik.length; i++) {
			System.out.println("nizPravougaonik[" + i + "]: A:" + nizPravougaonik[i].getA() + " B:" + nizPravougaonik[i].getB());
		}
		
		Pravougaonik najveci = NajvecaPovrsina(nizPravougaonik);
		System.out.println("Najveci pravougaonik: A:" + najveci.getA() + " B:" + najveci.getB());

	}

}
