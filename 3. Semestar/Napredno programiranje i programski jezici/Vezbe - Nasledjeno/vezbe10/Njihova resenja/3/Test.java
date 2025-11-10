package z3;

import java.util.Scanner;

public class Test {

	public static void main(String[] args) {
		//inicijalizacija stringa
		String name = "Scala"; //prvi String objekat
		String name_1 = "Scala"; //isti objekat kao prvi, dodeljena mu samo referenca na postojeci
		String name_2 = new String("Scala"); //novi String objekat
		
		char[] nameArray = { 'S', 'c', 'a', 'l', 'a'};
	    String name_3 = new String(nameArray);  
	    System.out.println(name_3);

		//vratice true
		if(name==name_1){ //poredi adrese
			System.out.println("both name and name_1 is pointing to same string object");
		}

		//vratice false
		if(name==name_2){ //poredi adrese
			System.out.println("both name and name_2 is pointing to same string object");
		}
		
		//vratice true
		if(name.equals(name_1)){ //poredi sadrzaj stringova
			System.out.println("name and name_1 are equal String by equals method");
		}

		//vratice true
		if(name.equals(name_2)){  //poredi sadrzaj stringova
			System.out.println("name and name_2 are equal String by equals method");
		}

		
		System.out.println("-------------------------------------");
		
		
		//Odredjivanje duzine stringa
		String palindrome = "Dot saw I was Tod";
	    int len = palindrome.length();
	    System.out.println("String Length is : " + len);
		
	    
	    System.out.println("-------------------------------------");
	    
	    
	    //Koriscenje Skenera za unos sa tastature, citanje karaktera sa odredjene pozicije u stringu
	    String original, reverse = "";
	    Scanner in = new Scanner(System.in);
	    
	    System.out.println("Enter a string to reverse");
	    
	    original = in.nextLine();
	    in.close();
	 
	    int length = original.length();
	 
	    for ( int i = length - 1 ; i >= 0 ; i-- )
	    	reverse = reverse + original.charAt(i);
	 
	    System.out.println("Reverse of entered string is: " + reverse);
	    
	    
	    System.out.println("-------------------------------------");

		
	    //konkatenacija sa metodom concat
	    String s2 = name.concat(name_2);
	    System.out.println(s2);
	    
		//konkatenacija sa operatorom +
		String s3 = name + " " + name_2;
		System.out.println(s3);


		System.out.println("-------------------------------------");
		
		
		//testiranje metoda indexOf, lastIndexOf i matches
		String str = "Java is the best programming language";

		if(str.indexOf("Java") != -1){
		     System.out.println("String contains Java at index :" + str.indexOf("Java"));
		}

		if(str.matches("J.*")){
		     System.out.println("String Starts with J");
		}

		str ="Do you like Java ME or Java EE";

		if(str.lastIndexOf("Java") != -1){
		      System.out.println("String contains Java lastly at: " + str.lastIndexOf("Java"));
		}
		
		
		System.out.println("-------------------------------------");
		
		//testiranje substring metode
		//vratice deo stringa str od indeksa 0 do 12
		String subString = str.substring(0, 12);
		    
		System.out.println("Substring: " + subString);
		
				
		System.out.println("-------------------------------------");
		
		
		String str2 = "   String Trim Example "; 
		System.out.println("Original String :" + str2); 
		System.out.println("After trim :" + str2.trim());
		
		//zamena karaktera karakterom
		String str3 = new String("Welcome to Tutorialspoint.com");
		System.out.println("Return Value :" + str3.replace('o', 'T'));
		
		//zamena niza karaktera nizom karaktera
		String replaceSample = "String replace Example of replacing Character Sequence";
		System.out.println("Return Value :" + replaceSample.replace("re", "RE"));
		
		//replaceAll(String regex, String replacement)
		String replaceSample2 = "String replace Example with regular expreSsion";
		System.out.println("Return Value :" + replaceSample2.replaceAll("^S","R"));
		
		//replaceFirst(String regex, String replacement)
		String replaceSample3 = "String replace Example with replaceFirst";
		System.out.println("Return Value :" + replaceSample3.replaceFirst("re","RE"));


		System.out.println("-------------------------------------");
		

        //pretvaranje velikih slova u mala i malih u velika
        String test = "mala VELIKA RaNdOm slova 123";
        System.out.println("Testni string: " + test);
        System.out.println("Mala slova: " + test.toLowerCase());
        System.out.println("Velika slova: " + test.toUpperCase());


        System.out.println("-------------------------------------");
		
		
		//testiranje split metode 
		
		String assetClasses = "Gold:Stocks:Fixed Income:Commodity:Interest Rates";
		String[] splits = assetClasses.split(":");

		System.out.println("splits.size: " + splits.length);

		for(String asset: splits){
		System.out.println(asset);
		}

		System.out.println("- - - - - - - - - - - - - - - - - - -");
		
		
		//testiranje split metode sa specijalnim karakterom

		String assetTrading = "Gold Trading|Stocks Trading|Fixed Income Trading|Commodity Trading|FX trading";

		String[] splits2 = assetTrading.split("\\|");  // two \\ is required because "\"     itself require escaping

		for(String trading: splits2){
		System.out.println(trading);
		}

		System.out.println("- - - - - - - - - - - - - - - - - - -");
		
		
		//testiranje split metode sa specijalnim karakterom

		String smartPhones = "Apple IPhone.HTC Evo3D.Nokia N9.LG Optimus.Sony Xperia.Samsung Charge";

		String[] smartPhonesSplits = smartPhones.split("\\.");

		for(String smartPhone: smartPhonesSplits){
		System.out.println(smartPhone);
		}

		
		System.out.println("-------------------------------------");
		
		
		//testiranje split metode sa ogranicenjem
		String places = "London.Switzerland.Europe.Australia";
		String[] placeSplits = places.split("\\.", 2);

		System.out.println("placeSplits.size: " + placeSplits.length );

		for(String contents: placeSplits){
		System.out.println(contents);
		}


		System.out.println("-------------------------------------");

		//testitanje formatiranja stringa
		float floatVar = 3.6f;
		int intVar = 6;
		String stringVar = "Sest";
		
		System.out.printf("The value of the float variable is " +
		                  "%f, while the value of the integer " +
		                  "variable is %d, and the string " +
		                  "is %s" + "\n", floatVar, intVar, stringVar);

		String fs;
		fs = String.format("The value of the float variable is " +
		                   "%f, while the value of the integer " +
		                   "variable is %d, and the string " +
		                   "is %s", floatVar, intVar, stringVar);
		System.out.println(fs);

	}

}