/*
 * H323Parser.cpp
 * 
 * Copyright (c) 2001 Institute for Information Industry, Taiwan, Republic of China 
 * (http://www.iii.org.tw/iiia/ewelcome.htm)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 1, or (at your option)
 * any later version.
 *
 * 2001/07/27 Huang-Ming Huang
 * Fixed the problem which the parser mistakes the Q.931 message for H.245 message.
 */

#define H323_MESSAGES_CXX
#define MULTIMEDIA_SYSTEM_CONTROL_CXX

#if _MSC_VER >= 1400
#pragma warning(disable:4996)
#endif

#include "h323_messages.h"
#include "multimedia_system_control.h"
#include "call_transfer_operations.h"
#include "call_diversion_operations.h"
#include "call_hold_operations.h"
#include "call_park_pickup_operations.h"
#include "call_waiting_operations.h"
#include "message_waiting_indication_operations.h"
#include "name_operations.h"
#include "call_completion_operations.h"
#include "call_offer_operations.h"

#include "q931pdu.h"
#include "perattacher.h"
#include <netmon.h>


// Globals -------------------------------------------------------------------
HPROTOCOL hRAS = NULL;
HPROTOCOL hTPKT  = NULL;
HPROTOCOL hQ931  = NULL;
HPROTOCOL hH245  = NULL;
DWORD     Attached = 0;
// Functions -----------------------------------------------------------------
extern VOID   WINAPI H323_Deregister( HPROTOCOL hRAS);
extern DWORD  WINAPI H323_FormatProperties( HFRAME hFrame, 
                                                LPBYTE pMacFrame, 
                                                LPBYTE pH323Frame, 
                                                DWORD nPropertyInsts, 
                                                LPPROPERTYINST p);
VOID WINAPIV Custom_Format( LPPROPERTYINST pPropertyInst);


extern VOID   WINAPI RAS_Register( HPROTOCOL hRAS);
extern LPBYTE WINAPI RAS_RecognizeFrame( HFRAME hFrame, 
                                              LPBYTE pMacFrame, 
                                              LPBYTE pH323Frame, 
                                              DWORD MacType, 
                                              DWORD BytesLeft, 
                                              HPROTOCOL hPrevProtocol, 
                                              DWORD nPrevProtOffset,
                                              LPDWORD pProtocolStatus,
                                              LPHPROTOCOL phNextProtocol, 
                                              LPDWORD InstData);
extern LPBYTE WINAPI RAS_AttachProperties( HFRAME hFrame, 
                                                LPBYTE pMacFrame, 
                                                LPBYTE pH323Frame, 
                                                DWORD MacType, 
                                                DWORD BytesLeft, 
                                                HPROTOCOL hPrevProtocol, 
                                                DWORD nPrevProtOffset,
                                                DWORD InstData);

extern VOID   WINAPI TPKT_Register( HPROTOCOL hTPKT);

extern LPBYTE WINAPI TPKT_RecognizeFrame( HFRAME hFrame, 
                                              LPBYTE pMacFrame, 
                                              LPBYTE pH323Frame, 
                                              DWORD MacType, 
                                              DWORD BytesLeft, 
                                              HPROTOCOL hPrevProtocol, 
                                              DWORD nPrevProtOffset,
                                              LPDWORD pProtocolStatus,
                                              LPHPROTOCOL phNextProtocol, 
                                              LPDWORD InstData);
extern LPBYTE WINAPI TPKT_AttachProperties( HFRAME hFrame, 
                                                LPBYTE pMacFrame, 
                                                LPBYTE pH323Frame, 
                                                DWORD MacType, 
                                                DWORD BytesLeft, 
                                                HPROTOCOL hPrevProtocol, 
                                                DWORD nPrevProtOffset,
                                                DWORD InstData);


extern VOID   WINAPI H245_Register( HPROTOCOL hTPKT);

extern LPBYTE WINAPI H245_RecognizeFrame( HFRAME hFrame, 
                                              LPBYTE pMacFrame, 
                                              LPBYTE pH323Frame, 
                                              DWORD MacType, 
                                              DWORD BytesLeft, 
                                              HPROTOCOL hPrevProtocol, 
                                              DWORD nPrevProtOffset,
                                              LPDWORD pProtocolStatus,
                                              LPHPROTOCOL phNextProtocol, 
                                              LPDWORD InstData);
extern LPBYTE WINAPI H245_AttachProperties( HFRAME hFrame, 
                                                LPBYTE pMacFrame, 
                                                LPBYTE pH323Frame, 
                                                DWORD MacType, 
                                                DWORD BytesLeft, 
                                                HPROTOCOL hPrevProtocol, 
                                                DWORD nPrevProtOffset,
                                                DWORD InstData);

extern VOID   WINAPI Q931_Register( HPROTOCOL hTPKT);

