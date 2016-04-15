// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include <stdio.h>
#include <tchar.h>

// TODO:  在此处引用程序需要的其他头文件

#define MY_IID_PPV_ARGS(x) (void**)x

#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <memory>
#include <string>
#include <exception>

#include <wrl.h>
#include <ppltasks.h>
#include "Utility.h"
#include "Macros.h"

// Math Relate
#include "Math/Vector.h"
#include "Math/Matrix.h"


// D3D  Relate
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcommon.h>
#include <dxgi.h>