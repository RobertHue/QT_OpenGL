#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "graphics/Vertex.h"

// Create a colored triangle
static const Vertex sg_vertexes[] = {
	//Vertex( Position, Color)
	Vertex(QVector3D(0.00f,  0.75f, 1.0f),	QVector3D(1.0f, 0.0f, 0.0f)),
	Vertex(QVector3D(0.75f, -0.75f, 1.0f),	QVector3D(0.0f, 1.0f, 0.0f)),
	Vertex(QVector3D(-0.75f, -0.75f, 1.0f),	QVector3D(0.0f, 0.0f, 1.0f))
};

#endif // TRIANGLE_H