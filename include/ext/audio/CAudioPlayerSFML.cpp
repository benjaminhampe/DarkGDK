// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CAudioPlayerSFML.h"

#ifdef _IRR_COMPILE_WITH_SFML_AUDIO_

namespace irr
{

CAudioPlayerSFML::CAudioPlayerSFML( )
: IsLoaded(false), IsPlaying(false), IsLooped(false)
, MasterVolume(0.5f), MasterPan(0.f), MasterPitch(1.0f)
, Position(0), Duration(0), ChannelCount(0), SampleRate(0), SampleCount(0), FFT_Calculator(0)
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::constructor()" );
	#endif // _DEBUG
	/// FFT
	FFT_Calculator = new core::FourierTransformRtoC( 1024 );
	if ( !FFT_Calculator )
	{
		printf( "Could not create FFT_Calculator\n" );
	}

}

//! dtor
CAudioPlayerSFML::~CAudioPlayerSFML()
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::destructor()" );
	#endif // _DEBUG
	stop();
	clearPlayList();
	if (FFT_Calculator)
	{
		FFT_Calculator->drop();
		FFT_Calculator = 0;
	}
}

/// API
core::stringc CAudioPlayerSFML::getAPIName( ) const
{
	core::stringc txt = "";

	txt += "SFML";
	#if (SFML_VERSION_MAJOR < 2)
		txt += "-1.6";
	#else
		txt += "-2.1";
	#endif
    txt += " + FFTW3";
	return txt;
}

// AudioCards
bool CAudioPlayerSFML::EnumerateDevices( )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::EnumerateDevices()" );
	#endif // _DEBUG

	# if ( SFML_VERSION_MAJOR < 2 )

	# else

	# endif
	return true;
}



bool CAudioPlayerSFML::setAudioDevice( u32 card, u32 sub_device )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::setAudioDevice()" );
	#endif // _DEBUG
	return true;
}

u32 CAudioPlayerSFML::getAudioDeviceCount( ) const
{
    return 0;
}

s32 CAudioPlayerSFML::getDefaultAudioDevice( ) const
{
    return 0;
}

core::stringc CAudioPlayerSFML::getAudioDeviceName( u32 card, u32 sub_device ) const
{
	core::stringc name = "unknown";
    return name;
}

u32 CAudioPlayerSFML::getChannelCount( ) const
{
	#if ( SFML_VERSION_MAJOR < 2 )
	return Buffer.GetChannelsCount();
	#else
	return Buffer.getChannelCount();
	#endif
}

u32 CAudioPlayerSFML::getSampleCount() const
{
	#if ( SFML_VERSION_MAJOR < 2 )
	return Buffer.GetSamplesCount();
	#else
	return Buffer.getSampleCount();
	#endif
}

u32 CAudioPlayerSFML::getSampleRate() const
{
	#if ( SFML_VERSION_MAJOR < 2 )
	return Buffer.GetSampleRate();
	#else
	return Buffer.getSampleRate();
	#endif
}

u32 CAudioPlayerSFML::getDuration() const
{
	return sfx::getDurationFromSoundBufferInMillis( &Buffer );
}

u32 CAudioPlayerSFML::getPosition() const
{
	return Position;
}

f32 CAudioPlayerSFML::getVolume() const
{
    return MasterVolume;
}


f32 CAudioPlayerSFML::getPitch() const
{
    return MasterPitch;
}


bool CAudioPlayerSFML::setPosition( u32 time_index_in_ms )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::setPosition()" );
	#endif // _DEBUG

	Position = time_index_in_ms;

	# if ( SFML_VERSION_MAJOR < 2 )
	Sound.Pause();
	Sound.SetPlayingOffset( (f32)Position / (f32)getDuration() );
	Sound.Play();
	# else
	Sound.pause();
	Sound.setPlayingOffset( sf::milliseconds( Position ) );
	Sound.play();
	# endif
	return true;
}

bool CAudioPlayerSFML::setPitch( f32 value )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::setPitch()" );
	#endif // _DEBUG

    if (value < 0.001f)
        value = 0.001f;
    if (value > 1000.0f)
        value = 1000.0f;

    MasterPitch = value;

	#if ( SFML_VERSION_MAJOR < 2 )
	Sound.SetPitch( MasterPitch );
	#else
	Sound.setPitch( MasterPitch );
	#endif
	return true;
}

bool CAudioPlayerSFML::setVolume( f32 value )
{
	#ifdef _DEBUG
	os::Printer::log( "setVolume()" );
	#endif // _DEBUG

    if (value < 0.0f)
        value = 0.0f;
    if (value > 1.0f)
        value = 1.0f;

    MasterVolume = value;

	# if ( SFML_VERSION_MAJOR < 2 )
		Sound.SetVolume( 100.0f*MasterVolume );
	# else
		Sound.setVolume( 100.0f*MasterVolume );
	# endif
	return true;
}

