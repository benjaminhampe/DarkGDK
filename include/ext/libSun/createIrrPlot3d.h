// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_HAMPE_CREATE_3D_PLOT_USING_IRRLICHT_H_INCLUDED__
#define __SUNLIB_HAMPE_CREATE_3D_PLOT_USING_IRRLICHT_H_INCLUDED__

#include <irrlicht.h>
#include <../source/Irrlicht/CImage.h>
#include <../source/Irrlicht/CGeometryCreator.h>
#include <../source/Irrlicht/CMeshManipulator.h>

#include "../irrDateTime.h"
#include "../irrTypedef.h"

#include "CSonnenstand.h"
#include "CSunCurve.h"
#include "CSunData.h"



namespace irr{

    /// Create a sun-graph plot as image

    IrrImage* createPlot3d( const IrrDim2u& size, CSunData* data );



    /// Create window that encapsulates another IGUIElement named 'content'

    IrrWindow* createWindow( const IrrStringW& title, IrrGUIElement* parent, IrrGUIElement* content, const IrrDim2u& size );



    // IrrImage* createPlot3d( const IrrDim2u& size, CSunData* data );


} // end namespace irr

#endif // __SUNLIB_HAMPE_CLASS_SONNENSTAND_H_INCLUDED__
