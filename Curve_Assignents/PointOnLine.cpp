#include <iostream>
#include <fstream>

using namespace std;

class Point {
    public:
    double x;
    double y;
};

int main() {
    Point p1, p2;
    double x,y,fac=0;
    int n;
    cout << "Enter point 1 (x, y): ";
    cin >> p1.x >> p1.y;

    cout << "Enter point 2 (x, y): ";
    cin >> p2.x >> p2.y;

    cout << "Enter number of points on line: ";
    cin >> n;

    ofstream outfile("PointsOnLines.dat");

    for (int i = 1; i < n; i++) {
        fac=fac+n/i;
        x = p1.x *(1-fac)+p2.x*fac;
        y = p1.y *(1-fac)+p2.y*fac;
        outfile << x << " " << y << endl;
    }

    outfile.close();
    
    return 0;
}
