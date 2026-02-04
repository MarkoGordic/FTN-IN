//OPIS: switch bez break i bez default
//RETURN: 5
int main() {
    int state;
    int x;
    state = 2;
    switch(state) {
	case 1: x = 1; 
	case 2: { x = 5;} 
    }
    
    return x;
}
