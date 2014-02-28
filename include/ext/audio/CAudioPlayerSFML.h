// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_AUDIO_PLAYER_SFML_H_INCLUDED__
#define __IRR_C_AUDIO_PLAYER_SFML_H_INCLUDED__

#include "HamLibCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_SFML_AUDIO_

#include "FourierTransformRtoC.h"

#include "irrAudio.h"

namespace irr
{

class CAudioPlayerSFML
{
    public:
		// Default constructor
        CAudioPlayerSFML();

		// Default destructor
        virtual ~CAudioPlayerSFML();

        virtual core::stringc getAPIName( ) const;

        virtual bool EnumerateDevices( );

        virtual u32 getAudioDeviceCount( ) const;

        virtual s32 getDefaultAudioDevice( ) const;

        virtual io::path getAudioDeviceName( u32 card = 0, u32 sub_device = 0) const;

        virtual bool setAudioDevice( u32 card = 0, u32 sub_device = 0 );

		// getter
		virtual u32 getPosition() const;

		virtual u32 getDuration() const;

        virtual u32 getChannelCount( ) const;

        virtual u32 getSampleCount() const;

        virtual u32 getSampleRate() const;

        virtual f32 getPitch() const; // speed

        virtual f32 getVolume() const;

        virtual bool isLooped() const
        {
        	return Sound.getLoop();
        }

		// Direct Access to SoundBuffer

		virtual sf::SoundBuffer* getSoundBuffer()
		{
			return &Buffer;
		}
		virtual const s16* getSamples()
		{
			return Buffer.getSamples();
		}

		virtual const sf::SoundBuffer* getSoundBuffer() const
		{
			return &Buffer;
		}

		virtual sf::Sound& getSound()
		{
			return Sound;
		}

		virtual const sf::Sound& getSound() const
		{
			return Sound;
		}

		virtual u32 getFFTSize() const
		{
			return (FFT_Calculator)?(FFT_Calculator->getFFTSize()):0;
		}

		virtual core::FourierTransformRtoC* getFourierTransform()
		{
			return FFT_Calculator;
		}

		// setter
		virtual bool setPosition( u32 time_index_in_ms );

        virtual bool setPitch( f32 value = 1.0f );

        virtual bool setVolume( f32 value = 0.5f );        // 50 %

        virtual bool mute();

		// Player Control
        virtual bool panic();

        virtual bool play( s32 loops = -1 );

 		virtual bool pause();

        virtual bool resume();

        virtual bool stop();

        virtual bool next();

        virtual bool prev();

		// PlayList Control
        virtual bool clearPlayList();

        virtual u32 getPlayListItemCount() const;

        virtual bool loadPlayList( const core::stringc& uri );

		virtual bool savePlayList( const core::stringc& uri );

		// Current Played File

        virtual bool loadFile( const core::stringc& uri );

        virtual bool saveFile( const core::stringc& uri );

        virtual bool closeFile( );

		// Sound-Effect Control
        virtual bool setReverbEffect( bool bEnable = false, f32 value = 0.0f );

        virtual bool setEchoEffect( bool bEnable = false, f32 value = 0.0f );

        virtual bool setFlangerEffect( bool bEnable = false, f32 value = 0.0f );

        virtual bool setCompressorEffect( bool bEnable = false, f32 value = 0.0f );

        virtual bool setDistortionEffect( bool bEnable = false, f32 value = 0.0f );

        virtual bool setChorusEffect( bool bEnable = false, f32 value = 0.0f );

//		virtual core::array<f32> createWavData( u32 uChannel, f32 time_start, f32 time_duration = 1.0f) const;
//		virtual core::array<f32> createFFTData( u32 uChannel, f32 time_start, f32 time_delta = 0.1f, u32 fft_size = 1024, u32 max_rows = 1) const;

    private:

		bool IsLoaded;
		bool IsPlaying;
		bool IsLooped;
		u32 Loops;

		f32 MasterVolume;
		f32 MasterPan;
		f32 MasterPitch;
		u32 Position;
		u32 Duration;
		u32 ChannelCount;
		u32 SampleRate;
		u32 SampleCount;

		core::stringc FileName; // current played file

		core::array<core::stringc> PlayList;

		/// FourierTransformation
		core::FourierTransformRtoC* FFT_Calculator;
		core::array<s16> FFT_InputBuffer;	// stores waveform
		core::array<f32> FFT_OutputBuffer;	// stores spectrum
		sf::Sound Sound;
		sf::SoundBuffer Buffer;

	public:

	static core::stringw getSoundBufferInfo( const sf::SoundBuffer& buf )
	{
		core::stringw s(L"SoundBuffer Info:\n");
	#if (SFML_VERSION_MAJOR < 2)
		s+=L"Chan ("; s+=(s32)buf.GetChannelsCount(); s+= L"), ";
		s+=L"Length ("; s+=(s32)buf.GetDuration(); s+=L" ms), ";
		s+=L"Samples ("; s+=(s32)buf.GetSamplesCount(); s+=L") ";
		s+=L"SampleRate ("; s+=(s32)buf.GetSampleRate(); s+=L") ";
		s+=L"SampleSize ("; s+=L"2 Byte(s) signed int"; s+=L") ";
	#else
		s+=L"Chan ("; s+=(s32)buf.getChannelCount(); s+= L"), ";
		s+=L"Length ("; s+=(s32)buf.getDuration().asMilliseconds(); s+=L" ms), ";
		s+=L"Samples ("; s+=(s32)buf.getSampleCount(); s+=L") ";
		s+=L"SampleRate ("; s+=(s32)buf.getSampleRate(); s+=L") ";
		s+=L"SampleSize ("; s+=L"2 Byte(s) signed int"; s+=L") ";
		//s+=L"Data = "; s+=(s32)buf.getSamples(); s+=L" ms";
	#endif
		return s;
	}

	static core::stringw getSoundInfo( const sf::Sound& snd )
	{
		core::stringw s(L"Sound Info:\n");
		// s+=L"Duration = "; s+=(s32)sndgetDuration(); s+=L" ms\n";
	#if (SFML_VERSION_MAJOR < 2)
		s+=getSoundBufferInfo( *snd.GetBuffer() ).c_str();
	#else
		s+=getSoundBufferInfo( *snd.getBuffer() ).c_str();
	#endif
		//s+=L"Data = "; s+=(s32)buf.getSamples(); s+=L" ms";
		return s;
	}
};

}

#endif // _IRR_COMPILE_WITH_SFML_AUDIO_

#endif // C_AUDIO__PLAYER_H
