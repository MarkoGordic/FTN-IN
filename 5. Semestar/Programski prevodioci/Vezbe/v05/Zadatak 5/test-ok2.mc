//OPIS: switch sa break bez default
void main() {
    int state;
    int x;
    state = 5;
    switch(state) {
	case 1: x = 1; break;
	case 2: { x = 5;} break;
    }
}
