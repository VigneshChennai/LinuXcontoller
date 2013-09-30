
#ifndef _TOUCHEVENTFORM_H_
#define _TOUCHEVENTFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FNet.h>
#include <FApp.h>
#include <FSysSystemTime.h>

#define SOFTKEY_0_ID 101
#define SOFTKEY_1_ID 102
#define MOUSE_BUTTON_ID 103


class TouchEventForm :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::ITouchEventListener,
 	public Osp::Ui::IActionEventListener
{
private:
	Osp::Net::Sockets::Socket * __sock;
	int __x,__y;
	bool __release,__clicked,__moved,__longPressed,__doubleClicked,__singleClicked;
	Osp::Ui::Controls::Button *__pButton1;
// Construction
public:
	TouchEventForm(void);
	virtual ~TouchEventForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:
	void DisplayMultipointTouchInfo(const Control &source);
// Generated call-back functions
public:

	Osp::Base::String Connect(Osp::Base::String ip);
	virtual void OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);

	virtual void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
};

#endif
