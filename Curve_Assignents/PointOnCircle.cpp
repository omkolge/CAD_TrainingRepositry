#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Point {
    public:
    double x;
    double y;
};

int main() {
    Point center;
    double radius;

    cout << "Enter center point (x, y): ";
    cin >> center.x >> center.y;

    cout << "Enter radius: ";
    cin >> radius;

    ofstream outfile("PointsOnCircle.dat");
    
    for (int i = 0; i < 50; i++) {
        double theta = i * M_PI / 25;
        double x = center.x + radius * cos(theta);
        double y = center.y + radius * sin(theta);

        outfile << x << " " << y << endl;
    }

    outfile.close();

    //system("gnuplot -e \"plot 'points.dat' with points\"");
    
    return 0;
}