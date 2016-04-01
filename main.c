#include <stdio.h>
#include <stdlib.h>

#include "ec_field.h"
#include "ec_curve.h"

int main(void) {
	gfInit();
	gfSelfTest(10000);	
	ecSelfTest(1000);
	gfQuit();
	return EXIT_SUCCESS;
}
