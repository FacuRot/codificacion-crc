#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

int contar0(vector<bool> a) {
	int cont = 0;
	int i=0;
	while(a[i] != true) {
		cont += 1;
		i++;
	}
	
	return cont;
}

vector<bool> div(vector<bool> M, vector<bool> C) {
	vector<bool> resto(0);
	if (M.size() == C.size()) {
		for(unsigned int i = 0; i<M.size(); i++) {
			resto.push_back(M[i] xor C[i]);
		}
	} else {
		vector<bool> aux(0);
		for (unsigned int i = 0; i<C.size(); i++) {
			aux.push_back(M[i] xor C[i]);
		}
		int desplazamiento = contar0(aux);
		aux.erase(aux.begin(), aux.begin()+desplazamiento);
		M.erase(M.begin(), M.begin()+(C.size()));
		M.insert(M.begin(), aux.begin(), aux.end());
		vector<bool> t = div(M, C);
		resto.insert(resto.begin(), t.begin(), t.end());
	}
	
	return resto;
}

int main(int argc, char *argv[]) {
	///Polinomio generador crc-6-gsm
	const vector<bool> crc6 = {1,1,0,1,1,1,1};
	///Polinomio generador crc-8-bluetooth
	const vector<bool> crc8 = {1,1,0,1,0,0,1,1,1}; 
	const string cadena = "Llego a la estacion a las 16:50";
	
	//Conversion de la cadena a binario ASCII
	vector<bool> binario(0);
	for (char a:cadena) {
		string arrbit(bitset<7>(a).to_string());
		
		for (int i=0; i<7; i++) {
			binario.push_back(arrbit[i] == '1');
		}
	}
	
	//Añado c-1 "0" al final de la cadena binaria, donde n es la cantidad de bits del polinomio generador
	for (unsigned int i=0; i<crc8.size(); i++) { //cambiar la variable crc8 dependiendo de que polinomio se quiera usar
		binario.push_back(0 == 1);
	}
	
	vector<bool> a3 = div(binario, crc8); //el segundo parametro de la funcion es el polinomio del crc en este caso crc-6-gsm o crc-8-bluetooth
	a3.erase(a3.begin(), a3.begin()+1);
	
	for (unsigned int i=0; i<crc8.size(); i++) { //cambiar la variable crc8 dependiendo de que polinomio se quiera usar
		binario.pop_back();
	}
	binario.insert(binario.end(), a3.begin(), a3.end());
	for (auto x:binario) {
		cout<<x;
	}
	
	return 0;
}

