#include <stdio.h>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

#define GLM_FORCE_RADIANS
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

glm::vec3
WhatPartOfALivesInBDir( glm::vec3 a, glm::vec3 b )
{
		glm::vec3 c;
		c = normalize(b);
		return(c * dot(a, c));
}


glm::vec3
WhatPartOfALivesPerpToB( glm::vec3 a, glm::vec3 b )
{
	glm::vec3 c;
	c = normalize(b);
	return(a - (c * dot(a, b)));
}




glm::vec3
UnitSurfaceNormal( glm::vec3 q, glm::vec3 r, glm::vec3 s )
{
	glm::vec3 a, b, c;
	a = (r - q);
	b = (s - q);

	c = cross(a, b);

	return(normalize(c));
}


float
Area( glm::vec3 q, glm::vec3 r, glm::vec3 s )
{
	 return(0.5 * length(cross((r-q),(s-q))));
}


bool
IsPointInTriangle( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p )
{
	glm::vec3 n, nq, nr, ns;
	n = cross((r-q), (s-q));
	nq = cross((r-q), (p-q));
	nr = cross((s-r), (p-r));
	ns = cross((q-s), (p-s));

	if( (dot(n, nq) > 0) && (dot(n, nr) > 0)  && (dot(n, ns) > 0)){
		return true;
	}
	return false;

}



float
DistanceFromPointToPlane( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p )
{
	glm::vec3 n;
	n = UnitSurfaceNormal(q, r, s);
	return(dot(normalize(n), (p - q)));
}


void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
	yourName = "Trent Vasquez";
	yourEmailAddress = "vasquezt@oregonstate.edu" ;
}
/*
int main(){
	glm::vec3 a(0, 4, 0);
	glm::vec3 b(4, 8, 0);
	glm::vec3 c(0, 9, 2);
	glm::vec3 d(4, -4, 3);
	glm::vec3 e;


	e = UnitSurfaceNormal(a, b, c);	
	printf("UnitSurfaceNormal = %f, %f, %f\n", e.x, e.y, e.z);
	
	float anw;
	anw = DistanceFromPointToPlane(a, b, c, d);
	printf("Distance From point to plane %f\n", anw);
	return 0;
}
*/
