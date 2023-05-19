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
    double theta = 2 * M_PI / 50;
    //cout<<theta<<endl;
    for (double i = 0; i <= 2 * M_PI; i += theta)
    {
        Points coordinate;
        
        coordinate.coordinates[0] = center.coordinates[0] + radius * cos(i);
        coordinate.coordinates[1] = center.coordinates[1] + radius * sin(i);
        coordinate.coordinates[2] = 10;
        circle.push_back(coordinate);
    }
    return true;
}

bool generateEclipseshape(Curve &eclipse)
{
    Points center;
    double majorRadius, minorRadius;

    cout << "Enter center point (x, y, z): ";
    cin >> center.coordinates[0] >> center.coordinates[1] >> center.coordinates[2];

    cout << "Enter majorRadius radius: ";
    cin >> majorRadius;

    cout << "Enter minorRadius radius: ";
    cin >> minorRadius;

    double theta = 2 * M_PI / 50;

    for (double i = 0; i <= 2 * M_PI;i += theta)
    {
        Points coordinate;
        
        coordinate.coordinates[0] = center.coordinates[0] + majorRadius * cos(i);
        coordinate.coordinates[1] = center.coordinates[1] + minorRadius * sin(i);
        coordinate.coordinates[2] = 0.0;
        // coordinate.coordinates[2] = center.coordinates[2] + minorRadius * tan(theta);
        eclipse.push_back(coordinate);
    }
    return true;
}

bool generateSurfaceLoft(Curve circle, Curve eclipse, int numV, Surface &loftSurface)
{
    if (circle.size() != eclipse.size())
        return false;
    if (circle.empty() || eclipse.empty())
    {
        return false;
    }
    double deltaV = 1.0 / numV;

    for (double v = 0; v <=1.0; v += deltaV)
    {
        Curve temp;
        temp.resize(circle.size());
        for (int i = 0; i < circle.size(); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                temp[i].coordinates[j] = circle[i].coordinates[j] * (1 - v) + eclipse[i].coordinates[j] * v;
            }
        }
        loftSurface.push_back(temp);
    }
    return true;
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
    Curve eclipse;
    Surface loftSurface;
    int numV = 40;

    generateCircleshape(circle);
    generateEclipseshape(eclipse);
    generateSurfaceLoft(circle, eclipse,numV,loftSurface);
    writeDataInFile(loftSurface);

    return 0;
}

/*
Enter center point (x, y, z): 10 50 25
Enter radius: 15
Enter center point (x, y, z): 5 75 25
Enter minorRadius radius: 18
Enter File name
CircleEclipseInter1.dat
*/