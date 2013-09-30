/*
 * ServerSearchImpli.cpp
 *
 *  Created on: 03-Sep-2011
 *      Author: Vignesh
 */
#include "ServerSearchImpli.h"
#include <FBase.h>
#include <FSystem.h>
#include <FNet.h>
using namespace Osp::Net::Sockets;
using namespace Osp::Net;
using namespace Osp::Base;
using namespace Osp::System;

unsigned int ServerSearchImpli::SearchServer() {
	Socket *sock;
	sock = new Socket();
	sock->Construct(NET_SOCKET_AF_IPV4, NET_SOCKET_TYPE_DATAGRAM,
			NET_SOCKET_PROTOCOL_UDP);
	unsigned long temp = 1;
	sock->Ioctl(NET_SOCKET_FIONBIO, temp);

	String ip = "192.168.1.";
	AppLog("Entered into Search Local Network For ULIS\n");
	for(int i=1;i<5;i++) {
		String tmp_ip = String(ip);
		tmp_ip.Append(i);
		Ip4Address *i4a = new Ip4Address(tmp_ip);
		NetEndPoint *nep = new NetEndPoint(*i4a, 3491);
		ByteBuffer *txBuffer = Osp::Base::Utility::StringUtil::StringToUtf8N(tmp_ip);
		AppLog("Content sent : %s  To Ip : %S",(char *)txBuffer->GetPointer(),i4a->ToString().GetPointer());
		if(sock->SendTo(*txBuffer,*nep) != E_SUCCESS) {
			AppLog("Error in sending.");
		}
		delete txBuffer;
		delete i4a;
		delete nep;
	}

	Osp::Base::Runtime::Thread::Sleep(1000);
	unsigned long buflen=0;
	sock->Ioctl(NET_SOCKET_FIONREAD,buflen);
	AppLog("Buffer Length : %ld", buflen);
	if(buflen >1 ) {
		Ip4Address peerAddr1(NET_SOCKET_INADDR_ANY);
		unsigned short port = 0;
		NetEndPoint point(peerAddr1, port);
		ByteBuffer bb;
		bb.Construct(100 +1);
		if(sock->ReceiveFrom(bb,point) == E_SUCCESS) {
			char *recvd_data = (char *)bb.GetPointer();
			AppLog("Content Received is : %s" ,recvd_data);
			unsigned int i=0;
			for(;i<strlen(recvd_data);i++) {
				if(recvd_data[i] == ':')
					break;
			}
			if(i<strlen(recvd_data)) {
				char temp[i];
				strncpy(temp,recvd_data,i);
				temp[i]='\0';
				AppLog("IP received %s",temp);
				__hostIP.push_back(String(temp));
				char *tmp2 = &recvd_data[i+1];
				__hostName.push_back(String(tmp2));
			}
			else {
				AppLog("Data received is not properly formatted.");
			}
		}
	}
	__SearchListLength = __hostIP.size();
	return 0;
}
unsigned int ServerSearchImpli::GetSearchListSize() {
	return __SearchListLength;
}
int ServerSearchImpli::GetSearchResult(Osp::Base::String *hostName,Osp::Base::String *hostIP,int ListLTH) {
	if(ListLTH < __SearchListLength) {
		return -1;
	}
	for(int i=0;i<__SearchListLength;i++) {
		hostName[i] = __hostName[i];
		hostIP[i] = __hostIP[i];
	}
	return 0;
}
