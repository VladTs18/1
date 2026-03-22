//
//  worker.cpp
//  lab 9 zavd 2
//
//  Created by USER on 15.03.2025.
//

#include "worker.hpp"


using namespace std;

const char fname[] = "workers.txt";

void addWorker() {
    FILE* file = fopen(fname, "ab");
    if (!file) {
        cerr << "Помилка відкриття файлу!" << endl;
        return;
    }
    Worker w;
    cout << "Прізвище: "; cin >> w.Name;
    cout << "Посада: "; cin >> w.Pos;
    
    cout << "Рік прийняття: ";
    while (!(cin >> w.Year) || w.Year < 1900 || w.Year > 2100) {
        cerr << "Неправильний рік! Введіть ще раз: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Місяць прийняття: ";
    while (!(cin >> w.Month) || w.Month < 1 || w.Month > 12) {
        cerr << "Неправильний місяць! Введіть ще раз: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    fwrite(&w, sizeof(Worker), 1, file);
    fclose(file);
}

int calculateExperience(int year, int month) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    int currentMonth = 1 + ltm->tm_mon;
    return (currentYear - year) * 12 + (currentMonth - month);
}

void showWorkers() {
    FILE* file = fopen(fname, "rb");
    if (!file) {
        cerr << "Файл не знайдено або ще не створений." << endl;
        return;
    }
    Worker w;
    cout << left << setw(5) << "№" << setw(20) << "Прізвище" << setw(20) << "Посада"
         << setw(10) << "Рік" << setw(10) << "Місяць" << setw(10) << "Стаж (міс)" << endl;
    cout << string(70, '-') << endl;
    int index = 1;
    bool found = false;
    while (fread(&w, sizeof(Worker), 1, file)) {
        found = true;
        cout << left << setw(5) << index++ << setw(20) << w.Name
             << setw(20) << w.Pos << setw(10) << w.Year << setw(10) << w.Month
             << setw(10) << calculateExperience(w.Year, w.Month) << endl;
    }
    if (!found) {
        cout << "Файл порожній." << endl;
    }
    fclose(file);
}

void deleteWorkerByIndex(int index) {
    FILE* file = fopen(fname, "rb");
    if (!file) {
        cerr << "Файл не знайдено." << endl;
        return;
    }
    FILE* temp = fopen("temp.txt", "wb");
    if (!temp) {
        cerr << "Помилка створення тимчасового файлу!" << endl;
        fclose(file);
        return;
    }
    
    Worker w;
    int currentIndex = 1;
    bool deleted = false;

    while (fread(&w, sizeof(Worker), 1, file)) {
        if (currentIndex++ != index) {
            fwrite(&w, sizeof(Worker), 1, temp);
        } else {
            deleted = true;
        }
    }

    fclose(file);
    fclose(temp);
    remove(fname);
    rename("temp.txt", fname);

    if (!deleted) {
        cerr << "Помилка: індекс виходить за межі списку!" << endl;
    } else {
        cout << "Працівника видалено." << endl;
    }
}

void deleteWorkerByName(const string& name) {
    FILE* file = fopen(fname, "rb");
    if (!file) {
        cerr << "Файл не знайдено." << endl;
        return;
    }
    FILE* temp = fopen("temp.txt", "wb");
    if (!temp) {
        cerr << "Помилка створення тимчасового файлу!" << endl;
        fclose(file);
        return;
    }

    Worker w;
    bool deleted = false;

    while (fread(&w, sizeof(Worker), 1, file)) {
        if (name != w.Name) {
            fwrite(&w, sizeof(Worker), 1, temp);
        } else {
            deleted = true;
        }
    }

    fclose(file);
    fclose(temp);
    remove(fname);
    rename("temp.txt", fname);

    if (!deleted) {
        cerr << "Працівник із таким ім'ям не знайдений!" << endl;
    } else {
        cout << "Працівника видалено." << endl;
    }
}
