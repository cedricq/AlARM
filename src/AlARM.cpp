#include "AlARM.h"

namespace alarm
{

static AlARM_Manager& AlARM_Manager::GetInstance()
{
	static AlARM_Manager alm_mgr;
	return alm_mgr;
}


}

