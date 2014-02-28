#include "FourierTransformRtoC.h"

namespace irr
{
namespace core
{

FourierTransformRtoC::FourierTransformRtoC( s32 fft_size, const c8* wisdomFile )
: FFT_Size(0), FFT_InputData(0), FFT_OutputData(0), FFT_WisdomFile(wisdomFile)
{
	// Check for wisdom
	if( fftw_import_wisdom_from_filename( FFT_WisdomFile.c_str() ) == 0 )
	{
		printf("wisdom not loaded.\n");
	}
	else
	{
		printf("wisdom loaded.\n");
	}

	if (fft_size < 0)
		FFT_Size = 1024;	// default
	else
		FFT_Size = (u32)fft_size;

	FFT_InputData = new f64[FFT_Size];
	if (!FFT_InputData)
	{
		printf("Could not create FFT_InputVectorArray.\n");
	}
	else
	{
		for (u32 i=0; i<FFT_Size; i++)
		{
			FFT_InputData[i] = 0.0;
			//FFT_OutputData[i].re = 0.0;
			//FFT_OutputData[i].im = 0.0;
		}
	}

	FFT_OutputData = (fftw_complex*) fftw_malloc( FFT_Size*sizeof(fftw_complex) );
	if (!FFT_OutputData)
	{
		printf("Could not create FFT_OutputVectorArray.\n");
	}
	else
	{
//				for (u32 i=0; i<FFT_Size; i++)
//				{
//					FFT_InputData[i] = 0.0;
//					//FFT_OutputData[i].re = 0.0;
//					//FFT_OutputData[i].im = 0.0;
//				}
	}

	FFT_Plan = fftw_plan_dft_r2c_1d( FFT_Size, FFT_InputData, FFT_OutputData, FFTW_MEASURE );
}

FourierTransformRtoC::~FourierTransformRtoC()
{
	// Store Wisdom
	fftw_export_wisdom_to_filename( FFT_WisdomFile.c_str() );

	fftw_destroy_plan(FFT_Plan);

	if (FFT_InputData)
		delete [] FFT_InputData;

	fftw_free(FFT_OutputData);
	fftw_cleanup();

	FFT_Size = 0;
	FFT_InputData = 0;
	FFT_OutputData = 0;
}

u32 FourierTransformRtoC::getFFTSize() const
{
	return FFT_Size;
}

void FourierTransformRtoC::fft()
{
	fftw_execute( FFT_Plan );
}

core::stringc FourierTransformRtoC::getPlanInfo() const
{
	f64 plan_add, plan_mul, plan_fma, fft_cost = fftw_cost( FFT_Plan );
	fftw_flops( FFT_Plan, &plan_add, &plan_mul, &plan_fma );

	core::stringc txt = "PlanType: RtoC with N="; txt += FFT_Size; txt += " \n";
	txt += "PlanCost = "; txt += fft_cost; txt += " \n";
	txt += "Used Additions = "; txt += plan_add; txt += " \n";
	txt += "Used Multiplications = "; txt += plan_mul; txt += " \n";
	txt += "Used Fused MulAdd = "; txt += plan_fma; txt += " ";
	return txt;
}

} // end namespace core

} // end namespace irr
