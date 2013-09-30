
#include "TouchEventForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Collection;
using namespace Osp::Graphics;
using namespace Osp::Net::Sockets;
using namespace Osp::Net;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Runtime;

TouchEventForm::TouchEventForm(void)
{
}

TouchEventForm::~TouchEventForm(void)
{
}

bool
TouchEventForm::Initialize()
{
	Form::Construct(L"IDF_FORM1");

	return true;
}

result
TouchEventForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here
	SetSoftkeyActionId(SOFTKEY_0, SOFTKEY_0_ID);
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	SetSoftkeyActionId(SOFTKEY_1, SOFTKEY_1_ID);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	AddTouchEventListener(*this);
	__release = false;
	__pButton1 = static_cast<Button *>(GetControl("IDC_BUTTON1"));
	if (__pButton1)
	{
		__pButton1->SetActionId(MOUSE_BUTTON_ID);
		__pButton1->AddActionEventListener(*this);
	}
	return r;
}
String
TouchEventForm::Connect(String ip)
{
	__sock = new Socket();
	__sock->Construct(NET_SOCKET_AF_IPV4,NET_SOCKET_TYPE_STREAM,NET_SOCKET_PROTOCOL_TCP);
	unsigned long temp=0;
	__sock->Ioctl(NET_SOCKET_FIONBIO,temp);

	String ret="Failed";
	result res = E_SUCCESS;

	Ip4Address *i4a = new Ip4Address(ip);
	NetEndPoint *nep = new NetEndPoint(*i4a,3490);
	res = __sock->Connect(*nep);
	if(IsFailed(res))
	{
		ret = "Failed";
	}
	else
	{
		char c[5]= {0,2,0,0,0};
		char c1[50];
		int i;
		__sock->Send((void *)c,5,i);
		__sock->Receive(c1,49,i);
		ret = String(c1);
	}
	delete i4a;
	delete nep;
	return ret;
}
result
TouchEventForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


void
TouchEventForm::DisplayMultipointTouchInfo(const Control &source)
{
    Touch touch;
    IList *pList = null;
    pList = touch.GetTouchInfoListN(source);
    if (pList)
    {
        for(int i=0; i<pList->GetCount(); i++ )
        {
            TouchInfo *pTouchInfo = static_cast<TouchInfo *>(pList->GetAt(i));
            AppLog("OnTouchMoved : [%d]%d,%d - %d", pTouchInfo->id, pTouchInfo->position.x ,pTouchInfo->position.y,pTouchInfo->status);
        }
        pList->RemoveAll(true);
        delete pList;
    }
}
void
TouchEventForm::OnTouchDoublePressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
    AppLog("OnTouchDoublePressed is called. [%d]%d,%d", touchInfo.GetPointId(), currentPosition.x, currentPosition.y);
    DisplayMultipointTouchInfo(source);
        //__sock->Send((void *)c,5,i);
        __doubleClicked = true;
        __singleClicked = false;
}

void
TouchEventForm::OnTouchFocusIn(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
    AppLog("OnTouchFocusIn is called. [%d]%d,%d", touchInfo.GetPointId(), currentPosition.x, currentPosition.y);
    DisplayMultipointTouchInfo(source);
}

void
TouchEventForm::OnTouchFocusOut(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
    AppLog("OnTouchFocusOut is called. [%d]%d,%d", touchInfo.GetPointId(), currentPosition.x, currentPosition.y);
    DisplayMultipointTouchInfo(source);
}

void
TouchEventForm::OnTouchLongPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
    AppLog("OnTouchLongPressed is called. [%d]%d,%d", touchInfo.GetPointId(), currentPosition.x, currentPosition.y);
    DisplayMultipointTouchInfo(source);
	char c[5];
	int i;
	c[0]=2;
	c[1]=2;
	c[2]=3;
	c[3]=2;
	c[4]=0;
	__sock->Send((void *)c,5,i);
	__longPressed = true;
    __singleClicked = false;
}

void
TouchEventForm::OnTouchMoved(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
    AppLog("OnTouchMoved is called. [%d]%d,%d", touchInfo.GetPointId(), currentPosition.x, currentPosition.y);
    DisplayMultipointTouchInfo(source);
    if(__doubleClicked == true) {
    	char c[5];
		c[0]=2;
		c[1]=2;
		c[2]=1;
		c[3]=(__release)?1:0;
		c[4]=0;
		int i;
		__sock->Send((void *)c,5,i);
		if(__release)
		{
			__pButton1->SetText(String("Mouse Press"));
		}
		else
		{
			__pButton1->SetText(String("Mouse Release"));
		}
		Draw();
		Show();
		__release = (__release)?false:true;
		__doubleClicked = false;
    }
    /*static long long lastTime=0;
    long long presentTime;
    Osp::System::SystemTime::GetTicks(presentTime);
    long limit = presentTime - lastTime;

    AppLog("Time diff : %ld",limit);
    if(limit >=20 ){
    	limit=1;
    }
    else if(limit < 16) {
		limit = 6;
    }else if(limit <17) {
    	limit =5;
    }else if(limit <20) {
    	limit =1;
    }
    AppLog("Limit Value : %ld",limit);
    //for(int j=0;j<3;j++) {*/
		char c[5];
		int i;
		c[0]=1;
		c[1]=2;
		c[2]=__x-currentPosition.x;
		c[3]=__y-currentPosition.y;
		c[4]=0;
		for(int j=0;j<3;j++)
		__sock->Send((void *)c,5,i);
    //}
		__x=currentPosition.x;
		__y=currentPosition.y;
		__moved = true;
		/*Osp::System::SystemTime::GetTicks(presentTime);
		lastTime = presentTime;*/
    __singleClicked = false;
}

void
TouchEventForm::OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
    AppLog("OnTouchPressed is called. [%d]%d,%d", touchInfo.GetPointId(), currentPosition.x, currentPosition.y);
    DisplayMultipointTouchInfo(source);
    __x=currentPosition.x;
    __y=currentPosition.y;
    __clicked = true;
    __moved = false;
    __doubleClicked = false;
    __longPressed = false;
}

void
TouchEventForm::OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
    AppLog("OnTouchReleased is called. [%d]%d,%d", touchInfo.GetPointId(), currentPosition.x, currentPosition.y);
    DisplayMultipointTouchInfo(source);
    if(__clicked == true && __moved == false && __doubleClicked == false && __longPressed == false)
    {
    	__singleClicked = true;
    	char c[5];
		int i;
		c[0]=2;
		c[1]=2;
		c[2]=1;
		c[3]=2;
		c[4]=0;
		__sock->Send((void *)c,5,i);
    }
    if(__doubleClicked == true && __moved == false) {
    	char c[5];
		int i;
		c[0]=2;
		c[1]=2;
		c[2]=1;
		c[3]=2;
		c[4]=0;
		__sock->Send((void *)c,5,i);
    }
}

void
TouchEventForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	// TODO: Add your implementation codes here
	switch(actionId)
	{
	case SOFTKEY_0_ID:
		AppLog("Exit Button is clicked! \n");
		Osp::App::Application::GetInstance()->Terminate();
		break;
	case MOUSE_BUTTON_ID:
		AppLog("Mouse pressed.");
		char c[5];
		c[0]=2;
		c[1]=2;
		c[2]=1;
		c[3]=(__release)?1:0;
		c[4]=0;
		int i;
		__sock->Send((void *)c,5,i);
		if(__release)
		{
			__pButton1->SetText(String("Mouse Press"));
		}
		else
		{
			__pButton1->SetText(String("Mouse Release"));
		}
		Draw();
		Show();
		__release = (__release)?false:true;
		break;
	}
}
