#ifndef ANDROIDAPP_HPP_INCLUDED
#define ANDROIDAPP_HPP_INCLUDED

class AndroidApp : public Application {
private:
    double minVersion;
    double targetVersion;
    static int androidCount;
public:
    AndroidApp () : Application("java", 150), minVersion(1.1), targetVersion(1.5) {
        androidCount++;
    }

    AndroidApp (double mv, double tv, double smb) : Application("java", smb), minVersion(mv), targetVersion(tv) {
        androidCount++;
    }

    AndroidApp (const AndroidApp& a) : Application(a), minVersion(a.minVersion), targetVersion(a.targetVersion) {
        androidCount++;
    }

    ~AndroidApp () {
        androidCount--;
    }

    int getCount() {
        return androidCount;
    }

    friend ostream& operator<<(ostream& out, const AndroidApp& a) {
        out << "\nAndroidApp" << endl;
        out << (Application)a << endl;  // pozvace operator ispisa iz roditeljske klase i ispisati polja
                                        // ili samo ispisati opet rucno :)
        out << "MinVersion: " << a.minVersion << endl;
        out << "TargetVersion: " << a.targetVersion << endl;
        out << endl;
        return out;
    }
};

// kod izrade statickog
// 1. static polje
// 2. inicijalizuj
// 3. povecaj u konstruktoru
// 4. smanji u destruktoru

int AndroidApp::androidCount = 0;

#endif // ANDROIDAPP_HPP_INCLUDED
