#ifndef DESKTOPAPP_HPP_INCLUDED
#define DESKTOPAPP_HPP_INCLUDED

#include "application.hpp"
#include "computer.hpp"

class DesktopApp : public Application{
    private:
        Computer minSysReq;
        Computer optimumSysReq;
        static int desktopCount;

    public:
        DesktopApp();
        DesktopApp(const Computer&, const Computer&, const char*, double);
        DesktopApp(const DesktopApp&);
        ~DesktopApp();

        friend ostream& operator<<(ostream&, const DesktopApp&);
        int getCount() const;
};

#endif // DESKTOPAPP_HPP_INCLUDED