extern LPBYTE WINAPI Q931_RecognizeFrame( HFRAME hFrame, 
                                              LPBYTE pMacFrame, 
                                              LPBYTE pH323Frame, 
                                              DWORD MacType, 
                                              DWORD BytesLeft, 
                                              HPROTOCOL hPrevProtocol, 
                                              DWORD nPrevProtOffset,
                                              LPDWORD pProtocolStatus,
                                              LPHPROTOCOL phNextProtocol, 
                                              LPDWORD InstData);
extern LPBYTE WINAPI Q931_AttachProperties( HFRAME hFrame, 
                                                LPBYTE pMacFrame, 
                                                LPBYTE pH323Frame, 
                                                DWORD MacType, 
                                                DWORD BytesLeft, 
                                                HPROTOCOL hPrevProtocol, 
                                                DWORD nPrevProtOffset,
                                                DWORD InstData);

// Define the entry points that we will pass back at dll entry time ----------
ENTRYPOINTS RASEntryPoints =
{
    // RAS Entry Point
    RAS_Register,
    H323_Deregister,
    RAS_RecognizeFrame,
    RAS_AttachProperties,
    H323_FormatProperties
};

ENTRYPOINTS TPKTEntryPoints =
{
    // TPKT Entry Point
    TPKT_Register,
    H323_Deregister,
    TPKT_RecognizeFrame,
    TPKT_AttachProperties,
    H323_FormatProperties
};

ENTRYPOINTS H245EntryPoints =
{
    // H245 Entry Point
    H245_Register,
    H323_Deregister,
    H245_RecognizeFrame,
    H245_AttachProperties,
    H323_FormatProperties
};

ENTRYPOINTS Q931EntryPoints =
{
    // H245 Entry Point
    Q931_Register,
    H323_Deregister,
    Q931_RecognizeFrame,
    Q931_AttachProperties,
    H323_FormatProperties
};

PROPERTYINFO  RasPropertyInfo = 
{ 0, 0,
   "",
   "",
   PROP_TYPE_SUMMARY,
   PROP_QUAL_NONE,
   NULL,
   160,
   &Custom_Format
};

PROPERTYINFO  TpktPropertyInfo = 
{ 0, 0,
   "",
   "",
   PROP_TYPE_SUMMARY,
   PROP_QUAL_NONE,
   NULL,
   80,
   &Custom_Format
};

PROPERTYINFO  H245PropertyInfo = 
{ 0, 0,
   "",
   "",
   PROP_TYPE_SUMMARY,
   PROP_QUAL_NONE,
   NULL,
   160,
   &Custom_Format
};

PROPERTYINFO  Q931PropertyInfo = 
{ 0, 0,
   "",
   "",
   PROP_TYPE_SUMMARY,
   PROP_QUAL_NONE,
   NULL,
   160,
   &Custom_Format
};

char* RAS_String[] = 
{
	"GRQ",
	"GCF",
	"GRJ",
	"RRQ",
	"RCF",
	"RRJ",
	"URQ",
	"UCF",
	"URJ",
	"ARQ",
	"ACF",
	"ARJ",
	"BRQ",
	"BCF",
	"BRJ",
	"DRQ",
	"DCF",
	"DRJ",
	"LRQ",
	"LCF",
	"LRJ",
	"IRQ",
	"IRR",
	"Non-Standard Message",
	"Unknown Message Response",
	"RIP",
	"RAI",
	"RAC",
	"IACK",
	"INAK"
};


BOOL RAS_AutoInstall(PPF_PARSERINFO pParserInfo)
{
    DWORD NumHandoffs;
    PPF_HANDOFFSET    pHandoffSet;
    PPF_HANDOFFENTRY  pHandoffEntry;

	wsprintf( pParserInfo->szProtocolName, "RAS" );
    wsprintf( pParserInfo->szComment,      "H.323 RAS Protocol" );
    wsprintf( pParserInfo->szHelpFile,     "");

    // the incoming handoff set ----------------------------------------------
    // allocate
    NumHandoffs = 2;
    pHandoffSet = (PPF_HANDOFFSET)HeapAlloc( GetProcessHeap(),
                                             HEAP_ZERO_MEMORY,
                                             sizeof( PF_HANDOFFSET ) +
                                             NumHandoffs * sizeof( PF_HANDOFFENTRY) );
    if( pHandoffSet == NULL )
    {
        // just return early
        return FALSE;
    }

    // fill in the incoming handoff set
    pParserInfo->pWhoHandsOffToMe = pHandoffSet;
    pHandoffSet->nEntries = NumHandoffs;

    // UDP PORT 1719
    pHandoffEntry = &(pHandoffSet->Entry[0]);
    wsprintf( pHandoffEntry->szIniFile,    "TCPIP.INI" );
    wsprintf( pHandoffEntry->szIniSection, "UDP_HandoffSet" );
    wsprintf( pHandoffEntry->szProtocol,   "RAS" );
    pHandoffEntry->dwHandOffValue =        1718;
    pHandoffEntry->ValueFormatBase =       HANDOFF_VALUE_FORMAT_BASE_DECIMAL;    

    // UDP PORT 1719
    pHandoffEntry = &(pHandoffSet->Entry[1]);
    wsprintf( pHandoffEntry->szIniFile,    "TCPIP.INI" );
    wsprintf( pHandoffEntry->szIniSection, "UDP_HandoffSet" );
    wsprintf( pHandoffEntry->szProtocol,   "RAS" );
    pHandoffEntry->dwHandOffValue =        1719;
    pHandoffEntry->ValueFormatBase =       HANDOFF_VALUE_FORMAT_BASE_DECIMAL;  

	return TRUE;
}

