#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


//****************HEADER*******************
void RobertDowneyJr();
int ElementareWatson();
void merge(int* v, int start, int center, int end);
void mergesort(int* v, int start, int end);
int Max(int i, int j);
int Sherlock(int riga, int colonna, int contaT, int valAt);
bool TrovaRiga(int riga);
int* FormattaMatrix(int riga);
int SherlockPack(int riga, int colonna, int contaT, int valAt);

//***************VARIABILI*****************

int serate, momenti, travestimenti;
int** matrice;
int contaStampa;
int** newMatrice;
int istanti = 0;
int contaSerateTolte = 0;

// IL VALORE 1 CORRISPONDE A J
// IL VALORE 0 CORRISPONDE A H

//***************FUNZIONI******************
int main(){
	RobertDowneyJr();
/*
	cout<<endl<<"NEW MATRICE"<<endl;
	for(int i = 0; i < serate-contaSerateTolte; i++){
		for(int j = 0; j < momenti; j++){
			cout<<newMatrice[i][j]<<" ";
		}
		cout<<endl;
	}
*/
	//istanti = ElementareWatson();
	//if(travestimenti!=0)
	//	istanti += Sherlock(0,0,0,-1);


	for(int i = 0; i < serate - contaSerateTolte; i++){
		newMatrice[i] = FormattaMatrix(i);
	}

	cout<<"istanti prima:"<<istanti<<endl;

	cout<<endl<<"MATRICE FORMATTATA"<<endl;
	for(int i = 0; i < serate-contaSerateTolte; i++){
		for(int j = 0; j < momenti; j++){
			cout<<newMatrice[i][j]<<" ";
		}
		cout<<endl;
	}


	istanti += SherlockPack(0,0,0,-1);

	

	cout<<endl<<"istanti:"<<istanti<<endl;


	ofstream out("output.txt");
	out<<istanti;
	
	return 0;
}

//inizializza
void RobertDowneyJr(){
	
	ifstream in ("input.txt");
	in >> serate >> momenti >> travestimenti;

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

	cout<<"N:"<<serate<<" m:"<<momenti<<" t:"<<travestimenti<<endl;
	cout<<"0:H 1:J"<<endl<<endl;

	cout<<"Matrice:"<<endl;
	for(int i = 0; i < serate; i++){
		for(int j = 0; j < momenti; j++){
			cout<<matrice[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	
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

	mergesort(totali,0,(serate*2)-1);

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
/*
IDEA:
soluzione dinamica:
trovare il max(cambio vestito, non cambio vestito) tra tutte le serate tramite una funzione ricorsiva.
questo finchè non ho esaurito i travestimenti
*/
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
		//cout<<"z:"<<z<<" array[z]:"<<array[z]<<" matrice[i][j]:"<<matrice[i][j]<<" valAt:"<<valAt<<endl;
	}

	//cout<<endl<<"riga:"<<riga<<endl;
	//for(int i = 0; i < momenti; i++)
	//	cout<<array[i]<<" ";
	//cout<<endl;

	return array;
}

bool TrovaRiga(int riga){
	int h = matrice[riga][0];
	for(int i = 1; i < momenti; i++){
		if(matrice[riga][i] != h)
			return false;
	}
	return true;
}

int Max(int i, int j){
	if(i>j)
		return i;
	else
		return j;
}

//ORDINAMENTO DECRESCENTE PER CASO BASE
void merge(int* v, int start, int center, int end){
  int s = start;
  int c = center+1;
  int supp[end-start];
  int i = 0;
  while(s<=center && c<=end){
    if(v[s] > v[c]){
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
void mergesort(int* v, int start, int end){
  if(start<end){
    int center = (start+end)/2;
    mergesort(v,start,center);
    mergesort(v,center+1,end);
    merge(v,start,center,end);
  }
}

