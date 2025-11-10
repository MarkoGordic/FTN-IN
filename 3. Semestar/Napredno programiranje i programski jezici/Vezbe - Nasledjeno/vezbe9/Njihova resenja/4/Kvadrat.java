package z1;

public class Kvadrat extends Pravougaonik {

	public Kvadrat(double a) {
		super(a, a);
	}
	
	@Override
	public void setA(double a) {
		super.setA(a);
		super.setB(a);
		}
	
	@Override
	public void setB(double b) {
		super.setA(b);
		super.setB(b);
	}
	
	@Override
	public String toString() {
		return "Kvadrat (a = " + a + ")";
	}
}
