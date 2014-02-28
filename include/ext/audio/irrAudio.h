#ifndef __IRR_EXTENSION_AUDIO_UTILS_H__
#define __IRR_EXTENSION_AUDIO_UTILS_H__

#include <irrlicht.h>
#include <../source/Irrlicht/CImage.h>

#include "HamLibCompileConfig.h"
#include "IColorGradient.h"
#include "FourierTransformRtoC.h"

#define IRR_AUDIO_VERSION "1.0"

//Töne Oktave Frequenzen
//    0       1       2       3       4       5       6       7
//C   16,35   32,70   65,41   130,81  261,63  523,25  1046,50 2093,00
//C’  17,32   34,65   69,30   138,59  277,18  554,37  1108,74 2217,46
//D   18,35   36,71   73,42   146,83  293,66  587,33  1174,66 2349,32
//D’  19,45   38,89   77,78   155,56  311,13  622,25  1244,51 2489,02
//E   20,60   41,20   82,41   164,81  329,63  659,26  1328,51 2637,02
//F   21,83   43,65   87,31   174,61  349,23  698,46  1396,91 2793,83
//F’  23,12   46,25   92,50   185,00  369,99  739,99  1479,98 2959,96
//G   24,50   49,00   98,00   196,00  392,00  783,99  1567,98 3135,96
//G’  25,96   51,91   103,83  207,65  415,30  830,61  1661,22 3322,44
//A   27,50   55,00   110,00  220,00  440,00  880,00  1760,00 3520,00
//A’  29,14   58,27   116,54  233,08  466,16  923,33  1864,66 3729,31
//H   30,87   61,74   123,47  246,94  493,88  987,77  1975,53 3951,07

namespace irr
{
	core::stringc currentDateString( ITimer * timer );

	core::stringc currentTimeString( ITimer * timer );

	core::stringc currentDateTimeString( ITimer * timer );

	core::stringc getHMS_fromMillis( u32 time_in_ms );

	core::stringc getHMS_fromSeconds( f32 time_in_s );

	template <class T> core::vector2d<T> getArrayMinMax( const core::array<T>& _array )
	{
		f32 _min_value = FLT_MAX;
		f32 _max_value = FLT_MIN;
		for ( u32 i=0; i<_array.size(); i++ )
		{
			const T& value = _array[i];
			const f32 valuef = (f32)value;
			if (_min_value > valuef)
				_min_value = valuef;
			if (_max_value < valuef)
				_max_value = valuef;
		}
		return core::vector2d<T>( (T)_min_value, (T)_max_value );
	}

	namespace sfx
	{

		core::array<core::stringc> scanFolderForAudioFiles( const core::stringc& root, s32 recursive_depth );

		bool drawLine( video::IImage* dst, const core::rectf& pos, const video::SColor& color );

		bool drawLine( video::IImage* dst, const core::rectf& pos, const video::SColor& color_a, const video::SColor& color_b );

		bool shiftMeshBuffer( scene::SMesh* mesh, s32 shifts );

		bool createFilledPath(
			scene::SMeshBuffer* buffer,
			const core::dimension2df& size,
			const core::array<f32>& points,
			const core::vector2df& y_range,
			video::IColorGradient* gradient,
			const core::vector3df& offset = core::vector3df(0,0,0) );

		bool createFilledPath(
			scene::SMeshBuffer* buffer,
			const core::dimension2df& size,
			const core::array<f32>& points,
			video::IColorGradient* gradient,
			const core::vector3df& offset = core::vector3df(0,0,0) );

		bool ApplyHammingWindow( f64* input, f64* output, u32 sample_count );

#ifdef _IRR_COMPILE_WITH_SFML_AUDIO_
		bool drawBackgroundImage( video::IImage* dst, const core::recti& pos, sf::SoundBuffer* sampleBuffer );

		core::array<s16> getSamplesFromSoundBuffer( const sf::SoundBuffer* _soundbuffer, u32 channel_index, u32 time_start, u32 sample_count = 0 );

		core::array<s16> getSamplesFromSoundBuffer( const sf::SoundBuffer* _soundbuffer, u32 channel_index, f32 time_start, f32 time_end, u32 sample_count = 0 );

		f32 getDurationFromSoundBufferInSeconds( const sf::SoundBuffer* _soundbuffer );

		u32 getDurationFromSoundBufferInMillis( const sf::SoundBuffer* _soundbuffer );

		// u32 getDurationFromSoundBufferInMillis( const sf::SoundBuffer& _soundbuffer );

		bool drawAudioWaveformFull( video::IImage* dst, const core::recti& pos, const video::SColor& color, const sf::SoundBuffer* buffer, s32 channel_index = 0 );

		bool drawAudioWaveformFast( video::IImage* dst, const core::recti& pos, video::IColorGradient* gradient, const sf::SoundBuffer* buffer, s32 channel_index = 0, bool scaleUp = true );

