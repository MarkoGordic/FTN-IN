#ifndef MAHCINE_HPP_INCLUDED
#define MAHCINE_HPP_INCLUDED

enum MachineState {
    sA,
    sB,
    sC,
    sD
};

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

    MachineState getCurrentState()const;
    int getValue()const;
};

#endif // MAHCINE_HPP_INCLUDED