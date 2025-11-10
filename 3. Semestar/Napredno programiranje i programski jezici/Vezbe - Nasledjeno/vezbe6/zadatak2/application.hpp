#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

class Application {
protected:
    DinString language;
    double sizeMB;
    DinString author;
    static int appCount;
public:
    Application () : language("c++"), sizeMB(3), author("nenad") {
        appCount++;
    }

    Application (const char lang[], double sMB) : language(lang) , sizeMB(sMB), author("nenad") {
        appCount++;
    }

    Application (const Application& a) : language(a.language), sizeMB(a.sizeMB), author(a.author) {
        appCount++;
    }

    int getCount () {
        return appCount;
    }

    friend ostream& operator<<(ostream& out, const Application &a) {
        out << "\nApplication" << endl;
        out << "Language: " << a.language << endl;
        out << "SizeMB: " << a.sizeMB << endl;
        out << "Author: " << a.author << endl;
        out << endl;
        return out;
    }

    ~Application () {
        appCount--;
    }
};

int Application::appCount = 0;

#endif // APPLICATION_HPP_INCLUDED
