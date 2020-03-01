#include "WOWayPointAbstract.h"
#include "FontsWayPoints.h"
#include <vector>
#include <iostream>

namespace Aftr
{

WOWP1* WOWP1::New(const WayPointParametersBase& params, float radius )
{
   WOWP1* ptr = new WOWP1(params, radius);
   ptr->onCreate();
   return ptr;
}

WOWP1::WOWP1(const WayPointParametersBase& params, float radius
             ) : WOWayPointSpherical( params, radius ), IFace( this )
{
}

WOWP1::~WOWP1()
{
}

void WOWP1::onTrigger()
{
   std::cout << "Waypoint 1 Triggered!" << std::endl << std::endl;
}

} //namespace Aftr