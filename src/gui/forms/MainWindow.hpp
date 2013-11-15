/** \addtogroup gui
 * \{
 */

#pragma once

#include "Base_MainWindow.hpp"
#include "AboutDialog.hpp"

#include <QtWidgets/QMainWindow>
#include <QtCore/QObject>

namespace tzgui {

/** @ingroup gui forms */
class MainWindow: public QMainWindow, public Base_MainWindow {

	Q_OBJECT

public:
	MainWindow();
	virtual ~MainWindow();

public slots:
	void on_app_about_triggered();


};

}
