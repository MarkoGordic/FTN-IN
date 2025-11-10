#ifndef DESKTOPAPP_HPP_INCLUDED
#define DESKTOPAPP_HPP_INCLUDED

class DesktopApp : public Application {
private:
    Computer minSysReg;
    Computer optimumSysReg;
    static int desktopCount;
public:
    DesktopApp () : Application("Java", 50), minSysReg(), optimumSysReg() { // minsys i optimumsys se po defaultu pozivaju ako postoje ali mogu i ovako
        desktopCount++;
    }

    DesktopApp (const Computer& msr, const Computer& osr, const char l[], double s) : Application(l, s), minSysReg(msr), optimumSysReg(osr) {
        desktopCount++;
    }

    DesktopApp (const DesktopApp& d) : Application(d), minSysReg(d.minSysReg), optimumSysReg(d.optimumSysReg) {
        desktopCount++;
    }

    friend ostream& operator<<(ostream& out, const DesktopApp& a) {
        out << "\nDesktopApp" << endl;
        out << (Application)a << endl;  // pozvace operator ispisa iz roditeljske klase i ispisati polja
                                        // ili samo ispisati opet rucno :)
        out << "min sys reg: " << a.minSysReg << endl;
        out << "optimum sys reg: " << a.optimumSysReg << endl;
        out << endl;
        return out;
    }

    int getCount () {
        return desktopCount;
    }

    ~DesktopApp () {
        desktopCount--;
    }
};

int DesktopApp::desktopCount = 0;

#endif // DESKTOPAPP_HPP_INCLUDED