BOOL H245_AutoInstall(PPF_PARSERINFO pParserInfo)
{
    DWORD NumHandoffs;
    PPF_HANDOFFSET    pHandoffSet;
    PPF_HANDOFFENTRY  pHandoffEntry;

    DWORD NumFollows;
    PPF_FOLLOWSET     pFollowSet;
    PPF_FOLLOWENTRY   pFollowEntry;

    wsprintf( pParserInfo->szProtocolName, "H.245" );
    wsprintf( pParserInfo->szComment,      "H.245 Protocol" );
    wsprintf( pParserInfo->szHelpFile,     "");

	
    // the incoming follow set -----------------------------------------------
    // allocate
    NumFollows = 2;
    pFollowSet = (PPF_FOLLOWSET)HeapAlloc( GetProcessHeap(),
                                           HEAP_ZERO_MEMORY,
                                           sizeof( PF_FOLLOWSET ) +
                                           NumFollows * sizeof( PF_FOLLOWENTRY) );
    if( pFollowSet == NULL )
    {
        // just return early
        return FALSE;
    }

    // fill in the incoming follow set
    pParserInfo->pWhoCanPrecedeMe = pFollowSet;
    pFollowSet->nEntries = NumFollows;

    // TCP
    pFollowEntry = &(pFollowSet->Entry[0]);
    wsprintf( pFollowEntry->szProtocol, "TCP" );

	// TPKT 
    pFollowEntry = &(pFollowSet->Entry[1]);
    wsprintf( pFollowEntry->szProtocol, "TPKT" );

	// the outgoing HandOff set -----------------------------------------------
    // allocate
    NumHandoffs = 1;
    pHandoffSet = (PPF_HANDOFFSET) HeapAlloc( GetProcessHeap(),
                                           HEAP_ZERO_MEMORY,
                                           sizeof( PF_HANDOFFSET ) +
                                           NumHandoffs * sizeof( PF_HANDOFFENTRY) );
    if( pHandoffSet == NULL )
    {
        // just return early
        return FALSE;
    }

    // fill in outgoing HandOff set
    pParserInfo->pWhoDoIHandOffTo = pHandoffSet;
    pFollowSet->nEntries = NumHandoffs;

	// TPKT 
    pHandoffEntry = &(pHandoffSet->Entry[0]);
    wsprintf( pHandoffEntry->szProtocol, "TPKT" );
	return TRUE;
}

BOOL Q931_AutoInstall(PPF_PARSERINFO pParserInfo)
{
    DWORD NumHandoffs;
    PPF_HANDOFFSET    pHandoffSet;
    PPF_HANDOFFENTRY  pHandoffEntry;

    DWORD NumFollows;
    PPF_FOLLOWSET     pFollowSet;
    PPF_FOLLOWENTRY   pFollowEntry;
    
	wsprintf( pParserInfo->szProtocolName, "Q.931" );
    wsprintf( pParserInfo->szComment,      "Q.931 Protocol" );
    wsprintf( pParserInfo->szHelpFile,     "");

	
    // the incoming follow set -----------------------------------------------
    // allocate
    NumFollows = 2;
    pFollowSet = (PPF_FOLLOWSET)HeapAlloc( GetProcessHeap(),
                                           HEAP_ZERO_MEMORY,
                                           sizeof( PF_FOLLOWSET ) +
                                           NumFollows * sizeof( PF_FOLLOWENTRY) );
    if( pFollowSet == NULL )
    {
        // just return early
        return FALSE;
    }

    // fill in the incoming follow set
    pParserInfo->pWhoCanPrecedeMe = pFollowSet;
    pFollowSet->nEntries = NumFollows;

    // TCP
    pFollowEntry = &(pFollowSet->Entry[0]);
    wsprintf( pFollowEntry->szProtocol, "TCP" );

	// TPKT 
    pFollowEntry = &(pFollowSet->Entry[1]);
    wsprintf( pFollowEntry->szProtocol, "TPKT" );

	// the outgoing HandOff set -----------------------------------------------
    // allocate
    NumHandoffs = 1;
    pHandoffSet = (PPF_HANDOFFSET) HeapAlloc( GetProcessHeap(),
                                           HEAP_ZERO_MEMORY,
                                           sizeof( PF_HANDOFFSET ) +
                                           NumHandoffs * sizeof( PF_HANDOFFENTRY) );
    if( pHandoffSet == NULL )
    {
        // just return early
        return FALSE;
    }

    // fill in outgoing HandOff set
    pParserInfo->pWhoDoIHandOffTo = pHandoffSet;
    pFollowSet->nEntries = NumHandoffs;

	// TPKT 
    pHandoffEntry = &(pHandoffSet->Entry[0]);
    wsprintf( pHandoffEntry->szProtocol, "TPKT" );
	return TRUE;
}

