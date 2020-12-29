#include<iostream>
#include<string>
#include <fstream>
#include <exception>
#include <vector>
using namespace std;
class Vehicule
{
protected:
	string marca;
	string model;
	static int nrVehicule;
	const int codVehicul;
	int reparatii;
	string* dataReparatiei;
	int* costReparatie;
	bool stareaVehiculelor;
	int stocuriDeLivrat;
public:
	//constructorul implicit
	Vehicule() :codVehicul(++nrVehicule) {
		this->marca = "Neidentificat";
		this->model = "neidentificat";
		this->reparatii = 0;
		this->costReparatie = NULL;
		this->dataReparatiei = NULL;
		this->stareaVehiculelor = false;
		this->stocuriDeLivrat = 0;
	}
	//constructor cu parametri(fara reparatii).............
	Vehicule(string marca, string model, bool stareaVehiculelor, int stocuri) :codVehicul(++nrVehicule) {
		this->marca = marca;
		this->model = model;
		this->stareaVehiculelor = stareaVehiculelor;
		this->reparatii = 0;
		this->costReparatie = NULL;
		this->dataReparatiei = NULL;
		this->stocuriDeLivrat = stocuri;

	}
	//constructor cu parametri cu reparatii
	Vehicule(string marca, string model, bool stareaVehiculelor, int stocuri, int nrReparatii, string* dataReparatiei, int* costReparatie) :codVehicul(++nrVehicule)
	{
		this->marca = marca;
		this->model = model;
		this->stareaVehiculelor = stareaVehiculelor;
		this->reparatii = nrReparatii;
		this->costReparatie = costReparatie;
		this->dataReparatiei = dataReparatiei;
		this->stocuriDeLivrat = stocuri;

	}

	//constructor de copiere
	Vehicule(const Vehicule& v) : codVehicul(v.codVehicul) {
		this->marca = v.marca;
		this->model = v.model;
		this->stareaVehiculelor = v.stareaVehiculelor;
		this->reparatii = v.reparatii;
		this->dataReparatiei = new string[this->reparatii];
		this->costReparatie = new int[this->reparatii];
		for (int i = 0; i < this->reparatii; i++) {
			this->costReparatie[i] = v.costReparatie[i];
			this->dataReparatiei[i] = v.dataReparatiei[i];
		}
		this->stocuriDeLivrat = v.stocuriDeLivrat;

	}
	~Vehicule()
	{
		if (this->dataReparatiei != NULL) delete[] this->dataReparatiei;
		if (this->costReparatie != NULL) delete[] this->costReparatie;

	}
	//setteri si getteri
	void setMarca(string marca)
	{
		if (marca.size() <= 2) throw "Prea scurt!";
		else
			this->marca = marca;
	}

	string getMarca()
	{
		return this->marca;
	}
//........................
	void setModel(string model)
	{
		if (model.size() <= 2) throw "Modelul este prea scurt!";
		else
			this->model = model;
	}

	string getModel()
	{
		return this->model;
	}
	//.............................
	void setstocuriDeLivrat(int stocuri)
	{
		if (stocuri > 0)
			this->stocuriDeLivrat = stocuri;
		else
			throw "Invalid";
	}

	int getStocuriDeLivrat()
	{
		return this->stocuriDeLivrat;
	}
	//...................................
	void setStareaVehiculelor(bool stareaVehiculelor)
	{
		if (stareaVehiculelor == 1)
			this->stareaVehiculelor = 1;
		if (stareaVehiculelor == 0)
			this->stareaVehiculelor = 0;
		if (stareaVehiculelor != 1 and stareaVehiculelor != 0)
			throw "Eroare";
	}

