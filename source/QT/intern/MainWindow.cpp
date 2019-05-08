#include "QT/MainWindow.h"

#include <iostream>
#include <cmath>

#include <QDir>
#include <QDebug>
#include <QString>

#include <QOpenGLShaderProgram>

#include "QT/Vertex.h"

// Create a colored triangle
static const Vertex sg_vertexes[] = {
  Vertex(QVector3D(0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)),
  Vertex(QVector3D(0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)),
  Vertex(QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f))
};

MainWindow::MainWindow(QWindow* parent)
	//:	
{
	std::cout << "MainWindow" << std::endl;

	// Tell Qt we will use OpenGL for this window
	//setSurfaceType(OpenGLSurface);

	// Set OpenGL Version information
	// Note: This format must be set before show() is called.
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(4, 5);
	setFormat(format);

	/*
	// Create an OpenGL context
	//m_context = new QOpenGLContext;
	//m_context->setFormat(format);
	//m_context->create();

	// Setup our scene
	//m_context->makeCurrent(this);
	//m_scene->setContext(m_context);
	//initializeGL();

	// Make sure we tell OpenGL about new window sizes
	//connect(this, SIGNAL(widthChanged(int)), this, SLOT(resizeGL()));
	//connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGL()));
	//resizeGL();*/
}

MainWindow::~MainWindow()
{
	std::cout << "~MainWindow" << std::endl;  
	makeCurrent();
	teardownGL();
}

void MainWindow::initializeGL()
{
	std::cout << "init" << std::endl;

	// Initialize OpenGL Backend
	// ensure that the object has resolved the function pointers to the OpenGL functions
	initializeOpenGLFunctions();
	printContextInformation();

	// Set global information
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_time = Clock::now();

	// Application-specific initialization
	{
		qDebug() << QDir::currentPath();

		// Create Shader (Do not release until VAO is created)
		m_program = new QOpenGLShaderProgram();
		m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/simple.vert");
		m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/simple.frag");
		m_program->link();
		m_program->bind();

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

void MainWindow::paintGL()
{
	dSeconds secs = Clock::now() - m_time;	// get elapsed time
	std::cout << "paintGL t : " << std::fixed << secs.count() << std::endl;


	const GLfloat color[] = { (float)std::sin(secs.count()) * 0.5f + 0.5f,
							  (float)std::cos(secs.count()) * 0.5f + 0.5f,
							  0.0f, 1.0f };


	// Clear
	glClear(GL_COLOR_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, color);

	// Render using our shader
	m_program->bind();
	{
		m_object.bind();
		glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
		m_object.release();
	}
	m_program->release();

	// animate continuously: schedule an update
	update();
}

void MainWindow::resizeGL(int width, int height)
{
	std::cout << "resizeGL" << std::endl;  
	
	// Currently we are not handling width/height changes
	(void)width;
	(void)height;
}

void MainWindow::teardownGL()
{  
	// Actually destroy our OpenGL information
	m_object.destroy();
	m_vertex.destroy();
	delete m_program;
}

/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void MainWindow::printContextInformation()
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