#pragma once 

#include <QtWidgets/QWidget>

#include "ui_perspView.h"

namespace tzgui {

/*
 *
 */
class ViewPerspective: public QWidget, protected Ui::ViewPerspective {
public:
	ViewPerspective();
};

} /* namespace tkacz */
