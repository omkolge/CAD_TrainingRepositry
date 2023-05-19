#include <iostream>
#include <vector>
#include <fstream>
#include<cmath>

using namespace std;

//#define M_PI 3.14159265358979323846

class Points
{
public:
    double coordinates[3];
    
};

typedef vector<Points> Curve;
typedef vector<Curve> Surface;

bool generateLineshape(Curve &line)
{
    Points P1,P2;
    double radius;
    int n=20;

    cout << "Enter P1 point (x, y, z): ";
    cin >> P1.coordinates[0] >> P1.coordinates[1] >> P1.coordinates[2];

    cout << "Enter P2 point (x, y, z): ";
    cin >> P2.coordinates[0] >> P2.coordinates[1] >> P2.coordinates[2];

    for (double i = 0; i <=1;i += 1 / (double)(n)) {
        //fac=fac+n/i;
        Points coordinate;
        coordinate.coordinates[0] = P1.coordinates[0] *(1-i)+P2.coordinates[0]*i;
        coordinate.coordinates[1] = P1.coordinates[1] *(1-i)+P2.coordinates[1]*i;
        coordinate.coordinates[2] = P1.coordinates[2] *(1-i)+P2.coordinates[2]*i;
        line.push_back(coordinate);
    }
    return true;
}

bool generateBeziershape(Curve &bezier)
{
    Points P1,P2,P3,P4;
    //double u;
    int n=20;
    cout << "Enter P1 point (x, y, z): ";
    cin >> P1.coordinates[0] >> P1.coordinates[1] >> P1.coordinates[2];

    cout << "Enter P2 point (x, y, z): ";
    cin >> P2.coordinates[0] >> P2.coordinates[1] >> P2.coordinates[2];

    cout << "Enter P3 point (x, y, z): ";
    cin >> P3.coordinates[0] >> P3.coordinates[1] >> P3.coordinates[2];

    cout << "Enter P4 point (x, y, z): ";
    cin >> P4.coordinates[0] >> P4.coordinates[1] >> P4.coordinates[2];
    
    for (double i = 0; i <=1;i += 1 / (double)(n))
    {
        Points coordinate;
        coordinate.coordinates[0] = (P1.coordinates[0] * pow((1 - i), 3)) + 3 * (P2.coordinates[0] * (pow((1 - i), 2)) * (i)) + 3 * (P3.coordinates[0] * (1 - i) * (pow((i), 2))) + (P4.coordinates[0] * pow(i, 3));
        coordinate.coordinates[1] = (P1.coordinates[1] * pow((1 - i), 3)) + 3 * (P2.coordinates[1] * (pow((1 - i), 2)) * (i)) + 3 * (P3.coordinates[1] * (1 - i) * (pow((i), 2))) + (P4.coordinates[1] * pow(i, 3));
        coordinate.coordinates[2] = (P1.coordinates[2] * pow((1 - i), 3)) + 3 * (P2.coordinates[2] * (pow((1 - i), 2)) * (i)) + 3 * (P3.coordinates[2] * (1 - i) * (pow((i), 2))) + (P4.coordinates[2] * pow(i, 3));
        bezier.push_back(coordinate);
    }
    return true;
}

bool generateSurfaceLoft(Curve c1, Curve c2, int numV, Surface &loftSurface)
{
    if (c1.size() != c2.size())
        return false;
    if (c1.size() != c2.size())
        return 0;
    double deltaV = 1.0 / numV;
    for (double v = 0; v <= 1.0; v += deltaV)
    {
        Curve c;
        c.resize(c1.size());
        for (int i = 0; i < c.size(); i++)
        {
            for (int j = 0; j < 3; j++)
                c[i].coordinates[j] = (c1[i].coordinates[j] * (1 - v)) + (c2[i].coordinates[j] * v);
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
    Curve line;
    Curve bezier;
    Surface loftSurface;
    int numV = 20;

    generateLineshape(line);
    cout<<"Size of Line : "<<line.size()<<endl;
    generateBeziershape(bezier);
    cout<<"Size of bezier : "<<bezier.size()<<endl;
    generateSurfaceLoft(line, bezier,numV,loftSurface);
    writeDataInFile(loftSurface);

    return 0;
}

/*
Enter P1 point (x, y, z): 0 0 12
Enter P2 point (x, y, z): 10 10 12
Size of Line : 20
Enter P1 point (x, y, z): 0 1 20
Enter P2 point (x, y, z): -1 5 20
Enter P3 point (x, y, z): -5 11 20
Enter P4 point (x, y, z): 10 9 20
*/