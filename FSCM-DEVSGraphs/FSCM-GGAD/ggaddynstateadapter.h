


#ifndef __GGAD_DYNAMICSTATEADAPTER_H__
#define __GGAD_DYNAMICSTATEADAPTER_H__

#include "ggaddynstate.h"
#include "ggadmsglist.h"

/** This class follos the adapter pattern to let its clients access the current dynamic state of the model without having to access it directly.
*/

class GgadDynamicStateAdapter {
    GgadDynamicState &dynState_;

public:
    GgadDynamicStateAdapter( GgadDynamicState &dynState )
    : dynState_(dynState)
    {}

    GgadDynamicState &getDynamicState() { return dynState_; }

};

#endif // __GGAD_DYNAMICSTATEADAPTER_H__


