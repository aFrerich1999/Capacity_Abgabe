// Capacity1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

// Capacity2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
//#include <graphics>

using namespace std;


/*

Baubereich wie folgt aufgebaut

x = laenge = Spalte
y = breite = Zeile

Labels:
Leer = 0
Wasserkraft = 1
Windkraft = 2
Solarpanele = 3


Bereich ist in Quadrate aufgeteilt -> Diese sind duchnummeriert

länge*(breite-1) ........      länge*breite-1
.
.
2*länge
länge    länge+1  länge+2 ...   2*länge-1
0          1        2     ...   länge-1


*/


enum Position { Leer, Wasserkraft, Windkraft, Solarpanele };
int laenge;
int breite;

void showPlan(Position* a_ptr);
void build(Position* a_ptr);
void clearArea(Position* a_ptr);


void build(Position* a_ptr)//(Position baubereich1[laenge][breite])
{
    int typeBuilding;
    int lengthBuilding;
    int widthBuilding;
    int x;
    int y;
    cout << "Type = " << endl;
    cin >> typeBuilding;
    cout << "Length = " << endl;
    cin >> lengthBuilding;
    cout << "Width = " << endl;
    cin >> widthBuilding;
    cout << "X-Coordinate = " << endl;
    cin >> x;
    cout << "Y-Coordinate = " << endl;
    cin >> y;

    //get start position
    int pos = x + y * laenge;


    //Check if start position is valid
    if (pos > (laenge * breite - 1))
    {
        cout << "Error: Coordinates outside the predefined Building-Area" << endl;
        return;
    }


    //check if measurements are valid
    if (((y + widthBuilding) > breite) || ((x + lengthBuilding) > laenge))
    {
        cout << "Error: Some parts of the building are located outside the predefined Building-Area" << endl;
        return;
    }

    int startpostition = pos;


    //Build
    for (int i = 0; i < widthBuilding; i++)
    {
        pos = startpostition + i * laenge;

        for (int a = 0; a < lengthBuilding; a++)
        {

            //Check if space is free
            if (a_ptr[pos] == Leer)
            {
                a_ptr[pos] = (Position)typeBuilding;
                pos += 1;
            }
            else
            {
                cout << "Error: This building collides with another building" << endl;
                return;
            }

        }

    }

    return;
}

void clearArea(Position* a_ptr)
{
    int lengthBuilding;
    int widthBuilding;
    int x;
    int y;
    cout << "Length = " << endl;
    cin >> lengthBuilding;
    cout << "Width = " << endl;
    cin >> widthBuilding;
    cout << "X-Coordinate = " << endl;
    cin >> x;
    cout << "Y-Coordinate = " << endl;
    cin >> y;

    //get start position
    int pos = x + y * laenge;


    //Check if start position is valid
    if (pos > (laenge * breite - 1))
    {
        cout << "Error: Coordinates outside the predefined Building-Area" << endl;
        return;
    }


    //check if measurements are valid
    if (((y + widthBuilding) > breite) || ((x + lengthBuilding) > laenge))
    {
        cout << "Error: Some parts of the building are located outside the predefined Building-Area" << endl;
        return;
    }

    int startpostition = pos;


    //Clear
    for (int i = 0; i < widthBuilding; i++)
    {
        pos = startpostition + i * laenge;

        for (int a = 0; a < lengthBuilding; a++)
        {
            a_ptr[pos] = Leer;
            pos += 1;
        }

    }

    return;
}

void showPlan(Position* a_ptr)
{
    for (int i = (breite - 1); i >= 0; i--)
    {
        for (int a = 0; a < laenge; a++)
        {
            cout << a_ptr[laenge * i + a];
        }
        cout << endl;
    }

    return;
}

int main(int argc, char* argv[])
{
    cout << "You have entered " << argc
        << " arguments:" << endl;

    for (int i = 0; i < argc; ++i)
        cout << argv[i] << endl;

    laenge = *argv[1] - 48; //char to int
    breite = *argv[2] - 48; //char to int

    cout << "Laenge = " << laenge << endl;
    cout << "Breite = " << breite << endl; 

    //Position baubereich[laenge + breite] = { Leer }; -> Ging in Code-Blocks, aber nicht mit Visual Studio (?)
    Position* baubereich = new Position[laenge * breite];
    for (int i = 0; i < (laenge * breite); i)
    {
        baubereich[i] = Leer;
        i++;
    }
    Position* a_ptr = baubereich;

    bool showMenue = true;
    int eingabe;
    while (showMenue) {
        cout << "Menue:" << endl;
        cout << "(1) build new building (0 = Leer, 1 = Wasserkraftwerk, 2 = Windkraftwerk, 3 = Solarpanele)" << endl;
        cout << "(2) clear area" << endl;
        cout << "(3) show plan" << endl;
        cout << "(4) end Program" << endl;
        cout << "Enter Command:";
        cin >> eingabe;
        switch (eingabe)
        {
        case 1: build(a_ptr);
            break;
        case 2: clearArea(a_ptr);
            break;
        case 3: showPlan(a_ptr);
            break;
        case 4: showMenue = false;
            break;
        default: cout << "command not supported";
        }

    }

    delete[] baubereich;

    return 0;
}


// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.


// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
