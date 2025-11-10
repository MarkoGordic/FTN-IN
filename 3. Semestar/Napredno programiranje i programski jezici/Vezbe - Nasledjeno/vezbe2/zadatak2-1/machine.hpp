#ifndef MACHINE_HPP_INCLUDED
#define MACHINE_HPP_INCLUDED

#define MIN_VREDNOST 0
#define MAX_VREDNOST 80
#define KORAK 20

enum MachineState{sA, sB, sC, sD};

class Machine{
private:
    MachineState currentState;
    int value;
public:
    Machine();
    bool metodaX();
    bool metodaY();
    bool metodaZ();
    bool metodaW();
    bool plus();
    bool minus();
    MachineState getCurrentState() const;
    int getValue() const;
};

#endif // MACHINE_HPP_INCLUDED
