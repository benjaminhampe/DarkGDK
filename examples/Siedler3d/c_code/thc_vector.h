// *********************************
//		Benni's  Vector  Library
// *********************************

#ifndef __THC_VECTOR_H_INCLUDED__
#define __THC_VECTOR_H_INCLUDED__

#include "thc_math.h"
#include "DarkGDK.h"

namespace thc
{
	// ### Vector Strukturen ###
	struct		Integer2{	int x,y;		};
	struct		Integer3{	int x,y,z;		};
	struct		Float2	{	float x,y;		};
	struct		Float3	{	float x,y,z;	};
	struct		Gerade3	{   Float3 A, B;	};
	struct		Matrix3	{	Float3 A, B, C; };

	// ### Vector Funktionen ###
	/*
	float		VectorAbs				( Float3 A);				// Betrag |a|
	float		VectorAbsQ				( Float3 A);				// Quadrat. Betrag = |a*a| -> ohne Wurzel
	float		VectorDist				( Float3 A, Float3 B);	//| B-A |
	float		VectorDistQ				( Float3 A, Float3 B);	//|(B-A)*(B-A)| -> ohne Wurzel
	Float3		VectorAdd				( Float3 A, Float3 B);	// Addition v = a+b
	Float3		VectorSub				( Float3 A, Float3 B);	// Subtraktion ab = b-a
	Float3		VectorMul				( Float3 A, float B);		// Skalar Multiplikation v = A*b
	Float3		VectorDiv				( Float3 A, float B);		// Skalar Division v=A/b
	float		VectorDotP				( Float3 A, Float3 B);	// Skalar Produkt v = a°b
	Float3		VectorCrossP			( Float3 A, Float3 B);	// Kreuz  Produkt n = axb
	float		VectorAngle				( Float3 A, Float3 B);	// Winkel ß = cos^-1[a°b/(|a|*|b|)]
	Float3		VectorNormalise			( Float3 A);					// v_hesse = a/|a|
	Float3		VectorNormal			( Float3 A, Float3 B);	// v_hesse = CrossP / |CrossP|
	Float3		VectorMiddle			( Float3 A, Float3 B);	// OM = OA + AB/2
	Float3		VectorRotation			( Float3 V, float alpha, float beta, float gamma); // v_rot = M_rot( alpha, beta, gamma ) * v0
	Float3		VectorMatrixProduct		( Matrix3 M, Float3 V);	// v_rot = M * v0
	Float3		SchnittGeradeEbene		( Gerade3 g, Matrix3 e);
	int			Fast2DTransform			( int Vector3);
	*/
	//##############################################################
	//
	// ### Vector Funktionen ###
	//
	//##############################################################
	inline int Fast2DTransform(int Vector3)
	{
		bool r;
		r = dbMakeMatrix4(1000);
		r = dbMakeMatrix4(1001);

		float Dist = dbZVector3(Vector3);
		dbSetVector3(Vector3, 2.0f * dbXVector3(Vector3) / (float)dbScreenWidth() - 1.0f,
									 1.0f - 2.0f * dbYVector3(Vector3) / (float)dbScreenHeight(),
									 0.0f);

		dbViewMatrix4(1000);
		dbProjectionMatrix4(1001);
		dbInverseMatrix4(1000, 1000);
		dbInverseMatrix4(1001, 1001);
		dbTransformCoordsVector3(Vector3, Vector3, 1001);
		dbNormalizeVector3(Vector3, Vector3);
		dbMultiplyVector3(Vector3, Dist);
		dbTransformCoordsVector3(Vector3, Vector3, 1000);
		r = dbDeleteMatrix4(1000);
		r = dbDeleteMatrix4(1001);

		return Vector3;
	}

