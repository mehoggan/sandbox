/*
 * main.cpp
 *
 *  Created on: March 5, 2010
 *      Author: Matthew
 */

#include "Daemon.h"

using namespace std;

int main(int argc, char* argv[])
{
	printf("Creating Daemon:\n");
	Daemon* daemon = new Daemon();
	return daemon->run();
}