BOOL TPKT_AutoInstall(PPF_PARSERINFO pParserInfo)
{
    DWORD NumFollows;
    PPF_FOLLOWSET     pFollowSet;
    PPF_FOLLOWENTRY   pFollowEntry;

    wsprintf( pParserInfo->szProtocolName, "TPKT" );
    wsprintf( pParserInfo->szComment,      "RFC 1001 TPKT Protocol" );
    wsprintf( pParserInfo->szHelpFile,     "");

	
    // the incoming follow set -----------------------------------------------
    // allocate
    NumFollows = 3;
    pFollowSet = (PPF_FOLLOWSET)HeapAlloc( GetProcessHeap(),
                                           HEAP_ZERO_MEMORY,
                                           sizeof( PF_FOLLOWSET ) +
                                           NumFollows * sizeof( PF_FOLLOWENTRY) );
    if( pFollowSet == NULL )
    {
        // just return early
        return FALSE;
    }

    // fill in the incoming follow set
    pParserInfo->pWhoCanPrecedeMe = pFollowSet;
    pFollowSet->nEntries = NumFollows;

    // TCP
    pFollowEntry = &(pFollowSet->Entry[0]);
    wsprintf( pFollowEntry->szProtocol, "TCP" );
    
    // Q.931
    pFollowEntry = &(pFollowSet->Entry[1]);
    wsprintf( pFollowEntry->szProtocol, "Q.931" );

    // H.245
    pFollowEntry = &(pFollowSet->Entry[2]);
    wsprintf( pFollowEntry->szProtocol, "H.245" );

	// the outgoing follow set -----------------------------------------------
    // allocate
    NumFollows = 2;
    pFollowSet = (PPF_FOLLOWSET)HeapAlloc( GetProcessHeap(),
                                           HEAP_ZERO_MEMORY,
                                           sizeof( PF_FOLLOWSET ) +
                                           NumFollows * sizeof( PF_FOLLOWENTRY) );
    if( pFollowSet == NULL )
    {
        // just return early
        return FALSE;
    }

    // fill in outgoing follow set
    pParserInfo->pWhoCanFollowMe = pFollowSet;
    pFollowSet->nEntries = NumFollows;

    // Q.931
    pFollowEntry = &(pFollowSet->Entry[0]);
    wsprintf( pFollowEntry->szProtocol, "Q.931" );

    // H.245
    pFollowEntry = &(pFollowSet->Entry[1]);
    wsprintf( pFollowEntry->szProtocol, "H.245" );

	return TRUE;

}

//============================================================================
// 
//  AutoInstall - return all of the information neede to install us
//
//  Modification history:
//                                                                            
//============================================================================
PPF_PARSERDLLINFO WINAPI ParserAutoInstallInfo() 
{
    PPF_PARSERDLLINFO pParserDllInfo; 
    DWORD NumProtocols;


    // Base structure ========================================================

    // Allocate memory for parser info:
    NumProtocols = 4;
    pParserDllInfo = (PPF_PARSERDLLINFO)HeapAlloc( GetProcessHeap(),
                                                   HEAP_ZERO_MEMORY,
                                                   sizeof( PF_PARSERDLLINFO ) +
                                                   NumProtocols * sizeof( PF_PARSERINFO) );
    if( pParserDllInfo == NULL)
    {
        return NULL;
    }       
    
    // fill in the parser DLL info
    pParserDllInfo->nParsers = NumProtocols;

    // fill in the individual parser infos...

	RAS_AutoInstall(&(pParserDllInfo->ParserInfo[0]));
	Q931_AutoInstall(&(pParserDllInfo->ParserInfo[1]));
	H245_AutoInstall(&(pParserDllInfo->ParserInfo[2]));
	TPKT_AutoInstall(&(pParserDllInfo->ParserInfo[3]));
 

    return pParserDllInfo;
}

