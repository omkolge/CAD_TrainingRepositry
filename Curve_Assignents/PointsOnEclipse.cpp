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
    Point center;
    double maj_rad1, min_rad2;
    cout << "Enter center point (x, y): ";
    cin >> center.x >> center.y;
    cout << "Enter major radius: ";
    cin >> maj_rad1;
    cout << "Enter minor radius: ";
    cin >> min_rad2;

    ofstream outfile("PointsOnEclipse.dat");

    for (int i = 0; i < 100; i++)
    {
        double angle = i * M_PI / 50;
        double x = center.x + maj_rad1 * cos(angle);
        double y = center.y + min_rad2 * sin(angle);
        outfile << x << " " << y << endl;
    }
    outfile.close();

    return 0;
}