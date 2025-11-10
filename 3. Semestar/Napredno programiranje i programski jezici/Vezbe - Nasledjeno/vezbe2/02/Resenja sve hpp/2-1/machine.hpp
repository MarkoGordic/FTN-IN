#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

#include <iostream>
using namespace std;

#define MAX_VALUE 80
#define MIN_VALUE 0
#define STEP_VALUE 20

enum MachineState {sA, sB, sC, sD};

class Machine {
    private:
        MachineState currentState;
        int value;
    public:
        Machine() {
            currentState = sC;
            value = MAX_VALUE;
        }

        bool metodaX() {
            bool success;

            if (currentState == sB || currentState == sC) {
                currentState = sA;
                success = true;
            } else {
                success = false;
            }

            return success;
        }

        bool metodaY() {
            bool success;

            if (currentState == sB || currentState == sD) {
                currentState = sC;
                value = MAX_VALUE;
                success = true;
            } else {
                success = false;
            }

            return success;
        }

        bool metodaZ() {
            bool success;

            if (currentState == sA) {
                currentState = sB;
                value = MIN_VALUE;
                success = true;
            } else {
                success = false;
            }

            return success;
        }

        bool metodaW() {
            bool success;

            if (currentState == sA) {
                currentState = sD;
                value = MIN_VALUE;
                success = true;
            } else {
                success = false;
            }

            return success;
        }

        bool plus() {
            bool success;

            if (currentState == sA && value + STEP_VALUE <= MAX_VALUE) {
                value += STEP_VALUE;
                success = true;
            } else {
                success = false;
            }

            return success;
        }

        bool minus() {
            bool success;

            if (currentState == sA && value - STEP_VALUE >= MIN_VALUE) {
                value -= STEP_VALUE;
                success = true;
            } else {
                success = false;
            }

            return success;
        }

        MachineState getCurrentState() const { return currentState; }
        int getValue() const { return value; }
};

#endif // MACHINE_H_INCLUDED
