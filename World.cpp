#include "World.h"
int i = 0;
World::World() 
{ 
	ship = 0; 
}

World::~World() { delete ship; }

void World::Initialize() {

	srand(time(NULL));

	x_eye = -300;
	y_eye = 320;
	z_eye = 300;

	sun.SetColor(1.0F, 1.0F, 0);
	sun.SetRadius(19);

	earth.SetColor(0.0F, 0.0F, 1.0F);
	earth.SetRadius(3.5);
	earth.SetOrbitRadius(190);
	earth.SetOmega(1.6);
	earth.SetAngle(rand()%360); // sets a random value between 0 and 359 for the first angle

	mars.SetColor(1.0F, 0.5F, 0);
	mars.SetRadius(2.3F);
	mars.SetOrbitRadius(310);
	mars.SetOmega(.8);
	mars.SetAngle(rand() % 360);

	mercury.SetColor(0.5F, 0.0F, 0.5F);
	mercury.SetRadius(1.5F);
	mercury.SetOrbitRadius(30);
	mercury.SetOmega(4.8);
	mercury.SetAngle(rand() % 360);

	venus.SetColor(0.8F, 0.5F, 1.0F);
	venus.SetRadius(2);
	venus.SetOrbitRadius(60);
	venus.SetOmega(3.9);
	venus.SetAngle(rand() % 360);

}

void World::Draw() 
{
	gluLookAt(x_eye, y_eye, z_eye,  // posicion del ojo
		0.0, -70, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y) 

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	sun.Draw();
	mercury.Draw();
	earth.Draw();
	mars.Draw();
	venus.Draw();
	
	if (ship) 
		ship->Draw();
}

void World::Timer() 
{		
	if (ship) {
		if (Interaction::ProximityOrbit(mars.GetPos(), ship->GetPos()))
			ship->OrbitAround(mars.GetPos()); // with this condition on you are able to pass to the next phase
		else
			ship->Move();
	}
	earth.Move();
	mercury.Move();
	mars.Move();
	venus.Move();
	
}

void World::Key(unsigned char key, int x_t, int y_t)
{
	if (key == ' ')
	{
		if (i == 0)
		{
			i = 1;
			ship = new Ship;
			ship->SetPos(earth.GetPos());
			ship->SetOmega(earth.GetOmega());
			ship->GetAV(mars.GetPos());
			earth.SetOmega(1.6 * 0.1);
			mars.SetOmega(0.8 * 0.1);
			venus.SetOmega(3.9 * 0.1);
			mercury.SetOmega(4.8 * 0.1);
		}
		else if (i == 1)
		{
			i = 0;
			earth.SetOmega(1.6);
			mars.SetOmega(0.8);
			mercury.SetOmega(4.8);
			venus.SetOmega(3.9);
		}
	}
}