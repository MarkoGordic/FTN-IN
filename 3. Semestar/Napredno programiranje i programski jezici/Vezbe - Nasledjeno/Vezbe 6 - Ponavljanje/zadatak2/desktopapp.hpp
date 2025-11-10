#ifndef DESKTOPAPP_HPP_INCLUDED
#define DESKTOPAPP_HPP_INCLUDED

class DesktopApp : public Application {
private:
    Computer minSysReg, optimumSysReg;
    static int desktopCount;
public:
    DesktopApp() : Application("Java", 0) {
        desktopCount++;
    }

    DesktopApp(const Computer& c1, const Computer& c2, const char* l, double sizem)
        : Application(l, sizem), minSysReg(c1), optimumSysReg(c2) {
            desktopCount++;
    }

    DesktopApp(const DesktopApp& d)
        : Application(d), minSysReg(d.minSysReg), optimumSysReg(d.optimumSysReg) {
            desktopCount++;
    }

    ~DesktopApp() {
        desktopCount--;
    }

    friend ostream& operator<<(ostream& out, const DesktopApp& d) {
        out << "DesktopApp" << endl;
        out << (Application)d << endl;
        out << "Min Sys Reg: " << d.minSysReg << endl;
        out << "Optimum Sys Reg: " << d.optimumSysReg << endl;
        return out;
    }

    int getCount() const {
        return desktopCount;
    }
};

int DesktopApp::desktopCount = 0;

#endif // DESKTOPAPP_HPP_INCLUDED
