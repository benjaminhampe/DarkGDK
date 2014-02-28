// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "createIrrPlot3d.h"

namespace irr{

    IrrImage* createPlot3d( const IrrDim2u& size, CSunData* data )
    {
        IrrImage* img = new video::CImage( video::ECF_A8R8G8B8, size);
        if (!img)
            return 0;

        return img;
    }

} // end namespace irr
