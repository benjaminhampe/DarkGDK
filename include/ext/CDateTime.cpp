// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <CDateTime.h>


namespace irr
{

namespace core
{

	DateTime DateTime::now()
	{
		DateTime my;
		time_t curtime = time(NULL);
		struct tm* t = gmtime(&curtime);
		if (t)
		{
			my.set(t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, 0, 0 );
			//delete t;
		}
		return my;
	}

#if IRRLICHT_VERSION_MINOR >= 8

	DateTime DateTime::now(const ITimer::RealTimeDate& rtd)
	{
		DateTime my;
		my.setDST( rtd.IsDST );
		my.set( rtd.Year, (s32)rtd.Month, (s32)rtd.Day, (s32)rtd.Hour, (s32)rtd.Minute, (s32)rtd.Second, 0, 0);
		return my;
	}

	DateTime DateTime::now( ITimer* timer )
	{
		if (timer)
			return DateTime::now( timer->getRealTimeAndDate() );
		else
			return (Real)0;
	}

	ITimer::RealTimeDate DateTime::getRealTimeDateFromJC( Real value )
	{
		ITimer::RealTimeDate date;
		return date;
	}

	ITimer::RealTimeDate DateTime::getRealTimeDateFromJD( Real value )
	{
		ITimer::RealTimeDate date;
		return date;
	}

	Real DateTime::getJDFromRealTimeDate(const ITimer::RealTimeDate& rtd)
	{
		return (Real)0;
	}

#endif // IRRLICHT_VERSION_MINOR

	/// STATIC functions handling conversion JulianDayNumber <-> DateTime

	//	static Real JD( s32 year, s32 month, s32 day, s32 hour = 0, s32 minute = 0, s32 second = 0, s32 u_sec = 0, s32 gmt_off_sec = 0);
	//	static Real JC( Real jd );
	//	static Real MJD( s32 year, s32 month, s32 day, s32 hour = 0, s32 minute = 0, s32 second = 0, s32 u_sec = 0, s32 gmt_off_sec = 0);
	//	static Real MJD( Real jd_utc );
	//	static Real JD( s32 year, Real dayOfYear );
	//	static void JDC( Real jd, s32 &year, s32 &month, s32 &day, s32 &hour, s32 &minute, s32 &second);
	//	static s32 getDaysOfYear( s32 year );
	//	static Real JulianCentury( Real jd );
	//	static Real getDayOfYear( Real jd );
	//	static s32 getDaysOfYear( Real jd );
	//	static bool isLeapYear( Real jd );

	// Julian Day, Greenwich mean noon 1st Jan 4713 B.C == year -4712
    Real DateTime::JD( s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, u32 u_sec, s32 gmt_off_sec)
    {
		Real j = 2299160.500000;
		if (year == 1582 && month == 10 && day>=5 && day <=14)
		{
			// this is a invalid gregorian date, the days 5.10.1582 till 14.10.1582 never existed
			// therefore it will always return 2299160.500000 for the 15.10.1582
		}
		else
		{
			if (month < 3)
			{
				month += 12;
				year--;
			}
			j = floor(365.25*((Real)year+4716.0));
			j += floor(30.6001*(month+1));
			j += day - 1524.5;

			// Here, the fraction of the day will be added to number of days 'j'
			j += ((Real)hour + ((Real)minute + ((Real)(second - gmt_off_sec) + 0.000001*(Real)u_sec) * core::INV_60) * core::INV_60) * core::INV_24;

			Real a=0.0;
			if (j > 2299160.0)
			{
				// a = floor(year/100);	// correct
				a = floor((Real)year/100); // also correct
				j += (2 - a + floor(a/4));
			}

		}


        return j;
    }

    // Julian Century
    Real DateTime::JC(Real jd)
    {
        return (jd - 2451545.0)/36525.0;
    }

	// Modified Julian Day MJD=JD-2400000.5
    Real DateTime::MJD(	s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second,	u32 u_sec, s32 gmt_off_sec)
    {
        return JD(year,month,day,hour,minute,second,u_sec,gmt_off_sec) - core::CONST_MJD;
    }

	// Modified Julian Day MJD=JD-2400000.5
    Real DateTime::MJD( Real jd_utc )
    {
        return jd_utc - core::CONST_MJD;
    }

    Real DateTime::JD(s32 year, Real dayOfYear)
    {
        return JD(year,1,1)+dayOfYear-1.0;
    }