	bool getStareaVehiculelor() {
		return this->stareaVehiculelor;
	}
	//functie care adauga o reparatie 
	void addReparatie(int cost, string data)
	{
		if (data.size() != strlen("YYYY/MM/DD"))
			throw "Data invalida!";
		if (cost < 0 or cost > 10000)
			throw "Costul invalid!";

		this->reparatii++;

		int* nou = new int[reparatii];
		string* nou1 = new string[reparatii];

		for (int i = 0; i < reparatii - 1; i++)
		{
			nou[i] = costReparatie[i];
			nou1[i] = dataReparatiei[i];
		}
		nou[reparatii - 1] = cost;
		nou1[reparatii - 1] = data;
		delete[] dataReparatiei;
		delete[] dataReparatiei;
		dataReparatiei = nou1;
		costReparatie = nou;
	}
	//Supraincarcare <<

	friend ostream& operator<<(ostream& out, Vehicule& v)
	{
		out << "Cod: " << v.codVehicul << endl;
		out << "Marca: " << v.marca << endl;
		out << "Model: " << v.model << endl;
		out << "Numar de reparatii: " << v.reparatii << endl;
		if (v.reparatii > 0)
		{
			for (int i = 1; i <= v.reparatii; i++)
				out << "Reparat " << i << "la data " << "data = " << v.dataReparatiei[i - 1]
				<< " cost = " << v.costReparatie[i - 1] << endl;
		}
		out << "Stare vehicul " << v.stareaVehiculelor << endl;
		out << "Stocuri de livrat: " << v.stocuriDeLivrat << endl;
		return out;
	}

	friend ofstream& operator<<(ofstream& out, Vehicule& v)
	{
		out << "Model: " << v.model << endl;
		out << "Cod: " << v.codVehicul << endl;
		out << "Marca: " << v.marca << endl;
		out << "Numar reparatii: " << v.reparatii << endl;
		if (v.reparatii > 0)
		{
			for (int i = 1; i <= v.reparatii; i++)
				out << "Reparat " << i << ": " << "data = " << v.dataReparatiei[i - 1] << " cost = " << v.costReparatie[i - 1] << endl;
		}
		out << "Stare functionare: " << v.stareaVehiculelor << endl;
		out << "Stocuri de livrat: " << v.stocuriDeLivrat << endl;
		return out;
	}
	//supraincarcare>>

	friend istream& operator>>(istream& in, Vehicule& v)
	{
		cout << "Marca: "; in >> v.marca;
		cout << "Model: "; in >> v.model;
		cout << "Numar reparatii: "; in >> v.reparatii;

		if (v.dataReparatiei != NULL or v.costReparatie != NULL)
		{
			delete[] v.dataReparatiei;
			delete[] v.costReparatie;
		}
		v.dataReparatiei = new string[v.reparatii];
		v.costReparatie = new int[v.reparatii];

		for (int i = 0; i < v.reparatii; i++) {
			cout << "Reparatia " << i + 1 << endl << "Data(YYYY/MM/DD): ";
			in >> v.dataReparatiei[i];
			cout << "Cost: ";
			in >> v.costReparatie[i];
		}
		cout << "Starea de functionare a vehiculelor (1/0): ";
		in >> v.stareaVehiculelor;

		cout << "Stocuri de livrat: ";
		in >> v.stocuriDeLivrat;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Vehicule& v)
	{

		getline(in, v.marca);
		getline(in, v.model);
		in >> v.reparatii;
		if (v.dataReparatiei != NULL or v.costReparatie != NULL)
		{
			delete[] v.dataReparatiei;
			delete[] v.costReparatie;
		}
		v.dataReparatiei = new string[v.reparatii];
		v.costReparatie = new int[v.reparatii];
		for (int i = 0; i < v.reparatii; i++) {
			in >> v.dataReparatiei[i];
			in >> v.costReparatie[i];
		}
		in >> v.stareaVehiculelor;
		in >> v.stocuriDeLivrat;
		return in;
	}
	
	//supraincarcare indexare
	/*int& operator[](int i) {
		if (i >= 0 and i < this->reparatii)
			return this->reparatii[i];
		else
			exit(1);
	}*/
	//supraincarcare +
	void operator+(Vehicule v) {
		this->stocuriDeLivrat += v.stocuriDeLivrat;

	}

	void operator-(Vehicule v) {
		this->stocuriDeLivrat -= v.stocuriDeLivrat;

	}
	// supraincarcare operator -- cu ambele forme

