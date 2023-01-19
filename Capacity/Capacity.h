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



    int grundPreis; //pro Quadratmeter
    string label; 
    std::map<Material, int> myMap;


    //Material materialListe[4];
    Holz h{};
    Kunststoff k{};
    Metall m{};



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

    }
};


class Wasserkraftwerk : public Building
{
public:
    Wasserkraftwerk()
    {
        grundPreis = 100000;
        label = "WA ";
         

        myMap[h] = 2;
        myMap[m] = 1;
        myMap[k] = 1;

    }

};


class Windkraftwerk : public Building
{
public:
    Windkraftwerk()
    {
        grundPreis = 200000;
        label = "WI ";
         

        myMap[h] = 1;
        myMap[m] = 2;
        myMap[k] = 1;

    }

};

class Solarpanele : public Building
{
public:
    Solarpanele()
    {
        grundPreis = 300000;
        label = "S0 ";
         

        myMap[h] = 1;
        myMap[m] = 1;
        myMap[k] = 2;

    }

};



class CapacitySim
{
public:
    int laenge;
    int breite;
    Building building{};
    Wasserkraftwerk wa{};
    Windkraftwerk wi{};
    Solarpanele so{};
    Leer le{};


    CapacitySim(int aLaenge, int aBreite) : laenge(aLaenge), breite(aBreite) {
        return;
    }

    void build(Building* a_ptr);
    void clearArea(Building* a_ptr);
    void showPlan(Building* a_ptr);
    void runCapacitySim();

};


bool operator<(const Material& c1, const Material& c2) {
    return c1.preis < c2.preis;
}




