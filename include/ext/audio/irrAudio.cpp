#include "irrAudio.h"

#include <irrlicht.h>

#include "CMatrix.h"

//#include "../irrImage.h"

#include "IColorGradient.h"

namespace irr{

core::stringc currentDateString( ITimer * timer )
{
	core::stringc txt = "";

	if (timer)
	{
		ITimer::RealTimeDate date = timer->getRealTimeAndDate();
		txt += date.Year; txt += "_";
		if ( date.Month < 10 ) txt += "0";
		txt += date.Month; txt += "_";
		if ( date.Day < 10 ) txt += "0";
		txt += date.Day;
	}

	return txt;
}

core::stringc currentTimeString( ITimer * timer )
{
	core::stringc txt = "";

	if (timer)
	{
		ITimer::RealTimeDate date = timer->getRealTimeAndDate();
		if ( date.Hour < 10 ) txt += "0";
		txt += date.Hour; txt += "_";
		if ( date.Minute < 10 ) txt += "0";
		txt += date.Minute; txt += "_";
		if ( date.Second < 10 ) txt += "0";
		txt += date.Second; txt += "_";
		txt += timer->getRealTime();
	}

	return txt;
}

core::stringc currentDateTimeString( ITimer * timer )
{
	core::stringc txt = "";

	if (timer)
	{
		txt = currentDateString( timer );
		txt += "_";
		txt = currentTimeString( timer );
	}

	return txt;
}

core::stringc getHMS_fromMillis( u32 time_in_ms )
{
	core::stringc txt = "";
	u32 hh = time_in_ms / (3600*1000);
	time_in_ms -= hh*3600*1000;
	u32 mm = time_in_ms / (60*1000);
	time_in_ms -= mm*60*1000;
	u32 ss = time_in_ms / 1000;
	time_in_ms -= ss*1000;
	if (hh<10) { txt += "0"; } txt += hh;
	txt += ":";
	if (mm<10) { txt += "0"; } txt += mm;
	txt += ":";
	if (ss<10) { txt += "0"; } txt += ss;
	txt += ".";
	if (time_in_ms<100)	{ txt += "0"; }
	if (time_in_ms<10)	{ txt += "0"; }
	txt += time_in_ms;
	return txt;
}

core::stringc getHMS_fromSeconds( f32 time_in_s )
{
	return getHMS_fromMillis( (u32)core::floor32( time_in_s * 1000.0f) );
}

namespace sfx
{

/// causes memory BUG, dont use, but i really dont know why
/// i guess something already went wrong at allocating input and output
/// so its maybe not the function itself
bool ApplyHammingWindow( f64* input, f64* output, u32 sample_count )
{
	if (!input)
		return false;

	if (!output)
		return false;

	if (sample_count == 0)
		return false;

	for (u32 i=0; i<sample_count; i++)
	{
		f64 n = -0.5f*sample_count + i;
		f64 f = 0.54 + 0.46*cos( 2.0*core::PI64*n / sample_count );
		f64 tmp = input[i] * f;
		output[i] = tmp;
	}

	return true;
}

f32 getFrequencyFromNote( s32 C_is_zero, s32 oktave )
{
	return 440.f*powf(2.f,(f32)((C_is_zero%12) + (12*oktave) - 69)/12.f);
}



core::array<core::stringc> scanFolderForAudioFiles( const core::stringc& root, s32 recursive_depth )
{
	core::array<core::stringc> container(0);

	return container;
}


//	bool drawLine( video::IImage* dst, const core::rectf& pos, const SColor& color );
//
//	bool drawLine( video::IImage* dst, const core::rectf& pos, const SColor& a, const SColor& b );

//! draw a Bresenham-line with 1 ARGB color that can be transparent to underground (src) pixel ( alpha < 255 )
bool drawLine( video::IImage* dst, const core::rectf& pos, const video::SColor& color )
{
	if (!dst)
		return false;

	const core::dimension2du img_size = dst->getDimension();

	if ( ( img_size.Width == 0 ) || ( img_size.Height == 0 ) )
		return false;

	const s32 x0 = core::round32( pos.UpperLeftCorner.X );
	const s32 y0 = core::round32( pos.UpperLeftCorner.Y );
	const s32 x1 = core::round32( pos.LowerRightCorner.X );
	const s32 y1 = core::round32( pos.LowerRightCorner.Y );

	const s32 dx = core::abs_<s32>( x1 - x0 );
	const s32 dy = core::abs_<s32>( y1 - y0 );

	if (dx==0 && dy==0)
		return false;

	s32 sx = 1; // sign
	s32 sy = 1; // sign

	if (x0 > x1)
		sx = -1;
	if (y0 > y1)
		sy = -1;

	s32 err = dx-dy;
	s32 e2 = 0;
	s32 x = x0;
	s32 y = y0;

	while (1)
	{
		if ( (x>=0) && (y>=0) && (x<(s32)img_size.Width) && (y<(s32)img_size.Height) )
		{
			dst->setPixel(x,y,color,true);
		}

		if (x == x1 && y == y1)
			break;

		e2 = err << 1;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
	return true;

}

bool drawLine( video::IImage* dst, const core::rectf& pos, const video::SColor& color_a, const video::SColor& color_b )
{
	if (!dst)
		return false;

	const core::dimension2du img_size = dst->getDimension();

	if ( ( img_size.Width == 0 ) || ( img_size.Height == 0 ) )
		return false;

	const s32 x0 = core::round32( pos.UpperLeftCorner.X );
	const s32 y0 = core::round32( pos.UpperLeftCorner.Y );
	const s32 x1 = core::round32( pos.LowerRightCorner.X );
	const s32 y1 = core::round32( pos.LowerRightCorner.Y );

	const s32 dx = core::abs_<s32>( x1 - x0 );
	const s32 dy = core::abs_<s32>( y1 - y0 );

	if (dx==0 && dy==0)
		return false;

	s32 sx = 1; // sign
	s32 sy = 1; // sign

	if (x0 > x1)
		sx = -1;
	if (y0 > y1)
		sy = -1;

	s32 err = dx-dy;
	s32 e2 = 0;
	s32 x = x0;
	s32 y = y0;

	s32 numpixels = 0;

	// count pixels
	while (1)
	{
		numpixels++;

		if (x == x1 && y == y1)
			break;

		e2 = err << 1;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}

	}

	// reset vars;
	err = dx-dy;
	e2 = 0;
	x = x0;
	y = y0;

	// values for linear color interpolation
	const f32 A1=(f32)color_a.getAlpha();
	const f32 R1=(f32)color_a.getRed();
	const f32 G1=(f32)color_a.getGreen();
	const f32 B1=(f32)color_a.getBlue();
	const f32 dA=(f32)color_b.getAlpha()-A1;
	const f32 dR=(f32)color_b.getRed()-R1;
	const f32 dG=(f32)color_b.getGreen()-G1;
	const f32 dB=(f32)color_b.getBlue()-B1;

	// actual drawing
	f32 f=0.f;
	s32 k=0;
	u32 cR=0, cG=0, cB=0, cA=0;
	while (1)
	{
		f = (f32)k/(f32)numpixels;
		k++;

		cA=A1;
		cR=R1;
		cG=G1;
		cB=B1;

		// maybe faster under the assumption that colors have most likely same alpha value
		if (dA>0) cA = (u32)core::clamp( core::round32(A1+dA*f), 0, 255);
		if (dR>0) cR = (u32)core::clamp( core::round32(R1+dR*f), 0, 255);
		if (dG>0) cG = (u32)core::clamp( core::round32(G1+dG*f), 0, 255);
		if (dB>0) cB = (u32)core::clamp( core::round32(B1+dB*f), 0, 255);

		if ( (x>=0) && (y>=0) && (x<(s32)img_size.Width) && (y<(s32)img_size.Height) )
		{
			dst->setPixel(x,y,video::SColor( cA, cR, cG, cB), true);
		}

		if (x == x1 && y == y1)
			break;

		e2 = err << 1;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
	return true;
}

bool shiftMeshBuffer( scene::SMesh* mesh, s32 shifts )
{
    printf( "shiftMeshBuffer( shifts = %d, buffercount = %d )\n", shifts, (mesh)?mesh->getMeshBufferCount():0 );

	if (!mesh)
		return false;

    if (shifts==0)
		return false;


	shifts = core::abs_<s32>( shifts );

	const u32 bufferCount = mesh->getMeshBufferCount();

	for (u32 b=0; b<bufferCount; b++)
	{
		u32 k = ( (u32)shifts + b )%bufferCount;

		/// save value at target position
		scene::IMeshBuffer* tmp = mesh->MeshBuffers[ k ];

		/// overwrite target position with new value
		mesh->MeshBuffers[ k ] = mesh->MeshBuffers[ b ];

		/// overwrite source position with save row-data
		mesh->MeshBuffers[ b ] = tmp;
	}

    return true;
}

bool createFilledPath(
	scene::SMeshBuffer* buffer,
	const core::dimension2df& size,
	const core::array<f32>& points,
	video::IColorGradient* gradient,
	const core::vector3df& offset )

{
	if (!buffer)
		return false;

	const u32 pointCount = points.size();

	const f32 step_x = size.Width*core::reciprocal( (f32)(pointCount-1) );

	const video::E_MATERIAL_TYPE matType = (gradient)?gradient->getMaterialType():video::EMT_SOLID;

	/// !!! User defined constant for maximum dB value
	const f32 diff_y_inv = core::reciprocal( 160.0f );

	buffer->Vertices.reallocate( 4*(pointCount-1) );
	buffer->Vertices.set_used( 0 );
	buffer->Indices.reallocate( 6*(pointCount-1) );
	buffer->Indices.set_used( 0 );

	buffer->Material.MaterialType = matType;
	buffer->Material.Lighting = false;
	buffer->Material.Wireframe = false;
	buffer->Material.FogEnable = false;
	buffer->Material.BackfaceCulling = false;
	buffer->Material.AntiAliasing = video::EAAM_QUALITY;
	buffer->Material.UseMipMaps = false;
	buffer->Material.TextureLayer[0].BilinearFilter = true;
	buffer->Material.TextureLayer[0].TrilinearFilter = true;
	buffer->Material.TextureLayer[0].AnisotropicFilter = 4;

	const video::SColor bgColor = gradient->getColor( 0.0f );

	const f32 scale_y = size.Height * diff_y_inv;

	for (u32 i=0; i<pointCount-1; i++)
	{
		f32 y1 = 0.f;
		f32 y2 = 0.f;

		if (i<pointCount) y1 = points[i];
		if (i+1<pointCount) y2 = points[i+1];

		video::SColor color1 = 0xffffffff;
		video::SColor color2 = 0xffffffff;
		if (gradient)
		{
			f32 t1 = core::abs_<f32>(y1)*diff_y_inv;
			f32 t2 = core::abs_<f32>(y2)*diff_y_inv;
			color1 = gradient->getColor( t1 );
			color2 = gradient->getColor( t2 );
		}

		/// @todo: reuse vertices to avoid flickering due to rounding errors
		/// @todo: set material AF
		/// @todo: set material AA

		video::S3DVertex A,B,C,D;
		A.Pos = offset+core::vector3df((f32)i*step_x,0.f,0.f);
		A.Normal = core::vector3df( 0,0,-1);
		A.Color = bgColor;
		A.TCoords = core::vector2df(0,0);
		B.Pos = offset+core::vector3df((f32)i*step_x,scale_y*y1,0.f);
		B.Normal = core::vector3df(0,0,-1);
		B.Color = color1;
		B.TCoords = core::vector2df(0,0);
		C.Pos = offset+core::vector3df((f32)(i+1)*step_x,scale_y*y2,0.f);
		C.Normal = core::vector3df(0,0,-1);
		C.Color = color2;
		C.TCoords = core::vector2df(0,0);
		D.Pos = offset+core::vector3df((f32)(i+1)*step_x,0.f,0.f);
		D.Normal = core::vector3df(0,0,-1);
		D.Color = bgColor;
		D.TCoords = core::vector2df(0,0);

		u32 vCount = buffer->Vertices.size();
		buffer->Vertices.push_back( A );
		buffer->Vertices.push_back( B );
		buffer->Vertices.push_back( C );
		buffer->Vertices.push_back( D );

		buffer->Indices.push_back( vCount );
		buffer->Indices.push_back( vCount+1 );
		buffer->Indices.push_back( vCount+2 );
		buffer->Indices.push_back( vCount );
		buffer->Indices.push_back( vCount+2 );
		buffer->Indices.push_back( vCount+3 );
	}

	buffer->recalculateBoundingBox();
	return true;
}

/// create filled path (xy-plane) with CLinearColorGradient
//
//bool createFilledPath(
//	scene::SMeshBuffer* buffer,
//	const core::dimension2df& size,
//	const core::array<f32>& points,
//	const core::vector2df& y_range,
//	video::IColorGradient* gradient,
//	const core::vector3df& offset )
//{
//	if (!buffer)
//		return false;
//
//	const u32 pointCount = points.size();
//
//	const f32 step_x = size.Width*core::reciprocal( (f32)(pointCount-1) );
//
//	const video::E_MATERIAL_TYPE matType = (gradient)?gradient->getMaterialType():video::EMT_SOLID;
//
//	// Calculate Minimum and Maximum y-values
//	f32 min_y = FLT_MAX;
//	f32 max_y = FLT_MIN;
//	for (u32 i=0; i<pointCount; i++)
//	{
//		// minimum
//		if (min_y > points[i])
//			min_y = points[i];
//
//		// maximum
//		if (max_y < points[i])
//			max_y = points[i];
//	}
//
//	const f32 diff_y = core::abs_<f32>( max_y - min_y );
//	f32 diff_y_inv = 1.0f;
//	if ( !core::equals( diff_y, 0.0f) )
//	{
//		diff_y_inv = core::reciprocal( diff_y );
//	}
//
//	buffer->Vertices.reallocate( 4*(pointCount-1) );
//	buffer->Vertices.set_used( 0 );
//	buffer->Indices.reallocate( 6*(pointCount-1) );
//	buffer->Indices.set_used( 0 );
//
//	buffer->Material.MaterialType = matType;
//	buffer->Material.Lighting = false;
//	buffer->Material.Wireframe = false;
//	buffer->Material.FogEnable = false;
//	buffer->Material.AntiAliasing = video::EAAM_QUALITY;
//	buffer->Material.UseMipMaps = false;
//	buffer->Material.TextureLayer[0].BilinearFilter = true;
//	buffer->Material.TextureLayer[0].TrilinearFilter = true;
//	buffer->Material.TextureLayer[0].AnisotropicFilter = 16;
//
//
//	const video::SColor bgColor = (gradient)?gradient->getColor( 0.0f ):0xffffffff;
//
////	const f32 scale_y = size.Height * diff_y_inv;
//
//	for (u32 i=0; i<pointCount-1; i++)
//	{
//		f32 scale_y = core::PI;
//
//		f32 y1 = 0.f;
//		f32 y2 = 0.f;
//		if (i<pointCount)
//			y1 = points[i];
//		if (i+1<pointCount)
//			y2 = points[i+1];
//
//		video::SColor color1 = 0xffffffff;
//		video::SColor color2 = 0xffffffff;
//
//		if (gradient)
//		{
//			f32 t1 = core::abs_<f32>(y1-min_y)*diff_y_inv;
//			f32 t2 = core::abs_<f32>(y2-min_y)*diff_y_inv;
//			color1 = gradient->getColor( t1 );
//			color2 = gradient->getColor( t2 );
//
////			if (t1<=0.5f || t2<=0.5f)
////				scale_y = 0.0f;
//		}
//
//		/// @todo: reuse vertices to avoid flickering due to rounding errors
//		/// @todo: set material AF
//		/// @todo: set material AA
//
//		video::S3DVertex A,B,C,D;
//		A.Pos = offset+core::vector3df((f32)i*step_x,0.f,0.f);
//		A.Normal = core::vector3df( 0,0,-1);
//		A.Color = bgColor;
//		A.TCoords = core::vector2df(0,0);
//		B.Pos = offset+core::vector3df((f32)i*step_x,scale_y*y1,0.f);
//		B.Normal = core::vector3df(0,0,-1);
//		B.Color = color1;
//		B.TCoords = core::vector2df(0,0);
//		C.Pos = offset+core::vector3df((f32)(i+1)*step_x,scale_y*y2,0.f);
//		C.Normal = core::vector3df(0,0,-1);
//		C.Color = color2;
//		C.TCoords = core::vector2df(0,0);
//		D.Pos = offset+core::vector3df((f32)(i+1)*step_x,0.f,0.f);
//		D.Normal = core::vector3df(0,0,-1);
//		D.Color = bgColor;
//		D.TCoords = core::vector2df(0,0);
//
//		u32 vCount = buffer->Vertices.size();
//		buffer->Vertices.push_back( A );
//		buffer->Vertices.push_back( B );
//		buffer->Vertices.push_back( C );
//		buffer->Vertices.push_back( D );
//
//		buffer->Indices.push_back( vCount );
//		buffer->Indices.push_back( vCount+1 );
//		buffer->Indices.push_back( vCount+2 );
//		buffer->Indices.push_back( vCount );
//		buffer->Indices.push_back( vCount+2 );
//		buffer->Indices.push_back( vCount+3 );
//	}
//
//	buffer->recalculateBoundingBox();
//	return true;
//}




/// uses SFML-2.0 Audio API

#ifdef _IRR_COMPILE_WITH_SFML_AUDIO_

// calculates the global ( very slow ) min-max values of a soundbuffer for a given FFT_Size
core::vector2df getFFTSpectrumMinMaxValue(	core::FourierTransformRtoC& fft_calc,
	const sf::SoundBuffer& buffer, u32 TimeStamps, s32 channel_index )
{
	// default
	core::vector2df my_minmax(0,0);

	u32 fft_size = fft_calc.getFFTSize();

	u32 time_dur = sfx::getDurationFromSoundBufferInMillis( &buffer );

	u32 time_delta = (u32)core::round32( (f32)time_dur / (f32)TimeStamps );

	u32 time_pos = 0;

	// FourierTransform InputDataBuffer
	core::array<s16> InputDataBuffer;
	InputDataBuffer.reallocate( fft_size );
	InputDataBuffer.set_used( fft_size );

	core::array<f32> OutputDataBuffer;
	OutputDataBuffer.reallocate( fft_size / 4*4*64 );
	OutputDataBuffer.set_used( fft_size / 4*4*64 );

	for (u32 k=0; k<TimeStamps; k++)
	{
		// FourierTransform
		sfx::fillSampleBuffer<s16>( InputDataBuffer, &buffer, 0, time_pos, InputDataBuffer.size() );
		fft_calc.setInputData<s16>( InputDataBuffer );
		fft_calc.fft();
		//fft_calc.getPowerSpectrum<f32>( OutputDataBuffer );
		fft_calc.getPowerSpectrumAsDecibels<f32>( OutputDataBuffer );
		//fft_calc.getScaledPowerSpectrum<f32>( OutputDataBuffer );
		// core::vector2d<f32> _minmax_ =

		// Fill Matrix with new values from FourierTransform
		core::vector2df _minmax = getArrayMinMax<f32>( OutputDataBuffer );

		if (my_minmax.X > _minmax.X)
			my_minmax.X = _minmax.X;

		if (my_minmax.Y > _minmax.Y)
			my_minmax.Y = _minmax.Y;

		time_pos += time_delta;

		// printf("fft-array-minmax ( pos = %d ) = { %f, %f } all [ %f, %f ]\n", time_pos, _minmax.X, _minmax.Y, my_minmax.X, my_minmax.Y );
	}

	#ifdef _DEBUG
	printf( "FFT_Spectrum MinMax [size=%d,stamps=%d,dur=%d,pos=%d] = { %f, %f };\n", fft_size, TimeStamps, time_dur, time_pos, my_minmax.X, my_minmax.Y );
	#endif // _DEBUG

	return my_minmax;
}

bool drawBackgroundImage( video::IImage* dst, const core::recti& pos, sf::SoundBuffer* sampleBuffer )
{
	if (!dst)
		return false;

	if (!sampleBuffer)
		return false;

	const core::dimension2du img_size = dst->getDimension();

	if ( ( img_size.Width == 0 ) || ( img_size.Height == 0 ) )
		return false;

	const s32 x0 = core::s32_min( pos.UpperLeftCorner.X, 0 );
	const s32 y0 = core::s32_min( pos.UpperLeftCorner.Y, 0 );
	const s32 x1 = core::s32_min( pos.LowerRightCorner.X, (s32)img_size.Width-1 );
	const s32 y1 = core::s32_min( pos.LowerRightCorner.Y, (s32)img_size.Height-1 );

	const s32 w = core::abs_<s32>( x1 - x0 );
	const s32 h = core::abs_<s32>( y1 - y0 );

	if ( ( w == 0 ) || ( h == 0 ) )
		return false;

//	// const core::recti NewPos( x0,y0,x1,y1 );
//	drawAudioSpectrum( )

	return true;
}

/// often used, because SFML 2.0 seems to give only crap from getDuration() function
f32 getDurationFromSoundBufferInSeconds( const sf::SoundBuffer* _soundbuffer )
{
	if (!_soundbuffer)
		return 0.0f;

	const u32& sc = _soundbuffer->getSampleCount();
	const u32& sr = _soundbuffer->getSampleRate();
	const u32& cc = _soundbuffer->getChannelCount();
	return (f32)(sc / cc) / (f32)sr;
}

/// often used, because SFML 2.0 seems to give only crap from getDuration() function
u32 getDurationFromSoundBufferInMillis( const sf::SoundBuffer* _soundbuffer )
{
	if (!_soundbuffer)
		return 0;

	const u32& sr = _soundbuffer->getSampleRate();
	const u32& sc = _soundbuffer->getSampleCount();
	const u32& cc = _soundbuffer->getChannelCount();
	return (u32)core::floor32( 1000 * (f32)(sc / cc) / (f32)sr);
}

///// fill an existing buffer with samples
//u32 fillSampleBuffer( core::array<s16>& _out, const sf::SoundBuffer* _in, u32 channel_index, u32 time_start, u32 sample_count )
//{
//	if ( !_in ) return 0;
//	if ( sample_count == 0 ) return 0;
//
//	if (_out.allocated_size() < sample_count)
//		_out.reallocate( sample_count, true );
//
//	const u32 sc = _in->getSampleCount();
//	const u32 cc = _in->getChannelCount();
//
//	if ( sc == 0 ) return 0;
//	if ( cc == 0 ) return 0;
//	if ( channel_index >= cc ) return 0;
//
//	const u32 duration = getDurationFromSoundBufferInMillis( _in );
//
//	if ( time_start >= duration ) return 0;
//
//	u32 sample_delta = core::floor32( (f32)time_start / duration * sc );
//	sample_delta -= sample_delta % cc;
//	sample_delta += channel_index;
//	if ( sample_delta >= sc ) return 0;
//
//	/// From here there is no turning back, meaning
//	/// the container is set to size zero ( no reallocation involved )
//	_out.set_used( 0 );
//
//	// get pointer to buffer
//	s16* p = const_cast<s16*>( _in->getSamples() );
//
//	// increment pointer to needed sample
//	p += sample_delta;
//
//	// fill array with samples
//	for ( u32 i=0; i<sample_count; i++)
//	{
//		if (sample_delta + cc*i >= sc )
//			break;
//
//		_out.push_back( *p );
//		p += cc; // add 2 for Stereo etc to get to the next sample ( data is interleaved 16-bit signed int )
//	}
//
//	return _out.size();
//}
//
///// fill an existing buffer with samples
//
//u32 fillSampleBuffer( core::array<s16>& _out, const sf::SoundBuffer* _in, u32 channel_index, f32 time_start, f32 time_end, u32 sample_count )
//{
//	if ( !_in ) return 0;
//	if ( sample_count == 0 ) return 0;
//
//	if (_out.allocated_size() < sample_count)
//		_out.reallocate( sample_count, true );
//
//	const u32 sr = _in->getSampleRate();
//	const u32 sc = _in->getSampleCount();
//	const u32 cc = _in->getChannelCount();
//
//	if ( sc == 0 ) return 0;
//	if ( cc == 0 ) return 0;
//	if ( channel_index >= cc ) return 0;
//
//	const f32 duration = _in->getDuration().asSeconds();
//
//	if ( time_start >= duration ) return 0;
//	if ( time_end > duration ) time_end = duration;
//	if ( time_end - time_start <= core::ROUNDING_ERROR_f32 ) return 0;
//
//	const f32 time_delta = (time_end - time_start) / (f32)(sample_count);
//	const s16* buffer_start = _in->getSamples();
//
//	/// From here there is no turning back, meaning
//	/// the container is set to size zero ( no reallocation involved )
//	_out.set_used( 0 );
//
//	// fill array with samples
//	for ( u32 i=0; i<sample_count; i++)
//	{
//		u32 sample_delta = core::floor32( (f32)sc* ((time_start + time_delta*i) / duration) );
//		sample_delta -= sample_delta % cc;
//		sample_delta += channel_index;
//
//		if ( sample_delta >= sc ) break;
//
//		s16* p = const_cast<s16*>(buffer_start);
//
//		p += sample_delta;
//
//		_out.push_back( *p );
//	}
//
//	return _out.size();
//}

core::array<s16> getSamplesFromSoundBuffer( const sf::SoundBuffer* _soundbuffer, u32 channel_index, u32 time_start, u32 sample_count )
{
	core::array<s16> container(0);

	if ( !_soundbuffer )
		return container;

	if ( sample_count == 0 )
		return container;

//	const u32 sr = _soundbuffer->getSampleRate();
	const u32 sc = _soundbuffer->getSampleCount();
	const u32 cc = _soundbuffer->getChannelCount();

	if ( sc == 0 )
		return container;

	if ( cc == 0 )
		return container;

	if ( channel_index >= cc )
		return container;

	container.reallocate( sample_count );

	// fill with zeros the C++ way
	container.set_used( 0 );

	for ( u32 i=0; i<container.size(); i++)
	{
		container.push_back( s16(0) );
	}

	const u32 duration = getDurationFromSoundBufferInMillis( _soundbuffer );

	// const u32 time_start ( in milliseconds )

	if ( time_start >= duration )
		return container;

	const s16* buffer_start = _soundbuffer->getSamples();

	u32 sample_delta = core::floor32( (f32)time_start / duration * sc );

	sample_delta -= sample_delta % cc;

	sample_delta += channel_index;

	if ( sample_delta >= sc )
		return container;

	s16* p = const_cast<s16*>(buffer_start);
	p += sample_delta;

	// fill with samples from soundbuffer

	container.set_used( 0 );

	for ( u32 i=0; i<sample_count; i++)
	{
		if (sample_delta + cc*i >= sc )
			break;

		container.push_back( *p );
		p += cc; // add 2 for Stereo etc to get to the next sample ( data is interleaved 16-bit signed int )
	}

	return container;
}

core::array<s16> getSamplesFromSoundBuffer( const sf::SoundBuffer* _soundbuffer, u32 channel_index, f32 time_start, f32 time_end, u32 sample_count )
{
	core::array<s16> container(0);

	if ( !_soundbuffer )
		return container;

	if ( sample_count == 0 )
		return container;

	const f32 duration = _soundbuffer->getDuration().asSeconds();

	if ( time_start >= duration )
		return container;

	if ( time_end > duration )
		time_end = duration;

	if ( time_end - time_start <= core::ROUNDING_ERROR_f32 )
		return container;

	const u32 sr = _soundbuffer->getSampleRate();
	const u32 sc = _soundbuffer->getSampleCount();
	const u32 cc = _soundbuffer->getChannelCount();

	if ( sc == 0 )
		return container;

	if ( cc == 0 )
		return container;

	if ( channel_index >= cc )
		return container;

	container.reallocate( sample_count );
	container.set_used( 0 );

	for ( u32 i=0; i<container.size(); i++)
	{
		container.push_back( s16(0) );
	}

	const f32 time_delta = (time_end - time_start) / (f32)(sample_count);

	const s16* buffer_start = _soundbuffer->getSamples();

	// fill with samples from soundbuffer

	container.set_used( 0 );

	for ( u32 i=0; i<sample_count; i++)
	{
		u32 sample_delta = core::floor32( (f32)sc* ((time_start + time_delta*i) / duration) );

		sample_delta -= sample_delta % cc;

		sample_delta += channel_index;

		if ( sample_delta >= sc )
			break;

		s16* p = const_cast<s16*>(buffer_start);

		p += sample_delta;

		container.push_back( *p );
	}

	return container;
}

bool drawAudioWaveformFull( video::IImage* dst, const core::recti& pos, const video::SColor& color, const sf::SoundBuffer* buffer, s32 channel_index )
{
	printf("drawAudioWaveform\n");

	if (!dst)
		return false;

	if (!buffer)
		return false;

	const core::dimension2du& img_size = dst->getDimension();

	const u32 sample_rate = buffer->getSampleRate();
	const u32 sample_count = buffer->getSampleCount();
	const u32 channel_count = buffer->getChannelCount();

	if ( sample_count == 0 )
		return false;

	if ( channel_count == 0 )
		return false;

	if ( channel_index >= (s32)channel_count)
		return false;

	const u32 samples_per_channel = sample_count / channel_count;

	core::array<s16> samples = getSamplesFromSoundBuffer( buffer, channel_index, 0, samples_per_channel );

	if (samples.size() == 0)
		return false;

	const f32 dx = (f32)img_size.Width / (f32)samples.size();
	const f32 dy = 1.0f / 65536.0f;

	const u32 duration = getDurationFromSoundBufferInMillis( buffer );

	printf("sample_count = %d\n", samples.size() );
	printf("samples_per_channel = %d\n", samples_per_channel );
	printf("channel_count = %d\n", channel_count );
	printf("sample_rate = %d\n", sample_rate );
	printf("w = %d, h = %d\n", img_size.Width, img_size.Height );
	printf("dx = %f, dy = %f\n", dx, dy );
	printf("duration = %f\n", 0.001f*duration );

	/// loop samples

	for ( u32 i = 0; i < samples.size()-1; i++ )
	{
		s16 s0 = samples[i];
		s16 s1 = samples[i+1];
		f32 n0 = core::clamp<f32>( 0.5f + dy * s0, 0.0f, 1.0f );
		f32 n1 = core::clamp<f32>( 0.5f + dy * s1, 0.0f, 1.0f );
		f32 y0 = img_size.Height * ( 1.0f-n0 );
		f32 y1 = img_size.Height * ( 1.0f-n1 );
		f32 x0 = dx * i;
		f32 x1 = dx * (i+1);
		drawLine( dst, core::rectf( x0,y0, x1,y1 ), color, color );
	}

	return true;
}

bool drawAudioWaveformFast( video::IImage* dst, const core::recti& pos, video::IColorGradient* gradient, const sf::SoundBuffer* buffer, s32 channel_index, bool scaleUp )
{
	#ifdef _DEBUG
	printf("drawAudioWaveformFast\n");
	#endif // _DEBUG

	if (!dst)
		return false;

	if (!buffer)
		return false;

	/// get values we need

	const core::dimension2du& img_size = dst->getDimension();

	const f32 duration = getDurationFromSoundBufferInSeconds( buffer );

	/// get 10 times the samples then image has pixels in x-direction ( little! slower but much better looking )
	///@todo test this paramter for better results

	const u32 x_scale = 100;

	const f32 x_scale_inv = core::reciprocal( (f32)x_scale );

	core::array<s16> samples = getSamplesFromSoundBuffer( buffer, channel_index, 0.0f, duration, x_scale * img_size.Width );
	if (samples.size() == 0)
		return false;

	#ifdef _DEBUG
	const u32 channel_count = buffer->getChannelCount();
	const u32 sample_rate = buffer->getSampleRate();
	printf("channel_count = %d\n", channel_count );
	printf("sample_rate = %d\n", sample_rate );
	printf("sample_count = %d\n", samples.size() );
	printf("samples_per_channel = %d\n", samples.size() / channel_count );
	printf("w = %d, h = %d\n", img_size.Width, img_size.Height );
	printf("duration = %f\n", 0.001f*duration );
	#endif // _DEBUG

	/// scaling factors to convert full 16-bit range to float in range 0..1
	s16 y_min = 32767;
	s16 y_max = -32768;
	f32 y_scale = 1.0f / 65536.0f;

	/// if only full range of collected samples should be used...
	if (scaleUp)
	{
		/// calculate the minimum and maximum values
		for ( u32 i = 0; i < samples.size()-1; i++ )
		{
			const s16 y = samples[i];
			if (y_min > y)
				y_min = y;
			if (y_max < y)
				y_max = y;
		}

		/// set scaling factor to inverse of diff in y
		y_scale = core::reciprocal( (f32)(y_max - y_min) );
	}

	#ifdef _DEBUG
	printf("y_max = %d, y_min = %d, y_range = %d\n", y_min, y_max, (s32)y_max-(s32)y_min );
	#endif // _DEBUG

	/// loop samples

//	const video::SColor c0 = (gradient)?(gradient->getColor(0.5f)):0xffffffff;
	const f32 y0 = (f32)pos.UpperLeftCorner.Y + 0.5f*(f32)pos.getHeight();
	video::SColor c1 = 0xffffffff;

	for ( u32 i = 0; i < samples.size(); i++ )
	{
		s16 s1 = samples[i];
		f32 t1 = core::clamp<f32>( 0.5f+y_scale*s1, 0.0f, 1.0f ); /// --> use this as t for ColorGradient
		f32 x = (f32)pos.UpperLeftCorner.X + x_scale_inv*i;
		f32 y1 = (f32)pos.UpperLeftCorner.Y + (f32)pos.getHeight() * ( 1.0f-t1 );

//		if (gradient)
//		{
//			c1 = gradient->getColor( t1 );
//		}

		drawLine( dst, core::rectf( x,y0,x,y1 ), c1 );
	}
//
//	video::SColor c0 = 0xffffffff;
//	video::SColor c1 = 0xffffffff;
//
//	for ( u32 i = 0; i < samples.size()-1; i++ )
//	{
//		/// convert 16-bit samples to float in range 0..1
//		s16 s0 = samples[i];
//		s16 s1 = samples[i+1];
//		f32 t0 = core::clamp<f32>( 0.5f+y_scale*s0, 0.0f, 1.0f ); /// --> use this as t for ColorGradient
//		f32 t1 = core::clamp<f32>( 0.5f+y_scale*s1, 0.0f, 1.0f ); /// --> use this as t for ColorGradient
//
//		f32 x0 = (f32)pos.UpperLeftCorner.X + x_scale_inv*i;
//		f32 x1 = (f32)pos.UpperLeftCorner.X + x_scale_inv*(i+1);
//		f32 y0 = (f32)pos.UpperLeftCorner.Y + (f32)pos.getHeight() * ( 1.0f-t0 );
//		f32 y1 = (f32)pos.UpperLeftCorner.Y + (f32)pos.getHeight() * ( 1.0f-t1 );
//
//		if (gradient)
//		{
//			c0 = gradient->getColor( t0 );
//			c1 = gradient->getColor( t1 );
//		}
//		drawLine( dst, core::rectf( x0,y0, x1,y1 ), c0, c1 );
//	}

	/// draw as EPT_LINES with one color ( good for creating selection masks and for further manipulations )

//	const video::SColor c0 = 0xffffffff;
//
//	for ( u32 i = 0; i < samples.size()-1; i++ )
//	{
//		/// convert 16-bit samples to float in range 0..1
//		s16 s0 = samples[i];
//		s16 s1 = samples[i+1];
//		f32 n0 = core::clamp<f32>( 0.5f+dy*s0, 0.0f, 1.0f );
//		f32 n1 = core::clamp<f32>( 0.5f+dy*s1, 0.0f, 1.0f );
//
////		f32 y0 = img_size.Height * ( 1.0f-n0 );
////		f32 y1 = img_size.Height * ( 1.0f-n1 );
////		f32 x0 = 0.1f*i;
////		f32 x1 = 0.1f*(i+1);
//
//		f32 x0 = (f32)pos.X + 0.1f*i;
//		f32 x1 = (f32)pos.X + 0.1f*(i+1);
//		f32 y0 = (f32)pos.Y + (f32)pos.getHeight() * ( 1.0f-n0 );
//		f32 y1 = (f32)pos.Y + (f32)pos.getHeight() * ( 1.0f-n1 );
//		drawLine( dst, core::rectf( x0,y0, x1,y1 ), c0, c0 );
//	}



	return true;
}

bool drawAudioSpectrum( video::IImage* dst, const core::recti& pos, video::IColorGradient* gradient, const sf::SoundBuffer* buffer, s32 channel_index )
{
	#ifdef _DEBUG
	printf( "drawAudioSpectrum\n" );
	#endif // _DEBUG

	if (!dst)
		return false;

	if (!buffer)
		return false;

	const core::dimension2du& img_size = dst->getDimension();

	// const f32 duration = getDurationFromSoundBufferInSeconds( buffer );

	const f32 duration = buffer->getDuration().asSeconds();

	const u32 channel_count = buffer->getChannelCount();

	const u32 sample_rate = buffer->getSampleRate();

	const u32 sample_count = buffer->getSampleCount();

	if ( channel_index >= (s32)channel_count)
		return false;

	#ifdef _DEBUG
	printf("w = %d, h = %d\n", img_size.Width, img_size.Height );
	printf("channel_count = %d\n", channel_count );
	printf("sample_rate = %d\n", sample_rate );
	printf("sample_count = %d\n", sample_count );
	printf("samples_per_channel = %d\n", sample_count / channel_count );
	printf("duration = %f sec\n", duration );
	#endif // _DEBUG

	// const u32		fft_size = sample_rate / 2;
	const u32		fft_size = 10*img_size.Height;
	f64* 			fft_input = new f64[ fft_size ];
	fftw_complex* 	fft_output = (fftw_complex*)fftw_malloc( sizeof( fftw_complex ) * fft_size );
	fftw_plan 		fft_plan = fftw_plan_dft_r2c_1d( fft_size, fft_input, fft_output, FFTW_ESTIMATE);

	const s16* sample_start = buffer->getSamples();

	const f32 time_delta = duration / (f32)(img_size.Width); // in sec

	#ifdef _DEBUG
	printf( "time_delta = %f / %u = %f sec.\n", duration, img_size.Width, time_delta );

	printf( "loop time axis\n" );

	printf( "iterations = %d\n", img_size.Width );
	#endif // _DEBUG

	video::SColor fillColor( 255,0,0,0 );

	if (gradient)
	{
		fillColor = gradient->getColor( 0.0f );
	}

	dst->fill( fillColor );

	video::SColor pixelColor( 255,255,255,255 );

	/// loop x direction
	for ( u32 x = 0; x < img_size.Width; x++ )
	{
		#ifdef _DEBUG
		printf( "iteration[%d/%d]\n",x, img_size.Width );
		#endif // _DEBUG

		s16* p = const_cast<s16*>(sample_start);

		u32 sample_delta = core::floor32( time_delta * x / duration * sample_count );

		sample_delta -= sample_delta % channel_count;

		sample_delta += channel_index;

		p += sample_delta;

		/// loop y - direction  y=f(x), my_fft_size samples needed to do fft

		for ( u32 y = 0; y < fft_size; y++ )
		{
			if ( sample_delta + y < sample_count )
			{
				fft_input[y] = (f64)p[y];
			}
			else
			{
				fft_input[y] = 0.0;
			}
		}

//		if (!ApplyHammingWindow( &my_fft_input[0], &my_fft_input[0], img_size.Width ))
//		{
//			printf( "HammingWindowFunction had error\n" );
//		}

		/// actual fft

		fftw_execute( fft_plan);

		/// get min/max

		f64 min_value = DBL_MAX;
		f64 max_value = DBL_MIN;

		for ( u32 y = 0; y < img_size.Height; y++ )
		{
			const fftw_complex& z = fft_output[y];
			f64 z_abs = sqrt( z[0]*z[0] + z[1]*z[1] );
			z_abs = 20.0f*log10( z_abs );
			if (min_value > z_abs)
				min_value = z_abs;
			if (max_value < z_abs)
				max_value = z_abs;
		}

		#ifdef _DEBUG
		printf( "spectrum min/max = %lf / %lf\n", min_value, max_value);
		#endif // _DEBUG

		if (min_value < 0.0)
			min_value = 0.0;

		/// write pixels

		for ( u32 y = 0; y < img_size.Height; y++ )
		{
			const fftw_complex& z = fft_output[y];
			f64 z_abs = sqrt(z[0]*z[0] + z[1]*z[1]);
			z_abs = 20.0f*log10( z_abs );
			f64 z_norm = (z_abs-min_value) / (max_value - min_value); // intervall [0..1]

			if (gradient)
			{
				pixelColor = gradient->getColor( z_norm );
			}

			dst->setPixel( x, y, pixelColor );
		}
	}

	/// complex to powerspectrum p = abs(z) = re*re + im*im

	/// db = 20 * log10( magnitude )

	fftw_destroy_plan( fft_plan );

	if ( fft_input )
		delete [] fft_input;

	// fftw_free(in);

	fftw_free( fft_output );

	return true;
}


bool drawAudioSpectrumEven( video::IImage* dst, const core::recti& pos, video::IColorGradient* gradient, const sf::SoundBuffer* buffer, s32 channel_index )
{
	#ifdef _DEBUG
	printf( "drawAudioSpectrumEven()\n" );
	#endif // _DEBUG

	if (!dst)
		return false;

	if (!buffer)
		return false;

	const core::dimension2du& img_size = dst->getDimension();
	const u32 sample_rate = buffer->getSampleRate();
	const u32 sample_count = buffer->getSampleCount();
	const u32 channel_count = buffer->getChannelCount();
	const f32 duration = buffer->getDuration().asSeconds();

	#ifdef _DEBUG
	printf("w = %d, h = %d\n", img_size.Width, img_size.Height );
	printf("channel_count = %d\n", channel_count );
	printf("sample_rate = %d\n", sample_rate );
	printf("sample_count = %d\n", sample_count );
	printf("samples_per_channel = %d\n", sample_count / channel_count );
	printf("duration = %f sec\n", duration );
	#endif // _DEBUG

	if ( channel_index >= (s32)channel_count)
		return false;

	u32 			my_fft_size = 32*img_size.Height;
	f64* 			my_fft_input = new f64[ my_fft_size ];
	fftw_complex* 	my_fft_output = (fftw_complex*)fftw_malloc( sizeof( fftw_complex ) * my_fft_size );
	fftw_plan 		my_fft_plan = fftw_plan_dft_r2c_1d( my_fft_size, my_fft_input, my_fft_output, FFTW_ESTIMATE);

	const s16* sample_start = buffer->getSamples();

	f32 time_delta = duration / (f32)(img_size.Width); // in sec

	#ifdef _DEBUG
	printf( "time_delta = %f / %u = %f sec.\n", duration, img_size.Width, time_delta );

	printf( "loop time axis\n" );

	printf( "iterations = %d\n", img_size.Width );
	#endif // _DEBUG

	video::SColor fillColor(255,0,0,0);

	if (gradient)
	{
		fillColor = gradient->getColor( 0.0f );
	}

	dst->fill( gradient->getColor( 0.0f ) );

	/// loop x direction

//	typedef core::array<f32> FloatArray;
//	typedef core::array<FloatArray> FloatMatrix;
//
//	FloatMatrix temp_dat;
//	temp_dat.reallocate(img_size.Height);
//	temp_dat.set_used(img_size.Height);
//
//	for (u32 y=0;y<img_size.Height;y++)
//	{
//		temp_dat[y].reallocate( img_size.Height)
//	}

	core::CMatrix temp_matrix( img_size.Height, img_size.Width );
	temp_matrix.fill( 0.0f );

	/// calculate min/max of ffts and temp save in matrix

	f64 min_value = DBL_MAX;
	f64 max_value = DBL_MIN;

	for ( u32 x = 0; x < img_size.Width; x++ )
	{
		s16* p = const_cast<s16*>(sample_start);

		u32 sample_delta = core::floor32( time_delta * x / duration * sample_count );

		sample_delta -= sample_delta % channel_count;

		sample_delta += channel_index;

		p += sample_delta;

		/// loop y - direction  y=f(x), my_fft_size samples needed to do fft
		for ( u32 y = 0; y < my_fft_size; y++ )
		{
			if ( sample_delta + y < sample_count )
			{
				my_fft_input[y] = (f64)p[y];
			}
			else
			{
				my_fft_input[y] = 0.0;
			}
		}

//		if (!ApplyHammingWindow( &my_fft_input[0], &my_fft_input[0], img_size.Width ))
//		{
//			printf( "HammingWindowFunction had error\n" );
//		}

		/// actual fft

		fftw_execute(my_fft_plan);

		for ( u32 y = 0; y < img_size.Height; y++ )
		{
			const fftw_complex& z = my_fft_output[y];
			f64 z_abs = sqrt( z[0]*z[0] + z[1]*z[1] );
			z_abs = 20.0f*log10( z_abs );

			temp_matrix.setElement( y,x, (f32)z_abs);

			if (min_value > z_abs)
				min_value = z_abs;

			if (max_value < z_abs)
				max_value = z_abs;
		}

	}

	#ifdef _DEBUG
	printf( "spectrum min/max = %lf / %lf\n", min_value, max_value);
	#endif // _DEBUG

	/// write pixels

	if (min_value < 0.0)
		min_value = 0.0;

	const f32 range_inv = (f32)core::reciprocal( max_value - min_value );
	const f32 range_min = (f32)min_value;

	video::SColor pixelColor(255,255,255,255);

	for ( u32 x = 0; x < img_size.Width; x++ )
	{
		for ( u32 y = 0; y < img_size.Height; y++ )
		{
			f32 z_abs = temp_matrix.getElement(y,x);
			f32 z_norm = (z_abs-(f32)range_min) * range_inv; // intervall [0..1]

			if (gradient)
			{
				pixelColor = gradient->getColor( z_norm );
			}

			dst->setPixel( x, y, pixelColor );
		}
	}

	temp_matrix.clear();

	/// complex to powerspectrum p = abs(z) = re*re + im*im

	/// db = 20 * log10( magnitude )

	fftw_destroy_plan(my_fft_plan);

	if (my_fft_input)
		delete [] my_fft_input;

	// fftw_free(in);

	fftw_free( my_fft_output);

	return true;
}


bool drawAudioSpectrum_8bit( video::IImage* dst, const core::recti& pos, const sf::SoundBuffer* buffer, s32 channel_index )
{
	#ifdef _DEBUG
	printf( "createPowerSpectrumFromAudio\n" );
	#endif // _DEBUG

	if (!dst)
		return false;

	if (!buffer)
		return false;

	const core::dimension2du& img_size = dst->getDimension();
	const u32 sample_rate = buffer->getSampleRate();
	const u32 sample_count = buffer->getSampleCount();
	const u32 channel_count = buffer->getChannelCount();
	const f32 duration = buffer->getDuration().asSeconds();

	#ifdef _DEBUG
	printf("w = %d, h = %d\n", img_size.Width, img_size.Height );
	printf("channel_count = %d\n", channel_count );
	printf("sample_rate = %d\n", sample_rate );
	printf("sample_count = %d\n", sample_count );
	printf("samples_per_channel = %d\n", sample_count / channel_count );
	printf("duration = %f sec\n", duration );
	#endif // _DEBUG

	if ( channel_index >= (s32)channel_count)
		return false;

	f64* 			my_fft_input = new f64[ 4*img_size.Height ];
	fftw_complex* 	my_fft_output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*4*img_size.Height);
	fftw_plan 		my_fft_plan = fftw_plan_dft_r2c_1d( 4*img_size.Height, my_fft_input, my_fft_output, FFTW_ESTIMATE);

	const s16* sample_start = buffer->getSamples();

	f32 time_delta = duration / (f32)(img_size.Width); // in sec

	#ifdef _DEBUG
	printf( "time_delta = %f / %u = %f sec.\n", duration, img_size.Width, time_delta );

	printf( "loop time axis\n" );

	printf( "iterations = %d\n", img_size.Width );
	#endif // _DEBUG

	/// loop time steps

	for ( u32 x = 0; x < img_size.Width; x++ )
	{
		#ifdef _DEBUG
		printf( "iteration[%d/%d]\n",x, img_size.Width );
		#endif // _DEBUG

		s16* p = const_cast<s16*>(sample_start);

		u32 sample_delta = core::floor32( time_delta * x / duration * sample_count );

		sample_delta -= sample_delta % channel_count;

		sample_delta += channel_index;

		p += sample_delta;

		/// loop samples needed to do fft

		for ( u32 y = 0; y < 4*img_size.Height; y++ )
		{
			if ( sample_delta + y < sample_count )
			{
				my_fft_input[y] = (f64)p[y];
			}
			else
			{
				my_fft_input[y] = 0.0;
			}
		}

//		if (!ApplyHammingWindow( &my_fft_input[0], &my_fft_input[0], img_size.Width ))
//		{
//			printf( "HammingWindowFunction had error\n" );
//		}

		/// actual fft

		fftw_execute(my_fft_plan);

		/// get min/max

		f64 min_value = DBL_MAX;
		f64 max_value = DBL_MIN;

		for ( u32 y = 0; y < img_size.Height; y++ )
		{
			const fftw_complex& z = my_fft_output[y];
			f64 z_abs = sqrt( z[0]*z[0] + z[1]*z[1] );
			z_abs = 20.0f*log10( z_abs );
			if (min_value > z_abs)
				min_value = z_abs;
			if (max_value < z_abs)
				max_value = z_abs;
		}

//		printf( "spectrum min/max = %lf / %lf\n", min_value, max_value);

		if (min_value < 0.0f)
			min_value = 0.0f;

		/// write pixels

		for ( u32 y = 0; y < img_size.Height; y++ )
		{
			const fftw_complex& z = my_fft_output[y];
			f64 z_abs = sqrt(z[0]*z[0] + z[1]*z[1]);
			z_abs = 20.0f*log10( z_abs );
			f64 z_norm = (z_abs-min_value) / (max_value - min_value); // intervall [0..1]
			u32 r = 255;
			u32 g = (u32)core::s32_clamp( (s32)(z_norm*255), 0, 255 );
			u32 b = 0;
			dst->setPixel( x, y, video::SColor(255,r,g,b) );
		}
	}

	/// complex to powerspectrum p = abs(z) = re*re + im*im

	/// db = 20 * log10( magnitude )

	fftw_destroy_plan(my_fft_plan);

	if (my_fft_input)
		delete [] my_fft_input;

	// fftw_free(in);

	fftw_free( my_fft_output);

	return true;
}
//
//
//video::IImage* createPowerSpectrumFromAudio( const sf::SoundBuffer* buffer, s32 channel_index, const core::dimension2du& img_size )
//{
//	printf( "createPowerSpectrumFromAudio\n" );
//
//	/// SoundBuffer
//	if (!buffer)
//		return 0;
//
//	video::CImage* img = new video::CImage( video::ECF_A8R8G8B8, img_size );
//
//	if (!img)
//		return 0;
//
//	printf( "created image( %d, %d, %d );\n", img_size.Width, img_size.Height, video::IImage::getBitsPerPixelFromFormat( img->getColorFormat() ) );
//
//	u32 sample_rate = buffer->getSampleRate();
//	u32 sample_count = buffer->getSampleCount();
//	u32 channel_count = buffer->getChannelCount();
//	f32 duration = buffer->getDuration().asSeconds();
//
//	printf( "scanned AudioBuffer:\n\tsample_rate = %d\n\tchannel_count = %d\n\tsample_count = %d\n\tduration in sec = %f\n", sample_rate, channel_count, sample_count, duration );
//
//	f64* 			my_fft_input = new f64[ 4*img_size.Height ];
//	fftw_complex* 	my_fft_output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*4*img_size.Height);
//	fftw_plan 		my_fft_plan = fftw_plan_dft_r2c_1d( 4*img_size.Height, my_fft_input, my_fft_output, FFTW_ESTIMATE);
//
//	img->fill( video::SColor(255,0,0,0) );
//
//	const s16* sample_start = buffer->getSamples();
//
//	f32 time_delta = duration / (f32)(img_size.Width); // in sec
//
//	printf( "time_delta = %f / %u = %f sec.\n", duration, img_size.Width, time_delta );
//
//	printf( "loop time axis\n" );
//
//	printf( "iterations = %d\n", img_size.Width );
//
//	for ( u32 x = 0; x < img_size.Width; x++ )
//	{
////		printf( "iteration[%d/%d]\n",x, img_size.Width );
//
//		s16* p = sample_start;
//
//		u32 sample_delta = core::floor32( time_delta * x / duration * sample_count );
//
//		sample_delta -= sample_delta % channel_count;
//
//		sample_delta += channel_index;
//
//		p += sample_delta;
//
//		for ( u32 y = 0; y < 4*img_size.Height; y++ )
//		{
//			if ( sample_delta + y < sample_count )
//			{
//				my_fft_input[y] = (f64)p[y];
//			}
//			else
//			{
//				my_fft_input[y] = 0.0;
//			}
//		}
//
////		if (!ApplyHammingWindow( &my_fft_input[0], &my_fft_input[0], img_size.Width ))
////		{
////			printf( "HammingWindowFunction had error\n" );
////		}
//
//		fftw_execute(my_fft_plan);
//
//		/// get min/max
//		f64 min_value = DBL_MAX;
//		f64 max_value = DBL_MIN;
//
//		for ( u32 y = 0; y < img_size.Height; y++ )
//		{
//			const fftw_complex& z = my_fft_output[y];
//			f64 z_abs = sqrt( z[0]*z[0] + z[1]*z[1] );
//			z_abs = 20.0f*log10( z_abs );
//			if (min_value > z_abs)
//				min_value = z_abs;
//			if (max_value < z_abs)
//				max_value = z_abs;
//		}
//
////		printf( "spectrum min/max = %lf / %lf\n", min_value, max_value);
//
//		if (min_value < 0.0f)
//			min_value = 0.0f;
//
//		for ( u32 y = 0; y < img_size.Height; y++ )
//		{
//			const fftw_complex& z = my_fft_output[y];
//			f64 z_abs = sqrt(z[0]*z[0] + z[1]*z[1]);
//			z_abs = 20.0f*log10( z_abs );
//			f64 z_norm = (z_abs-min_value) / (max_value - min_value); // intervall [0..1]
//			u32 r = 255;
//			u32 g = (u32)core::s32_clamp( (s32)(z_norm*255), 0, 255 );
//			u32 b = 0;
//			img->setPixel( x, y, video::SColor(255,r,g,b) );
//		}
//	}
//
//	/// complex to powerspectrum p = abs(z) = re*re + im*im
//
//	/// db = 20 * log10( magnitude )
//
//	fftw_destroy_plan(my_fft_plan);
//
//	if (my_fft_input) delete [] my_fft_input;
//
//	// fftw_free(in);
//
//	fftw_free( my_fft_output);
//
//
//	return img;
//}

#endif // _IRR_COMPILE_WITH_SFML_AUDIO_

} // end namespace sfx

} // end namespace irr