	Vehicule& operator--() {
		this->stocuriDeLivrat--;
		return *this;
	}

	Vehicule& operator--(int n) {
		this->stocuriDeLivrat--;
		return *this;
	}

	// supraincarcare operator ++ cu abele forme
	Vehicule& operator++() {
		this->stocuriDeLivrat++;
		return *this;
	}

	Vehicule& operator++(int n) {
		this->stocuriDeLivrat++;
		return *this;
	}
	//supraincarcare !
	bool operator!()
	{
		if (this->costReparatie != NULL)
			return false;
		else
			return true;
	}
	//supraincarcare >=
	bool operator>=(Vehicule v)
	{
		if (this->codVehicul >= v.codVehicul)
			return true;
		else return false;

	}
	//supraincarcare ==
	bool operator==(Vehicule v) {
		if (this->marca == v.marca and this->model == v.model and this->codVehicul == v.codVehicul)
			return true;
		else
			return false;
	}
}
;
class Depozite {
protected:
	char* denumire;
	char* adresa;
	int suprafata;
	int coleteInDepozit;
	int numarLivrari;
	int* istoricLivrari;
	const int codDepozit;
	static int numarDepozite;

public:
	//constructor fara parametrii
	Depozite() :codDepozit(++numarDepozite) {
		this->denumire = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		this->adresa = new char[strlen("Necunoscut") + 1];
		strcpy(this->adresa, "Necunoscut");
		this->suprafata = 0;
		this->coleteInDepozit = 0;
		this->numarLivrari = 0;
		this->istoricLivrari = NULL;

	}
	//constructor cu parametrii fara istoric de livrari

