// KnightsOfTable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
/*За круглым столом короля Артура сидят 12 рыцарей. Из них каждый враждует с двумя своими
соседями. Для участия в спецоперации по освобождению заколдованной принцессы нужно
выбрать 5 рыцарей, но при этом нельзя посылать вместе рыцарей, враждующих друг с другом.
Выборы проходят так: рыцари поднимают руки, чтобы вызваться, если соседи еще не вызвались.
Помогите выбрать рыцарей в поход.*/
using namespace std;

//Общее кол-во рыцарей и ко-во для похода
const int numberKnightsTable = 12;
const int numberMarchingKnights = 5;

//Функция поиска рыцарей
void findTeamForHike(int numberKnightsTable, int numThreads);
//Функция выборки 5ти рыцарей
void selectionKnights(int startId, int loadThread);
int main()
{
    // Выбор кол-ва потоков
    int numThreads;
    string numThreadsNoNumber;
        do {
            do {
                try {
                    cout << "Enter the number of threads : divisor " << numberKnightsTable << endl;
                    cin >> numThreadsNoNumber;
                    cout << endl;
                    numThreads = stoi(numThreadsNoNumber);
                }
            catch (...) {
                cout << endl << "Error" << endl;
                return(0);
            }
            } while (numThreads == 0);
        } while (12 % numThreads != 0);
    
   
    
    //Функция поиска рыцарей
    findTeamForHike(numberKnightsTable, numThreads);
}

//Описание функции поиска рыцарей
void findTeamForHike(int numberKnightsTable, int numThreads) {
    //Количество "обрабатываемых" рыцарей в одном потоке
    int loadThread = numberKnightsTable / numThreads;
    //вектор потоков
    vector<thread> threads;
    //Начальный номер рыцаря для каждого потока
    int startId;
    for (int i = 0; i < numThreads; i++) {
        startId = i * loadThread;
        //Добавление потока 
        threads.emplace_back(selectionKnights, startId, loadThread);
    }
    //Запуск потоков
    for (auto& thread : threads) {
        thread.join();
    }
}

//Описание функции выборки 5ти рыцарей
void selectionKnights(int startId, int loadThread) {
    string streamOfThread = "";
    cout << endl << "New Thread" << endl;
    for (int i = startId; i < startId + loadThread; i++) {
        for (int j = i + 1; j < numberKnightsTable - 3; j++)
            for (int k = j + 1; k < numberKnightsTable - 2; k++)
                for (int z = k + 1; z < numberKnightsTable - 1; z++)
                    for (int l = z + 1; l < numberKnightsTable; l++) {
                        if (abs(i - j) > 1 && abs(k - j) > 1 && abs(k - z) > 1 && abs(z - l) > 1 && abs(i - l) != 11) {
 //                           cout << i << ' ' << j << ' ' << k << ' ' << z << ' ' << l << endl;
                            streamOfThread += to_string(i) + ' ' + to_string(j) + ' ' + to_string(k) + ' ' + to_string(z) + ' ' + to_string(l) + '\n';
                        }
                    }

    }
    cout << streamOfThread;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
