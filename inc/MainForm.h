
#ifndef _MainForm_H_
#define _MainForm_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FNet.h>

class MainForm :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::IActionEventListener
{

// Construction
public:
	MainForm(void);
	virtual ~MainForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:
	Osp::Ui::Controls::Popup * __PopUp;
	virtual void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
};

#endif
