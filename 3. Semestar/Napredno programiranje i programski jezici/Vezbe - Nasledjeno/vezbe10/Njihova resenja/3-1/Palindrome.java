package z31;

import java.util.Scanner;

public class Palindrome {

	public static void main(String[] args) {
		 String pom, palindrome;

         System.out.println("Unesite recenicu: ");
         Scanner sc = new Scanner(System.in);
         palindrome = sc.nextLine();
         sc.close();
         
         pom = palindrome.replace(" ", "");
         pom = pom.toLowerCase();

         if (isPalindrome(pom)) {
        	 System.out.printf("%s is a palindrome.", palindrome);
         } else {
        	 System.out.printf("%s is NOT a palindrome.", palindrome);
         }
     }
     
     public static boolean isPalindrome(String word) {
    	 boolean ret = true;
         int duzina = word.length();

         for (int i = 0; i < duzina / 2; i++){
             if (word.charAt(i) != word.charAt(duzina - 1 - i)){
                 ret = false;
                 break;
             }
         }
             
         return ret;
     }

}