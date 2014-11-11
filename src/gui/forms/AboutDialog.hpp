/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2014 Thibault Polge. All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *                                                                [/licblock] */

#pragma once 

#include <iostream>

#include <QtCore/QObject>
#include <QtGui/QDesktopServices>
#include <QtCore/QString>

#include <Tkacz.hpp>
#include <Version.hpp>

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