ASN1::CoderEnv* env;
H4501_Supplementary_ServiceAPDU_Structure::Module* h4501Module;
H4501_General_Error_List::Module* errListModule;
Call_Transfer_Operations::Module* h4502Module;
Call_Diversion_Operations::Module* h4503Module;
Call_Hold_Operations::Module* h4504Module;
Call_Park_Pickup_Operations::Module* h4505Module;
Call_Waiting_Operations::Module* h4506Module;
Message_Waiting_Indication_Operations::Module* h4507Module;
Name_Operations::Module* h4508Module;
Call_Completion_Operations::Module* h4509Module;
Call_Offer_Operations::Module* h45010Module;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  Command, 
                       LPVOID lpReserved
					 )
{
    // what type of call is this
    switch( Command )
    {
    case DLL_PROCESS_ATTACH:
        // are we loading for the first time?
        if( Attached == 0 )
        {
            // the first time in we need to tell t kernel 
            // about ourselves
            hRAS = CreateProtocol( "RAS", 
                &RASEntryPoints, 
                ENTRYPOINTS_SIZE);
            
            hQ931 = CreateProtocol( "Q.931",
                &Q931EntryPoints,
                ENTRYPOINTS_SIZE);
            
            hH245 = CreateProtocol( "H.245",
                &H245EntryPoints,
                ENTRYPOINTS_SIZE);
            
            
            hTPKT = CreateProtocol( "TPKT",
                &TPKTEntryPoints,
                ENTRYPOINTS_SIZE);
            
            env = new ASN1::CoderEnv;
            h4501Module = new H4501_Supplementary_ServiceAPDU_Structure::Module;
            errListModule = new H4501_General_Error_List::Module;
            h4502Module = new Call_Transfer_Operations::Module(errListModule);
            h4503Module = new Call_Diversion_Operations::Module(errListModule);
            h4504Module = new Call_Hold_Operations::Module(errListModule);
            h4505Module = new Call_Park_Pickup_Operations::Module(errListModule);
            h4506Module = new Call_Waiting_Operations::Module;
            h4507Module = new Message_Waiting_Indication_Operations::Module(errListModule);
            h4508Module = new Name_Operations::Module;
            h4509Module = new Call_Completion_Operations::Module(h4504Module, errListModule);
            h45010Module = new Call_Offer_Operations::Module(h4506Module);
            
            Remote_Operations_Information_Objects::OPERATION& operations
                = h4501Module->get_OperationSet();

            operations.insert(h4502Module->get_H323CallTransferOperations().begin(),
                              h4502Module->get_H323CallTransferOperations().end());
            operations.insert(h4503Module->get_H323CallDiversionOperations().begin(),
                              h4503Module->get_H323CallDiversionOperations().end());
            operations.insert(h4504Module->get_CallHoldOperations().begin(),
                              h4504Module->get_CallHoldOperations().end());
            operations.insert(h4505Module->get_CallParkPickupOperations().begin(),
                              h4505Module->get_CallParkPickupOperations().end());
            operations.insert(h4506Module->get_CallWaitingOperations().begin(),
                              h4506Module->get_CallWaitingOperations().end());
            operations.insert(h4507Module->get_H323_MWI_Operations().begin(),
                              h4507Module->get_H323_MWI_Operations().end());
            operations.insert(h4508Module->get_NameOperations().begin(),
                              h4508Module->get_NameOperations().end());
            operations.insert(h4509Module->get_H323CallCompletionOperations().begin(),
                              h4509Module->get_H323CallCompletionOperations().end());
            operations.insert(h45010Module->get_H323CallOfferOperations().begin(),
                              h45010Module->get_H323CallOfferOperations().end());

            env->set_per_Basic_Aligned();
            env->insert(h4501Module);
            
        }
        Attached++;
        break;

    case DLL_PROCESS_DETACH:
        // are we detaching our last instance?
        Attached--;
        if( Attached == 0 )
        {
            // last guy out needs to clean up
            DestroyProtocol(hTPKT);
            DestroyProtocol(hH245);
            DestroyProtocol(hQ931);
            DestroyProtocol( hRAS);
            delete env;
            delete h45010Module;
            delete h4509Module;
            delete h4508Module;
            delete h4507Module;
            delete h4506Module;
            delete h4505Module;
            delete h4504Module;
            delete h4503Module;
            delete h4502Module;
            delete errListModule;
            delete h4501Module;
        }
        break;
    }

    // Netmon parsers ALWAYS return TRUE.
    return TRUE;
}



//============================================================================
//  Function: H323_Deregister
// 
//  Description: Destroy our property database and handoff set
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
VOID WINAPI H323_Deregister( HPROTOCOL hH323)
{
    // tell the kernel that it may now free our database
    DestroyPropertyDatabase( hH323);
}

//============================================================================
//  Function: H323_FormatProperties
// 
//  Description: Format the given properties on the given frame.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
DWORD BHAPI H323_FormatProperties( HFRAME          hFrame,
                                       LPBYTE          pMacFrame,
                                       LPBYTE          pBLRPLATEFrame,
                                       DWORD           nPropertyInsts,
                                       LPPROPERTYINST  p)
{
    // loop through the property instances
    while( nPropertyInsts-- > 0)
    {
        // and call the formatter for each
        ( (FORMAT)(p->lpPropertyInfo->InstanceData) )( p);
        p++;
    }

    return NMERR_SUCCESS;
}
//============================================================================
//  Function: Custom_Format
// 
//  Description: The custom formatter for the summary property
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
VOID WINAPIV Custom_Format( LPPROPERTYINST pPropertyInst)
{
    char*       pReturnedString = pPropertyInst->szPropertyText;

	strcpy(pReturnedString,(const char*)pPropertyInst->lpPropertyInstEx->Byte);
}