	void DateTime::JDC( Real jd, s32& year, s32& month, s32& day)
	{
        jd += 0.5;

        // Tage
        Real Z = (Real)(s32)jd;	// Dirty Version 1.6456 --> 1

        // Tagesbruchteil
        Real F = jd - Z;

        Real A,g; // Locals

        if (Z<2299161.0) // Ergebnis julianisch
        {
            A=Z;
        }
        else // Ergebnis gregorianisch
        {
            g=(Real)(s32)((Z-1867216.25)/36524.25);
            A=Z+1.0+g-(Real)(s32)(g/4.0);
        }
        Real B = A + 1524.0;
        Real Y = (Real)(s32)((B-122.1)/365.25);
        Real E = (Real)(s32)(365.25*Y);
        Real M = (Real)(s32)((B-E)/30.6001);

        // Tag inklusive Tagesbruchteil
        Real D = B-E-(Real)(s32)(30.6001*M) + F;

        // Tage
        day = (s32)(Real)(s32)(D);

        // Monate
        if (M<14.0)
            month = static_cast<s32>(M) - 1;
        else
            month = static_cast<s32>(M) - 13;
        // Jahre
        if (month>2)
            year = static_cast<s32>(Y) - 4716;
        else
            year = static_cast<s32>(Y) - 4715;
	}

    void DateTime::JDC(Real jd,	s32 &year, s32 &month, s32 &day, s32 &hour, s32 &minute, s32 &second)
    {
        jd += 0.5;

        // Tage
        Real Z = (Real)(s32)jd;	// Dirty Version 1.6456 --> 1

        // Tagesbruchteil
        Real F = jd - Z;

        // Locals
        Real A,g;

        // Ergebnis julianisch
        if (Z<2299161.0)
        {
            A=Z;
        }

        // Ergebnis gregorianisch
        else
        {
            g=(Real)(s32)((Z-1867216.25)/36524.25);
            A=Z+1.0+g-(Real)(s32)(g/4.0);
        }
        Real B = A + 1524.0;
        Real Y = (Real)(s32)((B-122.1)/365.25);
        Real E = (Real)(s32)(365.25*Y);
        Real M = (Real)(s32)((B-E)/30.6001);

        // Tag inklusive Tagesbruchteil
        Real D = B-E-(Real)(s32)(30.6001*M) + F;

        //		// LOCALS
        //	    s32 year, month, day, hour, minute, second;

        // Tage
        day = (s32)(Real)(s32)(D);

        // Monate
        if (M<14.0)
            month = static_cast<s32>(M) - 1;
        else
            month = static_cast<s32>(M) - 13;
        // Jahre
        if (month>2)
            year = static_cast<s32>(Y) - 4716;
        else
            year = static_cast<s32>(Y) - 4715;

        // Extraktion der Tageszeit
        second = core::round32( (f32)(F*Real(86400)) );
        minute = second/60;
        second -= minute*60;
        hour = minute/60;
        minute -= hour*60;

        //		return Calender(year,month,day,hour,minute,second);
    }

	void DateTime::JDC( Real jd, s32& year, s32& month, s32& day, s32& hour, s32& minute, s32& second, u32& u_sec, s32& gmt_off_sec )
	{
        jd += 0.5;

        // Tage
        Real Z = (Real)(s32)jd;	// Dirty Version 1.6456 --> 1

        // Tagesbruchteil
        Real F = jd - Z;

        // Locals
        Real A,g;

        // Ergebnis julianisch
        if (Z<2299161.0)
        {
            A=Z;
        }

        // Ergebnis gregorianisch
        else
        {
            g=(Real)(s32)((Z-1867216.25)/36524.25);
            A=Z+1.0+g-(Real)(s32)(g/4.0);
        }
        Real B = A + 1524.0;
        Real Y = (Real)(s32)((B-122.1)/365.25);
        Real E = (Real)(s32)(365.25*Y);
        Real M = (Real)(s32)((B-E)/30.6001);

        // Tag inklusive Tagesbruchteil
        Real D = B-E-(Real)(s32)(30.6001*M) + F;

        //		// LOCALS
        //	    s32 year, month, day, hour, minute, second;

        // Tage
        day = (s32)(Real)(s32)(D);

        // Monate
        if (M<14.0)
            month = static_cast<s32>(M) - 1;
        else
            month = static_cast<s32>(M) - 13;
        // Jahre
        if (month>2)
            year = static_cast<s32>(Y) - 4716;
        else
            year = static_cast<s32>(Y) - 4715;

        // Extraktion der Tageszeit
        second = core::round32( (f32)(F*Real(86400)) );
        minute = second/60;
        second -= minute*60;
        hour = minute/60;
        minute -= hour*60;

        // Real fMillis = F - (Real)second
	}

