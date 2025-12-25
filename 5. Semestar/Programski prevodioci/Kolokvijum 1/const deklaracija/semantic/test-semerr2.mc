//OPIS: GRESKA - tip vrednosti ne odgovara (int ocekuje int, dobija uint)

int main(){
	const int MAX = 100u;
	int a;
	a = MAX;
	return a;
}
