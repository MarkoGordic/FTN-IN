package z5;

public class Test5 {

	public static void main(String[] args) {
		Pravougaonik p1 = new Pravougaonik(3, 4);
		
		System.out.println(p1 + "\nP: " + p1.getP() + "\nO: " + p1.getO());
		p1.setA(5);
		p1.setB(6);
		System.out.println(p1 + "\nP: " + p1.getP() + "\nO: " + p1.getO());

		Krug k1 = new Krug(4);
		
		System.out.println(k1 + "\nP: " + k1.getP() + "\nO: " + k1.getO());
		k1.setR(5);
		System.out.println(k1 + "\nP: " + k1.getP() + "\nO: " + k1.getO());
		
		Kvadrat kv1 = new Kvadrat(5);
		System.out.println(kv1 + "\nP: " + kv1.getP() + "\nO: " + kv1.getO());
		p1.setA(5);
		p1.setB(6);
		System.out.println(kv1 + "\nP: " + kv1.getP() + "\nO: " + kv1.getO());
	}

}
