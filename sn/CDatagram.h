/*! ==========================================================================
	@file	CDatagram.h
	@author	Patrick Laukaitis
	@brief	Specification of the Datagram Object
	@par	January 28, 2004
	@par	Project: Silver Nine
	@par	Compiler: Visual C++ .Net 2003
	@par	Modifications:

	========================================================================== */

/*																         guard
------------------------------------------------------------------------------ */

#ifndef _C_DATAGRAM_H_
#define _C_DATAGRAM_H_

/*																	   defines
------------------------------------------------------------------------------ */


/*																	  includes
------------------------------------------------------------------------------ */
#include "precompiled.h"
#include "CPacket.h"
#include "NSL.h"

/*																	   classes
------------------------------------------------------------------------------ */
class CDatagram
{
public:
	CDatagram();
	~CDatagram();
	void Send(CPacket & packet, std::string & DestAddr, unsigned short Port);
	int GetDatagram() const { return datagram_; }
	bool Listening() const { return listening; }
	bool operator== (CDatagram & datagram);
	void Listen(unsigned short Port);
	void Disconnect();
	CDatagram & operator= (const CDatagram &);

private:
	int datagram_;
	struct sockaddr_in	broadcastAddr_;
	unsigned short broadcastPort_;
	int broadcastPermission_;
	bool listening;
};



#endif	/* _C_DATAGRAM_H_ */