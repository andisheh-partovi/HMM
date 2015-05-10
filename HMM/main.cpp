#include <conio.h>

#include "Run.h"

int main()
{
	Run* app = new Run();

	app->run("data");

	_getch();
	return 0;
}