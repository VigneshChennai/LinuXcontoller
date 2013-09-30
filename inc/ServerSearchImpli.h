/*
 * SearchServerImpli.h
 *
 *  Created on: 03-Sep-2011
 *      Author: Vignesh
 */

#ifndef SEARCHSERVERIMPLI_H_
#define SEARCHSERVERIMPLI_H_

#include<stdlib.h>
#include<vector>
#include <FBase.h>
#include <FSystem.h>

class ServerSearchImpli
{
private:
	std::vector<Osp::Base::String> __hostName,__hostIP;
	int __SearchListLength;
public:
	ServerSearchImpli() {
		__SearchListLength = 0;
	}
	unsigned int SearchServer();
	unsigned int GetSearchListSize();
	int GetSearchResult(Osp::Base::String *hostName,Osp::Base::String *hostIP,int ListLTH);
	~ServerSearchImpli() {
		__hostName.clear();
		__hostIP.clear();
	}
};
#endif /* SEARCHSERVERIMPLI_H_ */
