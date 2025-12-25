//OPIS: GRESKA - redefinicija konstante (ista konstanta 2 puta)

int main(){
	const int MAX = 100;
	const int MAX = 200;
	int a;
	a = MAX;
	return a;
}
