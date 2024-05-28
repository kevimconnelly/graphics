#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	//ID referece for the vertex array object
	GLuint ID;

	//Constructor that generate VAO ID
	VAO();

	//Links a VBO to the VAO using a certain laout
	void LinkVBO(VBO& VBO, GLuint layout);

	//Bings the VAO
	void Bind();

	//Unbinds the VAO
	void Unbind();

	//Deletes the VAO
	void Delete();
};
#endif
