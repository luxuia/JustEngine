// Application.cpp : 定义控制台应用程序的入口点。
//

#include "pch.h"
//#include <SFML/Window.hpp>
#include "GameCore.h"

using namespace GameCore;

const int MAX_FIX_LOOP_NUM = 5;
const float FIX_UPDATE_TICK = 1000.f/60.f;

class App : public IGameApp
{
public:

	App() = default;

	virtual void Start( void ) override;

	virtual void CleanUp( void ) override;

	virtual void Update( float deltaTime ) override;

	virtual void RenderScene( void ) override;
};

int _tmain(int argc, wchar_t** argv[])
{
	byte a = 1;
	byte* p = &a;

	byte* p1 = p++;
	printf( "0x%x 0x%x", p, p1);
	CREATE_APP( App );
	return 0;
}



void App::Start()
{

}

void App::CleanUp()
{

}

void App::Update(float deltaTime)
{

}

void App::RenderScene()
{

}