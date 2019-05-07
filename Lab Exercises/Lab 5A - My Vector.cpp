#include <iostream>

class MyVector {
    private:
        int *data;
        int count;
        int capacity;

    public:
        MyVector();
        MyVector(int values[], int size);
        int size() const;
        int get(int index) const;
        void set(int index, int value);
        int index(int value);
        void append(int value);
        void insert(int index, int value);
        int pop();
        int erase(int index);
        void clear();
        bool equals(const MyVector &other);
        MyVector slice(int start, int stop, int step);
};

MyVector::MyVector() {
    capacity = 10;
    count = 0;
    data = new int[capacity];
}

MyVector::MyVector(int values[], int size) {
    if(size > 10) capacity = size;
    else capacity = 10;

    count = size;
    data = new int[capacity];

    for(int i = 0; i < size; i++) {
        data[i] = values[i];
    }
}

int MyVector::size() const {
    return count;
}

int MyVector::get(int index) const {
    return data[index];
}

void MyVector::set(int index, int value) {
    data[index] = value;
}

int MyVector::index(int value) {
    for(int i = 0; i < count; i++) {
        if(data[i] == value) return i;
    }

    return -1;
}

void MyVector::append(int value) {
    if(++count > 10) capacity = count;

    int *arr = new int[capacity];

    for(int i = 0; i < count - 1; i++) {
        arr[i] = data[i];
    }

    arr[count - 1] = value;

    delete [] data;

    data = arr;
}

void MyVector::insert(int index, int value) {
    if(index < 0) index = 0;
    else if(index > count) index = count;

    if(++count > 10) capacity = count;

    int *arr = new int[capacity];

    for(int i = 0; i < count - 1; i++) {
        if(i < index) arr[i] = data[i];
        else arr[i + 1] = data[i];
    }

    arr[index] = value;

    delete [] data;

    data = arr;
}

int MyVector::pop() {
    if(--count > 10) capacity = count;
    else capacity = 10;
    
    int value = data[count];
    
    int *arr = new int[capacity];
    
    for(int i = 0; i < count; i++) {
        arr[i] = data[i];
    }
    
    delete [] data;
    
    data = arr;
    
    return value;
}

int MyVector::erase(int index) {
    if(--count > 10) capacity = count;
    else capacity = 10;
    
    int value = data[index];
    
    int *arr = new int[capacity];
    
    for(int i = 0; i < count; i++) {
        if(i < index) arr[i] = data[i];
        else arr[i] = data[i + 1]; 
    }
    
    delete [] data;
    
    data = arr;
    
    return value;
}

void MyVector::clear() {
    count = 0;
    delete [] data;
    
    data = new int[capacity];
}

bool MyVector::equals(const MyVector &other) {
    if(count != other.size()) return false;

    for(int i = 0; i < count; i++) {
        if(data[i] != other.get(i)) return false;
    }

    return true;
}

MyVector MyVector::slice(int start, int stop, int step) {
    MyVector ret;
    
    if(start >= 0 && start < count && ((stop - start > 0 && step > 0) || (stop - start < 0 && step < 0))) {
        if(step > 0) {
            for(int i = start; i < stop; i += step) {
                ret.append(data[i]);
            }
        } else if(step < 0) {
            for(int i = start; i > stop; i += step) {
                ret.append(data[i]);
            }
        }
    }
        
    return ret;
}

int main() {
    return 0;
}