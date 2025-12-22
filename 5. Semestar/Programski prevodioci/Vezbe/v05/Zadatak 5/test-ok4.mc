//OPIS: switch bez break i bez default
void main() {
    int state;
    int x;
    state = 5;
    switch(state) {
	case 1: x = 1; 
	case 2: { x = 5;} 
    }
}
