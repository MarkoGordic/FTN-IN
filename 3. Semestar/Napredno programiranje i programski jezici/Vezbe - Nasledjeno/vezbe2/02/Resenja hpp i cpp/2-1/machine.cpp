#include "machine.hpp"

// prazan konstruktor
Machine::Machine(){
    currentState = sC;
    value = MAX_VALUE;
}

bool Machine::metodaX(){
    bool success;

    if (currentState == sB || currentState == sC) {
        currentState = sA;
        success = true;
    } else {
        success = false;
    }

    return success;
}

bool Machine::metodaY(){
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

bool Machine::metodaZ(){
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

bool Machine::metodaW(){
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

bool Machine::plus(){
    bool success;

    if (currentState == sA && value + STEP_VALUE <= MAX_VALUE) {
        value += STEP_VALUE;
        success = true;
    } else {
        success = false;
    }

    return success;
}

bool Machine::minus(){
    bool success;

    if (currentState == sA && value - STEP_VALUE >= MIN_VALUE) {
        value -= STEP_VALUE;
        success = true;
    } else {
        success = false;
    }

    return success;
}

MachineState Machine::getCurrentState() const{
    return currentState;
}

int Machine::getValue() const{
    return value;
}
