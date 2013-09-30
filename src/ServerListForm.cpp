
#include "ServerListForm.h"
#include "TouchEventForm.h"
#include "ServerSearchImpli.h"
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


ServerListForm::ServerListForm()
{

}

ServerListForm::~ServerListForm(void)
{
}

bool
ServerListForm::Initialize()
{
	Form::Construct(L"IDF_FORM3");

	return true;
}

result
ServerListForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here
	SetSoftkeyActionId(SOFTKEY_0, 100);
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	SetSoftkeyActionId(SOFTKEY_1, 101);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	SetOptionkeyActionId(102);
	AddOptionkeyActionListener(*this);

	__List1 = static_cast<List *>(GetControl("IDC_LIST1"));
	if (__List1)
	{
		__List1->AddItemEventListener(*this);
	}
	return r;
}

result
ServerListForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}
void
ServerListForm::LoadList(String &ip,String &host)
{
	String temp("At Location : ");
	temp.Append(ip);
	__ips.push_back(ip);
	__List1->AddItem(&host,&temp,null,null,200 + __ips.size()-1);
}

void
ServerListForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	// TODO: Add your implementation codes here
	AppLog("Action performed");
	switch(actionId)
	{
	case 100:
		Osp::App::Application::GetInstance()->Terminate();
		break;
	case 101:
		__ips.clear();
		__List1->RemoveAllItems();
		ServerSearchImpli ssi;
		ssi.SearchServer();
		AppLog("Search Server List size : %d",ssi.GetSearchListSize());
		if (ssi.GetSearchListSize() > 0) {
			// Add the form to the frame
			Osp::Base::String hostIP[4];
			Osp::Base::String hostName[4];

			if(ssi.GetSearchResult(hostName,hostIP,4)!=-1) {
				__ips.clear();
				__List1->RemoveAllItems();
				for(unsigned int i=0;i<ssi.GetSearchListSize();i++)
					LoadList(hostIP[i],hostName[i]);
			}
			else {
				AppLog("Search list size exits length 4");
			}
		}
		this->Draw();
		this->Show();
		break;
	}
}

void
ServerListForm::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status)
{
	// TODO: Add your implementation codes here
	AppLog("Action performed in oic");
	AppLog("Entering Touch Event Form");
	int temp = itemId-200;
	TouchEventForm *tef = new TouchEventForm();
	tef->Initialize();
	tef->Connect(__ips[temp]);
	__ips.clear();
	Osp::App::Application * app = Osp::App::Application::GetInstance();
	Frame *pFrame = app->GetAppFrame()->GetFrame();
	pFrame->AddControl(*tef);
	pFrame->SetCurrentForm(*tef);
	tef->Draw();
	tef->Show();
}
