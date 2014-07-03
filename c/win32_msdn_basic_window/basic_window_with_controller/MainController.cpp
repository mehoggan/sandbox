#include "MainController.h"

MainController::MainController()
{
	
}

MainController::~MainController()
{
}

int MainController::CheckStatus()
{
	return ::MessageBox(NULL, TEXT("MainController now created"), TEXT("You Have Controll Over Main Window"), MB_OK);
}