// Volume Control
bool CAudioPlayerSFML::mute()
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::mute()" );
	#endif // _DEBUG

	#if ( SFML_VERSION_MAJOR < 2 )
	Sound.Stop();
	#else
	Sound.stop();
	#endif
	return true;
}


bool CAudioPlayerSFML::panic()
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::panic()" );
	#endif // _DEBUG

	# if ( SFML_VERSION_MAJOR < 2 )
	Sound.Stop();
	# else
	Sound.stop();
	# endif
	return true;
}


bool CAudioPlayerSFML::stop()
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::stop()" );
	#endif // _DEBUG

	# if ( SFML_VERSION_MAJOR < 2 )
	Sound.Stop();
	# else
	Sound.stop();
	# endif
	return true;
}

//bool CAudioPlayerSFML::volumeUp( f32 value )
//{
//    f32 vol = getVolume() + value;
//    setVolume( vol );
//}
//
//bool CAudioPlayerSFML::volumeDown( f32 value )
//{
//    f32 vol = getVolume() - value;
//    setVolume( vol );
//}

bool CAudioPlayerSFML::play( s32 loops )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::play()" );
	#endif // _DEBUG

	IsLooped = (loops>0);
	Loops = loops;

	#if ( SFML_VERSION_MAJOR < 2 )
	Sound.SetVolume(100.0f*MasterVolume);
	Sound.SetPitch(MasterPitch);
	Sound.SetLoop(IsLooped);
	Sound.Play();
	#else
	Sound.setVolume(100.0f*MasterVolume);
	Sound.setPitch(MasterPitch);
	Sound.setLoop(IsLooped);
	Sound.play();
	#endif
	return true;
}

bool CAudioPlayerSFML::pause()
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::pause()" );
	#endif // _DEBUG

	#if ( SFML_VERSION_MAJOR < 2 )
		Sound.Pause();
	#else
		Sound.pause();
	#endif
	return true;
}

bool CAudioPlayerSFML::resume( )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::resume()" );
	#endif // _DEBUG

	#if ( SFML_VERSION_MAJOR < 2 )
	Sound.Play();
	#else
	Sound.play();
	#endif
	return true;
}

//bool CAudioPlayerSFML::record( )
//{
//	#ifdef _DEBUG
//	if (Logger)
//		Logger->log(L"CAudioPlayerSFML::record()");
//	#endif // _DEBUG
//}
//
//
//

// Player Control
bool CAudioPlayerSFML::loadFile( const core::stringc& uri )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::loadFile()" );
	#endif // _DEBUG

	PlayList.push_back( uri );
//	u32 item = PlayList.size();

	# if ( SFML_VERSION_MAJOR < 2 )
	if ( !Buffer.LoadFromFile( uri.c_str()) )
	# else
	if ( !Buffer.loadFromFile( uri.c_str()) )
	# endif
	{
		#ifdef _DEBUG
		os::Printer::log( "Cant open audio-file" );
		#endif // _DEBUG
		return false;
	}

	#if ( SFML_VERSION_MAJOR < 2 )
	Sound.SetBuffer( Buffer);
	# else
	Sound.setBuffer( Buffer);
	# endif
    return true;
}

// Player Control
bool CAudioPlayerSFML::saveFile( const core::stringc& uri )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::saveFile()" );
	#endif // _DEBUG
    return true;
}

// Player Control
bool CAudioPlayerSFML::closeFile()
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::closeFile()" );
	#endif // _DEBUG
    return true;
}

bool CAudioPlayerSFML::clearPlayList()
{
	stop();
	PlayList.clear();
	return true;
}

u32 CAudioPlayerSFML::getPlayListItemCount() const
{
    return PlayList.size();
}

bool CAudioPlayerSFML::next( )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::next()" );
	#endif // _DEBUG

	return true;
}

bool CAudioPlayerSFML::prev( )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::prev()" );
	#endif // _DEBUG
	return true;
}


bool CAudioPlayerSFML::loadPlayList( const core::stringc& uri )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::loadPlayList()" );
	#endif // _DEBUG
	return true;
}

bool CAudioPlayerSFML::savePlayList( const core::stringc& uri )
{
	#ifdef _DEBUG
	os::Printer::log( "CAudioPlayerSFML::savePlayList()" );
	#endif // _DEBUG
	return true;
}

bool CAudioPlayerSFML::setReverbEffect( bool bEnable, f32 value )
{
	return false;
}

bool CAudioPlayerSFML::setEchoEffect( bool bEnable, f32 value )
{
	return false;
}

bool CAudioPlayerSFML::setFlangerEffect( bool bEnable, f32 value )
{
	return false;
}

bool CAudioPlayerSFML::setCompressorEffect( bool bEnable, f32 value )
{
	return false;
}

bool CAudioPlayerSFML::setDistortionEffect( bool bEnable, f32 value )
{
	return false;
}


bool CAudioPlayerSFML::setChorusEffect( bool bEnable, f32 value )
{
	return false;
}

} // end namespace irr

#endif // _IRR_COMPILE_WITH_SFML_AUDIO_
