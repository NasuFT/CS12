#include <iostream>
#include <string>
#include <vector>

using namespace std;

int GetYear(string str) {
    return stoi(str.substr(0, 4));
}

int GetStudentNumber(string str) {
    return stoi(str.substr(5, 5));
}

string GetName(string str) {
    return str.substr(12);
}

bool IsBatchMates(string str1, string str2) {
    int year_1 = GetYear(str1);
    int year_2 = GetYear(str2);

    if(year_1 != year_2) return false;

    string name_1 = GetName(str1);
    string name_2 = GetName(str2);

    if(name_1 > name_2) return false;

    return true;
}

bool Passed(string passers[], const char *name, int total) {
    for(int i = 0; i < total; i++) {
        if(passers[i].find(name) != string::npos) {
            return true;
        }
    }

    return false;
}

int GetIndex(string passers[], int total, const char *name) {
    for(int i = 0; i < total; i++) {
        if(passers[i].find(name) != string::npos) {
            return i;
        }
    }

    return -1;
}

int GetBatchStart(string passers[], int total, const char *name) {
    int index = GetIndex(passers, total, name);

    if(index - 1 >= 0) { 
        while(IsBatchMates(passers[index - 1], passers[index])) {
            index--;

            if(index - 1 < 0) break;
        }
    }

    return index;
}

int GetBatchEnd(string passers[], int total, const char *name) {
    int index = GetIndex(passers, total, name);

    if(index + 1 < total) {
        while(IsBatchMates(passers[index], passers[index + 1])) {
            index++;

            if(index + 1 >= total) break;
        }
    }

    return index;
}

int GetNumberBatchMates(string passers[], int batch_start, int batch_end) {
    int number_start = GetStudentNumber(passers[batch_start]);
    int number_end = GetStudentNumber(passers[batch_end]);

    return number_end - number_start + 1;
}

vector<string> GetPassers(string passers[], int batch_start, int batch_end) {
    vector<string> passed;

    for(int i = batch_start; i <= batch_end; i++) {
        passed.push_back(passers[i]);
    }

    return passed;
}

void wilson(string passers[], int total, const char *name, int namelen) {
    if(!Passed(passers, name, total)) cout << "0 / 0" << "\n";
    else {
        int batch_start = GetBatchStart(passers, total, name);
        int batch_end = GetBatchEnd(passers, total, name);

        int total_batch_mates = GetNumberBatchMates(passers, batch_start, batch_end);
        vector<string> batch_passers = GetPassers(passers, batch_start, batch_end);
        int failed = total_batch_mates - batch_passers.size();
        
        cout << failed << " / " << total_batch_mates << "\n";

        for(int i = 0; i < batch_passers.size(); i++) {
            cout << batch_passers[i] << "\n";
        }
    }
}

int main() {
    string passers[]{
        "2010-07933, COSETO, KEN ALEXANDRE CHUA",
        "2010-07951, SU, XAVIER FRANCIS WEE SIT",
        "2010-07960, BORROMEO, VITO MIKAEL CHUA",
        "2010-07964, COHERCO, WAYNE YU",
        "2010-07965, DESCALLAR, MICHAEL KEVIN DE CASTRO",
        "2010-07966, GO, NATHAN OLIVER SYQUIATCO",
        "2010-07967, KU, RAPHAEL LESMOND CHENG",
        "2010-07968, LAGMAN, ALBERT SALAO",
        "2010-07971, LEE, CARL JUSTIN CO",
        "2010-07973, LEE, WESTON COLEMAN CO",
        "2010-07974, LIM, CHARLES STEPHEN TAN",
        "2010-07975, LIM, KYNE DERRICK WONG",
        "2010-07976, MARCELO, LUIS ALBERTO CARRANCEJA",
        "2010-07977, NG, DUSTIN YU",
        "2010-07978, OCAMPO-TAN, KENRICK SIMON COYIUTO",
        "2010-07979, ONG, JONATHAN GERALD CABO CHANPONGCO",
        "2010-07982, SEE, KARL GERRARD TIU",
        "2010-07985, SIY, MICHAEL DOMINIC ONG",
        "2010-07986, TAN, DAVID CO",
        "2010-07987, TAN, JULIUS EDWARD LIM",
        "2010-07991, YAPTINCHAY, CARLOS GABRIEL ROXAS",
        "2010-07992, YU, HUXLEY COO",
        "2010-07996, CANCIO, NICHOLAS AGUSTIN CHUA"
    };

    int total{23};
    const char name[]{"COSETO"};
    int namelen{13};

    wilson(passers, total, name, namelen);

    return 0;
}