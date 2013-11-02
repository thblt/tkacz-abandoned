#pragma once

#include "types.h"

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