	inline float VectorAbs  ( Float3 A){	return dbSQRT( A.x*A.x + A.y*A.y + A.z*A.z);	}
	inline float VectorAbsQ ( Float3 A){	return A.x*A.x + A.y*A.y + A.z*A.z;	}
	inline float VectorDist ( Float3 A, Float3 B)
	{
		float x=B.x-A.x;
		float y=B.y-A.y;
		float z=B.z-A.z;
		return dbSQRT(x*x + y*y + z*z);
	}
	inline float VectorDistQ ( Float3 A, Float3 B)
	{
		float x=B.x-A.x;
		float y=B.y-A.y;
		float z=B.z-A.z;
		return x*x + y*y + z*z;
	}
	inline Float3 VectorAdd( Float3 A, Float3 B)
	{
		Float3	ergebnis;
					ergebnis.x=A.x+B.x;
					ergebnis.y=A.y+B.y;
					ergebnis.z=A.z+B.z;
		return	ergebnis;
	}
	inline Float3 VectorSub( Float3 A, Float3 B)
	{
		Float3 ergebnis;
				 ergebnis.x=B.x-A.x;
				 ergebnis.y=B.y-A.y;
				 ergebnis.z=B.z-A.z;
		return ergebnis;
	}
	inline Float3 VectorMul( Float3 A, float B)
	{
		Float3 ergebnis;
				 ergebnis.x=B*A.x;
				 ergebnis.y=B*A.y;
				 ergebnis.z=B*A.z;
		return ergebnis;
	}
	inline Float3 VectorDiv( Float3 A, float B)
	{
		Float3 ergebnis={A.x,A.y,A.z};
		if (B==0.0f) return ergebnis;
		ergebnis.x /= B;
		ergebnis.y /= B;
		ergebnis.z /= B;
		return ergebnis;
	}
	inline float VectorDotP ( Float3 A, Float3 B)	{return A.x*B.x + A.y*B.y + A.z*B.z;}
	inline float VectorAngle ( Float3 A, Float3 B)
	{
		return dbACOS(VectorDotP(A,B)/(VectorAbs(A)*VectorAbs(B)));
	}
	inline Float3 VectorCrossP ( Float3 A, Float3 B)
	{
		Float3 normale;
				 normale.x = A.y*B.z - A.z*B.y;
				 normale.y = A.z*B.x - A.x*B.z;
				 normale.z = A.x*B.y - A.y*B.x;
		return normale;
	}
	inline Float3 VectorNormalise( Float3 A)
	{
		return VectorDiv(A,VectorAbs(A));
	}
	inline Float3 VectorNormal( Float3 A, Float3 B)
	{
		return VectorNormalise (VectorCrossP ( A, B));
	}
	inline Float3 VectorMiddle( Float3 A, Float3 B)
	{
		return VectorAdd(A,VectorMul(VectorSub(A,B),0.5f));
	}
	//*******************************************
	//               ( Ax Bx Cx )     ( x )
	// Ergebnis  = M ( Ay By Cy ) x V ( y )
	//               ( Az Bz Cz )     ( z )
	//*******************************************
	inline Float3 VectorMatrixProduct(Matrix3 M, Float3 V)
	{
		 Float3 ergebnis;
				  ergebnis.x = M.A.x*V.x + M.B.x*V.y + M.C.x*V.z;
				  ergebnis.y = M.A.y*V.x + M.B.y*V.y + M.C.y*V.z;
				  ergebnis.z = M.A.z*V.x + M.B.z*V.y + M.C.z*V.z;
		 return ergebnis;
	}
	inline Float3 VectorRotation(Float3 V, float alpha, float beta, float gamma)
	{
		//Verfahren : Vektor V3 wird 3 mal mit einer Matrix multipliziert, Superpositionsprinzip
		//            ginge natürlich schneller wenn ich die fertige Rot Matrix genommen hätte, mh später.
		float s1=dbSin(alpha);
		float s2=dbSin(beta);
		float s3=dbSin(gamma);
		float c1=dbCos(alpha);
		float c2=dbCos(beta);
		float c3=dbCos(gamma);
		Float3 V3;
		Matrix3 M3;

		//X - Rotation -> Superpositionprinzip
		M3.A.x=1.0f;
		M3.A.y=0.0f;
		M3.A.z=0.0f;
		M3.B.x=0.0f;
		M3.B.y=c1;
		M3.B.z=s1;
		M3.C.x=0.0f;
		M3.C.y=-s1;
		M3.C.z=c1;
		V3=VectorMatrixProduct(M3,V);

		//Y - Rotation -> Superpositionprinzip
		M3.A.x=c2;
		M3.A.y=0.0f;
		M3.A.z=-s2;
		M3.B.x=0.0f;
		M3.B.y=1.0f;
		M3.B.z=0.0f;
		M3.C.x=s2;
		M3.C.y=0.0f;
		M3.C.z=c2;
		V3=VectorMatrixProduct(M3,V3);

		//Z - Rotation -> Superpositionprinzip
		M3.A.x=c3;
		M3.A.y=s3;
		M3.A.z=0.0f;
		M3.B.x=-s3;
		M3.B.y=c3;
		M3.B.z=0.0f;
		M3.C.x=0.0f;
		M3.C.y=0.0f;
		M3.C.z=1.0f;
		V3=VectorMatrixProduct(M3,V3);
		return V3;
	}
	//`*********************************************************
	inline Float3 SchnittGeradeEbene(Gerade3 g, Matrix3 e)
	//`*********************************************************
	{
		//`Zuerst wird geprüft ob ein Schnittpunkt existiert
		Float3 erg={0.0f,0.0f,0.0f};

		//`Ebene : 1. Richtungsvektor u
		Float3 u; u.x=e.B.x-e.A.x; u.y=e.B.y-e.A.y; u.z=e.B.z-e.A.z;

		//`Ebene : 2. Richtungsvektor v
		Float3 v; v.x=e.C.x-e.A.x; v.y=e.C.y-e.A.y; v.z=e.C.z-e.A.z;

		//`Gerade : Richtungsvektor w
		Float3 w; w.x=g.B.x-g.A.x;	w.y=g.B.y-g.A.y; w.z=g.B.z-g.A.z;

		//` n = u x v
		Float3 n=VectorCrossP(u, v);

		//`Skalar = (n ° w)
		float skalar_nw=VectorDotP(n, w);

		//`Auswertung, und damit Feststellung ob der Schnitpunkt exisitiert
		if(skalar_nw==0.0f)	return erg;
			
		//`Berechnung der Lösungsgleichung : einfacher gehts nicht, warum es geht, is aber komplizierter
		//`               ->   ->     ->                         ->   ->   ->
		//` geg: I. Gerade :  OX = OG + r* w      , II. Ebene :  0 = n ° (OX - OE) -> Hessesche Normalenform
		//`
		//` ges: Ebene = Gerade -> Schnittpunkt, erreicht man durchs einsetzen der Geradengleichung in die Ebenengleichung
		//`      und lösen dieser Gleichung nach Parameter r, damit wird das schon berechnete Skalar (n ° w) wiederverwendet.
		//`      ->  ->   ->     ->   ->           ->   ->    -> -> ->         -> ->    -> -> ->
		//` Lsg: 0 = n ° (OG + r* w - OE)    <=>   n°(r* w) = n°(OE-OG) <=> r*(n ° w) = n°(OE-OG)
		//`                    ->   -> ->   ->  ->
		//` Lsg: Parameter r = n ° (OE-OG)/(n ° w)

		//` 1. Ersetzten von (OE-OG) durch OZ [Z steht für Zähler]
		Float3 OZ;	OZ.x = e.A.x-g.A.x;	OZ.y = e.A.y-g.A.y;	OZ.z = e.A.z-g.A.z;

		//` 2. Zaehler (n ° (OE-OG)) berechnen = DotP(n, OZ)
		float zaehler = VectorDotP(n, OZ);

		//` 3. Fertigen Parameter r berechnen = Rationaler Bruch
		float r = zaehler / skalar_nw;

		//Nun Wird der Schnittpunkt berechnet, indem r in die Geradengleichung eingesetzt wird
		erg.x = g.A.x + r * w.x;	erg.y = g.A.y + r * w.y;	erg.z = g.A.z + r * w.z;

		return erg;
	}
}

#endif