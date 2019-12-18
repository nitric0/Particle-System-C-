#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

class __declspec(align(16)) Particle
{
public:
	friend class ParticleEmitter;

	Particle()
	{
		// construtor
		this->next = 0;
		this->prev = 0;
		this->rotation_velocity = -0.75f;
		this->rotation = 0.0f;
		this->position.set(0.0f, 0.0f, 0.0f);
		this->velocity.set(0.0f, 0.0f, 0.0f);
		this->scale = 0.0f;
		this->life = 0.0f;

	}

	~Particle()
	{
		// nothing to do
	}

	Particle(const Particle &tmp) = delete;
	Particle & operator = (const Particle &tmp) = delete;
	
	void Update(const float& time_elapsed);

	void *operator new(size_t size)
	{
		void *p = _aligned_malloc(size, 16);
		return p;
	}



		void operator delete(void *p)
	{
		_aligned_free(p);
	}



private:
	Particle * next;
	Particle *prev;
	float	rotation_velocity;
	float	rotation;

	Vect4D	position;
	Vect4D	velocity;

	float	scale;
	float	life;
	char	pad0;
	char	pad1;
	char	pad2;
	char	pad3;
	char	pad4;
	char	pad5;
	char	pad6;
	char	pad7;

};


#endif //PARTICLE_H