		bool drawAudioSpectrum( video::IImage* dst, const core::recti& pos, video::IColorGradient* gradient, const sf::SoundBuffer* buffer, s32 channel_index = 0 );

		bool drawAudioSpectrumEven( video::IImage* dst, const core::recti& pos, video::IColorGradient* gradient, const sf::SoundBuffer* buffer, s32 channel_index = 0 );

		/// calculates the global ( very slow ) min-max values of a soundbuffer for a given FFT_Size
		core::vector2df getFFTSpectrumMinMaxValue(	core::FourierTransformRtoC& fft_calc, const sf::SoundBuffer& buffer, u32 TimeStamps, s32 channel_index = 0 );

		/// fill an existing array ( any type ) with audiosamples ( 16-bit )
		/** This Function fills an existing array of any type ( mostly s16, s32 and f32 ) with
		  *	audio-samples from an existing sf::SoundBuffer
		  *	the array will be resized when too small
		**/
		template <class T> u32 fillSampleBuffer(
													core::array<T>& _out,
													const sf::SoundBuffer* _in,
													u32 channel_index,
													u32 time_start,
													u32 sample_count )
		{
			if ( !_in ) return 0;
			if ( sample_count == 0 ) return 0;

			if (_out.allocated_size() < sample_count)
				_out.reallocate( sample_count, false );

			const u32 sc = _in->getSampleCount();
			const u32 cc = _in->getChannelCount();

			if ( sc == 0 ) return 0;
			if ( cc == 0 ) return 0;
			if ( channel_index >= cc ) return 0;

			const u32 duration = getDurationFromSoundBufferInMillis( _in );

			if ( time_start >= duration ) return 0;

			u32 sample_delta = core::floor32( (f32)time_start / duration * sc );
			sample_delta -= sample_delta % cc;
			sample_delta += channel_index;
			if ( sample_delta >= sc ) return 0;

			/// From here there is no turning back, meaning
			/// the container is set to size zero ( no reallocation involved )
			_out.set_used( 0 );

			// get pointer to buffer
			s16* p = const_cast<s16*>( _in->getSamples() );

			// increment pointer to needed sample
			p += sample_delta;

			// fill array with samples
			for ( u32 i=0; i<sample_count; i++)
			{
				if (sample_delta + cc*i >= sc )
					break;

				_out.push_back( ((T)(*p)) );
				p += cc; // add 2 for Stereo etc to get to the next sample ( data is interleaved 16-bit signed int )
			}

			return _out.size();
		}


		/// fill an existing array ( any type ) with audiosamples ( 16-bit )
		/** This Function fills an existing array of any type ( mostly s16, s32 and f32 ) with
		  *	audio-samples from an existing sf::SoundBuffer
		  *	the array will be resized when too small
		**/

		template <class T>
		u32 fillSampleBuffer( core::array<T>& _out, const sf::SoundBuffer* _in, u32 channel_index, f32 time_start, f32 time_end, u32 sample_count )
		{
			if ( !_in ) return 0;
			if ( sample_count == 0 ) return 0;

			if (_out.allocated_size() < sample_count)
				_out.reallocate( sample_count, true );

			const u32 sr = _in->getSampleRate();
			const u32 sc = _in->getSampleCount();
			const u32 cc = _in->getChannelCount();

			if ( sc == 0 ) return 0;
			if ( cc == 0 ) return 0;
			if ( channel_index >= cc ) return 0;

			const f32 duration = _in->getDuration().asSeconds();

			if ( time_start >= duration ) return 0;
			if ( time_end > duration ) time_end = duration;
			if ( time_end - time_start <= core::ROUNDING_ERROR_f32 ) return 0;

			const f32 time_delta = (time_end - time_start) / (f32)(sample_count);
			const s16* buffer_start = _in->getSamples();

			/// From here there is no turning back, meaning
			/// the container is set to size zero ( no reallocation involved )
			_out.set_used( 0 );

			// fill array with samples
			for ( u32 i=0; i<sample_count; i++)
			{
				u32 sample_delta = core::floor32( (f32)sc* ((time_start + time_delta*i) / duration) );
				sample_delta -= sample_delta % cc;
				sample_delta += channel_index;

				if ( sample_delta >= sc ) break;

				s16* p = const_cast<s16*>(buffer_start);

				p += sample_delta;

				_out.push_back( ((T)(*p)) );
			}

			return _out.size();
		}
#endif // _IRR_COMPILE_WITH_SFML_AUDIO_

		/// get frequency from piano key ( C = 0, H = 11 for A4 use getFrequencyFromNote(9,4) = 440 Hz )
		f32 getFrequencyFromNote( s32 C_is_zero, s32 oktave );



	} // end namespace sfx

} // end namespace irr


#endif // __IRR_EXTENSION_AUDIO_UTILS_H__
