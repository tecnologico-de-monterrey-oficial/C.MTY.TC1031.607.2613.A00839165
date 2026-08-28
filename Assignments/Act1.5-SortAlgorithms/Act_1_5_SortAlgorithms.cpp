//Julio Eduardo Rodriguez Ruiz A00839165

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void swapsort (vector <T> &list){

int n = list.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (list[j] < list[i]) {
                swap(list[i], list[j]);
            }
        }
    }
}

template <typename T>
void bubbleSort(vector<T> &list) {
    int n = list.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (list[j] > list[j + 1]) {
                swap(list[j], list[j + 1]);
            }
        }
    }
}

int main() {
    vector<int> datos = {2, 12, 3, 43, 1};
    vector<int> datos2 = {2, 12, 3, 43, 1};


    cout << "Original: ";
    for (int x : datos) cout << x << " ";
    cout << "\n";

    swapsort(datos);

    cout << "Ordenado: ";
    for (int x : datos) cout << x << " ";
    cout << "\n";

    bubbleSort(datos2);

    cout << "Ordenado: ";
    for (int x : datos2) cout << x << " ";
    cout << "\n";

    return 0;
}