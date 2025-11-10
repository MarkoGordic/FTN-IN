package z5;

public class Krug implements GeometrijskaFigura {
	private double r;

	public double getR() {
		return r;
	}

	public void setR(double r) {
		this.r = r;
	}

	public Krug(double r) {
		super();
		this.r = r;
	}
	
	@Override
	public double getP() {
		return Math.pow(r, 2) * Math.PI;
	}

	@Override
	public double getO() {
		return 2 * Math.PI * r;
	}
	
	@Override
	public String toString() {
		return "Krug: r = " + r;
	}

}
