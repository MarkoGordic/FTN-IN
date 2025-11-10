#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#define BRIGHTNESS_STEP 2
#define BRIGHTNESS_MAX 20
#define BRIGHTNESS_MIN 0

enum ScreenStates { ssON, ssOFF};

class Screen{
private:
    ScreenStates state;
    int brightness;
public:

    Screen(){
        state = ssOFF;
        brightness = BRIGHTNESS_MIN;
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

    bool incB(){
        if (state == ssON && brightness + BRIGHTNESS_STEP <= BRIGHTNESS_MAX){

            brightness += BRIGHTNESS_STEP;
            return true;
        }
        return false;
    }

    bool decB(){
        if (state == ssON && brightness - BRIGHTNESS_STEP >= BRIGHTNESS_MIN){
            brightness -= BRIGHTNESS_STEP;
            return true;
        }
        return false;
    }


};


#endif // SCREEN_HPP_INCLUDED
