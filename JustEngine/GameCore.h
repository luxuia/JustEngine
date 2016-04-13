//
// Copyright (c) luxujia. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  luxuia@foxmail.com
//

#pragma once

#include "pch.h"

namespace GameCore
{
	class IGameApp
	{
	public :
		virtual void Start( void ) = 0;
		virtual void CleanUp( void ) = 0;

		virtual void Update( float deltaTime ) = 0;
		virtual void RenderScene( void ) = 0;

		virtual void RenderUI( void ) {};
	};
	
	void RunApp( IGameApp& app, const wchar_t* className );
}

#define CREATE_APP( app_class )\
	{ \
		GameCore::RunApp( app_class(), L#app_class ); \
		return 0; \
	}

