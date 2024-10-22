#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

enum ScreenStates {ssON, ssOFF};

class Screen {
private:
    ScreenStates state;
    int brightness;

public:
    Screen(){
        state = ssOFF;
        brightness = 0;
    }

    bool incB(){
        if(state == ssON && brightness + 2 <= 20){
            brightness+=2;
            return true;
        }

        return false;
    }

    bool decB(){
        if(state == ssON && brightness - 2 >= 0){
            brightness-=2;
            return true;
        }

        return false;
    }

    void setState(ScreenStates s){
        state = s;
    }

    ScreenStates getState()const{
        return state;
    }

    int getBrightness()const{
        return brightness;
    }
};

#endif // SCREEN_HPP_INCLUDED