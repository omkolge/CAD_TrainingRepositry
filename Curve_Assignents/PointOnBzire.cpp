#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Point {
    public:
    double x;
    double y;
};

int main()
{
    Point p1, p2, p3,p4,p;
    
    double u;

    cout << "Enter center point (x1, y1): ";
    cin >> p1.x >> p1.y;
    cout << "Enter center point (x2, y2): ";
    cin >> p2.x >> p2.y;
    cout << "Enter center point (x3, y3): ";
    cin >> p3.x >> p3.y;
    cout << "Enter center point (x4, y4): ";
    cin >> p4.x >> p4.y;

    ofstream outfile("PointsOnBzireCurve.dat");

    for (int i = 0; i < 10; i++)
    {
        p.x = (p1.x * pow((1 - u), 3)) + 3 * (p2.x * (pow((1 - u), 2)) * (u)) + 3 * (p3.x * (1 - u) * (pow((u), 2))) + (p4.x * pow(u, 3));
        p.y = (p1.y * pow((1 - u), 3)) + 3 * (p2.y * (pow((1 - u), 2)) * (u)) + 3 * (p3.y * (1 - u) * (pow((u), 2))) + (p4.y * pow(u, 3));
        outfile << p.x << " " << p.y << endl;
        u=u+0.1;
    }

    outfile.close();

    return 0;
}