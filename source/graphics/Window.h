#ifndef WINDOW_H
#define WINDOW_H
// see tutorial: https://www.trentreed.net/topics/opengl/

#include <chrono>

#include "graphics/Transform3D.h"

#include <QOpenGLWindow>

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_5_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLShaderProgram;


class Window
		:
		public QOpenGLWindow,
		protected QOpenGLFunctions_4_5_Core
{
		Q_OBJECT

				// OpenGL Events
public:
	Window(QWindow* parent = 0);
	~Window();
	virtual void initializeGL();					///to perform OpenGL resource initialization
	virtual void paintGL();							///to issue OpenGL commands or draw using QPainter
	virtual void resizeGL(int width, int height);	///to set up the transformation matrices and other window size dependent resources
	void teardownGL();								///to destroy opengl buffers and objects
protected slots:
		void update();

private:
		// OpenGL State Information
		QOpenGLBuffer m_vertex;
		QOpenGLVertexArrayObject m_object;
		QOpenGLShaderProgram* m_program;

private:
		// Shader Information
		int u_modelToWorld;
		int u_worldToView;
		QMatrix4x4 m_projection;
		Transform3D m_transform;

private:
		// Private Helpers
		void printContextInformation();	///to print information about the OpenGL Context we have acquired, for debugging purposes.

private:
		// Time for Animations
		typedef std::chrono::high_resolution_clock Clock;
		typedef std::chrono::high_resolution_clock::time_point TimePoint;
		typedef std::chrono::duration<double> dSeconds;
		TimePoint m_time;
		dSeconds  m_elapsedTime;
};

#endif // WINDOW_H