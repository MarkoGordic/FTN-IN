package z5;

//default paket mozemo koristiti ako obrisemo module.info
//ipak po konvenciji bi trebalo sve u nove pakete :)

public interface GeometrijskaFigura {
	public abstract double getP();
	public abstract double getO();
	
	// u interfejsu mozemo samo final polja da koristimo pored metoda, to su konstante
	// dok apstraktna klasa moze imati i normalna polja, pored metoda
	// moze se naslediti samo 1 klasa i beskonacno mnogo interfejsa
}
