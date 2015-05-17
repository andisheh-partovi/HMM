#include <conio.h>

#include "Run.h"

int main()
{
	Run* app = new Run();

	app->run("data\\house3.txt");

	_getch();
	return 0;
}