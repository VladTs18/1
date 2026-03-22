#include "worker.hpp"

using namespace std;

int main() {
    int choice;
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Додати працівника\n";
        cout << "2. Переглянути працівників\n";
        cout << "3. Видалити працівника за номером\n";
        cout << "4. Видалити працівника за іменем\n";
        cout << "5. Вихід\n";
        cout << "Оберіть опцію: ";
        
        if (!(cin >> choice)) {
            cerr << "Помилка: введіть число!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore();
        
        switch (choice) {
            case 1:
                addWorker();
                break;
            case 2:
                showWorkers();
                break;
            case 3: {
                int index;
                cout << "Введіть номер працівника для видалення: ";
                if (!(cin >> index) || index < 1) {
                    cerr << "Помилка: введіть правильний номер!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
                deleteWorkerByIndex(index);
                break;
            }
            case 4: {
                string name;
                cout << "Введіть прізвище для видалення: ";
                cin >> name;
                deleteWorkerByName(name);
                break;
            }
            case 5:
                return 0;
            default:
                cerr << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    }
}

