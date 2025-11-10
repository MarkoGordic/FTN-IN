#include "machine.hpp"
Machine::Machine(){
    currentState = sC;
    value = MAX_VREDNOST;
}

bool Machine::metodaX(){
    bool success;
    if (currentState == sC || currentState == sB){
        currentState = sA;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Machine::metodaY(){
    bool success;
    if (currentState == sD || currentState == sB){
        currentState = sC;
        value = MAX_VREDNOST;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Machine::metodaZ(){
    bool success;
    if (currentState == sA){
        currentState = sB;
        value = MIN_VREDNOST;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Machine::metodaW(){
    bool success;
    if (currentState == sA){
        currentState = sD;
        value = MIN_VREDNOST;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Machine::plus(){
    bool success;
    if (currentState == sA && value + KORAK <= MAX_VREDNOST){
        value += KORAK;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Machine::minus(){
    bool success;
    if (currentState == sA && value - KORAK >= MIN_VREDNOST){
        value -= KORAK;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

MachineState Machine::getCurrentState() const {
    return currentState;
}

int Machine::getValue() const {
    return value;
}
