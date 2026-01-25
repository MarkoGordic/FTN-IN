//OPIS: ugnjezdeni for
//RETURN: 60
int main(){
	int suma;
	int i;
	int p;
	suma = 0;
	for (i = 0; i < 5; i++) {
	    suma = suma + i;
	    for (p = 0; p < 5; p++)
	        suma = suma + i;
	}
	return suma;
}

