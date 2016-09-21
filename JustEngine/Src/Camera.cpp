
#include "Camera.h"
#include "Matrix.h"
#include "Frustum.h"
#include "Signal.h"
#include "GameObject.h"

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

	void Camera::SetPerspective(float fov, float aspect, float nearz, float farz)
	{
		mNear = nearz;
		mFar = farz;
		mPerspective = true;

		mProjectionMatrix.PerspectiveFovLH(fov, aspect, nearz, farz);
	}

	void Camera::SetOrtho( float width, float height, float nearz, float farz )
	{
		mNear = nearz;
		mFar = farz;
		mPerspective = false;

		mProjectionMatrix.OrthoLH( width, height, nearz, farz );
	}

	const Matrix4& Camera::GetProjectionMatrix() const
	{
		return mProjectionMatrix;
	}

	const JustEngine::Matrix4& Camera::GetViewMatrix() const
	{
		return mViewMatrix;
	}

	const Frustum& Camera::GetFrustum() const
	{
		return *mFrustum;
	}

	bool Camera::IsVisible( const Vector4& point ) const
	{
		return true;
	}

	bool Camera::IsPerspective() const 
	{
		return mPerspective;
	}

	void Camera::OnOwnerTransformChange(const std::shared_ptr<void>& sender) {
		auto node = std::static_pointer_cast<GameObject>(sender);

		auto& worldPos = node->GetWorldPosition();
		mViewMatrix.LookAt(worldPos, Vector3(0, 0, 0), Vector3::Up);
	}

	void Camera::OnAttach( const std::shared_ptr<GameObject> &node )
	{
		Component::OnAttach( node );

		auto& self = shared_from_this();
		node->GetSignal()->Connect(GameObject::TransfromChange, self, BIND_FUNC(self, &Camera::OnOwnerTransformChange));
	}

	void Camera::OnDetach( const std::shared_ptr<GameObject> &node )
	{
		Component::OnDetach( node );

		node->GetSignal()->Disconnect(GameObject::TransfromChange, shared_from_this());
	}
}