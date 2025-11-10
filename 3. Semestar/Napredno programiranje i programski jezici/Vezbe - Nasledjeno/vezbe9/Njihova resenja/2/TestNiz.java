package z2;

import z1.Pravougaonik;


public class TestNiz {

	public static void main(String[] args) {
		System.out.println("Niz realnih brojeva");
		double a[] = new double[3];
		a[0] = 2.5;

		//iteracija kroz niz
		//koristimo polje Length koje poseduje svaki niz
		for (int i = 0; i < a.length; i++) {
			System.out.println("Element na poziciji "+ i + " je " + a[i]);
		}
		

		System.out.println("\nNiz celih brojeva");
		//kreiranje i inicijalizacija niza
		int b[] = {1, 7, 9, 3, 4};

		for (int i = 0; i < b.length; i++) {
			System.out.println("Element na poziciji "+ i + " je " + b[i]);
		}
		
		
		
		System.out.println("\nNiz objekata");
		Pravougaonik pravougaonici[] = new Pravougaonik[5];
        pravougaonici[0] = new Pravougaonik(10, 2);
        pravougaonici[1] = new Pravougaonik(5, 8);
        pravougaonici[2] = new Pravougaonik(3, 9);
        pravougaonici[3] = new Pravougaonik(7, 1);
        pravougaonici[4] = new Pravougaonik(6, 11);
        
		for (int i = 0; i < pravougaonici.length; i++) {
			System.out.println("Pravougaonik na poziciji " + i + " ima povrsinu " 
					+ pravougaonici[i].getP());
		}
		
        // pravougaonik sa najveæom površinom
		System.out.println();

        Pravougaonik pMax = NajvecaPovrsina(pravougaonici);
        if (pMax != null) 
        {
        	System.out.println("Pravougaonik sa najvecom povrsinom je pravougaonik sa stranicama " + pMax.getA() + " i " + pMax.getB());
        }

	}
	
    public static Pravougaonik NajvecaPovrsina(Pravougaonik[] pravougaonici)
    {
        if (pravougaonici == null)
            return null;

        Pravougaonik pMax = pravougaonici[0];
        for (int i = 1; i < pravougaonici.length; i++)
        {
            if (pravougaonici[i].getP() > pMax.getP())
            {
                pMax = pravougaonici[i];
            }
        }
        return pMax;
    }
}
