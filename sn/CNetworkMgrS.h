/*! ==========================================================================
	@file	CNetworkMgrS.h
	@author	Patrick Laukaitis
	@brief	Specification of the Networking Manager
	@par	November 07, 2003
	@par	Project: Silver Nine
	@par	Compiler: Visual C++ .Net 2003
	@par	Modifications:
			January 15, 2004	--	plaukait	--	Ported to new SN libraries

	========================================================================== */

/*																         guard
------------------------------------------------------------------------------ */

#ifndef _C_NETWORKMGR_S_H_
#define _C_NETWORKMGR_S_H_

/*																	   defines
------------------------------------------------------------------------------ */
#define MAX_PAYLOAD_SIZE 8192	// move this into the class as a constant
#define BITS_IN_BYTE 8			// used for size calculations in ProcessNetwork
#define GAME_PORT	2501		// Port used for network communication
#define NetworkManager	(CNetworkMgrS::instance())
#define INVALID_ARGUMENT 10022	// Invalid argument code returned by select()

/*																	  includes
------------------------------------------------------------------------------ */
#include "precompiled.h"
#include "CSocket.h"
#include "CDatagram.h"
#include "CPacket.h"
#include "CPacketFactory.h"

/*																	   classes
------------------------------------------------------------------------------ */
class CNetworkMgrS : public nsl::singleton< CNetworkMgrS >
{
public:
	CNetworkMgrS();
	~CNetworkMgrS();
	void ProcessNetwork();			// Get data from the network, invoke callbacks
	void RegisterConnectFunc(void (*userCallB)(CSocket & socket)) { ConnectCallB = userCallB; };	// Notifies of successful connection
	void RegisterDiscnnectFunc(void (*userCallB)()) { DiscnnectCallB = userCallB; };// Notifies of successful disconnection
	void RegisterAcceptFunc(void (*userCallB)()) { AcceptCallB = userCallB; };		// Notifies of new listened-for connection
	void RegisterSendFunc(void (*userCallB)()) { SendCallB = userCallB; };			// Notifies of successful data transmission
	void RegisterRecvFunc(void (*userCallB)(CPacket & packet, CSocket & socket)) { RecvCallB = userCallB; };	// Notifies of successful reception of data
	void AddSocketToList(CSocket & socket);	// Add a socket to the internal list for listening
	void AddDatagramToList(CDatagram & datagram);	// Add a datagram to the internal list for recv'ing
	void RemoveSocketFromList(CSocket & socket);
	void RemoveDatagramFromList(CDatagram & datagram);
	void ClearSocketList();			// Clear everything from the socket list
	void ClearDatagramList();		// Clear everything from the datagram list
	CPacket* MakePacket(CPacket::ID pck);
	std::vector<CSocket> sockList;		// list of CSockets to be listened on
	
private:

	// User Callbacks
	void (*ConnectCallB)(CSocket & socket);
	void (*DiscnnectCallB)();
	void (*AcceptCallB)();
	void (*SendCallB)();
	void (*RecvCallB)(CPacket & packet, CSocket & socket);

	// socket info
	struct timeval tval;
	fd_set	master_fd;					// master list of sockets to select() on
	fd_set  use_fd;						// socket list we actually use
	fd_set	master_UDP_fd;				// master list of UDP sockets to test
	char RecvBuffer[MAX_PAYLOAD_SIZE];
	std::vector<CDatagram> datagramList;	// list of CDatagrams to be listened on 
	int maxFD;
	int maxUDP_FD;						// Maximum value of a UDP file descriptor

	// Record Keeping
	unsigned long mSends;
	unsigned long mRecvs;
	unsigned long mConnects;
	unsigned long mSocketsInUse;
	unsigned long mDiscnnects;

	// data gathering / formatting 
	bool GetPacketData(unsigned int size, int socket, char * buffer, unsigned int buffLen);
	bool GetDatagramData(unsigned int size, int datagram, char * buffer, unsigned int buffLen);
	unsigned short GetPacketSize(char * buffer, unsigned int len);
	unsigned long GetPacketType(char * buffer, unsigned int buffLen);

	friend class CSocket;
	friend class CDatagram;
};

	// External Stub Functions
	void mStubConnect(CSocket & socket);
	void mStubDiscnnect();
	void mStubAccept();
	void mStubSend();
	void mStubRecv(CPacket & packet, CSocket & socket);

#endif	/* _C_NETWORKMGR_S_H_ */