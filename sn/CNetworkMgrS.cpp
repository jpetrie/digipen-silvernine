/*! ==========================================================================
	@file	CNetworkMgrS.cpp
	@author	Patrick Laukaitis
	@brief	Implementation of the Networking Layer
	@par	November 13, 2003
	@par	Project: Silver Nine
	@par	Compiler: Visual C++ .Net 2003
	@par	Modifications:
			January 15, 2004	--	plaukait	--	Ported to new SN libraries

	========================================================================== */

/*																      includes
------------------------------------------------------------------------------ */
#include "CNetworkMgrS.h"
#include "CGameEngine.h"

/*																	   statics
------------------------------------------------------------------------------ */

/*																	   methods
------------------------------------------------------------------------------ */
/* *************************************************************************** */
/*!
	@brief	Constructor
	@par	Initializes Winsock if compiling under windows
*/
/* *************************************************************************** */
CNetworkMgrS::CNetworkMgrS() 
{
	AcceptCallB = mStubAccept;
	ConnectCallB = mStubConnect;
	DiscnnectCallB = mStubDiscnnect;
	SendCallB = mStubSend;
	RecvCallB = mStubRecv;

	mSends = 0;
	mRecvs = 0;
	mConnects = 0;
	mSocketsInUse = 0;
	mDiscnnects = 0;
	maxFD = 0;
	maxUDP_FD = 0;

	// set the wait time to 0 -- no blocking
	tval.tv_sec = 0;
	tval.tv_usec = 0;

	// zero out the socket lists
	FD_ZERO(&master_fd);
	FD_ZERO(&use_fd);
	FD_ZERO(&master_UDP_fd);

//						   WINSOCK INITIALIZATION
// ----------------------------------------------
#ifdef NSL_VC		
	// Load Winsock 2.2
	WORD Version = MAKEWORD(2, 2);
	WSADATA wsaData;

										// WSAStartup returns non-zero on error
	if(WSAStartup(Version, &wsaData))	// winsock could not be initialized
		nlTHROW("Winsock 2.2 could not be initialized");

	if( LOBYTE(wsaData.wVersion) != 2 ||	// if wrong winsock version (not 2.2)
		HIBYTE(wsaData.wVersion) != 2 )
	{
		WSACleanup();
		nlTHROW("The wrong version of Winsock was initialized.  It should have been 2.2");
	}
#endif					
//					   END WINSOCK INITIALIZATION
// ----------------------------------------------
}

/* *************************************************************************** */
/*!
	@brief	Network Manager Destructor -- Winsock Cleanup
*/
/* *************************************************************************** */
CNetworkMgrS::~CNetworkMgrS()
{
// Windows cleanup
#ifdef NSL_VC	
	WSACleanup();		
#endif
}

