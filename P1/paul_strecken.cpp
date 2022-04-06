#include <iostream>
#include <string>
#include <fstream>

#define arraysize 1000

using namespace std;

class Punkt {
    double X, Y;
public:
    Punkt() { X = 0; Y = 0; }
    Punkt(double a, double b) { X = a; Y = b; }
    double getX(void) { return X; }
    double getY(void) { return Y; }
    void setX(double a) { X = a; }
    void setY(double a) { Y = a; }
};

double ccw(Punkt* p, Punkt* q, Punkt* r) {
    return (p->getX()*q->getY()-p->getY()*q->getX()) + (q->getX()*r->getY()-q->getY()*r->getX()) + (p->getY()*r->getX()-p->getX()*r->getY());
}

int main() {
    //Koordinaten zum Einlesen
    double P1X, P1Y, P2X, P2Y;
    //Array zum Speichern der Punkte
    Punkt* wert[arraysize+1][2];
    //Dateiname
    string filename("test.dat");
    //Dateistream
    ifstream input_file(filename);
    //Zähler zum Einlesen der Datei
    int counter_file = 0;
    //Zähler für schneidende Strecken
    int counter_cuts = 0;

    //File einlesen
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
            << filename << "'" << std::endl;
        return EXIT_FAILURE;
    }

    //Werte aus File in Array speichern
    while (input_file >> P1X >> P1Y >> P2X >> P2Y) {
        wert[counter_file][0] = new Punkt(P1X, P1Y);
        wert[counter_file][1] = new Punkt(P2X, P2Y);

        //ggf. ausgeben
/*
        cout <<  wert[counter_file][0]->getX()<<" ";
        cout <<  wert[counter_file][0]->getY()<<" ";
        cout <<  wert[counter_file][1]->getX()<<" ";
        cout <<  wert[counter_file][1]->getY() << endl;
        cout<<"___________________________-"<<endl;
*/
        counter_file++; // Hier haben wir beim anderen code vergessen, hochzuzählen
    }

    cout << "Number of lines: " << counter_file << endl;
    input_file.close();

    //Array nach schneidenden Strecken prüfen
    for (int i = 0; i < counter_file-1; i++) {
       /* cout <<  wert[i][0]->getX()<<" ";
        cout <<  wert[i][0]->getY()<<" ";
        cout <<  wert[i][1]->getX()<<" ";
        cout <<  wert[i][1]->getY() << endl;
        */double ccw_wert1;
        double ccw_wert2;
        for (int j = i + 1; j < counter_file; j++) {
          /*  cout <<  wert[j][0]->getX()<<" ";
            cout <<  wert[j][0]->getY()<<" ";
            cout <<  wert[j][1]->getX()<<" ";
            cout <<  wert[j][1]->getY() << endl;
          */  ccw_wert1 = ccw(wert[i][0], wert[i][1], wert[j][0]);
            ccw_wert2 = ccw(wert[i][0], wert[i][1], wert[j][1]);
            if (ccw_wert1 * ccw_wert2 <= 0) {
                ccw_wert1 = ccw(wert[j][0], wert[j][1], wert[i][0]);
                ccw_wert2 = ccw(wert[j][0], wert[j][1], wert[i][1]);
                if (ccw_wert1 * ccw_wert2 <= 0){
                    counter_cuts++;

                   /* cout << "P1X: " << wert[i][0]->getX();
                    cout << " P1Y: " << wert[i][0]->getY();
                    cout << " P2X: " << wert[i][1]->getX();
                    cout << " P1Y: " << wert[i][1]->getY() << endl;

                    cout << "P1X: " << wert[j][0]->getX();
                    cout << " P1Y: " << wert[j][0]->getY();
                    cout << " P2X: " << wert[j][1]->getX();
                    cout << " P1Y: " << wert[j][1]->getY() << endl; */

                }
            }
        }
      //  cout<<"--------------------------\n";
    }
    cout << "Number of cuts: " << counter_cuts << endl;
}
