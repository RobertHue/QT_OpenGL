#include "QT/MainWindow.h"

#include <iostream>
#include <cmath>

#include <QDebug>
#include <QString>


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
}

void MainWindow::paintGL()
{
	dSeconds secs = Clock::now() - m_time;	// get elapsed time
	std::cout << "paintGL t : " << std::fixed << secs.count() << std::endl;


	const GLfloat color[] = { (float)std::sin(secs.count()) * 0.5f + 0.5f,
							  (float)std::cos(secs.count()) * 0.5f + 0.5f,
							  0.0f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, color);


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
	// Currently we have no data to teardown
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