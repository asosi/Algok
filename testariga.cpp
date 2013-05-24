#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

void RobertDowneyJr();
int WarMachine5(int trav, int i, int segno);

int serate, momenti, travestimenti, veritravestimenti;
int** matrice;
int** Targaryen;
vector<int> v;

int main(){
	RobertDowneyJr();
	for(int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
	Targaryen = new int*[travestimenti+1];
	for(int i=0; i< travestimenti+1; i++)
		Targaryen[i] = new int[momenti];
	for(int i=0; i<travestimenti+1; i++)
		for(int j=0; j< momenti; j++)
			Targaryen[i][j] = -1;
	int l;
	int ris=0;
	for(int trav=1; trav<=travestimenti && find; trav++){
		if(ris!=momenti){
			if(v[0]>0)
				l = WarMachine5(trav,0,-1);
			else
				l = WarMachine5(trav,0,1);
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
	int val = matrice[0][0];

	for(int i = 0; i < serate; i++){
		for(int j = 0; j < momenti; j++){
			if(matrice[i][j] == val){
				k+=matrice[i][j];
			}
			else{
				v.push_back(k);
				k=matrice[i][j];
				val=k;
			}
		}
		v.push_back(k);
	}
}

int WarMachine5(int trav, int i, int segno){

	//cout<<"val:"<<notte[Ri][i]<<" segno:"<<segno<<" trav:"<<trav<<endl;

	if(i==v.size()){
	 	return 0;
	}
	if(v[i]*segno>0){//uguali
		if(Targaryen[trav][i]!=-1){
		    return Targaryen[trav][i];
		}
		else{
			int o = segno/abs(segno);
			Targaryen[trav][i] = WarMachine5(trav,i+1,segno)+v[i]*o;
			return Targaryen[trav][i];
		}
	}
	else{//diversi
		if(Targaryen[trav][i]!=-1){
		    return Targaryen[trav][i];
		}
	  	if(trav-1>=0){
			int o = -segno/abs(segno);
		  	Targaryen[trav][i]= max(WarMachine5(trav-1,i+1,v[i])+v[i]*o,WarMachine5(trav,i+1,segno));
			return Targaryen[trav][i];	
	  	}
	  	else{
			Targaryen[trav][i] = WarMachine5(trav,i+1,segno);
		}
	}
	return Targaryen[trav][i];
}