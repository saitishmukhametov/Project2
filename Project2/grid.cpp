#include <vector>
#include "grid.h"
#include <algorithm> 
#include <cmath> 
#include <iostream>
using namespace std;

grid::grid(float a, float b, int n, float velocity, float tau)
{
	setLeft(a);
	setRight(b);
	setN(n);
	setVelocity(velocity);
	setTau(tau);
	setGamma();

}


grid::~grid()
{
}

void grid::setGamma() {
	float right = getRight();
	float left = getLeft();
	int n = getN();
	float tau = getTau();
	float h = (right - left) / n;
	float velocity = getVelocity();
	float gamma = velocity * tau / h;
	this->gamma = gamma;
}
float grid::getGamma() {
	return this->gamma;
}
void grid::setLeft(float a) {
	this->left = a;
}
void grid::setRight(float b) {
	this->right = b;
}
void grid::setN(int n) {
	this->n = n;
}
void grid::setGrid(vector<float> g) {
	this->gridValues = g;
}
vector<float> grid::getGrid() { 
	vector<float> v = this->gridValues;
	return v; 
};

void grid::setVelocity(float velocity) {
	this->velocity = velocity;
}

void grid::setTau(float tau) {
	this->tau = tau;

}

float grid::getLeft() {
	return this->left;
}
float grid::getRight()  {
	return this->right;
}
int grid::getN() {
	return this->n;
}
float grid::getVelocity() {
	return this->velocity;
}
float grid::getTau() {
	return this->tau;
}

vector<float> grid::getFuncValues() {
	return this->funcValues;
}
void grid::updateFuncValues(vector<float> f) {
	this->funcValues = f;
}

vector<float> grid::createPoints() {
	float left = getLeft();
	float right = getRight();
	int n = getN();
	vector<float> g;
	for (int i = 0; i <= n; i++) {
		g.push_back(left + (right - left) / n * i);
	}
	setGrid(g);
	return g;
}
vector<float> grid::setFunction() {
	vector<float> g = getGrid();
	vector<float> v;
	for (int i = 0; i < g.size(); ++i) {
		if ((g[i] <= 3) && (g[i] >= -3)) {
			v.push_back(exp(-g[i] * g[i]) - exp(-9/2)); //exponenta
			//v.push_back(1); // ne exponenta
		}
		else v.push_back(0);
	}
	updateFuncValues(v);
	return v;
}

float grid::limiter_current(int i) {    // MC LIMITER
	vector<float> v = getFuncValues();
	float minus = 0;
	float center = 0;
	float plus = 0;
	float gamma = getGamma();
	if (i == 0) {
		minus = 0;
		center = v[0];
		plus = v[1];
	}
	if (i == v.size() - 1) {
		minus = v[v.size()-2];
		center = v[v.size()-1];
		plus = 0;
	}
	if (i > 0 && i < v.size() - 2) {
		minus = v[i-1];
		center = v[i];
		plus = v[i+1];
	}
	if (plus - center >= 0) { return (center + (1 - gamma) / 2 * min ( min(abs(plus-minus)/2,2*abs(plus - center)), 2*abs(center - minus))); }
	else return center - (1-gamma)/2 *min ( min(abs(plus-minus)/2,2*abs(plus - center)),2* abs(center - minus));
}
float grid::limiter_minus(int i) {
	vector<float> v = getFuncValues();
	float minus = 0;
	float center = 0;
	float plus = 0;

	if (i == 0) {
		minus = 0;
		center = 0;
		plus = v[0];
	}
	if (i == 1) {
		minus = 0;
		center = v[0];
		plus = v[1];
	}
	if (i == v.size() - 1) {
		minus = v[v.size() - 3];
		center = v[v.size()-2];
		plus = v[v.size()-1];
	}
	if (i > 1 && i < v.size() - 1) {
		minus = v[i - 2];
		center = v[i - 1];
		plus = v[i];
	}
	if (plus - center >= 0) { return (center - (1 - gamma) / 2 * min (min( abs(plus - minus) / 2, 2*abs(plus - center)), 2*abs(center - minus))); }
	else return center + (1-gamma) /2 * min ( min(abs(plus - minus) / 2, 2*abs(plus - center)), 2*abs(center - minus));
}