    s32 DateTime::getDaysOfYear(s32 year)
    {
        // new version
        return (s32)(JD(year+1,1,1)-JD(year,1,1));
    }

    Real DateTime::getJulianCentury(Real jd)
    {
        return (jd - 2451545.0)/36525.0;
    }

    Real DateTime::getDayOfYear(Real jd)
    {
        s32 year,month,day,hh,mm,ss;
        JDC(jd, year,month,day,hh,mm,ss);
        return jd-JD(year, 1, 1, 0,0,0);
    }

    s32 DateTime::getDaysOfYear(Real jd)
    {
        s32 year,month,day,hh,mm,ss;
        JDC(jd, year,month,day,hh,mm,ss);
        return (s32)(JD(year+1,month,day,hh,mm,ss)-jd);
    }

    bool DateTime::isLeapYear(Real jd)
    {
        return (getDaysOfYear(jd)==366) ? true : false;
    }



//	public:	// CLASS constructors
//		/// default constructor
//		DateTime( );
//
//		/// copy constructor
//		DateTime(const DateTime& other);
//
//		/// constructor by 1 value ( JulianDays )
//		DateTime(Real jd);
//
//		/// constructor by 2 values ( Year,DayOfYear )
//		DateTime(s32 year, Real dayOfYear);
//
//		/// constructor by 3-8 values ( Year,Month,Day [,HH,MM,SS,GMT,DST] )
//		DateTime(s32 year, s32 month, s32 day, s32 hour=0, s32 minute=0, s32 second=0, s32 gmt=0, s32 dst=0);
//#if IRRLICHT_VERSION_MINOR >= 8
//		/// constructor by 1 value ( Pointer to ITimer );
//		DateTime( ITimer* timer );
//
//		/// constructor by 1 value ( Reference to ITimer::RealTimeDate )
//		DateTime( const ITimer::RealTimeDate& realtime );
//#endif // IRRLICHT_VERSION_MINOR
//
//		/// destructor
//		~DateTime();
//



	/// Konvertiert in lesbaren core::stringc
	core::stringc DateTime::toString() const
	{
		core::stringc s("DateTime(");
		s+=getYear(); s+=",";
		s+=m_month; s+=",";
		s+=m_day; s+=",";
		s+=m_hour; s+=",";
		s+=m_min; s+=",";
		s+=m_sec;
//		s+=",";
//		s+=m_gmt; s+=",";
//		s+=(m_isdst)?"true":"false";
		// s+=",";
		// s+=getJD();
		s+=")";

//		popen()

//		core::stringc s("");
//		s+=getYear();
//		s+=".";
//		if (m_month<10) s+="0"; s+=m_month; s+=".";
//		if (m_day<10) s+="0"; s+=m_day; s+=" ";
//		if (m_hour<10) s+="0"; s+=m_hour; s+=":";
//		if (m_min<10) s+="0"; s+=m_min; s+=":";
//		if (m_sec<10) s+="0"; s+=m_sec;
//		s+=" GMT ";
//		if (m_gmt>=0) s+="+";
//		s+=m_gmt;
//		s+=" DST ";
//		s+=m_isdst;
//		s+=" JD ";
//		s+= getJD();
		return s;
	}


	// Default Constructor
	DateTime::DateTime()
	: m_year(0), m_month(0), m_day(0), m_hour(0), m_min(0), m_sec(0)
	, m_gmt(0), m_isdst(false), m_jd(0.0), m_name("")
	{
		updateJD();
	}

	// Value Constructor
	DateTime::DateTime(Real jd)
	: m_year(0), m_month(0), m_day(0), m_hour(0), m_min(0), m_sec(0)
	, m_gmt(0), m_isdst(false), m_jd(0.0), m_name("")
	{
		this->setJD(jd);
	}

	// Value Constructor
	DateTime::DateTime(
		s32 year, s32 month, s32 day,
		s32 hour, s32 minute, s32 second, s32 gmt, s32 dst)
	: m_year(year), m_month(month),	m_day(day), m_hour(hour), m_min(minute), m_sec(second)
	, m_gmt(gmt), m_isdst(false), m_jd(0.0), m_name("")
	{
		updateJD();
	}

