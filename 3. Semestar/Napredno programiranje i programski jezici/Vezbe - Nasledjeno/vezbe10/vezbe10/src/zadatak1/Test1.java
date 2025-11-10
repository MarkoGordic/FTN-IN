package zadatak1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
// ctrl+shift+O odmah dodaje sve importe koji fale

public class Test1 {

	public static void main(String[] args) { // throws IOException ako ima ovo, znaci da ce neki ko poziva nasu metodu
											 // obraditi exception, nije zanimljivo nama sada
		System.out.println("Unesite identifikacioni broj: ");

		// unos se moze prihvatiti i sa
		// Scanner s = new Scanner(System.in);
		// String name = s.nextLine();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		try {
			String procitano = br.readLine(); // deo koda koji moze da izazove gresku ide u try

			int id = Integer.parseInt(procitano); // citamo int upotrebom omotacke klase Integer

			System.out.println("ID: " + id); // ctrl + shift + F formatira sve
		} catch (IOException e) {
			// deo koji obradjuje gresku ispisa/upisa
			e.printStackTrace();
		} catch (NumberFormatException nfe) { // morali smo izdvojiti jer IOException nije dobar za nas slucaj
			// deo koji obradjuje gresku za broj
			System.out.println("los format broja!");
			nfe.printStackTrace();
			
		} catch (Exception exc) { // najopstiji izuzetak se koristi na kraju
			// ako najopstiji ne stavim na kraj onda se oni nakon njega ne gledaju!!!
			// svaki izuzetak je naslednik od klase Exception
			System.out.println("desio se neki drugi izuzetak!");
		} finally { // izvrsava se i da se desio neki exception i da se nije desio
			// koristi se za zatvaranje bafera ili zatvaranje programa
			System.out.println("kraj programa");
			try {
				br.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace(); // izbacuje informacije o samom exception-u, nije dobro ovo ispisivati korisniku zbog odavanja info o sistemu
			}
		}
		
		// kolokvijum: unos sa tastature, da koristimo integer.parseint ako prihvatamo broj i da ga koristimo unutar samog try catch bloka
	}
}
