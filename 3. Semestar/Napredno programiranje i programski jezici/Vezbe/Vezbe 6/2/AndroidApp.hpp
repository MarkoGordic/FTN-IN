#ifndef ANDROIDAPP_HPP_INCLUDED
#define ANDROIDAPP_HPP_INCLUDED

#include "Application.hpp"

class AndroidApp : public Application {
private:
    double minVersion;
    double targetVersion;
    static int androidCount;
public:
    AndroidApp() : Application("Java", 0), minVersion(0), targetVersion(0) { androidCount++; }
    AndroidApp(double min, double target, double size) : Application("Java", size), minVersion(min), targetVersion(target) { androidCount++; }
    AndroidApp(const AndroidApp& a) : Application(a), minVersion(a.minVersion), targetVersion(a.targetVersion) { androidCount++; }
    ~AndroidApp() { androidCount--; }

    friend std::ostream& operator<<(std::ostream& out, const AndroidApp& a){
        out << (Application)a << ", MinVersion: " << a.minVersion << ", TargetVersion: " << a.targetVersion;
        return out;
    }

    static int getCount() { return androidCount; }
};

int AndroidApp::androidCount = 0;

#endif // ANDROIDAPP_HPP_INCLUDED