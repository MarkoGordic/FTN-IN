#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

class Application {
protected:
    DinString language;
    double sizeMB;
    DinString author;
    static int appCount;
public:
    Application() : sizeMB(0) {
        appCount++;
    }

    Application(const char* lang, double mb) : language(lang), sizeMB(mb), author("firma") {
        appCount++;
    }

    Application(const Application& app)
        : language(app.language), sizeMB(app.sizeMB), author(app.author) {
        appCount++;
    }

    ~Application() {
        appCount--;
    }

    friend ostream& operator<<(ostream& out, const Application& app) {
        out << "Application" << endl;
        out << "Lanugage: " << app.language << endl;
        out << "Size: " << app.sizeMB << endl;
        out << "Author:" << app.author << endl;
        return out;
    }

    int getCount() const {
        return appCount;
    }
};

int Application::appCount = 0;

#endif // APPLICATION_HPP_INCLUDED
