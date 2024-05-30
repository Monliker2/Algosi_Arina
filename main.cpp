#include <iostream>
#include <stack>
#include <chrono>
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
    int GetValue(int index) {
        Numbers tmp;
        int ret = 0;
        for(int i = 0; i != index; ++i){
            int t = top();
            pop();
            tmp.push(t);
        }
        ret = top();
        while(!tmp.isEmpty()){
            int temp = tmp.top();
            tmp.pop();
            push(temp);
        }
        return ret;
    }

    void SetValue(int index, int value, int size) {
        Numbers tmp;

        for(int i = 0; i != index; ++i){
            int t = top();
            pop();
            tmp.push(t);
        }
        pop();
        push(value);
        for(int i = index; i != size; ++i){
            int t = top();
            pop();
            tmp.push(t);
        }
        for(int i = 0; i != size; ++i){
            int t = tmp.top();
            tmp.pop();
            push(t);
        }

    }


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

void Sort(Numbers *temp, int size) {
    //Numbers keys;
    Numbers arr;
    for (int i = size-1; i >= 0; --i) {
        arr.push(temp->GetValue(i));
    }
    //cout<<arr.GetValue(0)<< ' '<< arr.GetValue(9)<<'\n';
    /*for (int i = 0; i < size; ++i) {
        keys.push(temp->GetValue(i));
    }*/
    bool flag1 = true;
    bool flag2 = true;
    bool flag3 = true;
    //int *arr = new int[size * 2];

    int f, s, d, i, j, k, l;
    s = 0;
    do {
        flag2 = true;
        if (s == 0) {
            i = 0;
            j = size - 1;
            k = size;
            l = (2 * size) - 1;
        }
        if (s == 1) {
            i = size;
            j = (2 * size) - 1;
            k = 0;
            l = size - 1;
        }
        d = 1;
        f = 1;
        if ((arr.GetValue(i) <= arr.GetValue(j) && i != j) || arr.GetValue(i) > arr.GetValue(j)) {
            //if (((arr[i] <= arr[j])&&(i!=j))|| (arr[i] > arr[j])) {
            do {
                if (arr.GetValue(i) <= arr.GetValue(j) && i != j) {
                    if (arr.GetValue(i) <= arr.GetValue(j) && i != j)
                        //if (arr[i] <= arr[j] && i != j) {
                        do {
                            flag3 = true;
                            flag1 = true;
                            int t = arr.GetValue(i);
                            arr.SetValue(k, t, size);
                            //arr[k] = arr[i];
                            k += d;
                            i++;
                            if (i > size - 1 || arr.GetValue(i - 1) <= arr.GetValue(i)) {
                                //if (arr[i - 1] <= arr[i]) {
                                flag3 = false;
                                break;
                            }
                            do {
                                int t = arr.GetValue(j);
                                arr.SetValue(k, t, size);
                                //arr[k] = arr[j];
                                k += d;
                                j--;
                                if (j < 0 || arr.GetValue(j + 1) <= arr.GetValue(j))continue;
                                //if (arr[j + 1] <= arr[j])continue;
                                else {
                                    flag1 = false;
                                    flag3 = false;
                                    f = 0;
                                    d = -d;
                                    int ser = k;
                                    k = l;
                                    l = ser;
                                    break;
                                }
                            } while (flag1);
                        } while (flag3);
                }
                if (arr.GetValue(i) > arr.GetValue(j)) {
                    //if (arr[i] > arr[j]) {
                    do {
                        flag3 = true;
                        flag1 = true;
                        int t= arr.GetValue(j);
                        arr.SetValue(k, t, size);
                        //arr[k] = arr[j];
                        k += d;
                        j--;
                        if (j < 0 || arr.GetValue(j + 1) <= arr.GetValue(j)) {
                            //if (arr[j + 1] <= arr[j]) {
                            flag3 = false;
                            break;
                        }
                        do {
                            int t = arr.GetValue(i);
                            arr.SetValue(k, t, size);
                            //arr[k] = arr[i];
                            k += d;
                            i++;
                            if (arr.GetValue(i - 1) <= arr.GetValue(i)) continue;
                            //if (arr[i - 1] <= arr[i])continue;
                            else {
                                flag1 = false;
                                flag3 = false;
                                f = 0;
                                d = -d;
                                int ser = k;
                                k = l;
                                l = ser;
                                break;
                            }
                        } while (flag1);
                    } while (flag3);
                }
                if (i == j) {
                    flag2 = false;
                    break;
                }
            } while (flag2);
        }
        if (i == j) {
            int t = arr.GetValue(i);
            arr.SetValue(k, t, size);
            //arr[k] = arr[i];
            if (f == 0) {
                s = 1 - s;
            } else {
                break;
            }
        }
    } while (f == 0);

    // for (int i = 0; i <size; i++)
    //     cout << arr.GetValue(i) << " ";
}



int main() {
    setlocale(LC_ALL, "Russian");
    Numbers Stack1;
    stack<int> oldStack;
    for (int i = 0; i < 10; ++i) {
        int num = rand() % 1000;
        Stack1.push(num);
        oldStack.push(num);
    }
    for (int i = 0; i < 10; ++i) {
        Stack1.SetValue(i,i,10);
    }

    //cout << "Old Stack1: \n";

    /*for(int i =0; i<10;++i) {
        cout << Stack1.GetValue(i) << " ";
    }*/
    cout<<"\n";

    for(int i =0; i <10;++i) {
        cout<< Stack1.GetValue(i)<< ' ';
    }
    cout<<"\n";
    //Stack1.ArrayThroughStack();
    Sort(&Stack1, 5);
    //cout << "New Stack1: ";
    while (!Stack1.isEmpty()) {
        std::cout << Stack1.top() << " ";
        Stack1.pop();
    }

    Numbers Stack;
    int key[1000];
    for (int i = 0; i <= 1000-1; ++i) {
        key[i] = rand() % 1000;
    }
    int size = 100;
    while (size != 1100) {
        for (int i = 0; i != size; ++i) {
            Stack.push(key[i]);
        }
        cout << "\n";
        auto start = chrono::high_resolution_clock::now();
        Stack.ArrayThroughStack();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        cout << "Сортировка " << size << " элементов заняла: " << elapsed.count() << " мс";
        /*for (int i = 0; i != size; ++i) {
            cout << Stack.top() << " ";
            Stack.pop();
        }*/
        size += 100;
        Stack.clear();
    };
}