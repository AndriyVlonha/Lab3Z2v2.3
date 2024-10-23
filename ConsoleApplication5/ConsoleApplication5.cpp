#include <iostream>
using namespace std;

class Vector {
private:
    double* data;
    int size;
    int status;
    static int objectCount;

public:
    Vector() : data(new double[1] {0.0}), size(1), status(0) { objectCount++; }

    Vector(int s) {
        try {
            data = new double[s]();
            size = s;
            status = 0;
            objectCount++;
        }
        catch (std::bad_alloc&) {
            status = 1;
            size = 0;
            data = nullptr;
        }
    }

    Vector(int s, double value) {
        try {
            data = new double[s];
            fill(data, data + s, value);
            size = s;
            status = 0;
            objectCount++;
        }
        catch (std::bad_alloc&) {
            status = 1;
            size = 0;
            data = nullptr;
        }
    }

    Vector(const Vector& other) {
        try {
            data = new double[other.size];
            size = other.size;
            copy(other.data, other.data + size, data);
            status = 0;
            objectCount++;
        }
        catch (std::bad_alloc&) {
            status = 1;
            size = 0;
            data = nullptr;
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            try {
                data = new double[other.size];
                size = other.size;
                copy(other.data, other.data + size, data);
                status = 0;
            }
            catch (std::bad_alloc&) {
                status = 1;
                size = 0;
                data = nullptr;
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
        objectCount--;
    }

    void setElement(int index, double value = 0.0) {
        if (index >= 0 && index < size) {
            data[index] = value;
            status = 0;
        }
        else status = 2;
    }

    double getElement(int index) {
        if (index >= 0 && index < size) {
            status = 0;
            return data[index];
        }
        status = 2;
        return 0.0;
    }

    void print() {
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << endl;
    }

    Vector operator+(const Vector& other) {
        if (size != other.size) {
            Vector result;
            result.status = 3;
            return result;
        }
        Vector result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] + other.data[i];
        return result;
    }

    Vector operator-(const Vector& other) {
        if (size != other.size) {
            Vector result;
            result.status = 3;
            return result;
        }
        Vector result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] - other.data[i];
        return result;
    }

    Vector operator*(double scalar) {
        Vector result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] * scalar;
        return result;
    }

    Vector operator/(double scalar) {
        if (scalar == 0) {
            Vector result;
            result.status = 4;
            return result;
        }
        Vector result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] / scalar;
        return result;
    }

    bool operator>(const Vector& other) {
        if (size != other.size) {
            status = 3;
            return false;
        }
        double sum1 = 0, sum2 = 0;
        for (int i = 0; i < size; i++) {
            sum1 += data[i];
            sum2 += other.data[i];
        }
        return sum1 > sum2;
    }

    bool operator<(const Vector& other) {
        if (size != other.size) {
            status = 3;
            return false;
        }
        double sum1 = 0, sum2 = 0;
        for (int i = 0; i < size; i++) {
            sum1 += data[i];
            sum2 += other.data[i];
        }
        return sum1 < sum2;
    }

    bool operator==(const Vector& other) {
        if (size != other.size) {
            status = 3;
            return false;
        }
        return equal(data, data + size, other.data);
    }

    int getStatus() const { return status; }
    static int getObjectCount() { return objectCount; }
};

int Vector::objectCount = 0;

int main() {
    Vector v1;
    cout << "v1: "; v1.print();

    Vector v2(3);
    cout << "v2: "; v2.print();

    Vector v3(3, 2.5);
    cout << "v3: "; v3.print();

    Vector v4 = v3;
    cout << "v4 (copy of v3): "; v4.print();

    v2 = v3;
    cout << "v2 after assignment: "; v2.print();

    v2.setElement(1, 5.0);
    cout << "Element at index 1: " << v2.getElement(1) << endl;

    Vector v5 = v2 + v3;
    cout << "v2 + v3: "; v5.print();

    Vector v6 = v2 - v3;
    cout << "v2 - v3: "; v6.print();

    Vector v7 = v2 * 2.0;
    cout << "v2 * 2.0: "; v7.print();

    Vector v8 = v2 / 2.0;
    cout << "v2 / 2.0: "; v8.print();

    cout << "v2 == v3: " << (v2 == v3) << endl;
    cout << "v2 > v3: " << (v2 > v3) << endl;
    cout << "v2 < v3: " << (v2 < v3) << endl;

    cout << "Number of Vector objects: " << Vector::getObjectCount() << endl;

    return 0;
}
