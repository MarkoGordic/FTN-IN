package zadatak3_1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Test3_1 {
	public static boolean isPalindrome(String str) {
		str = str.toLowerCase();
		str = str.trim();
		String[] splits = str.split(" ");
		String temp = new String();
		for (String s : splits) {
			temp += s;
		}
		for (int i = 0; i < temp.length() / 2; i++) {
			if (temp.charAt(i) != temp.charAt(temp.length() - i - 1)) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			String str = br.readLine();
			System.out.println(isPalindrome(str));
		} catch(IOException ioe) {
			System.out.println("Greska prilikom unosa!");
		} catch(Exception e) {
			e.printStackTrace();
		} finally {
			try {
				br.close();
			} catch(IOException ioe) {
				System.out.println("Greska prilikom zatvaranja BufferedReadera!");
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
	}
}
