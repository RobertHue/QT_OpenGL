#include "graphics/Window.h"
#include "graphics/Vertex.h"
#include "vertex_data/Cube.h"

#include <iostream>
#include <cmath>

#include <QDir>
#include <QDebug>
#include <QString>

#include <QOpenGLShaderProgram>


Window::Window(QWindow* parent)
{
	std::cout << "Window" << std::endl;

	// Set OpenGL Version information
	// Note: This format must be set before show() is called.
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(4, 5);
	setFormat(format);

	m_transform.translate(0.0f, 0.0f, -5.0f);
}

Window::~Window()
{
	std::cout << "~Window" << std::endl;  
	makeCurrent();
	teardownGL();
}

void Window::initializeGL()
{
	std::cout << "init" << std::endl;

	// Init the time (for animations)
	m_time = Clock::now();

	// Initialize OpenGL Backend
	// ensure that the object has resolved the function pointers to the OpenGL functions
	initializeOpenGLFunctions();
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update())); //  schedule a redraw immediately after VSync (non-timer solution)
	printContextInformation();

	// Set global information
	glEnable(GL_CULL_FACE);	// draw faces which wind counter-clockwise
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Application-specific initialization
	{
		qDebug() << QDir::currentPath();

		// Create Shader (Do not release until VAO is created)
		m_program = new QOpenGLShaderProgram(this);
		bool bVertShaderAdded = m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/simple.vert");
		bool bFragShaderAdded = m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/simple.frag");
		bool bShaderLinking = m_program->link();
		bool bShaderBinding = m_program->bind();

		if (!bVertShaderAdded)	qDebug() << "vert shader could not be added";
		if (!bFragShaderAdded)	qDebug() << "frag shader could not be added";
		if (!bShaderLinking)	qDebug() << "shaders could not be linked";
		if (!bShaderBinding)	qDebug() << "shaders could not be binded";

		// Cache Uniform Locations - can fail => TODO error handling
		u_modelToWorld = m_program->uniformLocation("modelToWorld");
		u_worldToView  = m_program->uniformLocation("worldToView");

		if (u_modelToWorld == -1)	qDebug() << "uniformLocation could not be found";
		if (u_worldToView  == -1)	qDebug() << "uniformLocation could not be found";

		// Create Buffer (Do not release until VAO is created)
		m_vertex.create();
		m_vertex.bind();        
		m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

		// Create Vertex Array Object
		m_object.create();
		m_object.bind();    
		m_program->enableAttributeArray(0);
		m_program->enableAttributeArray(1);
		m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
		m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

		// Release (unbind) all
		m_object.release();
		m_vertex.release();
		m_program->release();
	}
}

void Window::paintGL()
{
	std::cout << "paintGL";

	// Clear
	glClear(GL_COLOR_BUFFER_BIT);

	const GLfloat color[] = { (float)std::sin(m_elapsedTime.count()) * 0.5f + 0.5f,
							  (float)std::cos(m_elapsedTime.count()) * 0.5f + 0.5f,
							  0.0f, 1.0f };
	//glClearBufferfv(GL_COLOR, 0, color);

	// Render using our shader
	m_program->bind();  
	m_program->setUniformValue(u_worldToView, m_projection);
	{
		m_object.bind();
		m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
		glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
		m_object.release();
	}
	m_program->release();
}

void Window::update()
{
	// Update elapsed time
	m_elapsedTime = Clock::now() - m_time;	// get elapsed time
	std::cout << "update t : " << std::fixed << m_elapsedTime.count() << std::endl;

	// Update instance information
	m_transform.rotate(1.0f, QVector3D(0.0f, 1.0f, 1.0f));
	m_transform.setScale((float)std::sin(m_elapsedTime.count()) * 0.5f + 0.5f);
	m_transform.setTranslation((float)std::sin(m_elapsedTime.count()), (float)std::cos(m_elapsedTime.count()), -5.0f);

	// Animate continuously: Schedule an Update hence Redraw
	QOpenGLWindow::update();
}

void Window::resizeGL(int width, int height)
{
	std::cout << "resizeGL" << std::endl;  

	m_projection.setToIdentity();
	m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void Window::teardownGL()
{  
	// Actually destroy our OpenGL information
	m_object.destroy();
	m_vertex.destroy();
	delete m_program;
}

/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void Window::printContextInformation()
{
	QString glType;
	QString glVersion;
	QString glProfile;

	// Get Version Information
	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

	// Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
	switch (format().profile())
	{
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	// qPrintable() will print our QString w/o quotes around it.
	qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}