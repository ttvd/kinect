/*
 *  display.h
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

#if !defined(KINECT_03_OPENGL_DISPLAY_H)
#define KINECT_03_OPENGL_DISPLAY_H

#include <QtGui/QDialog>
#include <QtCore/QtGlobal>
 
#if defined(Q_OS_WIN)
	#include <GL/glew.h>
#endif
 
#include <QtOpenGL/QGLWidget>

#include <vector>

//#include <Windows.h>
//#include <MSR_NuiApi.h>

class QTimer;
class QGLShaderProgram;

namespace Kinect
{
	class KinectThread;
	class Display;

	class Display : public QGLWidget
	{
		Q_OBJECT

		public:

			Display(QWidget* parent = NULL);
			virtual ~Display();

		protected:

			void loadShaders();

		protected:

			void initializeGL();
			void paintGL();
			void resizeGL(int width, int height);

		public:

			void drawColor(const unsigned char* data);

		protected:

			QTimer* m_timer_scene_update;

			unsigned int m_width;
			unsigned int m_height;

			bool m_initialized_opengl_resources;

			GLuint m_texture;
			QGLShaderProgram* m_shader_color;
	};
}

#endif //!defined(KINECT_03_OPENGL_DISPLAY_H)
