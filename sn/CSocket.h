/*! ==========================================================================
	@file	CSocket.h
	@author	Patrick Laukaitis
	@brief	Specification of the Socket Object
	@par	November 07, 2003
	@par	Project: Silver Nine
	@par	Compiler: Visual C++ .Net 2003
	@par	Modifications:
			January 15, 2004	--	plaukait	--	Ported to new SN libraries

	========================================================================== */

/*																         guard
------------------------------------------------------------------------------ */

#ifndef _C_SOCKET_H_
#define _C_SOCKET_H_

/*																	   defines
------------------------------------------------------------------------------ */
#define MAX_LISTEN_BACKLOG 50


/*																	  includes
------------------------------------------------------------------------------ */
#include "precompiled.h"
#include "CPacket.h"
#include "NSL.h"

/*																	   classes
------------------------------------------------------------------------------ */
class CSocket
{
public:
	CSocket();
	~CSocket();
	void Connect(std::string & addr, int port, struct sockaddr_in * existingAddress = NULL);
	void Disconnect();
	void Listen(int local_port);
	void Send(CPacket & packet);
	int  GetSocket() { return mSocket; };
	bool Listening() { return listening; };
	void SetSocket(int socket);
	bool operator== (CSocket & socket);
	struct sockaddr_in * GetForeignAddress() { return &mForeignAddress; };
	struct sockaddr_in * GetLocalAddress() { return &mLocalAddress; };
	void SetForeignAddress(struct sockaddr_in * addr) { mForeignAddress = *addr; };
	CSocket & operator= (const CSocket &);

private:
	int mSocket;
	struct sockaddr_in mForeignAddress;
	struct sockaddr_in mLocalAddress;
	const int MAX_BACKLOG;
	bool listening;
	unsigned long ResolveDNS(std::string & hostName);	// Get DNS info
};



#endif	/* _C_SOCKET_H_ */