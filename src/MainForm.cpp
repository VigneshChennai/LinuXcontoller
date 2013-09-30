#include "MainForm.h"
#include "TouchEventForm.h"
#include "ServerListForm.h"
#include "ServerSearchImpli.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Net::Sockets;
using namespace Osp::Net;
MainForm::MainForm(void) {
}

MainForm::~MainForm(void) {
}

bool MainForm::Initialize() {
	Form::Construct(L"IDF_FORM2");

	return true;
}

result MainForm::OnInitializing(void) {
	result r = E_SUCCESS;

	// TODO: Add your initialization code here
	SetSoftkeyActionId(SOFTKEY_0, 201);
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	SetSoftkeyActionId(SOFTKEY_1, 202);
	AddSoftkeyActionListener(SOFTKEY_1, *this);

	Button *pButton1 = static_cast<Button *> (GetControl("IDC_BUTTON1"));
	if (pButton1) {
		pButton1->SetActionId(100);
		pButton1->AddActionEventListener(*this);
	}
	return r;
}

result MainForm::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}
void MainForm::OnActionPerformed(const Osp::Ui::Control &source,int actionId) {
	// TODO: Add your implementation codes here
	switch (actionId) {
	case 100:
	{
		AppLog("Entered into action performed\n");
		ServerSearchImpli ssi;
		ssi.SearchServer();
		AppLog("Search Server List size : %d",ssi.GetSearchListSize());
		if (ssi.GetSearchListSize() > 0) {
			// Add the form to the frame
			Osp::Base::String hostIP[4];
			Osp::Base::String hostName[4];

			if(ssi.GetSearchResult(hostName,hostIP,4)!=-1) {
				ServerListForm *slf = new ServerListForm();
				slf->Initialize();
				Application * app = Osp::App::Application::GetInstance();
				Frame *pFrame = app->GetAppFrame()->GetFrame();
				pFrame->AddControl(*slf);
				pFrame->SetCurrentForm(*slf);
				for(unsigned int i=0;i<ssi.GetSearchListSize();i++)
					slf->LoadList(hostIP[i],hostName[i]);
				slf->Draw();
				slf->Show();
			}
			else {
				AppLog("Search list size exits length 4");
			}
		}
		else
		{
			__PopUp= new Popup();
			__PopUp->Construct(L"IDP_POPUP1");
			Label *pLabel = static_cast<Label *> (__PopUp->GetControl("IDC_LABEL1"));
			pLabel->SetBackgroundColor(SYSTEM_COLOR_POPUP_BACKGROUND);
			Button *pButton = static_cast<Button *> (__PopUp->GetControl("IDC_BUTTON1"));
			if(pButton)
			{
				pButton->SetActionId(301);
				pButton->AddActionEventListener(*this);
			}
			__PopUp->SetShowState(true);
			__PopUp->Show();
		}
		break;
	}
	case 301:
		AppLog("Button Clicked");
		__PopUp->SetShowState(false);
		this->Draw();
		this->Show();
		break;
	case 201:
		AppLog("Exit button clicked.");
		Osp::App::Application::GetInstance()->Terminate();
		break;
	}
}
