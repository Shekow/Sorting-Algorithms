#include <iostream>
#include <chrono>
#include <bits/stdc++.h>
#include "Sorting.cpp"
#define ull unsigned long long
#define ll long long
#define ld long double
#define each auto &
#define endl '\n'
#define pll pair<ll, ll>
#define all(v) v.begin(), v.end()
using namespace std;
using namespace Sorting;

ll compCounter;
class Student
{
    friend ostream &operator<<(ostream &os, Student student);
    friend istream &operator>>(istream &is, Student &student);
    string id, name;
    double gpa;
    public:
        Student() = default;
        Student(string name, string id, double gpa): id(id), name(name), gpa(gpa) {};
        bool operator<(Student &other)
        {
            return name < other.name;
        }
        bool operator==(Student &other)
        {
            return name == other.name && id == other.id && gpa == other.gpa;
        }
        bool operator!=(Student &other)
        {
            return !(*this == other);
        }
        static bool compareByName(Student &a, Student &b)
        {
            compCounter++;
            return a.name < b.name;
        }
        static bool compareByGPA(Student &a, Student &b)
        {
            compCounter++;
            return a.gpa > b.gpa;
        }
        static ll key(Student &student)
        {
            return student.gpa * 100;
        }
};

ostream &operator<<(ostream &os, Student student)
{
    os << student.name << endl;
    os << student.id << endl;
    os << student.gpa << endl;
    return os;
}

istream &operator>>(istream &is, Student &student)
{
    is.ignore();
    getline(is, student.name);
    is >> student.id >> student.gpa;
    return is;
}

template<class T, class F, class C>
void testAlgorithm(T begin, T end, F fn, C comp, string name)
{
    vector tmp(begin, end);
    cout << "Algorithm: " << name << endl;
    compCounter = 0;
    auto start = chrono::high_resolution_clock::now();
    fn(all(tmp), comp);
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> runningTime = finish - start;
    cout << "Number of Comparisions: " << compCounter << endl;
    cout << "Running Time: " << runningTime.count() * 1000 << " milliseconds" << endl;
    for (each e: tmp)
        cout << e << endl;
}

int main()
{
    freopen("students.txt", "r", stdin);
    
    ll n;
    cin >> n;
    vector<Student> students(n);
    for (each e: students)
        cin >> e;
    freopen("SortedByGPA.txt", "w", stdout);
    testAlgorithm(all(students), insertionSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByGPA, "Insertion Sort");
    testAlgorithm(all(students), selectionSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByGPA, "Selection Sort");
    testAlgorithm(all(students), bubbleSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByGPA, "Bubble Sort");
    testAlgorithm(all(students), shellSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByGPA, "Shell Sort");
    testAlgorithm(all(students), mergeSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByGPA, "Merge Sort");
    testAlgorithm(all(students), quickSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByGPA, "Quick Sort");
    testAlgorithm(all(students), heapSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByGPA, "Heap Sort");

    cout.flush();
    freopen("SortedByName.txt", "w", stdout);
    testAlgorithm(all(students), insertionSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByName, "Insertion Sort");
    testAlgorithm(all(students), selectionSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByName, "Selection Sort");
    testAlgorithm(all(students), bubbleSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByName, "Bubble Sort");
    testAlgorithm(all(students), shellSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByName, "Shell Sort");
    testAlgorithm(all(students), mergeSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByName, "Merge Sort");
    testAlgorithm(all(students), quickSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByName, "Quick Sort");  
    testAlgorithm(all(students), heapSort<vector<Student>::iterator, bool (*)(Student&, Student&)>, Student::compareByName, "Heap Sort");  
}