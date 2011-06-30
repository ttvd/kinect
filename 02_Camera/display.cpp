/*
 *  display.cpp
 *  Kinect demo.
 *
 *  Display.
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

#include <QtGui/QLabel>
#include <QtGui/QImage>

namespace Kinect
{
	//--
	Display::Display(QLabel* label, unsigned int width, unsigned int height, QObject* parent) :
	m_label(label),
	QObject(parent),
	m_width(width),
	m_height(height)
	{
		// [rad] Allocate buffer for image data.
		m_buffer = new unsigned char[width * height * 4];
	}


	//--
	Display::~Display()
	{
		delete[](m_buffer);	
	}


	//--
	void 
	Display::DrawColor(const unsigned char* data)
	{
		QImage qimage((const unsigned char*) data, m_width, m_height, QImage::Format_RGB32);
    	m_label->setPixmap(QPixmap::fromImage(qimage.scaled(m_label->frameSize())));
	}


	//--
	void 
	Display::DrawDepth(const unsigned char* data)
	{
		unsigned short* depth = (unsigned short*) data;

		unsigned int stride = m_width * 4;
		unsigned int off_x = 0;

		unsigned short data_depth;
		unsigned char depth_intensity;

		for(unsigned int idx_y = 0; idx_y < m_height; idx_y++)
    	{
    		for(unsigned int idx_x = 0; idx_x < m_width;)
    		{
    			// [rad] Mask out top 4 bits just to be sure.
    			data_depth = *depth & 0x0FFF;
    			depth++;    

    			// [rad] Normalize depth buffer and also invert, looks brighter.
    			depth_intensity = 255 - static_cast<unsigned char>((data_depth / 4096.0f) * 255.0f);				
				
				// [rad] Kinect seems to give horz inverted image, why?
    			m_buffer[idx_y * stride + stride - idx_x - off_x - 4] = depth_intensity;
    			m_buffer[idx_y * stride + stride - idx_x - off_x - 3] = depth_intensity;
    			m_buffer[idx_y * stride + stride - idx_x - off_x - 2] = depth_intensity;
    			m_buffer[idx_y * stride + stride - idx_x - off_x - 1] = 255;

    			idx_x++;
    			off_x += 3;
    		}

    		off_x = 0;
    	}

    	QImage qimage((const unsigned char*) m_buffer, m_width, m_height, QImage::Format_RGB32);
    	m_label->setPixmap(QPixmap::fromImage(qimage.scaled(m_label->frameSize())));
	}
}
