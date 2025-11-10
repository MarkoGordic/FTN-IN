package z3;

public interface GeometrijskaFigura {
	
	//apstraktna metoda
	//nema telo i ima rezervisanu rec abstract
	//ali se kod interfejsa ne mora pisati jer su sve metode u interfejsu apstraktne
	//u javi je svaka metoda virtualna (ne treba dodatno pisati)
	public double getObim();
	public double getPovrsina();

}