	// Value Constructor
	DateTime::DateTime( s32 year, Real dayOfYear )
	: m_year(year), m_month(1),	m_day(1), m_hour(0), m_min(0), m_sec(0)
	, m_gmt(0), m_isdst(false), m_jd(0.0), m_name("")
	{
		Real jdYear = JD(year,1,0,0,0,0,0,0);
		m_jd = jdYear+dayOfYear;
		JDC(m_jd, m_year, m_month, m_day, m_hour, m_min, m_sec);
	}

//
//	DateTime::DateTime(const char* menu)
//	: m_year(0), m_month(0), m_day(0), m_hour(0), m_min(0), m_sec(0)
//	, m_gmt(0), m_isdst(false), m_jd(0.0), m_name("")
//	{}

	DateTime::DateTime(const DateTime& other)
	: m_year(0), m_month(0), m_day(0), m_hour(0), m_min(0), m_sec(0)
	, m_gmt(0), m_isdst(false), m_jd(0.0), m_name("")
	{
		*this = other;
	}
//
//	DateTime::DateTime(const core::stringc& name)
//	: m_year(0), m_month(0), m_day(0), m_hour(0), m_min(0), m_sec(0)
//	, m_gmt(0), m_isdst(false), m_jd(0.0), m_name(name)
//	{
//		updateJD();
//	}
//
//	DateTime::DateTime(const core::stringc& name, Real jd)
//	: m_year(0), m_month(0), m_day(0), m_hour(0), m_min(0), m_sec(0)
//	, m_gmt(0), m_isdst(false), m_jd(0.0), m_name(name)
//	{
//		this->setJD(jd);
//	}
//
//	DateTime::DateTime(
//		const core::stringc& name,
//		s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second,
//		s32 gmt, s32 dst)
//	: m_year(year), m_month(month),	m_day(day), m_hour(hour), m_min(minute), m_sec(second)
//	, m_gmt(gmt), m_isdst(false), m_jd(0.0), m_name(name)
//	{
//		updateJD();
//	}
//
//	DateTime::DateTime(const core::stringc& name, const char* menu)
//	: m_year(0), m_month(0), m_day(0), m_hour(0), m_min(0), m_sec(0)
//	, m_gmt(0), m_isdst(false), m_jd(0.0), m_name(name)
//	{}

	/// Destructor
	DateTime::~DateTime()
	{

	}

//
//		/// copy operator
//		DateTime& operator= (const DateTime& other);
//
//		/// copy operator
//		DateTime& operator= (const Real& jd);
//
//		/// copy operator
//		DateTime& operator= (const ITimer::RealTimeDate& value);
//

/// copy operator
DateTime& DateTime::operator= (const DateTime& other)
{
	return *this;
}

/// copy operator
DateTime& DateTime::operator= (const Real& jd)
{
	return *this;
}

/// copy operator
DateTime& DateTime::operator= (const ITimer::RealTimeDate& value)
{
	return *this;
}

//	public:
//		/// equality operator ( using JulianDayNumber )
//		bool operator== (const DateTime& other); // op is equal to other
//
//		/// inequality operator ( using JulianDayNumber )
//		bool operator!= (const DateTime& other); // op is not equal to other
//
//		/// greater operator ( using JulianDayNumber )
//		bool operator> (const DateTime& other); // op greater than other
//
//		/// lower operator ( using JulianDayNumber )
//		bool operator< (const DateTime& other); // op lower than other
//
//		/// greater or equal operator ( using JulianDayNumber )
//		bool operator>= (const DateTime& other); // op greater or equal than other
//
//		/// lower or equal operator ( using JulianDayNumber )
//		bool operator<= (const DateTime& other); // op lower or equal than other
//
//		/// C = A+B
//		/// @brief adds timespan "other" to "this" ( uses JulianDays internally )
//		/// @return New instance of class
//		DateTime operator+ (const DateTime& other);
//
//		/// C = A-B
//		/// @brief substracts timespan "other" from "this" ( uses JulianDays internally )
//		/// @return New instance of class
//		DateTime operator- (const DateTime& other);
//
//		/// A = A+B
//		/// @brief adds timespan "other" to "this" ( uses JulianDays internally )
//		/// @return writeable reference to "this" class
//		DateTime& operator+= (const DateTime& other);
//
//		/// A = A-B
//		/// @brief substracts timespan "other" from "this" ( uses JulianDays internally )
//		/// @return writeable reference to "this" class
//		DateTime& operator-= (const DateTime& other);
//

