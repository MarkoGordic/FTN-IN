#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#define MAX_BRIGHTNESS 20
#define MIN_BRIGHTNESS 0
#define STEP_BRIGHTNESS 2

enum ScreenStates {ssOFF, ssON};

class Screen {
private:
    ScreenStates state;
    int brightness;
public:
    Screen(){
        state = ssOFF;
        brightness = MIN_BRIGHTNESS;
    }

    bool incB(){
        if (brightness + STEP_BRIGHTNESS <= MAX_BRIGHTNESS && state == ssON){
            brightness += STEP_BRIGHTNESS;
            return true;
        }
        return false;
    }

    bool decB() {
        if (brightness - STEP_BRIGHTNESS >= MIN_BRIGHTNESS && state == ssON){
            brightness -= STEP_BRIGHTNESS;
            return true;
        }
        return false;
    }

    void setState(ScreenStates ss){
        state = ss;
    }

    ScreenStates getState() const {
        return state;
    }

    int getBrightness() const {
        return brightness;
    }
};

#endif // SCREEN_HPP_INCLUDED
