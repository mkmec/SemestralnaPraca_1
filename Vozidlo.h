#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/linked_list.h"
#include <string>
#include "Datum.h"
#include "Zasielka.h"

using namespace std;

class Vozidlo
{
private:
	structures::LinkedList<string> *trasa_;
	std::string spz_;
	double nosnost_;
	double naklady_;
	double celkoveNaklady_;
	Datum datum_;
	double hmotnostZvoz_, hmotnostRozvoz_, aktualnaHmotnost_;
	structures::LinkedList<Zasielka*> *zasielky_;

	
public:
	void setAktualnaHmotnost(double hmotnost);
	double getAktualnaHmotnost();
	structures::LinkedList<Zasielka*>* getZasielky();
	void setCelkoveNaklady(int pocetPrekldisk);
	void pridajZasielkuNaRozvoz(Zasielka *zasielka);
	void setHmotnostRozvoz(double hmotnost);
	void setHmotnostZvoz(double hmotnost);
	int getDlzkaTrasy();
	string getTrasa();
	double getNaklady();
	string getSpz();
	double getNosnost();
	double getHmotnostZvoz();
	double getHmotnostRozvoz();
	bool patriRegionu(string region);
	void vypisInfo();
	Vozidlo(string spz, double nosnost, double naklady, Datum datum, structures::LinkedList<string> *trasa);
	~Vozidlo();
};

