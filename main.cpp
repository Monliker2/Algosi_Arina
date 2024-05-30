#include <iostream>
#include <stack>
#include <chrono>
#include <windows.h>
using namespace std;


class CustomStack {
private:
    int* arr;
    int capacity;
    int topIndex;

public:
    CustomStack(int size = 10000) {
        arr = new int[size];
        capacity = size;
        topIndex = -1;
    }

    ~CustomStack() {
        delete[] arr;
    }

    void push(int value) {
        if (topIndex == capacity - 1) {   // 2n
            int newCapacity = capacity * 2; //2
            int* newArr = new int[newCapacity]; //2
            for (int i = 0; i < capacity; i++) {  //3n
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }
        arr[++topIndex] = value;  //1
    } //

    void pop() {
        if (isEmpty()) {  //
            cout << "Stack is empty. Cannot pop" << endl;
            return;
        }
        topIndex--; //1
    }

    int top() {
        if (isEmpty()) { //
            cout << "Stack is empty. Cannot get top element" << endl;
            return -1;
        }
        return arr[topIndex]; //1
    }

    bool isEmpty() {
        return topIndex == -1; //1
    }

    void clear() {
        topIndex = -1; //1
        delete[] arr;  //1
        arr = new int[capacity]; //1
    }
};
class Numbers : public CustomStack {
public:
    void merge(int* arr, int left[], int left_size, int right[], int right_size) {
        int i = 0, j = 0, k = 0;
        //меньший элемент из left[i] и right[j] добавляется в массив arr на позицию k, и соответствующий индекс увеличивается
        while (i < left_size && j < right_size) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            }
            else {
                arr[k++] = right[j++];
            }
        }
        //если один из массивов left или right закончился, оставшиеся элементы из другого массива просто добавляются в конец массива arr
        while (i < left_size) {
            arr[k++] = left[i++];
        }
        while (j < right_size) {
            arr[k++] = right[j++];
        }
    }

    void natural_two_way_merge_sort(int* arr, int size) {
        if (size <= 1) {
            return;
        }
        int mid = size / 2;
        int* left = new int[mid];
        int* right = new int[size - mid];
        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        for (int i = mid; i < size; i++) {
            right[i - mid] = arr[i];
        }
        natural_two_way_merge_sort(left, mid);
        natural_two_way_merge_sort(right, size - mid);
        merge(arr, left, mid, right, size - mid);
    }

    void ArrayThroughStack() {
        int size = 0;
        std::stack<int> tempStack;
        while (!isEmpty()) {
            tempStack.push(top());
            pop();
            size++;
        }

        int* temp = new int[size];
        int i = 0;
        while (!tempStack.empty()) {
            temp[i++] = tempStack.top();
            tempStack.pop();
        }
        natural_two_way_merge_sort(temp, size);

        for (int j = size - 1; j >= 0; --j) {
            push(temp[j]);
        }

        delete[] temp;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Numbers Stack1;
    stack<int> oldStack;
    for (int i = 0; i < 10; ++i) {
        int num = rand() % 1000;
        Stack1.push(num);
        oldStack.push(num);
    }

    cout << "Old Stack1: ";
    while (!oldStack.empty()) {
        cout << oldStack.top() << " ";
        oldStack.pop();
    }
    cout << "\n";
    Stack1.ArrayThroughStack();
    cout << "New Stack1: ";
    while (!Stack1.isEmpty()) {
        std::cout << Stack1.top() << " ";
        Stack1.pop();
    }
    cout << "\n";
    Numbers Stack;
    int key[1000];
    for (int i = 0; i <= 1000-1; ++i) {
        key[i] = rand() % 1000;
    }
    int n = 100;
    while (n != 1100) {
        for (int i = 0; i != n; ++i) {
            Stack.push(key[i]);
        }
        cout << "\n";
        auto start = chrono::high_resolution_clock::now();
        Stack.ArrayThroughStack();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        cout << "Сортировка " << n << " элементов заняла: " << elapsed.count() << " мс\n";
        /*for (int i = 0; i != n; ++i) {
            cout << Stack.top() << " ";
            Stack.pop();
        }*/
        n += 100;
        Stack.clear();
    };
}