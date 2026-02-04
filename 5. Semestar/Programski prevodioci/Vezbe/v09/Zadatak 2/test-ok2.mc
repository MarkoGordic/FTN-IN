//OPIS: switch sa break bez default
//RETURN: 1
int main() {
    int state;
    int x;
    state = 1;
    switch(state) {
	case 1: x = 1; break;
	case 2: { x = 5;} break;
    }
    return x;
}
