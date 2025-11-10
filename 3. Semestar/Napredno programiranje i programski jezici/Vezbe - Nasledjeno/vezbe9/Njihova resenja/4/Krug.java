package z1;

public class Krug extends GeometrijskaFigura {
	
	protected double r;
	
	public Krug(double r) {
		this.r = r;
	}
	
	public double getR() {
		return r;
	}
	public void setR(double r) {
		this.r = r;
	}
	
	@Override
	public String toString() {
		return "Krug (r = " + r + ")";
	}
	
	//klasa Math sadrzi matematicke funkcije i konstante
	@Override
	public double getObim() {
		return 2 * r * Math.PI;
	}

	//funkcija pow dize r na stepen 2
	@Override
	public double getPovrsina() {
		return Math.pow(r, 2) * Math.PI;
	}

	

}
