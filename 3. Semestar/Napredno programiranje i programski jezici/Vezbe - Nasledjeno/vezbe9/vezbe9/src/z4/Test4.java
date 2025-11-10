package z4;

public class Test4 {
	
	public static void IspisiFiguru(GeometrijskaFigura g) {
		System.out.println(g);
	}
	
	public static void main(String[] args) {
		Pravougaonik p1 = new Pravougaonik(3, 4);
		Krug k1 = new Krug(3);
		Kvadrat kv1 = new Kvadrat(3);
		
		IspisiFiguru(p1);
		IspisiFiguru(k1);
		IspisiFiguru(kv1);
	}

}
