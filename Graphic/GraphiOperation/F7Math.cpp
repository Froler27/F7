#include "F7Math.h"

namespace F7 {
	bool F7Equal(double L, double R)
	{
		double dTem = L - R;
		if (dTem < ESP_DOUBLE && dTem > -ESP_DOUBLE)
			return true;
		else
			return false;
	}


}
