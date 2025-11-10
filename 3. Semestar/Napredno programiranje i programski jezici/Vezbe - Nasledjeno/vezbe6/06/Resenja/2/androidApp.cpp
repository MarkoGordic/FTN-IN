#include "androidApp.hpp"

int AndroidApp::androidCount = 0;

AndroidApp::AndroidApp() : Application("Java", 5)
{
    minVersion = 12;
    targetVersion = 20;
    androidCount++;
}

AndroidApp::AndroidApp(double m, double t, double s) : Application("Java", s)
{
    minVersion = m;
    targetVersion = t;
    androidCount++;
}

AndroidApp::AndroidApp(const AndroidApp& a) : Application(a)
{
    minVersion = a.minVersion;
    targetVersion = a.targetVersion;
    androidCount++;
}

AndroidApp::~AndroidApp()
{
    androidCount--;
}

ostream& operator<<(ostream &out, const AndroidApp &a)
{
    out << "ANDROID APPLICATION" << endl;
    out << (Application)a;
    out << "Minimum SDK version: " << a.minVersion << endl;
    out << "Target SDK version: " << a.targetVersion << endl;
    return out;
}

int AndroidApp::getCount() const{
    return androidCount;
}