//============================================================================
//  Function: RAS_Register
// 
//  Description: Create our property database and handoff sets.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
void BHAPI RAS_Register( HPROTOCOL hRAS)
{
    // tell the kernel to make reserve some space for our property table
    CreatePropertyDatabase( hRAS, 1);
    // add our properties to the kernel's database
    AddProperty( hRAS, &RasPropertyInfo);
}


//============================================================================
//  Function: RAS_RecognizeFrame
// 
//  Description: Determine whether we exist in the frame at the spot 
//               indicated. We also indicate who (if anyone) follows us
//               and how much of the frame we claim.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
LPBYTE BHAPI RAS_RecognizeFrame( HFRAME      hFrame,         
                                      LPBYTE      pMacFrame,      
                                      LPBYTE      pFrame, 
                                      DWORD       MacType,        
                                      DWORD       BytesLeft,      
                                      HPROTOCOL   hPrevProtocol,  
                                      DWORD       nPrevProtOffset,
                                      LPDWORD     pProtocolStatus,
                                      LPHPROTOCOL phNextProtocol,
                                      LPDWORD     InstData)       
{
	*pProtocolStatus = PROTOCOL_STATUS_NOT_RECOGNIZED;

	try {
        H323_MESSAGES::RasMessage msg;
		ASN1::PERDecoder decoder((char*)pFrame, (char*)pFrame+BytesLeft);
        if (msg.accept(decoder))
			*pProtocolStatus = PROTOCOL_STATUS_CLAIMED;
	}
	catch (...)
	{
	}

    return NULL;
}

//============================================================================
//  Function: RAS_AttachProperties
// 
//  Description: Indicate where in the frame each of our properties live.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
LPBYTE BHAPI RAS_AttachProperties( HFRAME      hFrame,         
                                        LPBYTE      pMacFrame,     
                                        LPBYTE      pFrame,   
                                        DWORD       MacType,        
                                        DWORD       BytesLeft,      
                                        HPROTOCOL   hPrevProtocol,  
                                        DWORD       nPrevProtOffset,
                                        DWORD       InstData)       

{
    // Decode the first byte to determine the type of the message

	int tag;
	if ((pFrame[0] & 0x80) == 0)
		tag = pFrame[0] >> 2;
	else
		tag = pFrame[0] & 0x3F + 25;

	// Attach the summery
    std::ostringstream strm;
    strm << "RAS " << RAS_String[tag] << " (Length = " << BytesLeft << ")";

    std::string str = strm.str();
    AttachPropertyInstanceEx( hFrame,
		RasPropertyInfo.hProperty,
		BytesLeft,
		pFrame,
		(DWORD) str.size()+1,
		(void*) str.c_str(), 
		0, 0, 0);

    H323_MESSAGES::RasMessage msg;
    ASN1::PERDecoder decoder((char*)pFrame, (char*)pFrame+BytesLeft, env);
    PERAttacher attacher(decoder, hFrame, RasPropertyInfo.hProperty, "RasMessage ",1);
	msg.accept(attacher);

    return NULL;
}

//============================================================================
//  Function: TPKT_Register
// 
//  Description: Create our property database and handoff sets.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
void BHAPI TPKT_Register( HPROTOCOL hTPKT)
{
    // tell the kernel to make reserve some space for our property table
    CreatePropertyDatabase( hTPKT, 1);
    // add our properties to the kernel's database
    AddProperty( hTPKT, &TpktPropertyInfo);
}

//============================================================================
//  Function: TPKT_RecognizeFrame
// 
//  Description: Determine whether we exist in the frame at the spot 
//               indicated. We also indicate who (if anyone) follows us
//               and how much of the frame we claim.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
LPBYTE BHAPI TPKT_RecognizeFrame( HFRAME      hFrame,         
                                      LPBYTE      pMacFrame,      
                                      LPBYTE      pFrame, 
                                      DWORD       MacType,        
                                      DWORD       BytesLeft,      
                                      HPROTOCOL   hPrevProtocol,  
                                      DWORD       nPrevProtOffset,
                                      LPDWORD     pProtocolStatus,
                                      LPHPROTOCOL phNextProtocol,
                                      LPDWORD     InstData)       
{
	*pProtocolStatus = PROTOCOL_STATUS_NOT_RECOGNIZED;

	if (BytesLeft >=4 && pFrame[0] == 0x03 && pFrame[1] == 0x00 && 
		!(pFrame[2] == 0 && pFrame[3] == 0))
	{
		pFrame += 4;
		int len = ( pFrame[2] << 8 | pFrame[3]);
		if (BytesLeft < 8 &&  BytesLeft != len)
			*pProtocolStatus = PROTOCOL_STATUS_CLAIMED;
		else
			*pProtocolStatus = PROTOCOL_STATUS_RECOGNIZED;

	}

    return pFrame;
}

