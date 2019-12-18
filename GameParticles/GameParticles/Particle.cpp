#include "Particle.h"
#include "Matrix.h"




void Particle::Update(const float& time_elapsed)
{
	Matrix tmp;
	float MatrixScale = tmp.Determinant();

	// serious math below - magic secret sauce
	life += time_elapsed;
	position += (velocity * time_elapsed);
	Vect4D z_axis(0.0f, -0.25f, 1.0f);
	Vect4D v(3.0f, 4.0f, 0.0f);
	position.Cross(z_axis, v);
	v.norm(v);
	position += v * 0.05f * life;
	rotation += MatrixScale + rotation_velocity * time_elapsed *2.01f;
}


// End of file


