#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include "dinstring.hpp"

class Application {
protected:
    DinString language;
    double sizeMB;
    DinString author;
    static int appCount;

public:
    Application() : language(""), sizeMB(0), author("") { appCount++; }
    Application(const char* lang, double size) : language(lang), sizeMB(size), author("Bananiranje NS") { appCount++; }
    Application(const Application& a) : language(a.language), sizeMB(a.sizeMB), author(a.author) { appCount++; }
    ~Application() { appCount--; }

    friend std::ostream& operator<<(std::ostream& out, const Application& a){
        out << "Language: " << a.language << ", Size: " << a.sizeMB << "MB, Author: " << a.author;
        return out;
    }

    static int getCount() { return appCount; }
};

int Application::appCount = 0;

#endif // APPLICATION_HPP_INCLUDED