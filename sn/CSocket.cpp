/*! ==========================================================================
	@file	CSocket.cpp
	@author	Patrick Laukaitis
	@brief	Implementation of the Socket class
	@par	November 13, 2003
	@par	Project: Silver Nine
	@par	Compiler: Visual C++ .Net 2003
	@par	Modifications:
			January 15, 2004	--	plaukait	--	Ported to new SN libraries

	========================================================================== */

/*																      includes
------------------------------------------------------------------------------ */
#include "CSocket.h"
#include "CNetworkMgrS.h"

/*																	   methods
------------------------------------------------------------------------------ */
/* *************************************************************************** */
/*!
	@brief	CSocket constructor 
*/
/* *************************************************************************** */
CSocket::CSocket() : MAX_BACKLOG(MAX_LISTEN_BACKLOG)
{
	if(-1 == (mSocket = static_cast<int>(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))))	
		nlTHROW("Error creating a socket");
	listening = false;
}

/* *************************************************************************** */
/*!
	@brief	CSocket destructor
*/
/* *************************************************************************** */
CSocket::~CSocket()
{
}

/* *************************************************************************** */
/*!
	@brief	Connect Method
*/
/* *************************************************************************** */
void CSocket::Connect(std::string & address, int port, struct sockaddr_in * existingAddress)
{
	if(!existingAddress)
	{
		memset(&mForeignAddress, 0x00, sizeof(mForeignAddress));
		mForeignAddress.sin_family = AF_INET;
		mForeignAddress.sin_port = htons((u_short)port);
		mForeignAddress.sin_addr.s_addr = ResolveDNS(address);
	}
	else
		mForeignAddress = *existingAddress;

	// attempt to connect
	if(connect(mSocket, (struct sockaddr *)&mForeignAddress, sizeof(mForeignAddress)) < 0)
		nlTHROW("Error connecting to a remote host");

	NetworkManager->AddSocketToList(*this);
	NetworkManager->ConnectCallB(*this);
}

/* *************************************************************************** */
/*!
	@brief	Send Method
*/
/* *************************************************************************** */
void CSocket::Send(CPacket & packet)
{
	nsl::byte_t * data = packet.Serialize();
	if( send(mSocket, (char *)data, packet.Size(), 0) < 0)
		nlTHROW("Error sending a data packet");
	
	NetworkManager->SendCallB();
}

/* *************************************************************************** */
/*!
	@brief	Listen Method
*/
/* *************************************************************************** */
void CSocket::Listen(int local_port)
{
	// setup the local address information	
	memset(&mLocalAddress, 0x00, sizeof(mLocalAddress));
	mLocalAddress.sin_family = AF_INET;
	mLocalAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	mLocalAddress.sin_port = htons((u_short)local_port);

	// bind the member socket to the local port
	if( bind(mSocket, (struct sockaddr *)&mLocalAddress, sizeof(mLocalAddress)) < 0)
		nlTHROW("Error binding a socket to an address");

	// listen on the socket --> shouldn't block
	if( listen(mSocket, MAX_BACKLOG) < 0 )
		nlTHROW("Error listening on a socket");

	listening = true;
	NetworkManager->AddSocketToList(*this);
}

/* *************************************************************************** */
/*!
	@brief	Disconnect Method
*/
/* *************************************************************************** */
void CSocket::Disconnect()
{
#ifdef NSL_VC
	if(mSocket)
		if(closesocket(mSocket))
			nlTHROW("Error closing a socket");
#else	// *NIX
	if(mSocket)
        if(close(mSocket) < 0)
			nlTHROW("Error closing a socket");
#endif

	if(listening)
	{
		NetworkManager->RemoveSocketFromList(*this);
		listening = false;
	}

	mSocket = 0;
	NetworkManager->DiscnnectCallB();
}

/* *************************************************************************** */
/*!
	@brief	Resolves names to addresses via DNS
*/
/* *************************************************************************** */
unsigned long CSocket::ResolveDNS(std::string & hostName)
{
	struct hostent * host;

	// access the DNS servers to get the host information
	if( NULL == (host = gethostbyname(hostName.c_str())) )
		nlTHROW("Error resolving a DNS name");
	return (*(unsigned long *)host->h_addr_list[0]);
}

/* *************************************************************************** */
/*!
	@brief	Assigns a new socket value
*/
/* *************************************************************************** */
void CSocket::SetSocket(int socket)
{
	// close the previously allocated socket
	if(mSocket)
	{
#ifdef NSL_VC
		closesocket(mSocket);
#else
		close(mSocket);
#endif
	}
	mSocket = socket;
}

/* *************************************************************************** */
/*!
	@brief	Test if two sockets are equal to each other
	@par	BSD Sockets from the OS are unique, so that is all that is checked
*/
/* *************************************************************************** */
bool CSocket::operator== (CSocket & socket)
{
	if(mSocket == socket.GetSocket())
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
CSocket & CSocket::operator= (const CSocket & socket)
{
	if(this != &socket)
	{
		mSocket = socket.mSocket;
		listening = socket.listening;
		mForeignAddress = socket.mForeignAddress;
		mLocalAddress = socket.mLocalAddress;
	}

	return *this;
}