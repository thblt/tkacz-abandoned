#pragma once 

#include <iostream>

#include <QtCore/QObject>
#include <QtGui/QDesktopServices>
#include <QtCore/QString>

#include <Tkacz.hpp>

#include "ui_dlgAbout.h"

namespace tzgui {

/*
 *
 */
class AboutDialog: public QDialog, public Ui_AboutDialog {

Q_OBJECT

public:
	AboutDialog() {
		setupUi(this);
		setModal(true);
		setWindowFlags(Qt::Popup);
		versionLabel->setText(
				versionLabel->text().arg(
						QString(((std::string) tkacz::Tkacz::version).c_str()),
						tkacz::Tkacz::version.name.c_str()));
	}
	virtual ~AboutDialog() {
	}

public slots:
	void on_versionLabel_linkActivated(const QString & link) {
		textBrowser->setSource(QUrl(link));
		pages->setCurrentIndex(1);
	}
	void on_linkLabel_linkActivated(const QString &link) {
		QDesktopServices::openUrl(link);
	}

	void on_backButton_clicked() {
		pages->setCurrentIndex(0);
	}

	void on_textBrowser_anchorClicked(const QUrl& link) {
		QDesktopServices::openUrl(link);
	}
};

}
