#include <vector>

using namespace std;

class grid
{

public:
	grid(float a, float b, int n, float velocity, float tau);
	~grid();

	void setLeft(float a);
	float getLeft();
	void setRight(float b);
	float getRight();
	void setN(int n);
	int getN();
	float limiter_current(int i);
	float limiter_minus(int i);

	void setVelocity(float velocity);
	float getVelocity();

	void setTau(float tau);
	float getTau();
	

	float getGamma();
	void setGamma();

	void setGrid(vector<float> v);
	vector<float> getGrid();


	void updateFuncValues(vector<float> f);
	vector<float> getFuncValues();
	void oneStep();
	void multipleSteps(int n);



	vector<float> createPoints();
	vector<float> setFunction();

private:
	float left;
	float right;
	int n;
	float tau;
	float velocity;
	float gamma;
	vector<float> gridValues;
	vector<float> funcValues;
};

