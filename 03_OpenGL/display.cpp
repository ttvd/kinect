/*
 *  display.cpp
 *  Kinect demo.
 *
 *  display widget.
 *
 *  Created by radix on 06/30/11.
 *  Copyright Mykola Konyk, <mykola@konyk.org>, 2011.
 *
 *  This code is under Microsoft Reciprocal License (Ms-RL)
 *  Please see http://www.opensource.org/licenses/ms-rl.html
 *
 *  Important points about the license (from Ms-RL):
 *
 *  [A] For any file you distribute that contains code from the software (in source code or binary format), you must provide
 *  recipients the source code to that file along with a copy of this license, which license will govern that file.
 *  You may license other files that are entirely your own work and do not contain code from the software under any terms
 *  you choose.
 *
 *  [B] No Trademark License- This license does not grant you rights to use any contributors' name, logo, or trademarks.
 *
 *  [C] If you bring a patent claim against any contributor over patents that you claim are infringed by the software, your
 *  patent license from such contributor to the software ends automatically.
 *
 *  [D] If you distribute any portion of the software, you must retain all copyright, patent, trademark, and attribution notices
 *  that are present in the software.
 *
 *  [E] If you distribute any portion of the software in source code form, you may do so only under this license by including a
 *  complete copy of this license with your distribution. If you distribute any portion of the software in compiled or object
 *  code form, you may only do so under a license that complies with this license.
 *
 *  [F] The software is licensed "as-is." You bear the risk of using it. The contributors give no express warranties, guarantees
 *  or conditions. You may have additional consumer rights under your local laws which this license cannot change. To the extent
 *  permitted under your local laws, the contributors exclude the implied warranties of merchantability, fitness for a particular
 *  purpose and non-infringement.
 *
 */

#include <display.h>

#include <QtCore/QTimer>
#include <QtCore/QDebug>

#include <QtOpenGL/QGLShaderProgram>

namespace Kinect
{
	//--
	Display::Display(QWidget* parent) :
	QGLWidget(parent),
	m_timer_scene_update(NULL),
	m_width(0),
	m_height(0),
	m_texture(0),
	m_initialized_opengl_resources(false),
	m_shader_color(NULL)
	{
		// [rad] Create GL update timer.
		m_timer_scene_update = new QTimer(this);
		connect(m_timer_scene_update, SIGNAL(timeout()), this, SLOT(updateGL()));
		m_timer_scene_update->start(0);
	}	


	//--
	Display::~Display()
	{
		if(m_texture)
		{
			glDeleteTextures(1, &m_texture);
		}	
	}


	//--
	void
	Display::loadShaders()
	{
		m_shader_color = new QGLShaderProgram(this);

		if(!m_shader_color->addShaderFromSourceFile(QGLShader::Vertex, ":/shader_color.vert"))
		{
			qDebug() << "Vertex shader 'color' was not found or failed to compile.";
			qDebug() << m_shader_color->log();
		}

		if(!m_shader_color->addShaderFromSourceFile(QGLShader::Fragment, ":/shader_color.frag"))
		{
			qDebug() << "Fragment shader 'color' was not found or failed to compile.";
			qDebug() << m_shader_color->log();
		}
	}


	//--
	void
	Display::resizeGL(int width, int height)
	{
		m_width = width;
		m_height = height;
		
		if(!m_height)
		{
			m_height = 1;
		}	

		glViewport(0, 0, m_width, m_height);
	}


	//--
	void
	Display::initializeGL()
	{
		QGLWidget::initializeGL();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 

		#if defined(Q_OS_WIN)

			// [rad] Initialize glew.
			GLenum err = glewInit();

			if(GLEW_OK != err)
			{
				qDebug() << "Error initializing GLEW " << glewGetErrorString(err);
			}

		#endif

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}


	//--
	void
	Display::paintGL()
	{
		if(!m_initialized_opengl_resources)
		{
			if(!wglGetCurrentContext())
			{
				return;
			}

			loadShaders();	
			m_initialized_opengl_resources = true;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		// [rad] We have no texture to draw.
		if(!m_texture)
		{
			return;
		}

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		m_shader_color->bind();
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, m_texture);
		m_shader_color->setUniformValue("tex", 0);

		glBegin(GL_QUADS); 
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
        
        	glTexCoord2f(0, 1); 
        	glVertex3f(-1.0f,-1.0f,0); 
        
        	glTexCoord2f(1, 1); 
        	glVertex3f(1.0f,-1.0f,0); 
        
        	glTexCoord2f(1, 0); 
        	glVertex3f(1.0f,1.0f,0); 
        
        	glTexCoord2f(0, 0); 
        	glVertex3f(-1.0f,1.0f,0); 

        glEnd(); 


		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		m_shader_color->release();
		
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	

	//--
	void
	Display::drawColor(const unsigned char* data)
	{
		if(!m_texture)
		{
			glGenTextures(1, &m_texture);
			glBindTexture(GL_TEXTURE_2D, m_texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		}	

		glBindTexture(GL_TEXTURE_2D, m_texture);		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, &data[0]);
	}


}
