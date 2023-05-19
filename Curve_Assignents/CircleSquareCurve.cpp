#include <iostream>
#include <vector>
#include <fstream>
#include<cmath>

using namespace std;

#define M_PI 3.14159265358979323846

class Points
{
public:
    double coordinates[3];
    
};

typedef vector<Points> Curve;
typedef vector<Curve> Surface;

bool generateCircleshape(Curve &circle)
{
    Points center;
    double radius;

    cout << "Enter center point (x, y, z): ";
    cin >> center.coordinates[0] >> center.coordinates[1] >> center.coordinates[2];

    cout << "Enter radius: ";
    cin >> radius;
    double theta = 2 * M_PI / 40;
    for (double i = 0; i < 2 * M_PI; i += theta)
    {
        Points coordinate;
        coordinate.coordinates[0] = center.coordinates[0] + radius * cos(i);
        coordinate.coordinates[1] = center.coordinates[1] + radius * sin(i);
        coordinate.coordinates[2] = 10;
        circle.push_back(coordinate);
    }
    return true;
}

bool generateLineshape(Points P1, Points P2, int numU, Curve &line)
{
    for (double i = 0; i < 1; i += 1 / (double)(numU)) {
        Points coordinate;
        coordinate.coordinates[0] = P1.coordinates[0] *(1-i)+P2.coordinates[0]*i;
        coordinate.coordinates[1] = P1.coordinates[1] *(1-i)+P2.coordinates[1]*i;
        coordinate.coordinates[2] = P1.coordinates[2] *(1-i)+P2.coordinates[2]*i;
        line.push_back(coordinate);
    }
    return true;
}

bool generateSquareshape(Curve &square)
{
    Points P1,P2,P3,P4;
    int numU=40;
    cout << "Enter P1 point (x, y, z): ";
    cin >> P1.coordinates[0] >> P1.coordinates[1] >> P1.coordinates[2];
    
    cout << "Enter P2 point (x, y, z): ";
    cin >> P2.coordinates[0] >> P2.coordinates[1] >> P2.coordinates[2];

    cout << "Enter P3 point (x, y, z): ";
    cin >> P3.coordinates[0] >> P3.coordinates[1] >> P3.coordinates[2];

    cout << "Enter P4 point (x, y, z): ";
    cin >> P4.coordinates[0] >> P4.coordinates[1] >> P4.coordinates[2];
    
    Curve line[4];
    generateLineshape(P1,P2,numU/4,line[0]);
    generateLineshape(P2,P3,numU/4,line[1]);
    generateLineshape(P3,P4,numU/4,line[2]);
    generateLineshape(P4,P1,numU/4,line[3]);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < numU/4; j++)
            square.push_back(line[i][j]);
    }
    return true;
}

bool generateSurfaceLoft(Curve circle, Curve square, int numV, Surface &loftSurface)
{
    if (circle.size() != square.size())
        return false;
    if (circle.size() != square.size())
        return 0;
    double deltaV = 1.0 / (numV-1);
    for (double v = 0; v <= 1.0; v += deltaV)
    {
        Curve c;
        c.resize(circle.size());
        for (int i = 0; i < c.size(); i++)
        {
            for (int j = 0; j < 3; j++)
                c[i].coordinates[j] = (circle[i].coordinates[j] * (1 - v)) + (square[i].coordinates[j] * v);
        }
        loftSurface.push_back(c);
    }
    return 1;
}

bool writeDataInFile(Surface &loftSurface)
{
    string fileName;
    ofstream insertPointInFile;

    cout << "Enter File name" << endl;
    cin >> fileName;

    insertPointInFile.open(fileName, ios::out | ios::trunc);
    
    //insertPointInFile << fixed << setprecision(4);
    for (int i = 0; i < loftSurface.size(); i++)
    {
        for (int j = 0; j < loftSurface[i].size(); j++)
        {
            for (int k = 0; k < 3; k++)
            {
                insertPointInFile << loftSurface[i][j].coordinates[k] << " ";
            }
            insertPointInFile << endl;
        }
        insertPointInFile << endl;
    }
    insertPointInFile.close();
    return true;
}



int main()
{
    Curve circle;
    Curve square;
    Surface loftSurface;
    int numV = 50;

    generateCircleshape(circle);
    cout<<"Size of Line : "<<circle.size()<<endl;
    generateSquareshape(square);
    cout<<"Size of bezier : "<<square.size()<<endl;
    generateSurfaceLoft(circle, square,numV,loftSurface);
    writeDataInFile(loftSurface);

    return 0;
}

/*
Enter center point (x, y, z): 25 25 0
Enter radius: 25
Enter P1 point (x, y, z): 5 5 0
Enter P2 point (x, y, z): 50 5 0
Enter P3 point (x, y, z): 50 50 0
Enter P4 point (x, y, z): 5 50 0

*/