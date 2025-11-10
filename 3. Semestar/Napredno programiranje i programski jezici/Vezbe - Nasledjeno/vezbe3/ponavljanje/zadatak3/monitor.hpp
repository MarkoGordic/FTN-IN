#ifndef MONITOR_HPP_INCLUDED
#define MONITOR_HPP_INCLUDED

enum MonitorStates {sON, sOFF, sOUT, sTEST, sSTANDBY};

class Monitor {
private:
    MonitorStates state;
    Screen screen;
public:
    Monitor () : screen () {
        state = sOFF;
    }

    bool turnOn () {
        if (state == sOFF || state == sTEST || state == sSTANDBY) {
            screen.setState(ssON);
            state = sON;
            return true;
        }
        return false;
    }

    bool turnOff () {
        if (state == sON || state == sTEST || state == sSTANDBY) {
            screen.setState(ssOFF);
            state = sOFF;
            return true;
        }
        return false;
    }

    bool turnOut () {
        if (state != sOUT) {
            screen.setState(ssOFF);
            state = sOUT;
            return true;
        }
        return false;
    }

    bool turnTest () {
        if (state == sON) {
            screen.setState(ssON);
            state = sTEST;
            return true;
        }
        return false;
    }

    bool turnStandBy () {
        if (state == sON) {
            screen.setState(ssOFF);
            state = sSTANDBY;
            return true;
        }
        return false;
    }

    bool repair () {
        if (state == sOUT) {
            screen.setState(ssOFF);
            state = sOFF;
            return true;
        }
        return false;
    }

    bool incB () {
        if (state == sON || state == sTEST){
            return screen.incB();
        }
        return false;
    }

    bool decB () {
        if (state == sON || state == sTEST){
            return screen.decB();
        }
        return false;
    }

    MonitorStates getMonitorState () const {
        return state;
    }

    ScreenStates getScreenState () const {
        return screen.getState();
    }

    int getBrightness () const {
        return screen.getBrightness();
    }

    friend void printInfo (const Monitor& m);
};

#endif // MONITOR_HPP_INCLUDED
