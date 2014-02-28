#ifndef __IRR_EXTENSION_QUICK_FOURIER_TRANSFORM_CLASS_H__
#define __IRR_EXTENSION_QUICK_FOURIER_TRANSFORM_CLASS_H__

#include <irrlicht.h>
#include <fftw3.h>

namespace irr
{
namespace core
{
	/// quick FOURIER_TRANSFORM real to complex

	/// Umwandlung in vom Amplitude(Zeit) Bereich

	/// y = A(x), mit x = 0...N-1 numbers

	/// in den Frequenzraum F[index] = a + b*i

	/// z = F(s) = a + b*i, mit s = 0...N-1 numbers

	/// FourierTransform is orthogonal and symmetric

	/// Die 'FFT-Size' kann verschieden von der Aufnahmesamplerate sein.

	/// daher gibt die 'FFT-Size' nur die Anzahl an Eingabesamples an

	/// die für die Rechnung benutzt werden.

	/// pro Eingabezahl werden zwei Zahlen erzeugt ( Real- und Imaginärteil )

	/// sample[index] --> f[index] = { re, im } gespeichert.

	/// Die tatsächliche Frequenz ist aber abhängig von der Aufnahmesamplerate.


	/// --> |z| = a^2 + b^2

	class FourierTransformRtoC : public IReferenceCounted
	{
	private:
		u32  			FFT_Size;
		f64*			FFT_InputData;	// real input-vector
		fftw_complex*	FFT_OutputData; // complex output-vector
		fftw_plan 		FFT_Plan;
		core::stringc   FFT_WisdomFile;

	public:
		FourierTransformRtoC( s32 fft_size = -1, const c8* wisdomFile = "FourierTransformRtoC.wisdom" );

		virtual ~FourierTransformRtoC();

		virtual u32 getFFTSize() const;

		virtual void fft();

		virtual core::stringc getPlanInfo() const;


		template<class T>
		void setInputData( const core::array<T>& _in )
		{
			u32 i_max = core::min_<u32>( _in.size(), FFT_Size );

			for (u32 i=0; i<i_max; i++)
			{
				FFT_InputData[i] = (f64)_in[i];
			}

			if (i_max < FFT_Size)
			{
				for (u32 i=i_max; i<FFT_Size; i++)
				{
					FFT_InputData[i] = 0.0;
				}
			}
		}

		template<class T>
		core::vector2d<T> getMinMax( const core::array<T>& _in, T min_init, T max_init )
		{
			core::vector2d<T> result( min_init, max_init );

			for (u32 i=0; i<_in.size(); i++)
			{
				const T value = _in[i];

				if (result.X > value)
					result.X = value;

				if (result.Y < value)
					result.Y = value;
			}

			return result;
		}


		template<class T>
		void getPowerSpectrumAsDecibelsThreshold( core::array<T>& _out, T threshold )
		{
			const u32 i_max = core::min_<u32>( _out.size(), FFT_Size );

			_out.set_used( 0 );

			for (u32 i=0; i<i_max; i++)
			{
				const fftw_complex& z = FFT_OutputData[i];	// Lesezugriff auf komplexe Zahl

				f64 z_abs = sqrt( z[0]*z[0] + z[1]*z[1] );	// Betrag der komplexen Zahl z

				z_abs = 20.0f*log10( z_abs );				// Umwandlung in Dezibels

				if (threshold > z_abs)
					z_abs = 0.0;

				_out.push_back( ((T)z_abs) );
			}
		}


		template<class T>
		void getPowerSpectrumAsDecibels( core::array<T>& _out )
		{
			const u32 i_max = core::min_<u32>( _out.size(), FFT_Size );

			_out.set_used( 0 );

			for (u32 i=0; i<i_max; i++)
			{
				const fftw_complex& z = FFT_OutputData[i];	// Lesezugriff auf komplexe Zahl

				f64 z_abs = sqrt( z[0]*z[0] + z[1]*z[1] );	// Betrag der komplexen Zahl z

				z_abs = 20.0f*log10( z_abs );				// Umwandlung in Dezibels

				_out.push_back( ((T)z_abs) );
			}
		}

		template<class T>
		void getScaledPowerSpectrum( core::array<T>& _out, f64 dB_min = 0.0, f64 dB_max = 150.0 )
		{
			const u32 i_max = core::min_<u32>( _out.size(), FFT_Size );

			_out.set_used( 0 );

			const f64 dB_range_inv = core::reciprocal( dB_max - dB_min );

			// const f64 base_2 = core::reciprocal( log10(2.0) );
			for (u32 i=0; i<i_max; i++)
			{
				const fftw_complex& z = FFT_OutputData[i];	// read only access to complex number

				f64 z_abs = sqrt( z[0]*z[0] + z[1]*z[1] );	// magnitude ( abs ) of complex number / Betrag der komplexen Zahl z

				z_abs = 1.0f*log10( z_abs ) ;				// convert to decibels / Umwandlung in Dezibels

				z_abs -= dB_min;							// value is in range [ 0, dB_range ] now

				if ( z_abs > dB_max )						// clip values to maximum, if greater
					z_abs = dB_max;

				z_abs *= dB_range_inv;						// value is in range [ 0, 1 ] now, normalized

				_out.push_back( ((T)z_abs) );				// insert at the end of array, no allocation involved
			}
//
//			if (core::equals( y_scale, 0.0f ) ||			// if scale factor is 0 or 1 ( epsilon is ROUNDING_ERROR_F64 )
//				core::equals( y_scale, 1.0f ) )
//				return;									// exit function
//
//			for (u32 i=0; i<_out.size(); i++)				// loop array-elements
//			{
//				_out[i] *= y_scale;							// scale each array element by factor
//			}
		}

		template<class T>
		void getPowerSpectrum( core::array<T>& _out )
		{
			const u32 i_max = core::min_<u32>( _out.size(), FFT_Size );

			_out.set_used( 0 );

			for (u32 i=0; i<i_max; i++)
			{
				const fftw_complex& z = FFT_OutputData[i];		// Lesezugriff auf komplexe Zahl

				f64 z_abs = sqrt( z[0]*z[0] + z[1]*z[1] );	// Betrag der komplexen Zahl z

				_out.push_back( ((T)z_abs) );
			}

			const core::vector2d<T> z_minmax = getMinMax<T>( _out, FLT_MAX, FLT_MIN );

			const f64 z_range_inv = 100.0*core::reciprocal( (f64)z_minmax.Y - (f64)z_minmax.X );

			for (u32 i=0; i<i_max; i++)
			{
				T value = (T)(z_range_inv*((f64)_out[i]-(f64)z_minmax.X));
				_out[i] = value;
			}
		}



	};

} // end namespace core

} // end namespace irr

#endif // __IRR_EXTENSION_QUICK_FOURIER_TRANSFORM_CLASS_H__