	Depozite(const char* denumire, const char* adresa, int suprafata, int coleteInDepozit) :codDepozit(++numarDepozite) {
		this->denumire = new char[strlen(denumire) + 1];
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->denumire, denumire);
		strcpy(this->adresa, adresa);
		this->suprafata = suprafata;
		this->coleteInDepozit = coleteInDepozit;
		this->numarLivrari = 0;
		this->istoricLivrari = NULL;

	}
	//constructor 
	Depozite(const char* denumire, const char* adresa, int suprafata, int coleteInDepozit, int numarLivrari, int* istoricLivrari) :codDepozit(++numarDepozite)
	{
		this->denumire = new char[strlen(denumire) + 1];
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->denumire, denumire);
		strcpy(this->adresa, adresa);
		this->suprafata = suprafata;
		this->coleteInDepozit = coleteInDepozit;
		this->numarLivrari = numarLivrari;
		this->istoricLivrari = new int[numarLivrari];
		for (int i = 0; i < numarLivrari; i++)
			this->istoricLivrari[i] = istoricLivrari[i];
	}

	//constructor de copiere
	Depozite(const Depozite& d) :codDepozit(d.codDepozit) {
		this->denumire = new char[strlen(d.denumire) + 1];
		this->adresa = new char[strlen(d.adresa) + 1];
		strcpy(this->denumire, d.denumire);
		strcpy(this->adresa, d.adresa);
		this->suprafata = d.suprafata;
		this->coleteInDepozit = d.coleteInDepozit;
		this->numarLivrari = d.numarLivrari;
		this->istoricLivrari = new int[d.numarLivrari];
		for (int i = 0; i < d.numarLivrari; i++)
			this->istoricLivrari[i] = d.istoricLivrari[i];


	}
	//destructor
	~Depozite() {
		if (this->istoricLivrari != NULL)
			delete[] this->istoricLivrari;
		this->numarDepozite--;
	}


	//setteri si getteri
	void setDenumire(const char* denumire) {
		if (strlen(denumire) > 2)
		{
			delete[] denumire;
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else
			throw "Data invalida";
	}
	const char* getDenumire() {
		return this->denumire;
	}
	void setAdresa(const char* adresa) {
		if (strlen(adresa) > 2)
		{
			delete[] this->adresa;
			this->adresa = new char[strlen(adresa) + 1];
			strcpy(this->adresa, adresa);
		}
		else
			throw "Data invalida";

	}
	const char* getAdresa() {
		return this->adresa;
	}
	void setSuprafata(int suprafata) {
		if (suprafata > 0 and suprafata < 50000)
			this->suprafata = suprafata;
		else
			throw "Data invalida";
	}
	int getSuprafata()
	{
		return this->suprafata;
	}
	void setColeteInDepozit(int coleteInDepozit) {
		if (coleteInDepozit > 0 and coleteInDepozit < 50000)
			this->coleteInDepozit = coleteInDepozit;
		else
			throw "Data invalida";
	}
	int getColeteInDepozit() {
		return this->coleteInDepozit;
	}
	void setIstoricLivrari(int* istoricLivrari, int numarLivrari) {
		if (numarLivrari > 0 and numarLivrari < 5000)
		{
			if (this->istoricLivrari != NULL)
				delete[] istoricLivrari;
			this->istoricLivrari = istoricLivrari;
		}
		else
			throw "Date invalide";
	}
	int getNumarLivrari() {
		return this->numarLivrari;
	}
	int* getIstoricLivrari() {
		return this->istoricLivrari;
	}
	friend istream& operator>>(istream& in, Depozite& d)
	{
		char denumire1[50], adresa1[50];
		cout << "Denumire: ";
		in >> denumire1;
		cout << "Adresa: ";
		in >> adresa1;
		if (d.denumire != NULL)
		{
			delete[] d.denumire;
		}
		d.denumire = new char[strlen(denumire1) + 1];
		strcpy(d.denumire, denumire1);
		if (d.adresa != NULL)
		{
			delete[] d.adresa;
		}
		d.adresa = new char[strlen(adresa1) + 1];
		strcpy(d.adresa, adresa1);
		cout << "Suprafata: ";
		in >> d.suprafata;
		cout << "Colete in Depozit: ";
		in >> d.coleteInDepozit;
		cout << "Numar Livrari: ";
		in >> d.numarLivrari;
		if (d.istoricLivrari != NULL)
		{
			delete[] d.istoricLivrari;
		}
		d.istoricLivrari = new int[d.numarLivrari];
		for (int i = 0; i < d.numarLivrari; i++)
		{
			cout << "Livrarea " << i + 1 << ": ";
			in >> d.istoricLivrari[i];
		}
		return in;
	}

	friend ifstream& operator>>(ifstream& in, Depozite& d)
	{
		char denumire1[50], adresa1[50];

		in.getline(denumire1, 50);

		in.getline(adresa1, 50);
		if (d.denumire != NULL)
		{
			delete[] d.denumire;
		}
		d.denumire = new char[strlen(denumire1) + 1];
		strcpy(d.denumire, denumire1);
		if (d.adresa != NULL)
		{
			delete[] d.adresa;
		}
		d.adresa = new char[strlen(adresa1) + 1];
		strcpy(d.adresa, adresa1);
		in >> d.suprafata;
		in >> d.coleteInDepozit;
		in >> d.numarLivrari;
		if (d.istoricLivrari != NULL)
		{
			delete[] d.istoricLivrari;
		}

		d.istoricLivrari = new int[d.numarLivrari];
		for (int i = 0; i < d.numarLivrari; i++)
		{
			in >> d.istoricLivrari[i];
		}
		return in;
	}

	//supraincarcare <<
	friend ostream& operator<<(ostream& out, Depozite& d)
	{
		out << "Cod depozit: " << d.codDepozit << endl;
		out << "Denumire: " << d.denumire << endl;
		out << "Adresa: " << d.adresa << endl;
		out << "Suprafata:" << d.suprafata << endl;
		out << "Colete in depozit: " << d.coleteInDepozit << endl;
		out << "Numar livrari: " << d.numarLivrari << endl;
		if (d.numarLivrari > 0)
		{
			for (int i = 0; i < d.numarLivrari; i++)
				out << "Livrarea " << i + 1 << ": " << d.istoricLivrari[i] << endl;
		}
		return out;
	}

	friend ofstream& operator<<(ofstream& out, Depozite& d) {
		out << "Cod depozit: " << d.codDepozit << endl;
		out << "Denumire: " << d.denumire << endl;
		out << "Adresa: " << d.adresa << endl;
		out << "Suprafata:" << d.suprafata << endl;
		out << "Colete in depozit: " << d.coleteInDepozit << endl;
		out << "Numar livrari: " << d.numarLivrari << endl;
		if (d.numarLivrari > 0)
		{
			for (int i = 0; i < d.numarLivrari; i++)
				out << "Livrarea " << i + 1 << ": " << d.istoricLivrari[i] << endl;
		}
		return out;
	}

	//operator !
	bool operator!()
	{
		if (this->istoricLivrari != NULL)
			return false;
		else
			return true;
	}

	//supraincarcare >=
	bool operator>=(Depozite d)
	{
		if (this->coleteInDepozit >= d.coleteInDepozit)
			return true;
		else return false;

	}
	//supraincarcare +
	void operator+(Depozite d) {
		this->coleteInDepozit += d.coleteInDepozit;

	}
	//supraincarcare ==
	bool operator==(Depozite d) {
		if (this->denumire == d.denumire and this->adresa == d.adresa and this->coleteInDepozit == d.coleteInDepozit)
			return true;
		else
			return false;
	}

	//supraincarcare operator++ cu ambele forme
	Depozite& operator++() {
		this->coleteInDepozit++;
		return *this;
	}

	Depozite& operator++(int n) {
		this->coleteInDepozit++;
		return *this;
	}
	//supraincarcare operator-- cu ambele forme

	Depozite& operator--() {
		this->coleteInDepozit--;
		return *this;
	}

	Depozite& operator--(int n) {
		this->coleteInDepozit--;
		return *this;
	}
	int operator[](int i) {
		if (i >= 0 and i < this->numarLivrari)
			return this->istoricLivrari[i];
		else
			exit(1);
	}
	//supraincarcare *
	void operator*(int x) {

		this->coleteInDepozit = this->coleteInDepozit * x;
	}
	//supraincarcare =
	Depozite& operator=(const Depozite& d) {
		if (this->denumire != NULL)
			delete[] denumire;
		if (this->adresa != NULL)
			delete[] adresa;

		this->denumire = new char[strlen(d.denumire) + 1];
		strcpy(this->denumire, d.denumire);
		this->adresa = new char[strlen(d.adresa) + 1];
		strcpy(this->adresa, d.adresa);
		this->suprafata = d.suprafata;
		this->coleteInDepozit = d.coleteInDepozit;
		this->numarLivrari = d.numarLivrari;
		this->istoricLivrari = new int[this->numarLivrari];
		for (int i = 0; i < this->numarLivrari; i++)
			this->istoricLivrari[i] = d.istoricLivrari[i];
		return *this;
	}
	//Functii de prelucrare si afisare
	int capacitateMaximaStocare() {
		return this->suprafata * 10;

	}
	int venitLivrari() {
		return this->numarLivrari * 4;
	}
};
//clasa pentru relatia HAS-a
class Onomastica {
private:
	int zi;
	int luna;
	int an;
public:

