#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <chrono>

#include <QOpenGLWindow>

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_5_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLShaderProgram;

/**
A typical application will subclass QOpenGLWindow and reimplement the following virtual functions:

	initializeGL() to perform OpenGL resource initialization
	resizeGL() to set up the transformation matrices and other window size dependent resources
	paintGL() to issue OpenGL commands or draw using QPainter
*/
class MainWindow 
	: 
	public QOpenGLWindow,
	protected QOpenGLFunctions_4_5_Core
{
	Q_OBJECT
	
public:
	MainWindow(QWindow* parent = 0);
	~MainWindow();
	void teardownGL();

protected:
	/*	This virtual function is called once before the first call to paintGL() or resizeGL(). Reimplement it in a subclass.
		This function should set up any required OpenGL resources and state. = startup()*/
	virtual void initializeGL();

	/*	This virtual function is called whenever the window contents needs to be painted.Reimplement it in a subclass. = run?*/
	virtual void paintGL();

	/*	This virtual function is called whenever the widget has been resized. Reimplement it in a subclass. 
		The new size is passed in w and h. avoid opengl calls here*/
	virtual void resizeGL(int width, int height);

private:
	/* helper function will print information about the OpenGL Context we have acquired, for debugging purposes. */
	void printContextInformation();

private:
	static constexpr GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };  
	
	// OpenGL State Information
	QOpenGLBuffer m_vertex;
	QOpenGLVertexArrayObject m_object;
	QOpenGLShaderProgram* m_program;

private:
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::high_resolution_clock::time_point TimePoint;
	typedef std::chrono::duration<double> dSeconds;
	TimePoint m_time;
};

#endif // MAINWINDOW_H


/* INFO_01:
	You do not need to subclass to access the functionality of QOpenGLFunctions,
	if you’d rather, you may grab the available functions via QOpenGLContext.
	This may be instantiated as a local variable in one of two ways:

	QOpenGLFunctions functions(QOpenGLContext::currentContext());
	functions.glFunctionHere();
	// or...
	QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();
	functions->glFunctionHere();
*/