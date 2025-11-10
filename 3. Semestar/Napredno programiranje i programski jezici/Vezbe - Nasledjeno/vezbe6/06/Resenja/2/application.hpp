#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <iostream>
using namespace std;

#include "dinstring.hpp"

class Application{
    protected:
        DinString language;
        DinString author;
        double sizeMB;
        static int appCount;

    public:
        Application();
        Application(const char*, double);
        Application(const Application&);
        ~Application();

        friend ostream& operator<<(ostream&, const Application&);
        int getCount() const;
};

#endif // APPLICATION_HPP_INCLUDED