	void setData(int zi, int luna, int an) {
		this->zi = zi;
		this->luna = luna;
		this->an = an;
	}

	void getDataNastere() {
		cout << "Data nastere: " << this->zi << "/" << luna << "/" << an << endl;
	}

};
//clasaabstracta
class Angajat {
protected:
	string nume;
	string prenume;
	int salariuBaza;
	int salariuFinal = 0;
	Onomastica o;
public:
	string getNume() {
		return this->nume;
	}
	string getPrenume() {
		return this->prenume;
	}
	int getSalariuBaza() {
		return this->salariuBaza;
	}
	int getSalariuFinal() {
		return this->salariuFinal;
	}
	void setNume(string x) {
		this->nume = x;
	}
	void setPrenume(string x) {
		this->prenume = x;
	}
	void setSalariuBaza(int x) {
		this->salariuBaza = x;
	}
	void setDataNastere(int zi, int luna, int an) {
		o.setData(zi, luna, an);
	}
	void afisareDataNastere() {
		o.getDataNastere();
	}


	virtual void calculSalariu() = 0;

	Angajat(string nume, string prenume, int salariu) {
		this->nume = nume;
		this->prenume = prenume;
		this->salariuBaza = salariu;
	}
	friend ostream& operator<<(ostream& out, Angajat& a) {
		out << "Nume: " << a.nume << endl;
		out << "Prenume: " << a.prenume << endl;
		out << "salariuBaza " << a.salariuBaza << endl;
		return out;

	}
};
//Interfata cu o functie virtuala
class IAfisare {
	virtual void afisare() = 0;
};

