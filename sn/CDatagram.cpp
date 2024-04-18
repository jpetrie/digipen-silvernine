/*! ==========================================================================
	@file	CDatagram.cpp
	@author	Patrick Laukaitis
	@brief	Implementation of the Datagram object
	@par	January 28, 2004
	@par	Project: Silver Nine
	@par	Compiler: Visual C++ .Net 2003
	@par	Modifications:
			January 29, 2004	--	plaukait	--	Added disconnect, 
													moved the RemoveDatagramFromList() call
			
========================================================================== */

/*																      includes
------------------------------------------------------------------------------ */
#include "CDatagram.h"
#include "CNetworkMgrS.h"

/*																	   methods
------------------------------------------------------------------------------ */
/* *************************************************************************** */
/*!
	@brief	CDatagram constructor 
*/
/* *************************************************************************** */
CDatagram::CDatagram()
{
	if( (datagram_ = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 )
		throw("Error creating a UDP Socket");

	broadcastPermission_ = 1;
	if(setsockopt(datagram_, SOL_SOCKET, SO_BROADCAST, (const char *)&broadcastPermission_, 
						sizeof(broadcastPermission_)) < 0)
		throw("Error -- could not set socket opt");

	listening = false;	// not listening by default
}

/* *************************************************************************** */
/*!
	@brief	CDatagram destructor
*/
/* *************************************************************************** */
CDatagram::~CDatagram()
{
}

/* *************************************************************************** */
/*!
	@brief	Send Method
*/
/* *************************************************************************** */
void CDatagram::Send(CPacket & packet, std::string & DestAddr, unsigned short Port)
{
	// Create the local address 
	memset(&broadcastAddr_, 0x00, sizeof(broadcastAddr_));
	broadcastAddr_.sin_family = AF_INET;
	broadcastAddr_.sin_addr.s_addr = inet_addr(DestAddr.c_str());
	broadcastAddr_.sin_port = htons(Port);

	// The size isn't calculated until after serialization.  This ensures that serialization does indeed take place first.
	char * packData = (char *)packet.Serialize();

	// Send the thing whole or don't send it at all.  No segmentation and reconstruction takes place.
	if( packet.Size() != sendto(datagram_, packData, packet.Size(), 0, 
		(struct sockaddr *)&broadcastAddr_, sizeof(broadcastAddr_)) )
			nlTHROW("Error, could not send the entire datagram at once");

	NetworkManager->SendCallB();
}

/* *************************************************************************** */
/*!
	@brief	Bind the UDP Datagram to a port and address -- NetworkMgr will recv
	@par	Will not block (no blocking calls here)
*/
/* *************************************************************************** */
void CDatagram::Listen(unsigned short Port)
{
	// Set up the info for binding the datagram
	memset(&broadcastAddr_, 0x00, sizeof(broadcastAddr_));
	broadcastAddr_.sin_family = AF_INET;
	broadcastAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
	broadcastAddr_.sin_port = htons(Port);

	// Bind to the address
	if( bind(datagram_, (struct sockaddr *)&broadcastAddr_, sizeof(broadcastAddr_)) < 0 )
		nlTHROW("Error, could not bind the datagram");

	listening = true;

	NetworkManager->AddDatagramToList(*this);
}

/* *************************************************************************** */
/*!
	@brief	Disconnect the UDP socket (close it)
	@par	UDP is connectionless, but the socket must still be returned to the OS
*/
/* *************************************************************************** */
void CDatagram::Disconnect()
{
#ifdef NSL_VC
	if(datagram_)
        if(closesocket(datagram_))
			nlTHROW("Error closing a socket");
#else	// *NIX
	if(datagram_)
        if(close(datagram_) < 0)
			nlTHROW("Error closing a socket");
#endif

	if(listening)
	{
        NetworkManager->RemoveDatagramFromList(*this);
		listening = false;
	}

	NetworkManager->DiscnnectCallB();
}

/* *************************************************************************** */
/*!
	@brief	Test if two sockets are equal to each other
	@par	BSD Sockets from the OS are unique, so that is all that is checked
*/
/* *************************************************************************** */
bool CDatagram::operator== (CDatagram & datagram)
{
	if(datagram_ == datagram.GetDatagram())
		return true;
	else
		return false;
}

/* *************************************************************************** */
/*!
	@brief	Assignment operator -- dangerous to use because of the potential
			for multiple registration
*/
/* *************************************************************************** */
CDatagram & CDatagram::operator= (const CDatagram & datagram)
{
	if(this != &datagram)
	{
		datagram_ = datagram.datagram_;
		broadcastAddr_ = datagram.broadcastAddr_;
		listening = datagram.listening;
		broadcastPermission_ = datagram.broadcastPermission_;
		broadcastPort_ = datagram.broadcastPort_;
	}

	return *this;
}