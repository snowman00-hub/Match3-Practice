#include "stdafx.h"
#include "Framework.h"

int main()
{
    FRAMEWORK.Init(720, 960, "FrameWork");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}