/** \addtogroup gui
 * \{
 */

#pragma once

#include "Base_MainWindow.hpp"
#include "AboutDialog.hpp"

#include <QtCore/QObject>

namespace tzgui {

/** @ingroup gui forms */
class MainWindow: public Base_MainWindow {

	Q_OBJECT

public:
	MainWindow();

public slots:
	void on_app_about_triggered();


};

}
