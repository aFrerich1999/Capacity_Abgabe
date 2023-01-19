#pragma once
#pragma once
using namespace std;


class Material
{
public:
    int preis;
    string ausgabe;

};

bool operator<(const Material& c1, const Material& c2);

class Holz : public Material
{
public:
    Holz()
    {
        preis = 10000;
        ausgabe = "Holz";
    }

};

class Metall : public Material
{
public:
    Metall()
    {
        preis = 20000;
        ausgabe = "Metall";
    }

};

class Kunststoff : public Material
{
public:
    Kunststoff()
    {
        preis = 30000;
        ausgabe = "Kunststoff";
    }
};

class Comparator {
public:
    bool operator()(const Material& c1, const Material& c2) {
        return c1.preis < c2.preis;
    }
};

class Building
{


public:

    int grundPreis; //Euro pro Quadratmeter
    string label;
    std::map<Material, int> myMap;
    Holz h{};
    Kunststoff k{};
    Metall m{};
    int leistung; //Megawatt pro Quadratmeter 

    int gesamtPreisMaterial(Building* a_ptr, int breite, int laenge);
    int gesamtPreis(Building* a_ptr, int breite, int laenge);
    float gesamtLeistung(Building* a_ptr, int breite, int laenge);


};


class Leer : public Building
{
public:
    Leer()
    {
        grundPreis = 0;
        label = "LE ";

        myMap[h] = 0;
        myMap[m] = 0;
        myMap[k] = 0;

        leistung = 0;

    }
};


class Wasserkraftwerk : public Building
{
public:
    Wasserkraftwerk()
    {
        grundPreis = 123000;
        label = "WA ";

        myMap[h] = 2;
        myMap[m] = 1;
        myMap[k] = 1;

        leistung = 10000;

    }

};


class Windkraftwerk : public Building
{
public:
    Windkraftwerk()
    {
        grundPreis = 204000;
        label = "WI ";

        myMap[h] = 1;
        myMap[m] = 2;
        myMap[k] = 1;

        leistung = 20000;

    }

};

class Solarpanele : public Building
{
public:
    Solarpanele()
    {
        grundPreis = 309000;
        label = "S0 ";

        myMap[h] = 1;
        myMap[m] = 1;
        myMap[k] = 2;

        leistung = 30000;

    }

};





class Blueprint
{
public:
    int laenge;
    int breite;
    bool identisch;
    Building* a_ptr;
    Building building{};
    Wasserkraftwerk wa{};
    Windkraftwerk wi{};
    Solarpanele so{};
    Leer le{};
    Blueprint(int aLaenge, int aBreite) : laenge(aLaenge), breite(aBreite)
    {
        a_ptr = new Building[laenge * breite];
        for (int i = 0; i < (laenge * breite); i)
        {
            a_ptr[i] = le;
            i++;
        }
        return;
    }

    void build();
    void clearArea();
    void showPlan();
    Blueprint startNewPlan(vector<Blueprint>& planSpeicher);
    void showAllPlans(vector<Blueprint>& planSpeicher);
    float kennzahl();

    //Functor
    bool operator()(Building* planAlt, Building* planNeu);

};

class CapacitySim
{
public:
    int laenge;
    int breite;

    vector<Blueprint> planSpeicher;

    CapacitySim(int aLaenge, int aBreite) : laenge(aLaenge), breite(aBreite) {
        return;
    }

    void runCapacitySim();

};

bool operator<(const Material& c1, const Material& c2) {
    return c1.preis < c2.preis;
}




