#ifndef ANDROIDAPP_HPP_INCLUDED
#define ANDROIDAPP_HPP_INCLUDED

#include "application.hpp"

class AndroidApp : public Application{
    private:
        double minVersion;
        double targetVersion;
        static int androidCount;

    public:
        AndroidApp();
        AndroidApp(double, double, double);
        AndroidApp(const AndroidApp&);
        ~AndroidApp();

        friend ostream& operator<<(ostream&, const AndroidApp&);
        int getCount() const;
};

#endif // ANDROIDAPP_HPP_INCLUDED
