#include <conio.h>

#include "Run.h"

int main()
{
	Run* app = new Run();

	app->run("HMMassignment\\house1.txt");

	_getch();
	return 0;
}