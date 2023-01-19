// Capacity3.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <ranges>
#include <cmath>
#include <algorithm>
#include <functional> 
#include <map>
#include <list> 
#include <vector> 
#include <string>  
#include "Capacity.h"  

using namespace std;

int indexSpeicher = 0;

int main(int argc, char* argv[])
{

    cout << "You have entered " << argc
        << " arguments:" << endl;

    for (int i = 0; i < argc; ++i)
        cout << argv[i] << endl;

    int laenge = *argv[1] - 48; //char to int
    int breite = *argv[2] - 48; //char to int

    cout << "Laenge = " << laenge << endl;
    cout << "Breite = " << breite << endl;



    CapacitySim capacitySim{ laenge, breite };

    capacitySim.runCapacitySim();


}

void CapacitySim::runCapacitySim()
{
    Blueprint blueprint{ laenge, breite };
    Blueprint startBlueprint{ laenge, breite };

    auto it = planSpeicher.begin();
    planSpeicher.insert(it, startBlueprint);

    bool showMenue = true;
    int eingabe;
    while (showMenue) {
        cout << endl << endl << "Menue:" << endl;
        cout << "(1) build new building (0 = Leer, 1 = Wasserkraftwerk, 2 = Windkraftwerk, 3 = Solarpanele)" << endl;
        cout << "(2) clear area" << endl;
        cout << "(3) show plan" << endl;
        cout << "(4) end Program" << endl;
        cout << "(5) save and start new plan" << endl;
        cout << "(6) show all plans" << endl;
        cout << "Enter Command:";
        cin >> eingabe;
        cout << endl;
        switch (eingabe)
        {
        case 1: blueprint.build();
            break;
        case 2: blueprint.clearArea();
            break;
        case 3: blueprint.showPlan();
            break;
        case 4: showMenue = false;
            break;
        case 5: blueprint = blueprint.startNewPlan(planSpeicher);
            cout << "You can start new plan now..." << endl;
            break;
        case 6:
            blueprint.showAllPlans(planSpeicher);
            break;
        default: cout << "command not supported";
        }

    }

    delete[] blueprint.a_ptr;
}


void Blueprint::build()
{
    int typeBuilding;
    int lengthBuilding;
    int widthBuilding;
    int x;
    int y;
    std::cout << "Type = " << endl;
    cin >> typeBuilding;
    std::cout << "Length = " << endl;
    cin >> lengthBuilding;
    std::cout << "Width = " << endl;
    cin >> widthBuilding;
    std::cout << "X-Coordinate = " << endl;
    cin >> x;
    std::cout << "Y-Coordinate = " << endl;
    cin >> y;

    //get start position
    int pos = x + y * laenge;


    //Check if start position is valid
    if (pos > (laenge * breite - 1))
    {
        std::cout << "Error: Coordinates outside the predefined Building-Area" << endl;
        return;
    }


    //check if measurements are valid
    if (((y + widthBuilding) > breite) || ((x + lengthBuilding) > laenge))
    {
        std::cout << "Error: Some parts of the building are located outside the predefined Building-Area" << endl;
        return;
    }


    //get BuildingType
    if (typeBuilding == 0)
    {
        building = le;
    }
    else if (typeBuilding == 1)
    {

        building = wa;
    }
    else if (typeBuilding == 2)
    {

        building = wi;
    }
    else if (typeBuilding == 3)
    {

        building = so;
    }
    else
    {
        std::cout << "Error: Undefined Buildingtype" << endl;
        return;
    }



    int startpostition = pos;

    Building newBuilding = building;

    //Build
    for (int i = 0; i < widthBuilding; i++)
    {
        pos = startpostition + i * laenge;

        for (int a = 0; a < lengthBuilding; a++)
        {

            //Check if space is free
            if (a_ptr[pos].label == le.label)
            {
                a_ptr[pos] = newBuilding;
                pos += 1;
            }
            else
            {
                std::cout << "Error: This building collides with another building" << endl;
                return;
            }

        }

    }

    return;
}

void Blueprint::clearArea()
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
            a_ptr[pos] = le;
            pos += 1;
        }

    }

    return;
}

