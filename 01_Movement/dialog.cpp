/*
 *  dialog.cpp
 *  Kinect demo.
 *
 *  Main ui dialog.
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

#include <dialog.h>
#include <ui_kinect.h>

#include <Windows.h>
#include <MSR_NuiApi.h>

namespace Kinect
{
	//--
	Dialog::Dialog() :
	QDialog(0, Qt::Dialog | Qt::WindowMinimizeButtonHint),
	m_ui(new Ui::Dialog()),
	m_kinect_angle(0)
	{
		// [rad] Setup ui for this dialog.
		setupUi();

		setWindowTitle(tr("Kinect Demo 01: Movement"));

		// [rad] Disable resizing.
		setSizeGripEnabled(false);
		setFixedSize(width(), height());

		// [rad] Initialize kinect.
		kinectInitialize();
	}


	//--
	Dialog::~Dialog()
	{
		// [rad] Shutdown kinect.
		kinectFinalize();

		if(m_ui)
		{
			delete(m_ui);
		}
	}


	//--
	void
	Dialog::setupUi()
	{
		// [rad] Construct internal Qt dialog ui.
		m_ui->setupUi(this);

		// [rad] Connect callbacks and setup gui elements.
		QObject::connect(m_ui->button_up, SIGNAL(clicked()), this, SLOT(eventButtonUp()));
		QObject::connect(m_ui->button_down, SIGNAL(clicked()), this, SLOT(eventButtonDown()));
		QObject::connect(m_ui->button_center, SIGNAL(clicked()), this, SLOT(eventButtonCenter()));
	}


	//--
	void
	Dialog::kinectInitialize()
	{
		// [rad] We don't need any of the advaced features.
		::NuiInitialize(NUI_INITIALIZE_FLAG_USES_COLOR);

		eventButtonCenter();
	}


	//--
	void
	Dialog::kinectFinalize()
	{
		::NuiShutdown();	
	}


	//--
	void
	Dialog::eventButtonCenter()
	{
		m_kinect_angle = 0;
		::NuiCameraElevationSetAngle(m_kinect_angle);
	}


	//--
	void
	Dialog::eventButtonUp()
	{
		// [rad] Check so that we don't go over max elevation.
		if(m_kinect_angle + 5 > NUI_CAMERA_ELEVATION_MAXIMUM)
		{
			return;
		}

		m_kinect_angle += 5;
		::NuiCameraElevationSetAngle(m_kinect_angle);
	}


	//--
	void
	Dialog::eventButtonDown()
	{
		// [rad] Check so that we don't go over max elevation.
		if(m_kinect_angle - 5 < NUI_CAMERA_ELEVATION_MINIMUM)
		{
			return;
		}

		m_kinect_angle -= 5;
		::NuiCameraElevationSetAngle(m_kinect_angle);
	}
}