//============================================================================
//  Function: TPKT_AttachProperties
// 
//  Description: Indicate where in the frame each of our properties live.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
LPBYTE BHAPI TPKT_AttachProperties( HFRAME      hFrame,         
                                        LPBYTE      pMacFrame,     
                                        LPBYTE      pFrame,   
                                        DWORD       MacType,        
                                        DWORD       BytesLeft,      
                                        HPROTOCOL   hPrevProtocol,  
                                        DWORD       nPrevProtOffset,
                                        DWORD       InstData)       

{
    // apply the header overlay in order to decode the protocol
	int len = pFrame[2] << 8 | pFrame[3];
    char buf[80];
	
	sprintf(buf, "TPKT Header (Packet Length = %d)", len);

	AttachPropertyInstanceEx(hFrame, TpktPropertyInfo.hProperty, 4, pFrame, 
		strlen(buf)+1, buf, 0, 0, 0);

	AttachPropertyInstanceEx(hFrame, TpktPropertyInfo.hProperty, 1, pFrame,
		28, "TPKT Identifier Byte = 0x03", 0 , 1, 0);

	AttachPropertyInstanceEx(hFrame, TpktPropertyInfo.hProperty, 1, pFrame+1,
		21, "Reserved Byte = 0x00", 0 , 1, 0);

	sprintf(buf, "Packet Length = %d", len);

	AttachPropertyInstanceEx(hFrame, TpktPropertyInfo.hProperty, 2, pFrame+2, 
		strlen(buf)+1, buf, 0, 1, 0);


    return pFrame+4;
}

//============================================================================
//  Function: H245_Register
// 
//  Description: Create our property database and handoff sets.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
void BHAPI H245_Register( HPROTOCOL hH245)
{
    // tell the kernel to make reserve some space for our property table
    CreatePropertyDatabase( hH245, 1);
    // add our properties to the kernel's database
    AddProperty( hH245, &H245PropertyInfo);
}

//============================================================================
//  Function: H245_RecognizeFrame
// 
//  Description: Determine whether we exist in the frame at the spot 
//               indicated. We also indicate who (if anyone) follows us
//               and how much of the frame we claim.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
LPBYTE BHAPI H245_RecognizeFrame( HFRAME      hFrame,         
                                      LPBYTE      pMacFrame,      
                                      LPBYTE      pFrame, 
                                      DWORD       MacType,        
                                      DWORD       BytesLeft,      
                                      HPROTOCOL   hPrevProtocol,  
                                      DWORD       nPrevProtOffset,
                                      LPDWORD     pProtocolStatus,
                                      LPHPROTOCOL phNextProtocol,
                                      LPDWORD     InstData)       
{
	*pProtocolStatus = PROTOCOL_STATUS_NOT_RECOGNIZED;


    ASN1::PERDecoder decoder((char*)pFrame, (char*)pFrame+BytesLeft, env, true);
    MULTIMEDIA_SYSTEM_CONTROL::MultimediaSystemControlMessage msg;

	try
	{
        if (msg.accept(decoder))
		{
            unsigned char* nextPos = (unsigned char*)decoder.getNextPosition();

            if ( nextPos - pFrame < (int)BytesLeft)
            {
                if (*nextPos != '\x03' ||
                    *(nextPos+1) != '\x00')
                    return pFrame;
            }
            else if (pFrame[0] == '\x03' && pFrame[1] == '\x00' &&
                pFrame[4] == '\x08' && pFrame[5] == '\x02')
            {
                unsigned len = pFrame[2] << 8 | pFrame[3];
                if (len <= BytesLeft)
                {
                    unsigned char* q931Frame = pFrame+4;
                    unsigned char* nextFrame;
                    if ((nextFrame = Q931_RecognizeFrame(hFrame,         
                        pMacFrame,      
                        q931Frame, 
                        MacType,        
                        BytesLeft-4,      
                        hPrevProtocol,  
                        nPrevProtOffset,
                        pProtocolStatus,
                        phNextProtocol,
                        InstData)) != q931Frame)
                    {
                    	*pProtocolStatus = PROTOCOL_STATUS_NOT_RECOGNIZED;
                        if (nextFrame <= (pFrame+ BytesLeft-4))
                        {
                            if (nextFrame[0] == '\x03' && nextFrame[1] == '\x00')
                                return pFrame;
                        }
                        else if (nextFrame == pFrame+ BytesLeft)
                            return pFrame;
                    }
                }
            }

			pFrame = nextPos;
    		*pProtocolStatus = PROTOCOL_STATUS_NEXT_PROTOCOL;
			*phNextProtocol = hTPKT;
		}
	}
	catch (...)
	{
	}

    return pFrame;
}

