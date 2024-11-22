#ifndef DESKTOPAPP_HPP_INCLUDED
#define DESKTOPAPP_HPP_INCLUDED

#include "Application.hpp"
#include "Computer.hpp"

class DesktopApp : public Application {
private:
    Computer minSysReq;
    Computer optimumSysReq;
    static int desktopCount;
public:
    DesktopApp() : Application("Java", 0), minSysReq(), optimumSysReq() { desktopCount++; }
    DesktopApp(const Computer& min, const Computer& opt, const char* name, double size) : Application(name, size), minSysReq(min), optimumSysReq(opt) { desktopCount++; }
    DesktopApp(const DesktopApp& d) : Application(d), minSysReq(d.minSysReq), optimumSysReq(d.optimumSysReq) { desktopCount++; }
    ~DesktopApp() { desktopCount--; }

    friend std::ostream& operator<<(std::ostream& out, const DesktopApp& d){
        out << (Application)d << ", MinSysReq: " << d.minSysReq << ", OptimumSysReq: " << d.optimumSysReq;
        return out;
    }

    static int getCount() { return desktopCount; }
};

int DesktopApp::desktopCount = 0;

#endif // DESKTOPAPP_HPP_INCLUDED