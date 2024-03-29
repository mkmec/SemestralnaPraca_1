#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include <string>
#include "Dron.h"
#include "Datum.h"


using namespace std;
using namespace structures;

class Prekladisko
{
private:
	string okres_;
	double maxHmotnost_;
	int pocetDorucenychZasielok_, pocetOdoslanychZasielok_;

	ArrayList<Dron*> *drony_;
	LinkedList<Zasielka*> *zasielkyNaOdvoz_;
	LinkedList<Zasielka*> *zasielkyNaRozvoz_;

public:
	int getPocetDorucenych();
	int getPocetOdoslanych();
	void dorucZasielky(Datum datum);
	LinkedList<Zasielka*>* getZasielkyNaRozvoz();
	LinkedList<Zasielka*>* getZasielkyNaOdvoz();
	void vylozDrony(Datum datum);
	ArrayList<Dron*>* getZoznamDronov();
	double getMaxHmotnost();
	Dron* getDron(double hmotnost, Datum *datum, double vzdialenost);
	Dron* getDron(double hmotnost, Datum *datum, Dron *dron_, double vzdialenost);
	//int getTopDron(int pouzitie); //vrati aky najlespi dron je v prekladisku
	void VypisDrony();
	void pridajDron(Dron *dron);
	string getOkres();
	Prekladisko(string okres, double maxHmotnost, int pocetDorucenychZasielok, int pocetOdoslanychZasielok, ArrayList<Dron*> *drony, LinkedList<Zasielka*> *zasielkyNaOdvoz, LinkedList<Zasielka*> *zasielkyNaRozvoz);
	Prekladisko(string okres);
	~Prekladisko();
};

