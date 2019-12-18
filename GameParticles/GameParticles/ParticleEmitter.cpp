#include "DO_NOT_MODIFY\Timer.h"
#include "DO_NOT_MODIFY\GlobalTimer.h"
#include "DO_NOT_MODIFY\OpenGLInterface.h"


//#define UNUSED_VAR(v) ((void *)v)
#include "ParticleEmitter.h"
#include "Settings.h"

static const unsigned char squareColors[] =
{
	255,  255,  000,  255,
	000,  255,  255,  255,
	000,  000,  000,  000,
	255,  000,  255,  255,
};

static const float squareVertices[] =
{
	-0.015f,  -0.015f, 0.0f,
	0.015f,  -0.015f, 0.0f,
	-0.015f,   0.015f, 0.0f,
	0.015f,   0.015f, 0.0f,
};


ParticleEmitter::ParticleEmitter()
	:headParticle(0),
	tailParticle(0),
	last_active_particle(-1),
	spawn_frequency(0.0000001f),
	start_position(0.0f, 0.0f, 0.0f),
	start_velocity(0.0f, 1.0f, 0.0f),
	vel_variance(1.0f, 4.0f, 0.4f),
	pos_variance(1.0f, 1.0f, 1.0f),
	max_life(MAX_LIFE),
	max_particles(NUM_PARTICLES),
	last_spawn(globalTimer::getTimerInSec()),
	last_loop(globalTimer::getTimerInSec())
	
	
	
{

}



ParticleEmitter::~ParticleEmitter()
{
	// do nothing
}


void ParticleEmitter::SpawnParticle()
{
	// create another particle if there are ones free
	if (last_active_particle < max_particles - 1)
	{

		// create new particle
		Particle *newParticle = new Particle();

		// initialize the particle
		newParticle->life = 0.0f;
		newParticle->position = start_position;
		newParticle->velocity = start_velocity;
		newParticle->scale = 1.0f;

		// apply the variance
		this->Execute(newParticle->position, newParticle->velocity, newParticle->scale);

		// increment count
		last_active_particle++;

		// add to list
		this->addParticleToList(newParticle);
	}
}

void ParticleEmitter::update()
{
	// get current time
	float current_time = globalTimer::getTimerInSec();

	// spawn particles
	float time_elapsed = current_time - last_spawn;

	// update
	while (spawn_frequency < time_elapsed)
	{
		// spawn a particle
		this->SpawnParticle();
		// adjust time
		time_elapsed -= spawn_frequency;
		// last time
		last_spawn = current_time;
	}

	// total elapsed
	time_elapsed = current_time - last_loop;

	Particle *p = this->headParticle;
	// walk the particles

	while (p != 0)
	{
		// call every particle and update its position 
		p->Update(time_elapsed);

		p = p->next;
	}

	last_loop = current_time;
}

void ParticleEmitter::addParticleToList(Particle *p)
{
	//assert(p);
	if (this->headParticle == 0)
	{ // first on list
		this->headParticle = p;
		this->tailParticle = p;
		p->next = 0;
		p->prev = 0;
	}
	else
	{ // add to front of list
		headParticle->prev = p;
		p->next = headParticle;
		p->prev = 0;
		headParticle = p;
	}

}


void ParticleEmitter::removeParticleFromList(Particle *pNode)
{
	
	if (pNode->prev != 0)
	{
		//middle or last node
	
		pNode->prev->next = pNode->next;
	}
	else
	{
		//first node
		this->headParticle = pNode->next;
	}

	if (pNode->next != 0)
	{
		//middle node
	
		pNode->next->prev = pNode->prev;
	}

	// bye bye
	delete pNode;
}

void ParticleEmitter::draw()
{
	// get the camera matrix from OpenGL
	// need to get the position
	Matrix cameraMatrix;

	// get the camera matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<float*>(&cameraMatrix));

	// OpenGL goo... don't worrry about this
	glVertexPointer(3, GL_FLOAT, 0, squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
	glEnableClientState(GL_COLOR_ARRAY);
	//Temporary matrix
	Matrix tmp;

	// get the position from this matrix
	Vect4D camPosVect;
	cameraMatrix.get(Matrix::MATRIX_ROW_3, &camPosVect);

	// camera position
	Matrix transCamera;
	transCamera.setTransMatrix(&camPosVect);

	// particle position
	Matrix transParticle;

	// rotation matrix
	Matrix rotParticle;

	// pivot Point
	Matrix pivotParticle;
	Vect4D pivotVect;


	// scale Matrix
	Matrix scaleMatrix;


	// iterate throught the list of particles
	Particle *p = this->headParticle;
	while (p != 0)
	{
		transParticle.setTransMatrix(&p->position);


		rotParticle.setRotZMatrix(p->rotation);

		pivotVect.set(1.0f, 0.0f, 50.0f);
		pivotVect *= 20.0f * p->life;
		pivotParticle.setTransMatrix(&pivotVect);

		scaleMatrix.setScaleMatrix(p->scale);

		// total transformation of particle
		tmp = scaleMatrix * transCamera * transParticle * rotParticle * scaleMatrix;

		// set the transformation matrix
		glLoadMatrixf(reinterpret_cast<float*>(&(tmp)));


		// draw the trangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// clears or flushes some internal setting, used in debug, but is need for performance reasons
		// magic...  really it's magic.
		 glGetError();

		p = p->next;
	}



	Particle *pPart = this->headParticle;
	Particle *pTmp;
	while (pPart != 0)
	{
		pTmp = pPart->next;

		if (pPart->life > max_life && (last_active_particle > 0))
		{
			removeParticleFromList(pPart);
			last_active_particle--;
		}


		pPart = pTmp;

	}

}
void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, float& sc)
{
	// Add some randomness...

	// Ses it's ugly - I didn't write this so don't bitch at me
	// Sometimes code like this is inside real commerical code ( so now you know how it feels )

	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.001f;
	float sign = static_cast<float>(rand() % 2);
	float *t_pos = reinterpret_cast<float*>(&pos);
	float *t_var = &pos_variance[x];
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	// x  - add velocity
	t_pos = &vel[x];
	t_var = &vel_variance[x];
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// correct the sign
	var = 2.0f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	if (sign == 0)
	{
		var *= -1.0;
	}
	sc *= var;
}




// End of file