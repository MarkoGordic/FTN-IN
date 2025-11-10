#ifndef ANDROIDAPP_HPP_INCLUDED
#define ANDROIDAPP_HPP_INCLUDED

class AndroidApp : public Application {
private:
    double minVersion, targetVersion;
    static int androidCount;
public:
    AndroidApp() : Application("Java", 0) {
        androidCount++;
    }

    AndroidApp(double m, double t, double mb) : Application("Java", mb), minVersion(m), targetVersion(t) {
        androidCount++;
    }

    AndroidApp(const AndroidApp& aa) : Application(aa), minVersion(aa.minVersion), targetVersion(aa.targetVersion) {
        androidCount++;
    }

    ~AndroidApp() {
        androidCount--;
    }

    friend ostream& operator<<(ostream& out, const AndroidApp& d) {
        out << "AndroidApp" << endl;
        out << "min version: " << d.minVersion << endl;
        out << "target version: " << d.targetVersion << endl;
        return out;
    }

    int getCount() const {
        return desktopCount;
    }
};

int AndroidApp::androidCount = 0;

#endif // ANDROIDAPP_HPP_INCLUDED
