#include "collision.h"

void writeString(int x, int y, void *font, char *string)
{
	char *c;
	glRasterPos2d(x, y);
	for (c=string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void model::getData(void)
{
	mt x;
	scanf("%d%lf%lf", &countMt, &dt, &eps);
	m.resize(countMt);
	
	for(int i = 0; i < countMt; i++)
	{
		scanf("%lf%lf%lf", &x.x, &x.Vx, &x.m);
		m[i].push_back(x);
	}

	count = 0;
}

void model::toSimulate(void)
{
	toPrintSost();

	while( willCollision() )
	{
		toMove();
		toCollision();
		toPrintSost();
	}

	toFindScale();
}

void model::collision(mt &a, mt &b)
{
	mt _a = a;
	mt _b = b;
	a.Vx = (2*_b.m*_b.Vx + _a.Vx*(_a.m - _b.m) )/(_a.m + _b.m);
	b.Vx = (2*_a.m*_a.Vx + _b.Vx*(_b.m - _a.m) )/(_a.m + _b.m);

	count++;
}

int model::willCollision(void)
{
	int last = m[0].size() - 1;
	mt m1, m2;
	for(int i = 0; i < countMt; i++)
		for(int j = i+1; j < countMt; j++)
		{
			m1 = m[i][last].x > m[j][last].x ? m[i][last] : m[j][last];
			m2 = m[i][last].x > m[j][last].x ? m[j][last] : m[i][last];

			if(m1.x - m2.x < 20*eps)
				return 1;

			if(m1.Vx + m2.Vx != 0 && (m1.Vx <= 0 && m2.Vx >= 0 ||
			   m1.Vx >= 0 && m2.Vx >= 0 && m2.Vx > m1.Vx ||
			   m1.Vx <= 0 && m2.Vx <= 0 && m2.Vx > m1.Vx ))
				return 1; 
		}

	return 0;
}

void model::toPrintSost(void)
{
	int last = m[0].size() - 1;
	for(int i = 0; i < countMt; i++)
		printf("%2d| x = %8.3lf; V = %8.3lf; m = %8.3lf;\n", i, m[i][last].x, m[i][last].Vx, m[i][last].m);
}

void model::toMove(void)
{
	int last = m[0].size() - 1;
	mt mx;
	for(int i = 0; i < countMt; i++)
	{
		mx = m[i][last];
		mx.x += m[i][last].Vx*dt;
		m[i].push_back(mx);
	}
}

void model::toCollision(void)
{
	int last = m[0].size() - 1;
	mt *m1, *m2;
	for(int i = 0; i < countMt; i++)
		for(int j = i+1; j < countMt; j++)
		{
			if(m[i][last].x > m[j][last].x)
			{
				m1 = &m[i][last];
				m2 = &m[j][last];
			} else {
				m1 = &m[j][last];
				m2 = &m[i][last];
			}

			if( m1->x - m2->x > eps )
				continue;

			if(m1->Vx <= 0 && m2->Vx >= 0 && m1->Vx != m2->Vx ||
			   m1->Vx >= 0 && m2->Vx >= 0 && abs(m2->Vx) > abs(m1->Vx) ||
			   m1->Vx <= 0 && m2->Vx <= 0 && abs(m2->Vx) < abs(m1->Vx) )
					collision(*m1, *m2);
		}
}

void model::toFindScale(void)
{
	int last = m[0].size() - 1;
	double minX = m[0][last].x, maxX = m[0][last].x;
	for(int i = 0; i < countMt; i++)
	{
		if(m[i][last].x < minX )
			minX = m[i][last].x;
		if(m[i][last].x > maxX )
			maxX = m[i][last].x;
	}

	relX = (double)(width-10)/last;
	relY = (double)(height-10)/(maxX - minX);
}

void model::toDisplay(void)
{
	//Display coords
	glBegin(GL_LINES);
	glColor3fv(colorSet[GREY]);
	for(int i = 0; i <= (width-10); i += (width-10)/10 )
	{
		glVertex2d(i, -(height-10)/2);
		glVertex2d(i,  (height-10)/2);
	}
	
	for(int i = -(height-10)/2; i <= (height-10)/2; i += (height-10)/10 )
	{
		glVertex2d(0       , i);
		glVertex2d(width-10, i);
	}
	
	glColor3fv(colorSet[BLACK]);
	glVertex2d(0,0);
	glVertex2d(width, 0);

	glVertex2d(0,-height/2);
	glVertex2d(0, height/2);
	glEnd();
	//Display objects
	for(int i = 0; i < countMt; i++)
	{
		glBegin(GL_LINE_STRIP);
		glColor3fv(colorSet[ i%3 + 2]);
		mt mx;
		
		for(int j = 0; j < m[i].size(); j++)
		{
			mx = m[i][j];
			glVertex2f(j*relX, mx.x*relY);
		}
		
		glEnd();
	}
}

void model::toDisplayDigit()
{
	char s[25];
	glColor3fv(colorSet[BLACK]);
	for(int i = 0; i <= (width-10); i += (width-10)/10 )
	{
		sprintf(s, "%8.4lf", i/relX*dt );
		writeString(i+2, 2, GLUT_BITMAP_HELVETICA_12, s);
	}
	
	for(int i = -(height-10)/2; i <= (height-10)/2; i += (height-10)/10 )
	{
		sprintf(s, "%8.4lf", i/relY );
		writeString(2, i+2, GLUT_BITMAP_HELVETICA_12, s);
	}
}

model::~model()
{
	printf("Count collision: %d;\n", count);
}	
