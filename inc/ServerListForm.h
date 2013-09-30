
#ifndef _SERVERLISTFORM_H_
#define _SERVERLISTFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>
#include <vector>

class ServerListForm :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::IActionEventListener,
 	public Osp::Ui::IItemEventListener
{
	Osp::Ui::Controls::List *__List1;
	std::vector<Osp::Base::String> __ips;
// Construction
public:
	ServerListForm(void);
	virtual ~ServerListForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

	void LoadList(Osp::Base::String &ip,Osp::Base::String &host);
	virtual void OnActionPerformed(const Osp::Ui::Control &source, int actionId);

	virtual void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);
};

#endif
