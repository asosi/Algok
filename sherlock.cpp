#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


// IL VALORE 1 CORRISPONDE A J
// IL VALORE 0 CORRISPONDE A H

//******************************************STRUCT******************************************
struct Serata{
	int scambi;
	vector<int> h;
	vector<int> j;
	int peso;
	int inizio;
};

class Stark{
public:
	int guadagno;
	int costo;

	Stark(int g, int c){
		guadagno = c;
		costo = g;
	}
};

//****************************************HEADER********************************************
void RobertDowneyJr();
void merge(Serata** v, int start, int center, int end);
void mergesort(Serata** v, int start, int end);
int Max(int i, int j);

void Sherlock_markII();

bool TrovaRiga(int riga);
int* FormattaMatrix(int riga);
int SommaElementi(vector<int> v);

void Ironman();
int WarMachine4(int Ri, int Ci, int trav);

void InvertiSegni2(int riga, int colonna);
void InvertiRiga(int riga);
int CalcolaSomma2(int** matrix);

void StampaMatrice(int** matrix, string nome);
void StampaVector(vector<int> v, string nome);
void StampaNotte(vector<int>* matrix, string nome, int somma);

int CalcolaSommaDX(int riga, int posx);
int CalcolaSommaPositiviRiga(int riga);


int WinterIsComing(int i, int trav);
int WinterIsComingII(int trav, int i);
//***************************************VARIABILI******************************************
int serate, momenti, travestimenti;
int veritravestimenti; //si potra togliere questa riga
int** matrice;
int** newMatrice;
int istanti = 0;
int contaSerateTolte = 0;
Serata** listaSerate;
vector<int>* notte;
vector<int>* notteIniziale;
int dimnotte;
int sommaFinale = 0;
int travestimentiInizio;
int istantiSherlock = 0;

int travestimentiSherlock;

int nValoriNeg;
int contaValNeg;

int rigaMax = 0;
vector<int> sommeMax;
vector<Stark*> winterFell;

int maxRiga=0;
int maxTotale = 0;
int travestimentiWinter;

int** grandeInverno;
//*****************************************************************************************

int main(){
	//inizializza tutto
	RobertDowneyJr();

	cout<<"N:"<<serate<<" m:"<<momenti<<" t:"<<travestimenti<<endl;
	cout<<"0->H - 1->J"<<endl<<endl;
	cout<<"istanti prima:"<<istanti<<endl<<endl;

	//FORMATTO LA MATRICE
	for(int i = 0; i < serate - contaSerateTolte; i++){
		newMatrice[i] = FormattaMatrix(i);
	}

	//CHIAMO IL METODO PER RISOLVERE L'ALGORITMO
		cout<<"travestimenti prima di sherlock:"<<travestimenti<<endl;
		travestimentiSherlock = travestimenti;
		Sherlock_markII();
		cout<<"travestimenti dopo sherlock:"<<travestimenti<<endl;
	//cout<<"istanti dopo sherlock:"<<istanti<<endl<<endl;
	

	//calcolo il numero di travestimenti necessari, se = travestimenti che ho, esco e restituisco il totale
	int sommatoria = contaSerateTolte;
	for(int i=0; i<serate-contaSerateTolte;i++)
	sommatoria+= listaSerate[i]->scambi;
	cout<<"MI SERVONO MASSIMO "<< sommatoria << " SCAMBI, E NE HO " << veritravestimenti <<"\n";
	
	if(sommatoria<=veritravestimenti)
		istanti = (serate)*(momenti);

	if(sommatoria <= veritravestimenti){
		int kistanti = istanti;
		kistanti += sommaFinale;

		if(serate == 0)
			kistanti += istantiSherlock;

		cout<<"kistanti:"<<kistanti<<endl;

		ofstream out("output.txt");
		out<<kistanti;
		return 0;
	}
	else{
		Ironman();
		notteIniziale = notte;

		for(int i=0; i<dimnotte; i++){
			for(int k=0; k<notte[i].size(); k++){
				if(notte[i][k] < 0)
					nValoriNeg++;
			}
		}

		contaValNeg = nValoriNeg;
		
		travestimenti -= serate;

		cout<<"travestimenti prima di war:"<<travestimenti<<endl;
		if(travestimenti>0){
			int istanti1;
			for(int i = 0; i < dimnotte; i++){
				if(notte[i][0] < 0 && notte[i][0]<notte[i][notte[i].size()-1]){
					InvertiRiga(i);
					//cout << "scambio: "<< notte[i][0]<< " " << notte[i][notte[i].size()-1]<< endl;
				}
				maxRiga = CalcolaSommaPositiviRiga(i);
				maxTotale = maxRiga;
				travestimentiWinter = travestimenti;
				istanti1 = WarMachine4(i, 0, travestimenti);
			}
			cout<<endl<<"Dopo la WarMAchine istanti:"<<istanti1<<endl;

			cout<<endl<<"winterFell:"<<endl;
			for(int i = 0; i < winterFell.size(); i++){
				cout<<"array "<<i<<": max:"<<winterFell[i]->guadagno<<" vestiti:"<<winterFell[i]->costo<<endl;
			}

			cout<<endl<<"Prima della winter mi rimangono travestimenti:"<<travestimenti<<endl;

			cout << "::::::::::::creo nuova matrice:::::::::::::::::::::::::::::::\n";
			grandeInverno = new int*[travestimenti+1];
			for(int i=0; i< travestimenti+1; i++)
				grandeInverno[i] = new int[winterFell.size()];
			for(int i=0; i<travestimenti+1; i++)
				for(int j=0; j< winterFell.size(); j++)
					grandeInverno[i][j] = -1;
			cout << ":::::::::::::Controllare::::::::::::::::::::::::::::::::::::::\nChiamo WinterIsComingII\n";
			int k = WinterIsComing(0,travestimenti);
			//int k = WinterIsComingII(travestimenti,0);
			cout<<istanti1<<endl;
			istanti+=istanti1;

			k += istantiSherlock;

			cout<<"****************************************************************";
			cout<<endl<<k<<endl;
			cout<<"****************************************************************";
			cout<<endl;

			ofstream out("output.txt");
			out<<k;
			return 0;

		}
		else
			istanti += istantiSherlock;

			cout<<"istanti:"<<istanti<<endl;
			ofstream out("output.txt");
			out<<istanti;
			return 0;
		}

}

