#include "desktopApp.hpp"

int DesktopApp::desktopCount = 0;

DesktopApp::DesktopApp()
{
    desktopCount++;
}

DesktopApp::DesktopApp(const Computer& mc, const Computer& oc, const char* l, double s) : Application(l, s), minSysReq(mc), optimumSysReq(oc)
{
    desktopCount++;
}

DesktopApp::DesktopApp(const DesktopApp& d) : Application(d), minSysReq(d.minSysReq), optimumSysReq(d.optimumSysReq)
{
    desktopCount++;
}

DesktopApp::~DesktopApp()
{
    desktopCount--;
}

ostream& operator<<(ostream &out, const DesktopApp &a)
{
    out << "DESKTOP APPLICATION" << endl;
    out << (Application)a;

    out << "Minimum system requirements----------" << endl;
    out << a.minSysReq;

    out << "-------------------------------------" << endl;
    out << "Optimum system requirements----------" << endl;
    out << a.optimumSysReq;

    out << "-------------------------------------" << endl;
    return out;
}

int DesktopApp::getCount() const{
    return desktopCount;
}
