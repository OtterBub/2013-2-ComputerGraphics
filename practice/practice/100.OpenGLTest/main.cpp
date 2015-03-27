#include <stdio.h>
#include "DrawSystem.h"

int main(int argc, char *argv[])
{
	DrawSystem sys;

	sys.Init();
	sys.Run();

	return 0;
}