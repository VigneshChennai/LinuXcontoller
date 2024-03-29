/**
 * Name        : LinuXcontroller
 * Version     : 
 * Vendor      : Vigneshwaran P
 * Description : A complete Controller of Linux system
 */


#include "LinuXcontroller.h"
#include "MainForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

LinuXcontroller::LinuXcontroller()
{
}

LinuXcontroller::~LinuXcontroller()
{
}

Application*
LinuXcontroller::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new LinuXcontroller();
}

bool
LinuXcontroller::OnAppInitializing(AppRegistry& appRegistry)
{
	// The application's permanent data and context can be obtained from the appRegistry.
	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// Create a form
	MainForm *pMain = new MainForm();
	pMain->Initialize();

	//Getting the application frame.
	Frame *pFrame = GetAppFrame()->GetFrame();

	pFrame->AddControl(*pMain);
	pFrame->SetCurrentForm(*pMain);
	pMain->Draw();
	pMain->Show();
	return true;
}

bool
LinuXcontroller::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
LinuXcontroller::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void
LinuXcontroller::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void
LinuXcontroller::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
LinuXcontroller::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
LinuXcontroller::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
LinuXcontroller::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
