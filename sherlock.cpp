#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// IL VALORE 1 CORRISPONDE A J
// IL VALORE 0 CORRISPONDE A H

//***************************************S**STRUCT******************************************
struct Serata{
	int scambi;
	vector<int> h;
	vector<int> j;
	int peso;
	int inizio;
};

//****************************************HEADER********************************************
void RobertDowneyJr();
int ElementareWatson();
void merge(Serata** v, int start, int center, int end);
void mergesort(Serata** v, int start, int end);
int Max(int i, int j);
int Sherlock(int riga, int colonna, int contaT, int valAt);
bool TrovaRiga(int riga);
int* FormattaMatrix(int riga);
int SherlockPack(int riga, int colonna, int contaT, int valAt);
void StampaMatrice(int** matrix, string nome);
void StampaVector(vector<int> v, string nome);
void Sherlock_markII();
int SommaElementi(vector<int> v);
int SommaElementi2(vector<int> v);
void Ironman();
void WarMachine();

void InvertiSegni(int riga, int colonna);
void CalcolaSomma();
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
int contaFine = 0;
int travestimentiInizio;
int posx = 0;
int posy = 0;
int posxIni;
int posyIni;
//*****************************************************************************************

int main(){
	//inizializza tutto
	RobertDowneyJr();

	cout<<"N:"<<serate<<" m:"<<momenti<<" t:"<<travestimenti<<endl;
	cout<<"0->H - 1->J"<<endl<<endl;
	//StampaMatrice(matrice,"MATRICE");
	cout<<"istanti prima:"<<istanti<<endl<<endl;
	//StampaMatrice(newMatrice,"NEW MATRICE");

	//FORMATTO LA MATRICE
	for(int i = 0; i < serate - contaSerateTolte; i++){
		newMatrice[i] = FormattaMatrix(i);
	}

	//StampaMatrice(newMatrice,"MATRICE FORMATTATA");

	//CHIAMO IL METODO PER RISOLVERE L'ALGORITMO
	//istanti += SherlockPack(0,0,0,-1);	
	Sherlock_markII();
	cout<<"istanti dopo sherlock:"<<istanti<<endl<<endl;
	

	Ironman();
	notteIniziale = notte;

	travestimentiInizio = travestimenti;
	for(int i=0; i<dimnotte; i++){
		for(int k=0; k<notte[i].size(); k++){
			if(notte[i][k] < 0)
				contaFine++;
		}
	}

	cout<<travestimenti<<endl;
	if(travestimenti>0){
		CalcolaSomma();
		WarMachine();
	}


	//int sommatoria = contaSerateTolte;
	//for(int i=0; i<serate-contaSerateTolte;i++)
	//sommatoria+= listaSerate[i]->scambi;
	//cout<<"MI SERVONO MASSIMO "<< sommatoria << " SCAMBI, E NE HO " << veritravestimenti <<"\n";
	//if(sommatoria==veritravestimenti)
	//	istanti = (serate)*(momenti);

	//istanti += sommaFinale;

	cout<<"istanti:"<<istanti<<endl;
	ofstream out("output.txt");
	out<<istanti;
	return 0;
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

//caso base
int ElementareWatson(){
	vector<int> contaJ;
	vector<int> contaH;
	
	int coH =0; 
	int coJ = 0;

	for(int i = 0; i < serate; i++){
		for(int j = 0; j < momenti; j++){
			if(matrice[i][j] == 0)
				coH++;
			else
				coJ++;
			if(j == momenti-1){
				contaJ.push_back(coJ);
				contaH.push_back(coH);
			}
		}
		coH = 0;
		coJ = 0;
	}

	
	cout<<"stampo numero H"<<endl;
	for(int i = 0; i < contaH.size(); i++){
		cout<<contaH[i]<<" ";
	}

	cout<<endl<<"stampo numero J"<<endl;
	for(int i = 0; i < contaJ.size(); i++){
		cout<<contaJ[i]<<" ";
	}

	cout<<endl;
	
	//ordino vettore
	int* totali = new int[serate*2];
	for(int i = 0; i < serate*2; i+=2){
		totali[i] = 0;
	}

 	int j = 0;
	for(int i = 0; i < serate*2; i+=2){
		totali[i] = contaH[j];
		totali[i+1] = contaJ[j];
		j++;
	}

	cout<<"totali:"<<endl;
	for(int i = 0; i < serate*2; i++){
		cout<<totali[i]<<" ";
	}
	cout<<endl;

	//mergesort(totali,0,(serate*2)-1); [TODO]: creare una merge per gli int se serve

	cout<<"totali ordinati:"<<endl;
	for(int i = 0; i < serate*2; i++){
		cout<<totali[i]<<" ";
	}
	cout<<endl;

	//calcolo soluzione
	int soluzione=0;

	for(int i = 0; i < travestimenti; i++){
		soluzione+=totali[i];
	}

	cout<<"soluzione:"<<soluzione<<endl;
	return soluzione;
}


//caso complicato:
//primo metodo: prende in input direttamente la matrice
int Sherlock(int riga, int colonna, int contaT, int valAt){

	if(colonna == momenti){
		if(riga<serate - contaSerateTolte){
			riga++;
			colonna = 0;
			valAt = -1;
		}
	}

	//cout<<"valAt"<<valAt<<" riga:"<<riga<<" colonna:"<<colonna<<" contaT:"<<contaT<<endl;


	if(riga == serate - contaSerateTolte){
		return 0;
	}
	else if(colonna==momenti){
		return 0;
	}
	if(contaT==travestimenti+1){
	//cout<<"finito con:"<<contaT<<" travestimenti"<<endl;
		return 0;
	}
	else if(newMatrice[riga][colonna] == valAt){
		//cout<<"entro"<<endl;
		return Sherlock(riga,colonna+1,contaT, valAt)+1;
	}
	else{
		if(contaT+1<travestimenti+1)
			return Max(Sherlock(riga,colonna+1,contaT+1, newMatrice[riga][colonna])+1,Sherlock(riga,colonna+1,contaT,valAt));
		else
			Sherlock(riga,colonna+1,contaT,valAt);

	}
}
//secondo metodo: prende in input la matrice formattata
int SherlockPack(int riga, int colonna, int contaT, int valAt){
	
	if(newMatrice[riga][colonna] == 0 || colonna == momenti){
		if(riga<serate - contaSerateTolte){
			riga++;
			colonna = 0;
			valAt = -1;
		}
	}

	if(riga == serate - contaSerateTolte){
		return 0;
	}
	else if(colonna==momenti || newMatrice[riga][colonna] == 0 ){
		return 0;
	}
	if(contaT==travestimenti+1){
	//cout<<"finito con:"<<contaT<<" travestimenti"<<endl;
		return 0;
	}
	else if(colonna%2 == valAt){
		//cout<<"entro"<<endl;
		return SherlockPack(riga,colonna+1,contaT, valAt)+ newMatrice[riga][colonna];
	}
	else{
		if(contaT+1<travestimenti+1){
			return Max(SherlockPack(riga,colonna+1,contaT+1, colonna%2)+newMatrice[riga][colonna],SherlockPack(riga,colonna+1,contaT,valAt));
		}
		else{
			SherlockPack(riga,colonna+1,contaT,valAt);
		}
	}
}
//terzo metodo: ?
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
		if(travestimenti>0){
			//cout<<massimi[i]<<endl;
			istanti += massimi[i];
			travestimenti--;
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
					notte[x].push_back(listaSerate[i]->h[k]);
					notte[x].push_back(0-listaSerate[i]->j[k]);
				}
				if(listaSerate[i]->h.size()>listaSerate[i]->j.size())
					notte[x].push_back(listaSerate[i]->h[listaSerate[i]->h.size()-1]);
			}
			else{
				for(int k=0; k<listaSerate[i]->h.size(); k++){
					notte[x].push_back(listaSerate[i]->j[k]);
					notte[x].push_back(0-listaSerate[i]->h[k]);
				}
				if(listaSerate[i]->j.size()>listaSerate[i]->h.size())
					notte[x].push_back(listaSerate[i]->j[listaSerate[i]->j.size()-1]);	
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

void WarMachine(){
	if(contaFine>0){
		if(travestimenti>1){
			for(int i=posx; i<dimnotte; i++){
				for(int k=0; k<notte[i].size(); k++){
					if(notte[i][k]<0){
						if(travestimenti == travestimentiInizio){
							posxIni = i;
							posyIni = k;
						}
						
						posx = i;
						posy = k;
						i = dimnotte;
						k = notte[i].size();		
					}
				}
			}		
		}
		else 
			if(travestimenti>0){		
			for(int i=posx; i<dimnotte; i++){
				for(int k=notte[i].size(); k>0; k--){
					if(notte[i][k]<0){
						if(travestimenti == travestimentiInizio){
							posxIni = i;
							posyIni = k;
						}
							posx = i;
							posy = k;
							i = dimnotte;
							k = 0;			
						}
					}
				}
			}	

		travestimenti--;
		if(travestimenti>=0){
			InvertiSegni(posx,posy);

			for(int i=0; i<dimnotte; i++){
				for(int k=0; k<notte[i].size(); k++){
					cout << notte[i][k] << " ";
				}
				cout << endl;
			}

			CalcolaSomma();
			WarMachine();
		}
	}
}

void InvertiSegni(int riga, int colonna){
	for(int k=colonna; k<notte[riga].size()+1; k++){
			notte[riga][k] = 0-notte[riga][k];
	}
}

void CalcolaSomma(){
	int somma = 0;

	for(int i=0; i<dimnotte; i++){
		for(int k=0; k<notte[i].size(); k++){
			if(notte[i][k]>0){
				somma += notte[i][k];
			}
		}
	}
	if(somma>sommaFinale)
		sommaFinale = somma;	

	if(travestimenti==0){
		notteIniziale[posxIni][posyIni] = 0;	
		notte = notteIniziale;
		travestimenti = travestimentiInizio;
		contaFine--;
		istanti = sommaFinale;
	}

	cout<<"SOMMA:"<<somma<<" sommaFinale:"<<sommaFinale<<endl;
}

//******************************************************************************************