//============================================================================
//  Function: H245_AttachProperties
// 
//  Description: Indicate where in the frame each of our properties live.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
LPBYTE BHAPI H245_AttachProperties( HFRAME      hFrame,         
                                        LPBYTE      pMacFrame,     
                                        LPBYTE      pFrame,   
                                        DWORD       MacType,        
                                        DWORD       BytesLeft,      
                                        HPROTOCOL   hPrevProtocol,  
                                        DWORD       nPrevProtOffset,
                                        DWORD       InstData)       

{
   // Decode the first byte to determine the type of the message

    ASN1::PERDecoder decoder((char*)pFrame, (char*)pFrame+BytesLeft, env);
    ASN1::PERDecoder::memento_type memento = decoder.get_memento();
    MULTIMEDIA_SYSTEM_CONTROL::MultimediaSystemControlMessage msg;
    msg.accept(decoder);

    if (msg.currentSelection() >= 0)
    {
        ASN1::CHOICE& choice = *static_cast<ASN1::CHOICE*>(msg.getSelection());
        
        // Attach the summery
        std::ostringstream strm;
        strm << "H.245 " << choice.getSelectionName() << " (Length = " 
            << decoder.getPosition()-(char*)pFrame << ")";
        std::string str = strm.str();
        
        AttachPropertyInstanceEx( hFrame,
            H245PropertyInfo.hProperty,
            decoder.getPosition()-(char*)pFrame,
            pFrame,
            (DWORD) str.size()+1,
            (void*) str.c_str(), 
            0, 0, 0) ;
        
        decoder.rollback(memento);
        
        // Attach the property of the whole message		
        strm.str("");
        strm << "MultimediaSystemControlMessage ::= ";
        
        PERAttacher attacher(decoder, hFrame,
            H245PropertyInfo.hProperty,
            strm.str(),
            1);
        
        msg.accept(attacher);
    }
    else
    {
        // Attach the summery
        std::ostringstream strm;
        strm << "H.245 unknown extension (Length = " 
            << decoder.getPosition()-(char*)pFrame << ")";
        std::string str = strm.str();
        
        AttachPropertyInstanceEx( hFrame,
            H245PropertyInfo.hProperty,
            decoder.getPosition()-(char*)pFrame,
            pFrame,
            (DWORD) str.size()+1,
            (void*) str.c_str(), 
            0, 0, 0) ;
    }

		
    return (unsigned char*)decoder.getPosition();
}

//============================================================================
//  Function: Q931_Register
// 
//  Description: Create our property database and handoff sets.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
void BHAPI Q931_Register( HPROTOCOL hQ931)
{
    // tell the kernel to make reserve some space for our property table
    CreatePropertyDatabase( hQ931, 1);
    // add our properties to the kernel's database
    AddProperty( hQ931, &Q931PropertyInfo);
}

//============================================================================
//  Function: Q931_RecognizeFrame
// 
//  Description: Determine whether we exist in the frame at the spot 
//               indicated. We also indicate who (if anyone) follows us
//               and how much of the frame we claim.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
LPBYTE BHAPI Q931_RecognizeFrame( HFRAME      hFrame,         
                                      LPBYTE      pMacFrame,      
                                      LPBYTE      pFrame, 
                                      DWORD       MacType,        
                                      DWORD       BytesLeft,      
                                      HPROTOCOL   hPrevProtocol,  
                                      DWORD       nPrevProtOffset,
                                      LPDWORD     pProtocolStatus,
                                      LPHPROTOCOL phNextProtocol,
                                      LPDWORD     InstData)       
{
	*pProtocolStatus = PROTOCOL_STATUS_NOT_RECOGNIZED;

	Q931Decoder decoder(pFrame, BytesLeft, env);
		
	Q931PDU msg;

	try
	{
		if (msg.accept(decoder))
		{
            int sz = decoder.getPosition();

            if ( sz < (int)BytesLeft)
            {
                if (*(pFrame+sz) != '\x03' ||
                    *(pFrame+sz+1) != '\x00')
                    return pFrame;
            }

			*pProtocolStatus = PROTOCOL_STATUS_NEXT_PROTOCOL;
			pFrame += sz;
			*phNextProtocol = hTPKT;
		}
	}
	catch (...)
	{
	}

    return pFrame;
}

//============================================================================
//  Function: Q931_AttachProperties
// 
//  Description: Indicate where in the frame each of our properties live.
//
//  Modification History
//
//  Huang-Ming Huang      08/11/2000    Created
//============================================================================
LPBYTE BHAPI Q931_AttachProperties( HFRAME      hFrame,         
                                        LPBYTE      pMacFrame,     
                                        LPBYTE      pFrame,   
                                        DWORD       MacType,        
                                        DWORD       BytesLeft,      
                                        HPROTOCOL   hPrevProtocol,  
                                        DWORD       nPrevProtOffset,
                                        DWORD       InstData)       

{
   // Decode the first byte to determine the type of the message
	Q931Decoder decoder(pFrame, BytesLeft,env);

	Q931PDU pdu;

	pdu.accept(decoder);
	pdu.attachProperties(hFrame, Q931PropertyInfo.hProperty);


    return pFrame+BytesLeft;
}

