/*
 * TZIO.h
 *
 *  Created on: 1 nov. 2013
 *      Author: thblt
 */

#pragma once

namespace tkacz {

virtual class DataBridge {
public:
	virtual Card getCard(int id);
	virtual int len();

	virtual bool close();

	virtual DataBridge();
	virtual ~DataBridge();
};

}
