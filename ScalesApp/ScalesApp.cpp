#include <iostream>
#include "Scale.h"

void printScale(Scale s){
    cout << s.getWeight() << "[" << s.getUnit() << "]";
}

void display(Scale s1, Scale s2) {
    string mark;
    if (s1 > s2)
        mark = " > ";
    else if (s1 < s2)
        mark = " < ";
    else
        mark = " = ";
    cout << "-----SCALE-----" << endl;
    cout << s1 << mark << s2 << endl;
}

int main(){

    Scale s1(10, "dag");
    Scale s2(1, "kg");
    string unit;
    display(s1, s2);
    cout << "Try It Your Self! Enter 2 values:" << endl;
    cout << "First value" << endl;
    cin >> s1;
    s1--;
    cout << s1 << endl;
    cout << "Second value" << endl;
    cin >> s2;
    display(s1, s2);
    cout << "Sum of given weights is " << s1 + s2 << endl;
    cout << "And sum of given weights is " << s2 + s1 << endl;
    cout << "Now you can convert 1'st value's unit to one of the following:" << endl;
    cout << "[Kg]; [lb]; [g]; [mg]; [oz]; [cwt]" << endl;
    cout << "Enter unit :";
    cin >> unit;
    s1.changeUnit(unit);
    cout << "now 1'st value is " << s1 << endl;

    return 0;
}