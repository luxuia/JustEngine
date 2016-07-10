
#include "Camera.h"
#include "Math/Matrix.h"

namespace JustEngine
{

	Camera::Ptr Camera::Create()
	{
		return std::make_shared<Camera>();
	}

	Camera::Camera( )
	{
		mTypeIdex = typeid(Camera); 
	}

	void Camera::SetPerspective( float width, float height, float nearz, float farz )
	{
		mNear = nearz;
		mFar = farz;
		mPerspective = true;

		mProjectionMatrix.PerspectiveLH(width, height, nearz, farz);
	}

	void Camera::SetOrtho( float width, float height, float nearz, float farz )
	{
		mNear = nearz;
		mFar = farz;
		mPerspective = false;

		mProjectionMatrix.OrthoLH( width, height, nearz, farz );
	}

	Matrix4 Camera::GetProjectionMatrix() const
	{
		return mProjectionMatrix;
	}

	Frustum Camera::GetFrustum() const
	{
		return mFrustum;
	}

	bool Camera::IsVisible( const Vector4& point ) const
	{
		return true;
	}

	bool Camera::IsPerspective() const 
	{
		return mPerspective;
	}

	void Camera::OnAttach( const std::shared_ptr<GameObject> &node )
	{
		Component::OnAttach( node );
	}

	void Camera::OnDetach( const std::shared_ptr<GameObject> &node )
	{
		Component::OnDetach( node );
	}
}