/* *************************************************************************** */
/*!
	@brief	Listens and receives data on each registered socket
*/
/* *************************************************************************** */
void CNetworkMgrS::ProcessNetwork()
{
	// copy the master list
	use_fd = master_fd;
	int newsocket;
	struct sockaddr_in clientAddress;
	int size = sizeof(clientAddress);
	CSocket tempSocket;
	bool CloseTempSocket = true;
	int error;

	// cycle through each socket until something is ready to be recv'd
	if(select(maxFD + 1, &use_fd, NULL, NULL, &tval) < 0)
	{	error = WSAGetLastError();
		if(INVALID_ARGUMENT != error)
            nlTHROW("Error checking sockets for pending data / connections using select"); 
	}


	// check each socket to see if any data is pending
	for(std::vector<CSocket>::iterator currentSocket = sockList.begin(); currentSocket != sockList.end(); ++currentSocket)
	{
		if(FD_ISSET( (*currentSocket).GetSocket(), &use_fd))
		{
			newsocket = (*currentSocket).GetSocket();
			// only sockets that are set to Listen() should be used with accept()
			if( (*currentSocket).Listening() )
			{	
				if( (newsocket = (int)accept((*currentSocket).GetSocket(), (struct sockaddr *)&clientAddress, &size)) < 0)
					nlTHROW("Error accepting a new connection");	// accept error
			
				// create a new socket object using the newly accepted connection 
				tempSocket.SetSocket(newsocket);
				tempSocket.SetForeignAddress(&clientAddress);

				// this will invalidate the iterator ONLY if the iterator points to the last
				// item in the stl::list.  Processing stops after insertion to prevent access errors
				AddSocketToList(tempSocket);
				AcceptCallB();
				CloseTempSocket = false;
				break;
			}
			
			// extract the first two bytes (they specify the size of the packet)
			GetPacketData(PACKET_SIZE_FIELD_LEN, newsocket, RecvBuffer, sizeof(RecvBuffer));
			// the first two bytes are the size
			unsigned short packetSize = GetPacketSize(RecvBuffer, PACKET_SIZE_FIELD_LEN);
			// get the rest of the packet data (don't overwrite the size data)
			GetPacketData(packetSize - PACKET_SIZE_FIELD_LEN, newsocket, RecvBuffer + PACKET_SIZE_FIELD_LEN, sizeof(RecvBuffer) - PACKET_SIZE_FIELD_LEN);
			// get the type of the packet
			unsigned long packetType = GetPacketType(RecvBuffer + PACKET_SIZE_FIELD_LEN, PACKET_TYPE_FIELD_LEN);
		
			CPacket * newPacket = CPacketFactory::ConstructPacket(packetType);
			newPacket->DeSerialize((nsl::byte_t *)RecvBuffer, packetSize);

			// give the client the new packet and the current socket
			RecvCallB(*newPacket, (*currentSocket));
		}
	}

	// Check the UDP list
	use_fd = master_UDP_fd;

	// cycle through each UDP socket until something is ready to be recv'd
	if(select(maxUDP_FD + 1, &use_fd, NULL, NULL, &tval) < 0)
	{
		int error = WSAGetLastError();
		if(INVALID_ARGUMENT != error)
            nlTHROW("Error checking sockets for pending data / connections using select"); 
	}

	for(std::vector<CDatagram >::iterator CurrentDatagram = datagramList.begin(); CurrentDatagram != datagramList.end(); ++CurrentDatagram)
	{
		if( FD_ISSET( (*CurrentDatagram).GetDatagram(), &use_fd) )
		{
			newsocket = (*CurrentDatagram).GetDatagram();

			// extract the first two bytes (they specify the size of the packet)
			GetDatagramData(PACKET_SIZE_FIELD_LEN, newsocket, RecvBuffer, sizeof(RecvBuffer));
			// the first two bytes are the size
			unsigned short packetSize = GetPacketSize(RecvBuffer, PACKET_SIZE_FIELD_LEN);

			// get the type of the packet
			unsigned long packetType = GetPacketType(RecvBuffer + PACKET_SIZE_FIELD_LEN, PACKET_TYPE_FIELD_LEN);
		
			CPacket * newPacket = CPacketFactory::ConstructPacket(packetType);
			newPacket->DeSerialize((nsl::byte_t *)RecvBuffer, packetSize);

			// give the client the new packet and the current socket
			RecvCallB(*newPacket, CSocket());	// No socket to send back on

		}
	}

	if(CloseTempSocket)
		tempSocket.Disconnect();
}

/* *************************************************************************** */
/*!
	@brief	Extract pending data of length 'size'(bytes) from socket.
	@par	The data is stuffed into buffer, up to the maximum length
			specified by buffLen.
	@par	A return value of false means everything went well.
			A return value of true indicates that more data is pending.
			Most likely, buffLen was smaller than size, indicating that 
			there was no way to pull off all of the pending data.
			In this case, data up unitl (in bytes) buffLen will be read.
			So, the remaining data to be obtained is simply the original 
			size parameter - buffLen.  Use that if multiple calls are required.
			(Or create a larger buffer)
*/
/* *************************************************************************** */
bool CNetworkMgrS::GetPacketData(unsigned int size, int socket, char * buffer, unsigned int buffLen)
{
	bool moreData = false;
	if(size > buffLen)
	{
		size = buffLen;
		moreData = true;
	}

	// get the remaining data
	int bytesRead;
	if( (bytesRead = recv(socket, buffer, size, 0)) < 0)	
		nlTHROW("Error receiving data from the network");

	// check that the amount of data gathered from the network is the correct amount
	if((unsigned int)bytesRead != size)
		nlTHROW("Error, too little data recv()'d from the rest of the pending packet");

	return moreData;	// more data pending b/c of a small buffer?
}