	bool DateTime::operator== (const DateTime& other) const
	{
		if ( core::equals( getJD(), other.getJD() ) )
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator!= (const DateTime& other) const
	{
		return (!((*this)==other));
	}

	bool DateTime::operator> (const DateTime& other) const
	{
		if ( getJD() > other.getJD() )
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator< (const DateTime& other) const
	{
		if ( getJD() < other.getJD() )
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator>= (const DateTime& other) const
	{
		if ( (*this)>other || (*this)==other )
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator<= (const DateTime& other) const
	{
		if ( (*this)<other || (*this)==other )
		{
			return true;
		}
		return false;
	}

	DateTime DateTime::operator+ (const DateTime& other)
	{
		return DateTime(getJD()+other.getJD());
	}

	DateTime DateTime::operator- (const DateTime& other)
	{
		return DateTime(getJD()-other.getJD());
	}

	DateTime& DateTime::operator+= (const DateTime& other)
	{
		setJD( getJD() + other.getJD() );
		return *this;
	}

	DateTime& DateTime::operator-= (const DateTime& other)
	{
		setJD( getJD() - other.getJD() );
		return *this;
	}

//protected:
//		/// updates values by JulianDayNumber ( sets IsDirty=false, JulianDayNumber=const )
//		void update();
//
//		/// updates JulianDayNumber by other values ( sets IsRealDirty=false )
//		void updateJD();
//

	void DateTime::update()
	{
		// if (!IsDirty)
		//	return;
		DateTime::JDC(m_jd, m_year, m_month, m_day, m_hour, m_min, m_sec);
		// IsDirty = false;
	}


	void DateTime::updateJD()
	{
		// if (!IsDirtyJD)
		//	return;
		m_jd = DateTime::JD(m_year, m_month, m_day, m_hour, m_min, m_sec, m_gmt, m_isdst);
		// IsDirtyJD = false;
	}

//		/// set JulianDayNumber, does not update anything else ( sets IsDirty=true )
//		void setJD(Real jd);
//		/// set values, does not update JulianDayNumber ( sets IsRealDirty=true )
//		void setYear(s32 y);
//		void setMonth(s32 m);
//		void setDay(s32 d);
//		void setDayOfMonth(s32 m);
//		void setDayOfYear(s32 m);
//		void setHour(s32 hh);
//		void setMinute(s32 mm);
//		void setSecond(s32 ss);
//		void setTimezone(s32 gmt);
//		void setGMT(s32 gmt);
//		void setDST(bool isDst);
//

	// setter
	DateTime& DateTime::set( s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, u32 u_sec, s32 gmt_off_sec )
	{
		m_year = year;
		m_month = month;
		m_day = day;
		m_hour = hour;
		m_min = minute;
		m_sec = second;
		m_nano = u_sec*1000;
		m_gmt = gmt_off_sec;
		m_isdst = (gmt_off_sec>0)?true:false;
		m_jd = JD( m_year, m_month, m_day, m_hour, m_min, m_sec, u_sec, m_gmt);
		return *this;
	}

	DateTime& DateTime::setJD(Real jd)
	{
		m_jd = jd;
		JDC( m_jd, m_year, m_month, m_day, m_hour, m_min, m_sec);
		return *this;
	}

	DateTime& DateTime::setMJD(Real jd)
	{
		m_jd = jd + core::CONST_MJD;
		JDC( m_jd, m_year, m_month, m_day, m_hour, m_min, m_sec);
		return *this;
	}

	DateTime& DateTime::setYear(s32 y)
	{
		m_year = y;
		updateJD();
		return *this;
	}
	DateTime& DateTime::setMonth(s32 m)
	{
		m_month = m;
		updateJD();
		return *this;
	}

	DateTime& DateTime::setDay(s32 d)
	{
		m_day = d;
		updateJD();
		return *this;
	}

	DateTime& DateTime::setHour(s32 hh)
	{
		m_hour = hh;
		updateJD();
		return *this;
	}

	DateTime& DateTime::setMinute(s32 mm)
	{
		m_min = mm;
		updateJD();
		return *this;
	}

	DateTime& DateTime::setSecond(s32 ss)
	{
		m_sec = ss;
		updateJD();
		return *this;
	}

	DateTime& DateTime::setGMT(s32 gmt)
	{
		m_gmt = gmt;
		updateJD();
		return *this;
	}
	DateTime& DateTime::setTimezone(s32 gmt)
	{
		m_gmt = gmt;
		updateJD();
		return *this;
	}
	DateTime& DateTime::setDST(bool isDst)
	{
		m_isdst = isDst;
		updateJD();
		return *this;
	}

//		// getter
//		Real getJD() const;
//		s32 getYear() const;
//		s32 getMonth() const;
//		s32 getDay() const;
//		s32 getDayOfMonth() const;
//		Real  getDayOfYear() const; // with fPart for Hours/Minutes/Seconds
//		s32 getDaysOfYear() const;
//		s32 getHour() const;
//		s32 getMinute() const;
//		s32 getSecond() const;
//		s32 getTimezone() const;
//		s32 getGMT() const;
//		s32 getDST() const;
//		bool isLeapYear() const;
//		bool isDST() const;
//
	Real DateTime::getJD() const
	{
		return m_jd;
	}

	Real DateTime::getMJD() const
	{
		return DateTime::MJD(m_jd);
	}

	// getter
	s32 DateTime::getSecond() const { return m_sec; }
	s32 DateTime::getMinute() const { return m_min; }
	s32 DateTime::getHour() const { return m_hour; }
	s32 DateTime::getDay() const { return m_day; }
	s32 DateTime::getMonth() const { return m_month; }
	s32 DateTime::getYear() const { return m_year; }
	s32 DateTime::getGMT() const { return m_gmt; }
	s32 DateTime::getTimezone() const { return m_gmt; }

	Real DateTime::getDayOfYear() const
	{
		return m_jd-JD(m_year, 1,1,0,0,0, m_gmt, m_isdst)+1.0;
	}

	s32 DateTime::getDaysOfYear() const
	{
		return (s32)(JD(m_year+1,1,1,0,0,0)-JD(m_year,1,1,0,0,0));
	}

	bool DateTime::isLeapYear() const
	{
		return (this->getDaysOfYear()==366) ? true : false;
	}

	bool DateTime::isDST() const { return m_isdst; }


//	//	void setTM(struct tm* m_time);
//	//	void setLocalTime();
//	//	void setGMTime();
//	protected:
//	//	void updateJD();
//	public:
//	//	static struct tm* getLocalTime();
//	//	static struct tm* getGMTime();
//	//	static Real JD(s32 year, s32 month, s32 day, s32 hour=0, s32 minute=0, s32 second=0, s32 gmt=0, s32 isdst=0);
//	//	static DateTime JD(Real jd);
//
//	private: // CLASS MEMBER Variables
//		s32 m_year;
//		s32 m_month;
//		s32 m_day;
//		s32 m_hour;
//		s32 m_min;
//		s32 m_sec;
//		s32 m_gmt;
//		bool m_isdst;
//		Real m_jd;
//		core::stringc m_name;
//	};




//
//	void
//	DateTime::setLocalTime()
//	{
//		time_t curtime = time(NULL);
//		struct tm *m_time;
//		m_time = localtime(&curtime);
//		m_year = (m_time->tm_year+1900);
//		m_month = (m_time->tm_mon+1);
//		m_day = (m_time->tm_mday);
//		m_hour = (m_time->tm_hour);
//		m_min = (m_time->tm_min);
//		m_sec = (m_time->tm_sec);
//		m_isdst = (m_time->tm_isdst);
//		m_gmt = -1*(timezone/3600);
//		updateJD();
//	}
//
//	void
//	DateTime::setGMTime()
//	{
//		time_t curtime = time(NULL);
//		struct tm *m_time;
//		m_time = gmtime(&curtime);
//		m_year = (m_time->tm_year+1900);
//		m_month = (m_time->tm_mon+1);
//		m_day = (m_time->tm_mday);
//		m_hour = (m_time->tm_hour);
//		m_min = (m_time->tm_min);
//		m_sec = (m_time->tm_sec);
//		m_isdst = (m_time->tm_isdst);
//		m_gmt = 0;
//		updateJD();
//	}
//
//	struct tm*
//	DateTime::getLocalTime()
//	{
//		time_t curtime = time(NULL);
//		return localtime(&curtime);
//	}
//
//	struct tm*
//	DateTime::getGMTime()
//	{
//		time_t curtime = time(NULL);
//		return gmtime(&curtime);
//	}

//		/// PRINT all internal data for DEBUGGING
//		core::stringc toString() const;
//


} // end namespace core
} // end namespace irr
