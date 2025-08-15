/**
 * Napisati C++ program koji cita podatke o studentima iz ulazne datoteke i potom 
 * za svakog studenta racuna prosek
 * 
 * U ulaznoj datoteci "studenti.csv" se u svakom redu nalaze informacije o studentu: 
 *     Ime,Prezime,Broj indeksa,Ocene 
 * Pritom su ocene odvojene medjusobno zarezima.
 * 
 * Prilikom obrade podataka o studentima, mora se proveriti format indeksa da li je validan. Ako nije, zanemariti taj unos.
 * Format indeksa je:
 *     [[:alpha:]][[:alnum:]]{1,2}\s[[:digit:]]{1,3}\/[[:digit:]]{4}
 * 
 * U tri izlazne datoteke rasporediti studente u zavisnosti od proseka.
 * Ukoliko je prosek > 9.00 potrebno je upisati studenta u datoteku "kandidati_stipendija.csv".
 * Ukoliko je prosek > 8.00 i prosek <= 9.00 potrebno je upisati studenta u datoteku "kandidati_kredit.csv".
 * U ostalim slucajevima upisati studenta u datoteku "ostali.csv".
 * Format u izlaznoj datoteci treba da odgovara sledecem: Ime,Prezime,Broj_indeksa,prosek
 * 
 * Treba napraviti jednu nit koja ce samo citati redove ulazne podatke, jednu nit 
 * koja ce samo pisati gotove podatke u izlazne datoteke i 10 niti radnika koji ce na osnovu redova
 * iz ulazne datoteke generisati sve neophodno za ispis u izlaznu datoteku.
*/

using namespace std;

class Student {
private:
public:
};

template<typename T>
class InputData {
private:
    mutex data_mtx;
    // TODO dodati polja po potrebi
public:
    InputData(): end(false) {
        // TODO
    }
    void add_data(T data_element) {
        // TODO
    }
    bool remove_data(T &data_element) {
        // TODO
        return false;
    }

    // TODO dodati metode po potrebi

};

template<typename T>
class OutputData {
private:
    mutex data_mtx;
    // TODO dodati polja po potrebi
public:
    OutputData(): end(false), data_producers_num(0) {}
    void add_data(T data_element) {
    }
    bool remove_data(T &data_element) {
        return false;
    }

    bool the_end() {
        return data.empty() && end;
    }

    // TODO dodati metode po potrebi
    
};

void reader(string input_file_name, InputData<string>& raw_data) {
    // TODO
}

void proccessing_data(InputData<string>& raw_data, OutputData<Student>& proccessed_data){
    // TODO
}

void writer(OutputData<Student>& proccessed_data) {
    // TODO
}


int main() {
    InputData<string> raw_data;
    OutputData<Student> proccessed_data;

    thread th_reader(reader, "studenti.csv", ref(raw_data));
    thread th_writer(writer, ref(proccessed_data));
    thread th_workers[10];

    for(auto &th: th_workers){
        th = thread(proccessing_data, ref(raw_data), ref(proccessed_data));
    }

    th_reader.join();
    for(auto &th: th_workers) {
        th.join();
    }
    th_writer.join();
    
    return 0;
}