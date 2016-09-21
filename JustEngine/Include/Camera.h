#pragma once

#include "pch.h"
#include "Component.h"

namespace JustEngine
{
	using namespace JustEngine;
	class Frustum;
	class DLL_EXPORT Camera : public Component, public std::enable_shared_from_this<Camera>
	{
	protected:
		Matrix4 mProjectionMatrix;
		Matrix4 mViewMatrix;

		Frustum* mFrustum;

		bool mPerspective = true;

		float mNear = 0.f;
		float mFar = 0.f;
	public:
		ObjTypePtr( Camera );

		static Ptr Create();
		Camera();

		void SetPerspective(float fov, float aspect, float nearz, float farz);

		void SetOrtho( float width, float height, float nearz, float farz );

		const Matrix4& GetProjectionMatrix() const;
		const Matrix4& GetViewMatrix() const;

		const Frustum& GetFrustum() const;

		bool IsPerspective() const;

		void OnOwnerTransformChange(const std::shared_ptr<void>& sender);

		bool IsVisible( const Vector4& point ) const;

	protected:
		virtual void OnAttach( const std::shared_ptr<GameObject> &node ) override;
		virtual void OnDetach( const std::shared_ptr<GameObject> &node ) override;

	private:
		
	};
}