/* *************************************************************************** */
/*!
	@brief	Extract pending data of length 'size'(bytes) from datagram.
	@par	The data is stuffed into buffer, up to the maximum length
			specified by buffLen.
	@par	A return value of false means everything went well.
			A return value of true indicates that more data is pending.
			Most likely, buffLen was smaller than size, indicating that 
			there was no way to pull off all of the pending data.
			In this case, data up unitl (in bytes) buffLen will be read.
			So, the remaining data to be obtained is simply the original 
			size parameter - buffLen.  Use that if multiple calls are required.
			(Or create a larger buffer)
*/
/* *************************************************************************** */
bool CNetworkMgrS::GetDatagramData(unsigned int size, int datagram, char * buffer, unsigned int buffLen)
{
	bool moreData = false;
	if(size > buffLen)
	{
		size = buffLen;
		moreData = true;
	}

	// HACK
	size = buffLen;		// The datagram will produce a Winsock Error 10040
						// If you try to read in less data than is actually available
						// Setting it to a huge value hackishly prevents this error.
	// END HACK

	int bytesRead;
	if( (bytesRead = recvfrom(datagram, buffer, size, 0, NULL, 0)) < 0)
	{
		bytesRead = WSAGetLastError();
		nlTHROW("Error, could not recv data from the datagram");
	}

	return moreData;		// more data pending b/c of a small buffer
}

/* *************************************************************************** */
/*!
	@brief	Gets the packet size by extracting the first two bytes from 
			buffer.
	@par	The data is assumed to be in big-endian (network byte) order
*/
/* *************************************************************************** */
unsigned short CNetworkMgrS::GetPacketSize(char * buffer, unsigned int len)
{
	// the packet format specifies the size as the first two bytes of the packet
	nlASSERT(PACKET_SIZE_FIELD_LEN == len);
	// ensure that the amount we actuall extract is correct
	nlASSERT(PACKET_SIZE_FIELD_LEN == sizeof(short));

	// interpret the first two bytes of buffer as a short 
	// The two bytes will be flip-flopped, so NetworkToHostShort() is called 
	// for re-ordering
	return ( ntohs(*(reinterpret_cast<short *>(buffer))) );
}

/* *************************************************************************** */
/*!
	@brief	Determines the type of the packet
	@par	The data is assumed to be in big-endian (network byte) order
			The returned value will be in host order, however
*/
/* *************************************************************************** */
unsigned long CNetworkMgrS::GetPacketType(char * buffer, unsigned int buffLen)
{
	// the packet specification calls for 4 bytes of a type field
	nlASSERT(PACKET_TYPE_FIELD_LEN <= buffLen);
	// ensure that we are not grabbing more data than we should be
	nlASSERT(PACKET_TYPE_FIELD_LEN == sizeof(long));

	// treat the first 4 bytes of buffer as a long.
	// Dereferencing like this will produce a long in network order.
	// ntohl (NetworkToHostLong) will re-order it to host order.
	return ntohl(*(reinterpret_cast<long *> (buffer)));
}

/* *************************************************************************** */
/*!
	@brief	Adds a socket to the internal list
*/
/* *************************************************************************** */
void CNetworkMgrS::AddSocketToList(CSocket & socket)
{
	// add the socket to the list of sockets to be listened on
	int newsocket = socket.GetSocket();
	FD_SET(newsocket, &master_fd);
	sockList.push_back(socket);
	++mSocketsInUse;

	if(newsocket > maxFD)		// record the socket with the greater value
		maxFD = newsocket;	
}

