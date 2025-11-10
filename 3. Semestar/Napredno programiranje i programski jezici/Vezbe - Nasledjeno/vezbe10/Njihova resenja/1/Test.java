package z1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class Test {

	public static void main(String[] args) {
		
		System.out.println("Unesite identifikacioni broj:");
		
		BufferedReader br = null;		
		
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
			int id = Integer.parseInt(br.readLine());
			System.out.println("Uneli ste identifikacioni broj: " + id);
		} catch (NumberFormatException nfe) {
			System.out.println("Identifikacioni broj mora biti celobrojna vrednost!");
			//nfe.printStackTrace();
		} catch (Exception e) {
			System.out.println("Dogodio se neki drugi izuzetak.");
			//e.printStackTrace();
		} finally {
			System.out.println("\nProgram zavrsen");
			//zatvaranje readera
			//i zatvaranje moze da baci izuzetak pa odatle novi try/catch
			try {
				br.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

}
