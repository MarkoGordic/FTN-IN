package primer1;

public class Test {

	public static void main(String[] args) {

		double a = 14.32712;

		double b = Math.round(a); // zaokruzivanje po matematickim pravilima
		double c = Math.ceil(a); // zaokruzivanje na prvi veci ceo broj
		double d = Math.floor(a); // zaokruzivanje na prvi manji ceo broj

		// zelimo da odsecemo sve cifre posle druge decimale
		a = a * 100;
		int e = (int) a;
		double f = (double) e / 100;

		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
		System.out.println(f);
	}

}