void Blueprint::showPlan()
{
    cout << endl;
    for (int i = (breite - 1); i >= 0; i--)
    {
        for (int a = 0; a < laenge; a++)
        {
            cout << a_ptr[laenge * i + a].label;
        }
        cout << endl;
    }

    bool waExists = false;
    bool wiExists = false;
    bool soExists = false;

    int waCounter = 0;
    int wiCounter = 0;
    int soCounter = 0;

    for (int i = (breite - 1); i >= 0; i--)
    {
        for (int a = 0; a < laenge; a++)
        {
            if (a_ptr[laenge * i + a].label == wa.label) { waExists = true; waCounter++; }
            if (a_ptr[laenge * i + a].label == wi.label) { wiExists = true; wiCounter++; }
            if (a_ptr[laenge * i + a].label == so.label) { soExists = true; soCounter++; }

        }
    }


    cout << "" << endl;

    std::map<Material, int>::iterator itWa = wa.myMap.begin();
    std::map<Material, int>::iterator itWi = wi.myMap.begin();
    std::map<Material, int>::iterator itSo = so.myMap.begin();

    int gesamtMaterialPreis = 0;

    if (waExists)
    {
        cout << endl << "Wasserkraftwerk (WA):" << endl;

        while (itWa != wa.myMap.end())
        {
            std::cout << "Material: " << itWa->first.ausgabe << ", Anzahl: " << itWa->second << std::endl;
            gesamtMaterialPreis += itWa->first.preis;
            ++itWa;
        }

        cout << "Preis pro Quadratmeter (Euro): " << wa.grundPreis << endl << "WA-Preis insgesamt (Euro): " << wa.grundPreis * waCounter << endl;
    }
    if (wiExists)
    {
        cout << endl << "Windkraftwerk (WI):" << endl;

        while (itWi != wi.myMap.end())
        {
            std::cout << "Material: " << itWi->first.ausgabe << ", Anzahl: " << itWi->second << std::endl;
            gesamtMaterialPreis += itWi->first.preis;
            ++itWi;
        }

        cout << "Preis pro Quadratmeter (Euro): " << wi.grundPreis << endl << "WI-Preis insgesamt (Euro): " << wi.grundPreis * wiCounter << endl;
    }
    if (soExists)
    {
        cout << endl << "Solarpanele (SO):" << endl;

        while (itSo != so.myMap.end())
        {
            std::cout << "Material: " << itSo->first.ausgabe << ", Anzahl: " << itSo->second << std::endl;
            gesamtMaterialPreis += itSo->first.preis;
            ++itSo;
        }

        cout << "Preis pro Quadratmeter (Euro): " << so.grundPreis << endl << "SO-Preis insgesamt (Euro): " << so.grundPreis * soCounter << endl;
    }
    cout << "" << endl;
    cout << "Gesamtmaterial Kosten (Euro): " << gesamtMaterialPreis << endl;
    cout << "Kennzahl: " << kennzahl() << endl;
    cout << "Gesamtpreis fuer alle Buildings (Euro): " << wi.grundPreis * wiCounter + wa.grundPreis * waCounter + so.grundPreis * soCounter << endl;


    return;
}

Blueprint Blueprint::startNewPlan(vector<Blueprint>& planSpeicher)
{
    //ersatzlösung -> views::filter wird nicht erkannt????
    bool same = false;


    //check if identical plan already exists
    for (auto blueprintAlt : planSpeicher)
    {
        Blueprint comp{ laenge, breite };

        comp(blueprintAlt.a_ptr, a_ptr);
        if (comp.identisch)
        {
            same = true;
        }

        delete[] comp.a_ptr;


    }

    if (!same)
    {
        planSpeicher.push_back(*this);
        cout << endl << "Plan has been saved..." << endl;
    }
    else
    {
        cout << endl << "Plan already exists..." << endl;
    }


    Blueprint newBlueprint{ laenge,breite };
    return newBlueprint;

}

void Blueprint::showAllPlans(vector<Blueprint>& planSpeicher)
{
    int counter = 1;

    //sort vector
    sort(planSpeicher.begin(), planSpeicher.end(), [](Blueprint a, Blueprint b) -> bool
        {
            return a.kennzahl() > b.kennzahl();
        });


    for (auto b : planSpeicher)
    {
        cout << endl << "Plan " << counter << ": " << endl;
        a_ptr = b.a_ptr;
        showPlan();
        counter++;
    }
    return;
}

float Blueprint::kennzahl()
{
    float K = 0;
    float gesamtLeistung = wa.gesamtLeistung(a_ptr, breite, laenge) + wi.gesamtLeistung(a_ptr, breite, laenge) + so.gesamtLeistung(a_ptr, breite, laenge);
    float gesamtPreis = wa.gesamtPreis(a_ptr, breite, laenge) + wi.gesamtPreis(a_ptr, breite, laenge) + so.gesamtPreis(a_ptr, breite, laenge);
    if (gesamtPreis != 0)
    {
        K = gesamtLeistung / gesamtPreis;
    }
    return K;
}

int Building::gesamtPreisMaterial(Building* a_ptr, int breite, int laenge)
{
    int counter = 0;
    int preisM = 0;

    for (int i = (breite - 1); i >= 0; i--)
    {
        for (int a = 0; a < laenge; a++)
        {
            if (a_ptr[laenge * i + a].label == label) { counter++; }

        }
    }

    std::map<Material, int>::iterator itWa = myMap.begin();

    while (itWa != myMap.end())
    {
        preisM += itWa->first.preis;
        ++itWa;
    }

    return preisM * counter;
}

int Building::gesamtPreis(Building* a_ptr, int breite, int laenge)
{
    int counter = 0;

    for (int i = (breite - 1); i >= 0; i--)
    {
        for (int a = 0; a < laenge; a++)
        {
            if (a_ptr[laenge * i + a].label == label) { counter++; }

        }
    }

    return grundPreis * counter;

}

float Building::gesamtLeistung(Building* a_ptr, int breite, int laenge)
{

    int counter = 0;

    for (int i = (breite - 1); i >= 0; i--)
    {
        for (int a = 0; a < laenge; a++)
        {
            if (a_ptr[laenge * i + a].label == label) { counter++; }

        }
    }

    return leistung * counter;
}

bool Blueprint::operator()(Building* planAlt, Building* planNeu)
{

    bool same = true;
    for (int i = (breite - 1); i >= 0; i--)
    {
        for (int a = 0; a < laenge; a++)
        {
            if (planAlt[laenge * i + a].label != planNeu[laenge * i + a].label) { same = false; }

        }
    }

    //ersatzlösung view::filter nicht gefunden
    identisch = same;

    return same;
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
