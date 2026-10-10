
#include <iostream>
#include "Fraction.h"

using namespace std;

int main()
{
    Fraction f1("3", 75);
    Fraction f2("12", 50);
    Fraction f3;

    f3.Init("2", 25, true);

    cout << "===== Fraction =====" << endl;

    cout << "f1 = ";
    f1.Display();
    cout << endl;

    cout << "f2 = " << f2.toString() << endl;

    cout << "f3 = ";
    f3.Display();
    cout << endl;

    Fraction f4;
    f4.Read();

    cout << "f4 = " << f4.toString() << endl;

    cout << "\n===== Arithmetic =====" << endl;

    cout << "f1 + f2 = " << (f1 + f2).toString() << endl;
    cout << "f1 - f2 = " << (f1 - f2).toString() << endl;
    cout << "f1 * f2 = " << (f1 * f2).toString() << endl;

    cout << "\n===== Comparison =====" << endl;

    cout << boolalpha;
    cout << "f1 == f2: " << (f1 == f2) << endl;
    cout << "f1 != f2: " << (f1 != f2) << endl;
    cout << "f1 < f2: " << (f1 < f2) << endl;
    cout << "f1 > f2: " << (f1 > f2) << endl;
    cout << "f1 <= f2: " << (f1 <= f2) << endl;
    cout << "f1 >= f2: " << (f1 >= f2) << endl;

    cout << "\n===== Array of Fraction =====" << endl;

    Fraction arr[3] = {
        Fraction("1", 25),
        Fraction("2", 50),
        Fraction("3", 75)
    };

    for (int i = 0; i < 3; i++)
    {
        arr[i].Display();
        cout << endl;
    }

    return 0;
}