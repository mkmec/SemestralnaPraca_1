#include "Dron.h"
#include "structures/heap_monitor.h"
#include <iostream>
#include <iomanip>

using namespace structures;
using namespace std;

int Dron::casNaDobitie(int minutyNaPrekladisko) //vrati cas potrebny na nabitie po obsluzeni danej zasielky zaroven aktualizuje cas kedy bude volny po obsluzeni zasielky
{
	int casNaNabitie = 0;

	if (typ_ == 1)
	{
		casNaNabitie = (minutyNaPrekladisko * 2) / 4 * 3;
		if (minutyNaPrekladisko % 4 != 0) casNaNabitie += 3;
		kapacitaBaterie_ -= (minutyNaPrekladisko * 2) / 40;
	}
	else
	{
		casNaNabitie = (minutyNaPrekladisko * 2) / 6 * 5;
		if (minutyNaPrekladisko % 6 != 0) casNaNabitie += 5;
		kapacitaBaterie_ -= (minutyNaPrekladisko * 2) / 60;
	}
	casVolny_ = Datum::pridajMinuty(casVolny_, minutyNaPrekladisko * 2);
	
	return casNaNabitie;
}

double Dron::getNalietaneHodiny()
{
	return nalietaneMinuty_ / (double)60;
}

structures::LinkedList<Zasielka*>* Dron::dorucZasielky(Datum datum) //vrati list zasielok ktore sa maju dorucit po posune casu
{
	LinkedList<Zasielka*> *zasielky = new LinkedList<Zasielka*>;
	LinkedList<Zasielka*> *nedokonceneZasielky = new LinkedList<Zasielka*>;

	for (Zasielka *zasielka : *zasielky_)
	{
		if (zasielka->getDatumAdresat() < datum && zasielka->Vyzdvihnuta())
		{
			pocetPrepravenychZasielok_++;
			zasielky->add(zasielka);			
		}
		else
		{
			nedokonceneZasielky->add(zasielka);
		}
		if (zasielky_->size() == 0) break;
	}
	zasielky_->clear();
	for (Zasielka *zasielka : *nedokonceneZasielky)
	{
		zasielky_->add(zasielka);
		//nedokonceneZasielky->tryRemove(zasielka);
		//if (nedokonceneZasielky->isEmpty()) break;
	}
	nedokonceneZasielky->clear();
	delete nedokonceneZasielky;
	
	return zasielky;
}

void Dron::setKapacitaBaterie(double kapacitaBaterie)
{
	kapacitaBaterie_ = kapacitaBaterie;
}

void Dron::setCasVolnyPoDobiti(int minuty)
{
	casVolny_ = Datum::pridajMinuty(casVolny_, minuty);
}

structures::LinkedList<Zasielka*> *Dron::vylozZasielky(Datum datum) // vrati list zasielok ktore sa maju vylozit na prekladisko pri posune casu
{
	LinkedList<Zasielka*> *zasielky = new LinkedList<Zasielka*>;
	LinkedList<Zasielka*> *nedokonceneZasielky = new LinkedList<Zasielka*>;


	for (Zasielka *zasielka : *zasielky_)
	{
		if (zasielka->getDatumNaLokPrekladisko() < datum && !zasielka->Vyzdvihnuta())
		{
			pocetPrepravenychZasielok_++;
			zasielky->add(zasielka);					
		}
		else
		{
			nedokonceneZasielky->add(zasielka);
		}
		if (zasielky_->size() == 0) break;
	}
	
	zasielky_->clear();

	for (Zasielka *zasielka : *nedokonceneZasielky)
	{
		zasielky_->add(zasielka);
		//nedokonceneZasielky->tryRemove(zasielka);
		//if (nedokonceneZasielky->isEmpty()) break;
	}
	nedokonceneZasielky->clear();
	delete nedokonceneZasielky;
	
	return zasielky;
}

double Dron::getKapacitaBaterie()
{
	return kapacitaBaterie_;
}

string Dron::getInfoNaZapis()
{
	string retazec;

	retazec += to_string(typ_) + " ";
	retazec += to_string(nalietaneMinuty_) + " ";
	retazec += to_string(pocetPrepravenychZasielok_) + " ";
	retazec += datumZaradenia_.naZapis() + " ";
	retazec += casVolny_.naZapis() + " ";
	retazec += serioveCislo_ + " ";
	retazec += to_string(kapacitaBaterie_);
	retazec += " ";
	retazec += to_string(zasielky_->size()) + " ";

	for (Zasielka *zasielka : *zasielky_)
	{
		retazec += zasielka->getZasielkaZapis();
	}

	return retazec;
}

void Dron::pridajZasielku(Zasielka * zasielka, int casNaPrekladisko, Datum datum)
{
	zasielky_->add(zasielka);
	
	int casNaNabitie = casNaDobitie(casNaPrekladisko);;

	zasielka->setCasNaDobitie(casNaNabitie);

	nalietaneMinuty_ += 2 * casNaPrekladisko;

	if (casVolny_ < datum)
	{
		casVolny_ = datum;
	}
	casVolny_ = Datum::pridajMinuty(casVolny_, casNaPrekladisko * 2);
}

Datum Dron::getCasVolny()
{
	int minutyNaDobitie = 0;	
	for (Zasielka *zasielka : *zasielky_)
	{
		minutyNaDobitie += zasielka->getCasNaDobitie();
	}	
	Datum newDatum = Datum::pridajMinuty(casVolny_, minutyNaDobitie);
	return newDatum;
}

int Dron::getTyp()
{
	return typ_;
}

void Dron::vypisInfo()
{
	double nalietaneHodiny = nalietaneMinuty_ / (double)60;
	cout << setw(12) << left << typ_;
	cout << setw(30) << left << nalietaneHodiny;
	cout << setw(30) << left << pocetPrepravenychZasielok_;
	cout << setw(30) << left << datumZaradenia_.toString();
	cout << endl;
}

Dron::Dron(int typ, int nalietaneMinuty, int pocetPrepravenychZasielok, Datum datumZaradenia, Datum casVolny, std::string serioveCislo, double kapacitaBaterie, structures::LinkedList<Zasielka*> *zasielky) :
	typ_(typ),
	nalietaneMinuty_(nalietaneMinuty),
	pocetPrepravenychZasielok_(pocetPrepravenychZasielok),
	datumZaradenia_(datumZaradenia),
	casVolny_(casVolny),
	serioveCislo_(serioveCislo),	
	kapacitaBaterie_(kapacitaBaterie),
	zasielky_(zasielky)
{
}

Dron::Dron(int typ, string serioveCislo, Datum datum):
	typ_(typ),
	serioveCislo_(serioveCislo), 
	pocetPrepravenychZasielok_(0),
	nalietaneMinuty_(0),
	datumZaradenia_(datum),
	casVolny_(datum),
	zasielky_(new structures::LinkedList<Zasielka*>),
	kapacitaBaterie_(1)
{
}


Dron::~Dron()
{
	for (Zasielka *zasielka : *zasielky_)
	{
		delete zasielka;
	}
	delete zasielky_;
}