/* *************************************************************************** */
/*!
	@brief	Adds a socket to the internal list
*/
/* *************************************************************************** */
void CNetworkMgrS::AddDatagramToList(CDatagram & datagram)
{
	// add the datagram to the list of sockets to be recv'd on 
	int newDatagram = datagram.GetDatagram();
	FD_SET(newDatagram, &master_UDP_fd);
	datagramList.push_back(datagram);
	++mSocketsInUse;

	if(newDatagram > maxUDP_FD)
		maxUDP_FD = newDatagram;
}

/* *************************************************************************** */
/*!
	@brief	Adds a socket to the internal list
*/
/* *************************************************************************** */
void CNetworkMgrS::RemoveDatagramFromList(CDatagram & datagram)
{
	std::vector<CDatagram>::iterator currentDatagram = datagramList.begin();

	// Check each datagram in the list
	while(currentDatagram != datagramList.end())
	{
		// Erase the correct datagram if there was a match
		if(datagram == (*currentDatagram))
		{
			datagramList.erase(currentDatagram);
			return;
		}
		++currentDatagram;
	}

	nlASSERT(0 && "Attempted to remove a datagram that was not registered");
}

/* *************************************************************************** */
/*!
	@brief	Adds a socket to the internal list
*/
/* *************************************************************************** */
void CNetworkMgrS::RemoveSocketFromList(CSocket & socket)
{
	std::vector<CSocket>::iterator currentSocket = sockList.begin();
	// check each socket in the list
	while(currentSocket != sockList.end())
	{
		// erase the correct one if it's equal
		if(socket == (*currentSocket))
		{
			sockList.erase(currentSocket);
			return;
		}
		++currentSocket;
	}

	nlASSERT(0 && "Attempted to remove a socket that was not registered");
}

/* *************************************************************************** */
/*!
	@brief	Clears the entire socket list
*/
/* *************************************************************************** */
void CNetworkMgrS::ClearSocketList()
{
	// Disconnect each socket
	for(unsigned int i = 0; i < sockList.size(); ++i)
		sockList[i].Disconnect();

	// Empty the container
	sockList.clear();

	// Re-set the BSD socket list
	FD_ZERO(&master_fd);								
	maxFD = 0;
}

/* *************************************************************************** */
/*!
	@brief	Clears the entire datagram list
*/
/* *************************************************************************** */
void CNetworkMgrS::ClearDatagramList()
{
	// Disconnect each datagram
	for(unsigned int i = 0; i < datagramList.size(); ++i)
		datagramList[i].Disconnect();

	// Empty the container
	datagramList.clear();

	// Re-set the BSD datagram list				
	FD_ZERO(&master_UDP_fd);				
	maxUDP_FD = 0;						
}

/* *************************************************************************** */
/*!
	@brief	Generate a packet for the client
*/
/* *************************************************************************** */
CPacket* CNetworkMgrS::MakePacket(CPacket::ID pck)
{
  return (CPacketFactory::ConstructPacket(pck));
}


/* *************************************************************************** */
/*!
	@brief	Send Stub
*/	
/* *************************************************************************** */
void mStubSend()
{	
}

/* *************************************************************************** */
/*!
	@brief	Recv Stub 
*/
/* *************************************************************************** */
void mStubRecv(CPacket & packet, CSocket & socket)
{
	packet;		// silence the compiler
	socket;
}

/* *************************************************************************** */
/*!
	@brief	Connnect Stub 
*/
/* *************************************************************************** */
void mStubConnect(CSocket & socket)
{
	socket;	// silence the compiler
}

/* *************************************************************************** */
/*!
	@brief	Accept Stub 
*/
/* *************************************************************************** */
void mStubAccept()
{
}

/* *************************************************************************** */
/*!
	@brief	Disconnect Stub
*/
/* *************************************************************************** */
void mStubDiscnnect()
{
}