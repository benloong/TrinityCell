//
//  scriptable.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef __TrinityCell__scriptable__
#define __TrinityCell__scriptable__

#include "component.h"

class Scriptable : public DCS::Component_T<Scriptable, 4096>
{
    int scriptID;
    
};

#endif /* defined(__TrinityCell__scriptable__) */
