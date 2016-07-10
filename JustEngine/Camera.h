#pragma once

#include "pch.h"
#include "Component.h"
#include "Frustum.h"

namespace JustEngine
{
	using namespace Math;
	class DLL_EXPORT Camera : public Component, public std::enable_shared_from_this<Camera>
	{
	protected:
		Matrix4 mProjectionMatrix;
		Frustum mFrustum;

		bool mPerspective = true;

		float mNear = 0.f;
		float mFar = 0.f;
	public:
		ObjTypePtr( Camera );

		static Ptr Create();
		Camera();

		void SetPerspective( float width, float height, float near, float far );

		void SetOrtho( float width, float height, float near, float far );

		Matrix4 GetProjectionMatrix() const;

		Frustum GetFrustum() const;

		bool IsPerspective() const;

		bool IsVisible( const Vector4& point ) const;

	protected:
		virtual void OnAttach( const std::shared_ptr<GameObject> &node ) override;
		virtual void OnDetach( const std::shared_ptr<GameObject> &node ) override;
	};
}