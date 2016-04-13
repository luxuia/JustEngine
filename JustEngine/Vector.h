#pragma once

#include "Macros.h"

namespace Math
{
	class DLL_EXPORT Vector4
	{
	public :
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float f[4];
			unsigned int u[4];
		};

		Vector4( ) : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 1.0f ) {}

		Vector4( const Vector4 &other ) : x( other.x ), y( other.y ), z( other.z ), w( other.w ) {}

		Vector4( float value ) : x( value ), y( value ), z( value ), w( 1 ) {}

		Vector4( float value, float w ) : x( value ), y( value ), z( value ), w( w ) {}

		Vector4( float x, float y, float z ) : x( x ), y( y ), z( z ), w( 1 ) {}

		Vector4( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) {}

		void Absolute();

		void Zero();

		void Normalize();

		Vector4 Normalized() const;

		float Length() const;

		float SquareLength() const;

		float Distance( Vector4 other ) const;

		Vector4 CrossProduct( Vector4 other ) const;

		Vector4 Project( Vector4 other ) const;

		Vector4 Clone() const;

		// all operator ignores w component.
		// or will simply set w to 1.0

		bool operator == (Vector4 other) const;

		bool operator != (Vector4 other) const;

		bool operator < (Vector4 other) const;

		bool operator <= (Vector4 other) const;

		bool operator > (Vector4 other) const;

		bool operator >= (Vector4 other) const;

		Vector4 &operator = (Vector4 other);

		Vector4 operator - () const;

		Vector4 operator + (Vector4 other) const;

		Vector4 operator - (Vector4 other) const;

		float operator * (Vector4 other) const;

		Vector4 operator * (const float other) const;

		Vector4 operator / (const float other) const;
	};

	class DLL_EXPORT Vector3
	{
	public:
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Down;

		union
		{
			struct
			{
				float x, y, z;
			};
			float f[3];
			unsigned int u[3];
		};

		Vector3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}
			 
		Vector3( const Vector4 &other ) : x( other.x ), y( other.y ), z( other.z ) {}
			  
		Vector3( float value ) : x( value ), y( value ), z( value ) {}
			  
		Vector3( float value, float w ) : x( value ), y( value ), z( value ) {}
			  
		Vector3( float x, float y, float z ) : x( x ), y( y ), z( z ) {}
			  
		Vector3( float x, float y, float z, float w ) : x( x ), y( y ), z( z ) {}

		void Absolute();

		void Zero();

		void Normalize();

		Vector3 Normalized() const;

		float Length() const;

		float SquareLength() const;

		float Distance( Vector3 other ) const;

		Vector3 CrossProduct( Vector3 other ) const;

		Vector3 Project( Vector3 other ) const;

		Vector3 Clone() const;

		// all operator ignores w component.
		// or will simply set w to 1.0

		bool operator == (Vector3 other) const;

		bool operator != (Vector3 other) const;

		bool operator < (Vector3 other) const;

		bool operator <= (Vector3 other) const;

		bool operator > (Vector3 other) const;

		bool operator >= (Vector3 other) const;

		Vector3 &operator = (Vector3 other);

		Vector3 operator - () const;

		Vector3 operator + (Vector3 other) const;

		Vector3 operator - (Vector3 other) const;

		float operator * (Vector3 other) const;

		Vector3 operator * (const float other) const;

		Vector3 operator / (const float other) const;
	};
}