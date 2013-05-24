#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

void RobertDowneyJr();
int WarMachine5(int trav,int r, int i, int segno);

int serate, momenti, travestimenti, veritravestimenti;
int** matrice;
int** Targaryen;
vector < vector < int > > v;

int main(){
	RobertDowneyJr();
	cout << "Stampo la matrice\n";
	for(int i = 0; i < v.size(); i++){
		for(int j=0; j<v[i].size(); j++){
			cout << v[i][j] << " "; 
		}
		cout << endl;
	}
	cout << endl;
	Targaryen = new int*[travestimenti+1];
	for(int i=0; i< travestimenti+1; i++)
		Targaryen[i] = new int[momenti];
	for(int i=0; i<travestimenti+1; i++)
		for(int j=0; j< momenti; j++)
			Targaryen[i][j] = -1;
	int l;
	int s;
	int ris=0;
	for(int trav=1; trav<=travestimenti; trav++){
		if(ris!=momenti){
			l= WarMachine5(trav,0,0,0);
			ris=l;
			cout << "**********************************\n";
			cout << "Con " << trav << " travestimenti riesco a fare " << l;
			cout << "\n**********************************\n";
			for(int i=0; i<travestimenti+1; i++)
				for(int j=0; j< momenti; j++)
					Targaryen[i][j] = -1;
		}
		else
			trav=travestimenti+1;
	}
}

void RobertDowneyJr(){
		
	ifstream in ("input.txt");
	in >> serate >> momenti >> travestimenti;
	veritravestimenti = travestimenti;
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
				matrice[i][j] = -1;
		}
		
	}

	int k=0;
	int val;
	v.resize(serate);
	for(int i = 0; i < serate; i++){
		val = matrice[i][0];
		for(int j = 0; j < momenti; j++){
			if(matrice[i][j] == val){
				k+=matrice[i][j];
			}
			else{
				v[i].push_back(k);
				k=matrice[i][j];
				val=k;
			}
		}
		v[i].push_back(k);
		k=0;
	}
}

int WarMachine5(int trav, int r, int i, int segno){
	if(i==v[r].size())
	 	return 0;
	int o;
	if(v[r][i]>0)
		o=1;
	else
		o=-1;
	if(segno==0){
		if(Targaryen[trav][i]!=-1){
		    return Targaryen[trav][i];
		}
		else{
			Targaryen[trav][i] = max(WarMachine5(trav-1,r,i+1,o)+v[r][i]*o,WarMachine5(trav,r,i+1,-o));
			return Targaryen[trav][i];
		}
	}
	else{
		if(v[r][i]*segno>0){//uguali
			if(Targaryen[trav][i]!=-1){
			    return Targaryen[trav][i];
			}
			else{
				Targaryen[trav][i] = WarMachine5(trav,r,i+1,segno)+v[r][i]*o;
				return Targaryen[trav][i];
			}
		}
		else{//diversi
			if(Targaryen[trav][i]!=-1){
			    return Targaryen[trav][i];
			}
		  	if(trav-1>=0){
			  	Targaryen[trav][i] = max(WarMachine5(trav-1,r,i+1,o)+v[r][i]*o,WarMachine5(trav,r,i+1,segno));
				return Targaryen[trav][i];
		  	}
		  	else{
				Targaryen[trav][i] = WarMachine5(trav,r,i+1,segno);
			}
		}
	}
	return Targaryen[trav][i];
}