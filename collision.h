#include <cstdio>
#include <vector>
#include <GL/glut.h>

#define BLACK 0
#define WHITE 1
#define RED	  2
#define GREEN 3
#define BLUE  4
#define GREY  5

using namespace std;

extern float colorSet[6][3];

void writeString(int x, int y, void *font, char *string);

struct mt
{
	double x;
	double Vx;
	double m;
};

class model
{
	public:
		model(int newWidth = 800, int newHeight = 600 ) : width(newWidth), height(newHeight) {};
		void getData(void);
		void toSimulate(void);
		void collision(mt &a, mt &b);
		void toPrintSost(void);
		void toMove(void);
		void toCollision(void);
		int willCollision(void);

		void toFindScale(void);
		void toDisplay(void);
		void toDisplayDigit(void);
		~model(void);
	private:
		int countMt;
		vector< vector<mt> > m;
		double dt, eps;
		int count;

		int width, height;
		double relX, relY;
};
