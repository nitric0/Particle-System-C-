#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"

#include <list>

class __declspec(align(16)) ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	ParticleEmitter(const ParticleEmitter &tmp) = delete;
	ParticleEmitter & operator = (const ParticleEmitter &tmp) = delete;

	void SpawnParticle();
	void update();
	void draw();

	void addParticleToList(Particle *p);
	void removeParticleFromList(Particle *p);

	void *operator new(size_t size)
	{
		void *p = _aligned_malloc(size, 16);
		return p;
	}

	void *operator new[](size_t size)
	{
		void *p = _aligned_malloc(size, 16);
		return p;
	}

		void operator delete(void *p)
	{
		_aligned_free(p);
	}

	void operator delete[](void *p)
	{
		_aligned_free(p);
	}


	//void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);
	void Execute(Vect4D& pos, Vect4D& vel, float& sc);

private:
	Particle * headParticle;
	Particle *tailParticle;
	int		last_active_particle;
	float	spawn_frequency;

	Vect4D	start_position;
	Vect4D	start_velocity;
	Vect4D	vel_variance;
	Vect4D	pos_variance;

	float	max_life;
	int		max_particles;
	float	last_spawn;
	float	last_loop;


	// added for speed efficiency


};

#endif // PARTICLEEMITTER_H
