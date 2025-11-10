package z5_1;

public class Test5_1 {

	public static void main(String[] args) {
		TeloA ta = new TeloA(2, 2, 2, 1, 1);
		System.out.println("TeloA ta");
		System.out.println(ta);
		System.out.println("P: " + ta.getP());
		System.out.println("V: " + ta.getV());
		
		TeloB tb = new TeloB(2);
		System.out.println("TeloB tb");
		System.out.println(tb);
		System.out.println("P: " + tb.getP());
		System.out.println("V: " + tb.getV());
	}

}
