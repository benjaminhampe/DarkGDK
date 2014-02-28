// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_DATETIME_H__
#define __IRR_EXTENSION_DATETIME_H__

#include <irrlicht.h>
#include <cstdlib>
#include <ctime>
//#include <iostream>
//#include "irrMath.h"
//#include <sys/syscall.h>

namespace irr
{
	typedef f64 Real;

	namespace core
	{
		const Real INV_3 = (Real)(1.0/3.0);
		const Real INV_6 = (Real)(1.0/6.0);
		const Real INV_12 = (Real)(1.0/12.0);
		const Real INV_24 = (Real)(1.0/24.0);
		const Real INV_60 = (Real)(1.0/60.0);
		const Real INV_288 = (Real)(1.0/288.0);
		const Real INV_360 = (Real)(1.0/360.0);
		const Real INV_1440 = (Real)(1.0/1440.0);
		const Real INV_3600 = (Real)(1.0/3600.0);
		const Real INV_86400 = (Real)(1.0/86400.0);
		const Real CONST_1_OVER_PI = (Real)(1.0/core::PI64);
		const Real CONST_2_OVER_PI = (Real)(2.0/core::PI64);
		const Real CONST_1_OVER_2PI = (Real)(0.5/core::PI64);
		const Real CONST_MJD = (Real)2400000.5;

		class DateTime
		{
		public:

			static DateTime now();

			static Real JD( s32 year, s32 month, s32 day, s32 hour = 0, s32 minute = 0, s32 second = 0, u32 u_sec = 0, s32 gmt_off_sec = 0);

			static Real JD( s32 year, Real dayOfYear );

			static Real JC( Real jd );

			static Real MJD( s32 year, s32 month, s32 day, s32 hour = 0, s32 minute = 0, s32 second = 0, u32 u_sec = 0, s32 gmt_off_sec = 0);

			static Real MJD( Real jd_utc );

			static void JDC( Real jd, s32& year, s32& month, s32& day);

			static void JDC( Real jd, s32& year, s32& month, s32& day, s32& hour, s32& minute, s32& second);

			static void JDC( Real jd, s32& year, s32& month, s32& day, s32& hour, s32& minute, s32& second, u32& u_sec, s32& gmt_off_sec );

			static Real getJulianCentury( Real jd );

			static Real getDayOfYear( Real jd );

			static s32 getDaysOfYear( s32 year );

			static s32 getDaysOfYear( Real jd );

			static bool isLeapYear( Real jd );

	#if IRRLICHT_VERSION_MINOR >= 8

			static ITimer::RealTimeDate getRealTimeDateFromJC( Real value );

			static ITimer::RealTimeDate getRealTimeDateFromJD( Real value );

			static Real getJDFromRealTimeDate(const ITimer::RealTimeDate& rtd);

			static DateTime now(const ITimer::RealTimeDate& rtd);

			static DateTime now( ITimer* timer );

	#endif

		public:

			/// default constructor
			DateTime( );

			/// copy constructor
			DateTime(const DateTime& other);

			/// constructor by 1 value ( JulianDays )
			DateTime(Real jd);

			/// constructor by 2 values ( Year,DayOfYear )
			DateTime(s32 year, Real dayOfYear);

			/// constructor by 3-8 values ( Year,Month,Day [,HH,MM,SS,GMT,DST] )
			DateTime(s32 year, s32 month, s32 day, s32 hour=0, s32 minute=0, s32 second=0, s32 gmt=0, s32 dst=0);

	#if IRRLICHT_VERSION_MINOR >= 8

			/// constructor by 1 value ( Pointer to ITimer );
			DateTime( ITimer* timer );

			/// constructor by 1 value ( Reference to ITimer::RealTimeDate )
			DateTime( const ITimer::RealTimeDate& realtime );

	#endif // IRRLICHT_VERSION_MINOR

			/// destructor
			~DateTime();

			/// print
			core::stringc toString() const;

			/// copy operator
			DateTime& operator= (const DateTime& other);

			/// copy operator
			DateTime& operator= (const Real& jd);

			/// copy operator
			DateTime& operator= (const ITimer::RealTimeDate& value);

		public:
			/// equality operator ( using JulianDayNumber )
			bool operator== (const DateTime& other) const; // op is equal to other

			/// inequality operator ( using JulianDayNumber )
			bool operator!= (const DateTime& other) const; // op is not equal to other

			/// greater operator ( using JulianDayNumber )
			bool operator> (const DateTime& other) const; // op greater than other

			/// lower operator ( using JulianDayNumber )
			bool operator< (const DateTime& other) const; // op lower than other

			/// greater or equal operator ( using JulianDayNumber )
			bool operator>= (const DateTime& other) const; // op greater or equal than other

			/// lower or equal operator ( using JulianDayNumber )
			bool operator<= (const DateTime& other) const; // op lower or equal than other

			/// C = A+B
			DateTime operator+ (const DateTime& other);

			/// C = A-B
			DateTime operator- (const DateTime& other);

			/// A = A+B
			DateTime& operator+= (const DateTime& other);

			/// A = A-B
			DateTime& operator-= (const DateTime& other);

	protected:
			/// updates values by JulianDayNumber ( sets IsDirty=false, JulianDayNumber=const )
			void update();

			/// updates JulianDayNumber by other values ( sets IsRealDirty=false )
			void updateJD();

	public:
			/// set JulianDayNumber, does not update anything else ( sets IsDirty=true )
			DateTime& set( s32 year, s32 month, s32 day, s32 hour = 0, s32 minute = 0, s32 second = 0, u32 u_sec = 0, s32 gmt_off_sec = 0 );

			DateTime& setJD(Real jd);

			DateTime& setMJD(Real jd);

			/// set values, does not update JulianDayNumber ( sets IsRealDirty=true )
			DateTime& setYear(s32 y);

			DateTime& setMonth(s32 m);

			DateTime& setDay(s32 d);

			DateTime& setDayOfMonth(s32 m);

			DateTime& setDayOfYear(s32 m);

			DateTime& setHour(s32 hh);

			DateTime& setMinute(s32 mm);

			DateTime& setSecond(s32 ss);

			DateTime& setTimezone(s32 gmt);

			DateTime& setGMT(s32 gmt);

			DateTime& setDST(bool isDst);

			// getter
			Real getJD() const;

			Real getMJD() const;

			s32 getYear() const;

			s32 getMonth() const;

			s32 getDay() const;

			s32 getDayOfMonth() const;

			Real  getDayOfYear() const; // with fPart for Hours/Minutes/Seconds

			s32 getDaysOfYear() const;

			s32 getHour() const;

			s32 getMinute() const;

			s32 getSecond() const;

			s32 getTimezone() const;

			s32 getGMT() const;

			bool isLeapYear() const;

			bool isDST() const;

		//	void setTM(struct tm* m_time);
		//	void setLocalTime();
		//	void setGMTime();
		protected:
		//	void updateJD();
		public:
		//	static struct tm* getLocalTime();
		//	static struct tm* getGMTime();
		//	static Real JD(s32 year, s32 month, s32 day, s32 hour=0, s32 minute=0, s32 second=0, s32 gmt=0, s32 isdst=0);
		//	static DateTime JD(Real jd);

		private:
			s32 m_year;
			s32 m_month;
			s32 m_day;
			s32 m_hour;
			s32 m_min;
			s32 m_sec;
			u32 m_nano;
			s32 m_gmt;
			bool m_isdst;
			Real m_jd;
			core::stringc m_name;
		};

	} // end namespace core

} // end namespace irr

#endif // __SUNLIB_HAMPE_CLASS_DATETIME_H_INCLUDED__