/*float grid::limiter_current(int i) {    // MINMOD LIMITER
	vector<float> v = getFuncValues();
	float minus = 0;
	float center = 0;
	float plus = 0;
	float gamma = getGamma();
	if (i == 0) {
		minus = 0;
		center = v[0];
		plus = v[1];
	}
	if (i == v.size() - 1) {
		minus = v[v.size()-2];
		center = v[v.size()-1];
		plus = 0;
	}
	if (i > 0 && i < v.size() - 2) {
		minus = v[i-1];
		center = v[i];
		plus = v[i+1];
	}
	if (plus - center >= 0) { return (center + (1 - gamma) / 2 * min(abs(plus - center), abs(center - minus))); }
	else return center - (1-gamma)/2 *min(abs(plus - center), abs(center - minus));
}
float grid::limiter_minus(int i) {
	vector<float> v = getFuncValues();
	float minus = 0;
	float center = 0;
	float plus = 0;

	if (i == 0) {
		minus = 0;
		center = 0;
		plus = v[0];
	}
	if (i == 1) {
		minus = 0;
		center = v[0];
		plus = v[1];
	}
	if (i == v.size() - 1) {
		minus = v[v.size() - 3];
		center = v[v.size()-2];
		plus = v[v.size()-1];
	}
	if (i > 1 && i < v.size() - 1) {
		minus = v[i - 2];
		center = v[i - 1];
		plus = v[i];
	}
	if (plus - center >= 0) { return (center - (1 - gamma) / 2 * min(abs(plus - center), abs(center - minus))); }
	else return center + (1-gamma) /2 * min(abs(plus - center), abs(center - minus));
}
*/
/*float grid::limiter_current(int i) {    // SUPERBEE Limiter
	vector<float> v = getFuncValues();
	float minus = 0;
	float center = 0;
	float plus = 0;
	float gamma = getGamma();
	if (i == 0) {
		minus = 0;
		center = v[0];
		plus = v[1];
	}
	if (i == v.size() - 1) {
		minus = v[v.size()-2];
		center = v[v.size()-1];
		plus = 0;
	}
	if (i > 0 && i < v.size() - 2) {
		minus = v[i-1];
		center = v[i];
		plus = v[i+1];
	}
	if (plus - center >= 0) { return (center + (1 - gamma) / 2 * max(min(2*abs(plus-center), abs(center-minus)),min(abs(plus-center),2*abs(center-minus)))); }
	else return center - (1-gamma)/2 * max(min(2 * abs(plus - center), abs(center - minus)), min(abs(plus - center), 2 * abs(center - minus)));
}
float grid::limiter_minus(int i) {
	vector<float> v = getFuncValues();
	float minus = 0;
	float center = 0;
	float plus = 0;

	if (i == 0) {
		minus = 0;
		center = 0;
		plus = v[0];
	}
	if (i == 1) {
		minus = 0;
		center = v[0];
		plus = v[1];
	}
	if (i == v.size() - 1) {
		minus = v[v.size() - 3];
		center = v[v.size()-2];
		plus = v[v.size()-1];
	}
	if (i > 1 && i < v.size() - 1) {
		minus = v[i - 2];
		center = v[i - 1];
		plus = v[i];
	}
	if (plus - center >= 0) { return (center - (1 - gamma) / 2 * max(min(2 * abs(plus - center), abs(center - minus)), min(abs(plus - center), 2 * abs(center - minus))));
	}
	else return center + (1-gamma) / 2 * max(min(2 * abs(plus - center), abs(center - minus)), min(abs(plus - center), 2 * abs(center - minus)));
}
*/


void grid::oneStep() {
	float right = getRight();
	float left = getLeft();
	int n = getN();
	vector<float> v = getFuncValues();
	vector<float> updatedValues;
	float tau = getTau();
	float h = (right - left) / n;
	float velocity = getVelocity();
	float gamma = getGamma();


	for (int i = 0; i < v.size(); ++i) {
		updatedValues.push_back(v[i] - gamma * (limiter_current(i) - limiter_minus(i)));
	}
	
	updateFuncValues(updatedValues);
}
void grid::multipleSteps(int n) {
	for (int i = 0; i < n; i++) {
		oneStep();
	}
}
