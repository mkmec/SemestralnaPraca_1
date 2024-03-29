#pragma once
#include "structures/heap_monitor.h"
#include "Datum.h"
#include "Vozidlo.h"
#include "Prekladisko.h"
#include "Objednavka.h"
#include "structures/list/array_list.h"

using namespace std;
using namespace structures;

class Spolocnost
{
private:
	Datum datum_;
	bool run_;
	int cisloObjednavky_ = 100;
	ArrayList<Vozidlo*> *vozidla_;
	ArrayList<Prekladisko*> *prekladiska_;
	ArrayList<Objednavka*> *objednavky_;
	

	void vypisMenu();
	int skontrolujInt();
	Prekladisko* getPrekladisko(string okres);
	bool overDolet(int topDron, double vzdialenost);
	bool overNosnost(int topDron, double hmotnost);
	Vozidlo* overNosnostAutaZvoz(string okres, double hmotnost);
	Vozidlo* overNosnostAutaRozvoz(string okres, double hmotnost);
	Dron* getDostupnyDron(double hmotnost, Prekladisko *prekladisko, double vzdialenost);
	Dron* getDostupnyDron(double hmotnost, Prekladisko *prekladisko, Dron *dron, double vzdialenost);
	void pridajVozidlo();
	void vypisVozidla();
	void pridajDronDoPrekladiska();
	void vypisDronyVPrekladisku();
	void pridajObjednavku(int cisloObjednavky);
	void vylozDrony();
	void navratVozidielDoCentralnehoSkladu();
	void nalozenieVozidielVCentralnomSklade();
	void transportZasielokDoLokalnychPrekladisk();
	void naplanujRozvozZasielok();
	void dorucZasielky();
	void vypisStatistiky();
	void zapisDoSuboru();
	void nacitajZoSuboru();


public:
	void vyber();
	Spolocnost(Datum datum);
	~Spolocnost();
};

