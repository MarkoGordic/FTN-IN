package z31;

public class TeloA {
	
	private Pravougaonik p1, p2, p3;
	private Trougao t;

    public TeloA(double a, double b, double c, double d, double h)
    {
        p1 = new Pravougaonik(a, d);
        p2 = new Pravougaonik(p1.getObim(), h);
        p3 = new Pravougaonik(c + b, d);
        t = new Trougao(a, b, c);
    }

    public double getP()
    {
        return p1.getPovrsina() + p2.getPovrsina() + p3.getPovrsina() + 2 * t.getPovrsina();
    }

    public double getV()
    {
        return p1.getPovrsina() * p2.getB() + t.getPovrsina() * p1.getB();
    }

}
