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

glm::mat4
Multiply( glm::mat4 a, glm::mat4 b )
{
	return(a * b);
}



glm::vec3
Multiply( glm::mat4 a, glm::vec3 b )
{
	glm::vec4 c, d;
	glm::vec3 anw;
	c[0] = b[0]; c[1] = b[1]; c[2] = b[2]; c[3] = 1;
	d = c * a;
	anw[0] = d[0]; anw[1] = d[1]; anw[2] = d[2];
	return anw;
}



glm::vec3
ScalePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale )
{
	glm::vec3 temp = inputPoint - centerPoint;
	glm::vec4 a(scale[0], 0, 0, 0);
	glm::vec4 b(0, scale[1], 0, 0);
	glm::vec4 c(0, 0, scale[2], 0);
	glm::vec4 d(0, 0, 0, 1);
	glm::mat4 a1(a, b, c, d);
	temp = Multiply(a1, temp);
	return(temp + centerPoint);
}



glm::vec3
RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third )
{
	glm::vec3 temp = inputPoint - centerPoint;
	temp = Multiply(first, temp);
	temp = Multiply(second, temp);
	temp = Multiply(third, temp);
	temp = temp + centerPoint;
	return temp;
}


void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
	yourName = "Trent Vasquez";
	yourEmailAddress = "vasquezt@oregonstate.edu" ;
}


void
PrintMatrix( glm::mat4 mat )
{
	for( int row = 0; row < 4; row++ )
	{
		fprintf( stderr, "  %7.2f %7.2f %7.2f %7.2f\n", mat[row][0], mat[row][1], mat[row][2], mat[row][3] );
	}
}
/*
int main(){
	
	glm::vec4 a(2, 2, 2, 2);
	glm::vec4 b(4, 4, 4, 4);
	glm::vec4 c(6, 6, 6, 6);
	glm::vec4 d(8, 8, 8, 8);
	glm::vec3 a3(2, 2, 2);
	glm::vec3 b3(1, 2, 3);
	glm::vec3 c3(4, 4, 4);
	glm::vec3 t3;

	glm::mat4 a1(a, b, c, d);

	t3 = ScalePointAroundAnotherPoint(b3, c3, a3);
	printf("vec 3 return %f, %f, %f\n", t3[0], t3[1], t3[2]); 

}
*/