class AgentPaza :public Angajat, public IAfisare {
	int oreLucrateLunar;
public:
	AgentPaza(string nume, string prenume, int salariu, int ore) :Angajat(nume, prenume, salariu) {
		this->oreLucrateLunar = ore;
	}
	void calculSalariu() override {
		this->salariuFinal = salariuBaza + 20 * this->oreLucrateLunar;
	}
	void afisare() override {
		cout << *this;
		cout << "Numar ore lucrate in aceasta luna: " << this->oreLucrateLunar << endl << "Salariul final: " << this->salariuFinal << endl;

	}
};
int main() 
{
	cout << "Faza 1 Proiect" << endl << endl;
	cout << "TESTARE CLASA VEHICULE" << endl;
	Vehicule v1;
	cout << "Testare constructor implicit si supraincarcarea operatorului <<" << endl << v1 << endl << endl;
	Vehicule v2;
	cout << "Testare supraincarcare operator>>" << endl;
	cout << endl << endl << v2 << endl << endl;
	Vehicule v3("Renault", "Kango", 1, 34);
	cout << "Testare unul dintre cei 2 constructori expliciti(cel fara date despre reparatie)" << endl << "comanda:Vehicul v3(Renault, Kango, 1,34);" << endl << v3 << endl << endl;
	Vehicule v6(v3);
	cout << "Testare constructor de copiere Vehicule v6(v3) si afisarea lui" << endl << v6 << endl;

	int* costtest = new int[2];
	costtest[0] = 564;
	costtest[1] = 906;
	string* datatest = new string[2];
	datatest[0] = "2004/07/19";
	datatest[1] = "2008/03/26";



	/*int* costtest = new int[2];
	costtest[0] = 564;
	costtest[1] = 906;
	string* datatest = new string[2];
	datatest[0] = "2004/07/19";
	datatest[1] = "2008/03/26";*/


	cout << "Testare al doilea constructor cu toate datele" << endl << "comanda:Vehicule v4(Mercedes, Delphin, 1,55, 2, datareparatie, costreparatie);" << endl;
	Vehicule v4("Mercedes", "Delphin", 1, 55, 2, datatest, costtest);
	cout << v4 << endl;

	cout << "Testare setMarca,setModel in v4 si afisare cu getMarca,getModel" << endl;
	v4.setMarca("VW");
	v4.setModel("Transporter");
	cout << "Marca: " << v4.getMarca() << endl
		 << "Model: " << v4.getModel() << endl << endl << endl;

	cout << "Testare set si get stareVehiculelor(setVehicul(0))" << endl;
	v4.setStareaVehiculelor(0);
	cout << "Noua stare de functionare: " << v4.getStareaVehiculelor() << endl << endl << endl;

	;


	cout << "Testare o functie de adaugare reparatie in vector(v4.addReparatie) si cout v4" << endl;
	v4.addReparatie(898, "2020/12/20");
	cout << v4 << endl << endl;


	cout << "Testare !v4 (cout<<!v4)" << endl;
	cout << !v4 << endl;

	
	cout << "Testare operator == " << endl;
	Vehicule v5;
	if (v3 == v5)
		cout << "sunt egale" << endl;
	else
		cout << "nu sunt egale" << endl << endl;


	cout << "Testare operator +" << endl << "stocuri v3: " << v3.getStocuriDeLivrat() << endl << "stocuri v4: " << v4.getStocuriDeLivrat() << endl;
	v3 + v4;
	cout << "stocuri v3 dupa comanda v3+v4: " << v3.getStocuriDeLivrat() << endl;
	
	

	/*cout << "Testare operator de indexare (cout<<v4[1])" << endl;
	cout << v4[1] << endl;*/

	cout << "Testare ++v4,v4++,--v4,v4--" << endl;
	cout << "stocuri v4 initiale: " << v4.getStocuriDeLivrat() << endl;

	++v4; v4++;
	cout << "stocuri v4 dupa comenzile ++v4;v4++; --" << v4.getStocuriDeLivrat() << endl;

	--v4;v4--;
	cout << "dtocuri v4 dupa comenzile --v4;v4--; --" << v4.getStocuriDeLivrat() << endl << endl;
	
	
	//Testare clasa depozite

	cout << "TESTARE CLASA DEPOZITE" << endl << endl;
	Depozite d1;
	cout << "Testare constructor implicit si afisare cu cout<<" << endl << d1 << endl << endl;
	Depozite d2("Central", "Testare", 1000, 27);
	cout << "Testare constructor 1 si afisare cu cout<<" << endl << d2 << endl << endl << endl;
	int* test = new int[3];
	test[0] = 1;
	test[1] = 2;
	test[2] = 3;
	cout << "Testare constructor 2 si afisare cu cout<<" << endl;
	Depozite d3("Central", "Testare", 1000, 27, 3, test);
	cout << d3 << endl << endl;

	Depozite d4(d3);
	cout << "Testare constructor de copiere d4(d3);cout<<d4" << endl << d4 << endl << endl << endl;

	Depozite d5;
	//cin >> d5;
	cout << endl << d5 << endl << endl;
	d4 = d2;
	cout << "Testare operator = (d4=d2);cout << d4" << endl << d4 << endl << endl;


	cout << "Testare operator >=" << endl;
	if (d3 >= d2)
		cout << "d3>=d2" << endl << endl;
	else
		cout << "d3<d2" << endl << endl;
	cout << "Testare operator ==" << endl;
	if (d3 == d2)
		cout << "d3==d2" << endl << endl;
	else
		cout << "d3!=d2" << endl << endl;

	cout << "Testare operator +" << endl << "Comanda: d2+d3" << endl << "Valoare initiala: " << d2.getColeteInDepozit() << endl;
	d2 + d3;
	cout << "Valoare dupa d2+d3: " << d2.getColeteInDepozit() << endl << endl << endl;

	cout << "Testare operator !d2" << endl;
	cout << !d2 << endl << endl;


	cout << "Testare operator[]" << endl << "Comanda: cout<<d3[2]" << endl;
	cout << d3[2] << endl << endl;

	cout << "Testare operatori ++ si -- cu cele 2 forme" << endl;
	cout << "Valoare initiala: " << d3.getColeteInDepozit() << endl; d3++;
	cout << "Valoare dupa d3++: " << d3.getColeteInDepozit() << endl; ++d3;
	cout << "Valoare dupa ++d3: " << d3.getColeteInDepozit() << endl; d3--;
	cout << "Valoare dupa d3--: " << d3.getColeteInDepozit() << endl; --d3;
	cout << "Valoare dpa --d3: " << d3.getColeteInDepozit() << endl << endl << endl;

	cout << "Testare setteri si getteri" << endl;
	d3.setAdresa("test set");
	d3.setColeteInDepozit(59);
	d3.setSuprafata(500);
	cout << "Adresa noua: " << d3.getAdresa() << endl << "Colete in depozit dupa set: " << d3.getColeteInDepozit() << endl << "Suprafata noua: " << d3.getSuprafata() << endl << endl;
	cout << "Testare 2 functii prelucrare" << endl;
	cout << "Functia 1: calculeaza cate colete pot fi depozitate in depozit in functie de suprafata" << endl;
	cout << "Capacitate depozitare: " << d3.capacitateMaximaStocare() << endl;
	cout << "Functia 2: calculeaza cat venit s-a obtinut in functie de numarul de livrari efectuate din depozit" << endl;
	cout << "Venit depozit: " << d3.venitLivrari() << endl << endl << endl;
	
	

}