//***************************************FUNZIONI******************************************

void StampaMatrice(int** matrix, string nome){

	int k;

	if(nome == "MATRICE")
		k = 0;
	else
		k = contaSerateTolte;

	cout<<nome<<endl;

	for(int i = 0; i < serate - k; i++){
		for(int j = 0; j < momenti; j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
void StampaVector(vector<int> v, string nome){

	cout<<nome;

	for(int i = 0; i < v.size(); i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
}
void StampaNotte(vector<int>* matrix, string nome, int somma){

	cout<<nome<<endl;
	for(int i=0; i<dimnotte; i++){
		for(int k=0; k<matrix[i].size(); k++){
			cout << matrix[i][k] << " ";
		}
		cout << endl;
	}
	cout<<"somma:"<<somma<<endl;
}

//inizializza
void RobertDowneyJr(){
	
	ifstream in ("input.txt");
	in >> serate >> momenti >> travestimenti;
	veritravestimenti = travestimenti; //si potrà togliere questa riga
	matrice = new int*[serate];

	for(int i = 0; i < serate; i++){
		matrice[i] = new int[momenti];
	}

	for(int i = 0; i < serate; i++){
		for(int j = 0; j < momenti; j++){
			char s;
			in >> s;
			if(s == 'J') // la matrice contiene 1 se J e 0 se H
				matrice[i][j] = 1;
			else
				matrice[i][j] = 0;
		}
		
	}

	int k=0;
	newMatrice = new int*[serate];

	for(int i = 0; i < serate; i++){
		newMatrice[i] = new int[momenti];
	}

	for(int i = 0; i < serate; i++){
		if(TrovaRiga(i)){
			if(travestimenti>0){
				travestimenti--;
				matrice[i][0] = -1;
				istanti += momenti;
				contaSerateTolte++;
			}
		}
		else{
			newMatrice[k] = matrice[i];
			k++;
		}
	}
}

void Sherlock_markII(){
	listaSerate = new Serata*[serate-contaSerateTolte];
	for(int i = 0; i < serate-contaSerateTolte; i++){
		listaSerate[i] = new Serata;
	}

	for(int i = 0; i < serate-contaSerateTolte; i++){
		listaSerate[i]->scambi = 0;
		for(int j = 0; j < momenti; j++){
			if(newMatrice[i][j] != 0){
				listaSerate[i]->scambi++;
				if(j%2==0)
					listaSerate[i]->h.push_back(newMatrice[i][j]);
				else
					listaSerate[i]->j.push_back(newMatrice[i][j]);	
			}		
		}
	}	
	vector<int> massimi;

	for(int i = serate-contaSerateTolte-1; i > -1; i--){
		int maxH = SommaElementi(listaSerate[i]->h);
		int maxJ = SommaElementi(listaSerate[i]->j);
		if(maxH > maxJ){
			listaSerate[i]->peso = maxH;
			listaSerate[i]->inizio = 0;
		}
		else{				
			listaSerate[i]->peso = maxJ;
			listaSerate[i]->inizio = 1;
		}
	}

	mergesort(listaSerate,0,(serate-contaSerateTolte)-1);

	for(int i = 0; i < serate-contaSerateTolte; i++){
		int maxH = SommaElementi(listaSerate[i]->h);
		int maxJ = SommaElementi(listaSerate[i]->j);
		if(maxH > maxJ){
			massimi.push_back(maxH);
		}
		else{				
			massimi.push_back(maxJ);
		}
	}

	StampaVector(massimi,"massimi: ");

	for(int i = 0; i < massimi.size(); i++){
		if(massimi[i]!=0)
		if(travestimentiSherlock>0){
			//cout<<massimi[i]<<endl;
			istantiSherlock += massimi[i];
			//cout<<"travestimenti in sherlock:"<<travestimenti<<endl;
			travestimentiSherlock--;
		}
	}
	
}

int SommaElementi(vector<int> v){
	int somma = 0;
	for(int i = 0; i < v.size(); i++)
		somma += v[i];
	return somma;
}
int SommaElementi2(vector<int> v){
	int somma = 0;
	for(int i = 0; i < v.size(); i++)
		if(v[i]>0)
		somma += v[i];
	return somma;
}

//metodo che formatta le righe della matrice es. 0001111 -> 34
int* FormattaMatrix(int riga){
	int* array = new int[momenti];

	for(int i = 0; i < momenti; i++)
		array[i] = 0;

	int valAt = -1;

	int z = -1;

	for(int j = 0; j < momenti; j++){
		if(newMatrice[riga][j] != valAt){
			valAt = newMatrice[riga][j];
			z++;
		}

		array[z]++;
	}

	return array;
}

//metodo che data una riga restituisce true se è formata da tutti 0 o tutti 1
bool TrovaRiga(int riga){
	int h = matrice[riga][0];
	for(int i = 1; i < momenti; i++){
		if(matrice[riga][i] != h)
			return false;
	}
	return true;
}

//trova il massimo tra due interi
int Max(int i, int j){
	if(i>j)
		return i;
	else
		return j;
}

//ORDINAMENTO CON MERGE SORT
void merge(Serata** v, int start, int center, int end){
  	int s = start;
  	int c = center+1;
  	Serata* supp[end-start];
  	int i = 0;
	while(s<=center && c<=end){
		if(v[s]->peso > v[c]->peso){
    		supp[i] = v[s];
      		s++;
    	}
    	else{
      		supp[i] = v[c];
      		c++;
    	}
    	i++;
  	}
  	while(s<=center){
    	supp[i] = v[s];
    	s++;
    	i++;
  	}
  	while(c<=end){
    	supp[i] = v[c];
    	c++;
    	i++;
  	}
  	for(int i=start; i<=end; i++)
    	v[i] = supp[i-start];
}
void mergesort(Serata** v, int start, int end){
  if(start<end){
    int center = (start+end)/2;
    mergesort(v,start,center);
    mergesort(v,center+1,end);
    merge(v,start,center,end);
  }
}

//mette valori negativi
void Ironman(){
	int x = 0;
	for(int i=0; i<serate-contaSerateTolte; i++){
		if(listaSerate[i]->scambi != 1){
			x++;
		}
	}
	dimnotte = x;
	notte = new vector<int>[dimnotte];
	x=0;
	for(int i=0; i<serate-contaSerateTolte; i++){
		if(listaSerate[i]->scambi != 1){
			if(listaSerate[i]->inizio==0){
				for(int k=0; k<listaSerate[i]->j.size(); k++){
					cout << "son qui\n";
					notte[x].push_back(listaSerate[i]->h[k]);
					notte[x].push_back(0-listaSerate[i]->j[k]);
				}
				if(listaSerate[i]->h.size()>listaSerate[i]->j.size())
					notte[x].push_back(listaSerate[i]->h[listaSerate[i]->h.size()-1]);
			}
			else{
				for(int k=0; k<listaSerate[i]->j.size(); k++){
					notte[x].push_back(0-listaSerate[i]->h[k]);
					notte[x].push_back(listaSerate[i]->j[k]);
				}
				if(listaSerate[i]->h.size()>listaSerate[i]->j.size())
					notte[x].push_back(0-listaSerate[i]->h[listaSerate[i]->h.size()-1]);	
			}
			x++;
		}
	}
	for(int i=0; i<dimnotte; i++){
		for(int k=0; k<notte[i].size(); k++){
			cout << notte[i][k] << " ";
		}
		cout << endl;
	}
}

int WarMachine4(int Ri, int Ci, int trav){
	int sol = 0;
	int poY = 0;
	int primoNeg = -1;
	int contaN = 0;
	if(trav == 0){
		//cout<<"esco"<<endl;
		return maxTotale;
	}
	else{
		for(int i = 0; i < notte[Ri].size(); i++){
			if(notte[Ri][0] < 0 && notte[Ri][0]<notte[Ri][notte[Ri].size()-1])
					InvertiRiga(i);
			if(notte[Ri][i]<0){
				if(primoNeg==-1){
					//cout<<"entro in quel cazzo di if: e i="<<i<<endl;
					poY = i;
					primoNeg++;
				}
				contaN++;
				int soluz = CalcolaSommaDX(Ri,i);
				cout<< notte[Ri][i] << " ha:"<<soluz<<" come somma a dx"<<endl;
				//cout<<"sol:"<<sol<<" soluz:"<<soluz<<endl;

				if(sol > soluz){
					poY = i;
					sol = soluz;
				}
			}
		}
		cout << "------------prendo: " << notte[Ri][poY] << " con somma dx: "<< sol <<"--------------\n";

		if(contaN > -1){
			//cout<<"posy"<<poY<<"primoNeg:"<<primoNeg<<endl;
			InvertiSegni2(Ri,poY);

			//cout<<endl;
			//StampaNotte(notte,"notte:",0);
			//cout<<endl;


			trav--;
			int maxT = CalcolaSommaPositiviRiga(Ri);

			if(maxT > maxTotale){
				maxTotale = maxT;
				winterFell.push_back(new Stark(travestimentiWinter-trav,maxTotale - maxRiga));//MODIFICATO, primo parametro era: travestimentiWinter-trav
				maxRiga = maxTotale;
				travestimentiWinter = trav;
			}

			//cout<<"max:"<<max<<" trav:"<<trav<<endl;

			WarMachine4(Ri,poY+1,trav);	
		}	
	}
}

void OrdinaPertravestimenti(){

	//MODIFICARE LA MERGE IN MODO CHE MI ORDINA WINTERFELL PER TRAVESTIMENTI
}

int CalcolaSommaDX(int riga, int posx){
	int s = 0;
	for(int j = posx; j < notte[riga].size(); j++)
		s += notte[riga][j];
	return s;
}

int CalcolaSommaPositiviRiga(int riga){
	int s = 0;
	for(int i = 0; i < notte[riga].size(); i++)
		if(notte[riga][i]>0)
			s += notte[riga][i];
	return s;
}

void InvertiSegni2(int riga, int colonna){
	for(int k=colonna; k<notte[riga].size(); k++){
		notte[riga][k] = 0-notte[riga][k];
	}
}

void InvertiRiga(int riga){
	for(int i = 0; i < notte[riga].size()/2; i++){
		int aiuto = notte[riga][i];
		notte[riga][i] = notte[riga][notte[riga].size()-1-i];
		notte[riga][notte[riga].size()-1-i] = aiuto;
	}
}

int WinterIsComing(int i, int trav){
	if(i < winterFell.size() && trav > 0){
		if(trav-winterFell[i]->costo>=0)
			return Max(WinterIsComing(i+1,trav-winterFell[i]->costo)+winterFell[i]->guadagno, WinterIsComing(i+1,trav));
		else
			return WinterIsComing(i+1,trav);
	}
	else
		return 0;
}


int WinterIsComingII(int trav, int i){
  if(trav<=0)
    return 0;
  if(i==winterFell.size())
    return 0;
  if(grandeInverno[trav][i]!=-1)
    return grandeInverno[trav][i];
  if(trav-winterFell[i]->costo>=0)
  	grandeInverno[trav][i]= Max(WinterIsComingII(trav-winterFell[i]->costo,i+1)+winterFell[i]->guadagno,WinterIsComingII(trav,i+1));
  return grandeInverno[trav][i];
}
//******************************************************************************************