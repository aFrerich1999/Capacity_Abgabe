#pragma once
using namespace std;

class Material
{
public:
    int preis;
    string ausgabe;

};


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
    //static int preis;
    //static string ausgabe;
};

class Kunststoff : public Material
{
public:
    Kunststoff()
    {
        preis = 30000;
        ausgabe = "Kunststoff";
    }
    //static int preis;
    //static string ausgabe;
};

class Building
{
public:
    int grundPreis; //pro Quadratmeter
    string label;
    Material materialListe[4];
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
    }

};


class Wasserkraftwerk : public Building
{
public:
    Wasserkraftwerk()
    {
        grundPreis = 100000;
        label = "WA ";
        materialListe[0] = h;
        materialListe[1] = h;
        materialListe[2] = m;
        materialListe[3] = k;

    }

};


class Windkraftwerk : public Building
{
public:
    Windkraftwerk()
    {
        grundPreis = 200000;
        label = "WI ";
        materialListe[0] = h;
        materialListe[1] = m;
        materialListe[2] = m;
        materialListe[3] = k;

    }

};

class Solarpanele : public Building
{
public:
    Solarpanele()
    {
        grundPreis = 300000;
        label = "S0 ";
        materialListe[0] = h;
        materialListe[1] = m;
        materialListe[2] = k;
        materialListe[3] = k;

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







