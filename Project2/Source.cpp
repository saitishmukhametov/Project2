#include <vector>
#include <iostream>
#include "grid.h"
#include <fstream>


using namespace std;

int main() {
	grid grid(-10,10,1000,0.03,0.07);// left, right, n, velocity, tau
	vector<float> v;
	vector<float> g;
	v = grid.createPoints();
	g = grid.setFunction();

	
	vector<float> updated = grid.getFuncValues();
	
	ofstream outFile("D:\MC_exp.txt");
	for (int i = 0; i < v.size(); ++i) {
		outFile << v[i] << ' ';
	}
	outFile << endl;
	
	for (int k = 0; k < 1000; k++) {
		
		for (int i = 0; i < v.size(); ++i) {
			updated = grid.getFuncValues();
			outFile << updated[i] << ' ';
			
		}
		grid.oneStep();
		outFile << endl;
	}
	


	

	return 0;
}