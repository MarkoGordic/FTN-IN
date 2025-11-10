#include "application.hpp"

int Application::appCount = 0;

Application::Application():language("C++"), author("\"Zdrav Razum\" doo")
{
    sizeMB = 200;
    appCount++;
}

Application::Application(const char* l, double s):language(l), author("\"Zdrav Razum\" doo")
{
    sizeMB = s;
    appCount++;
}

Application::Application(const Application &a):language(a.language), author(a.author)
{
    sizeMB = a.sizeMB;
    appCount++;
}

Application::~Application(){
    appCount--;
}

ostream& operator<<(ostream &out, const Application &a)
{
    out << "Language: " << a.language << endl;
    out << "Author: " << a.author << endl;
    out << "Size [MB]: " << a.sizeMB << endl;
    return out;
}

int Application::getCount() const{
    return appCount;
}
