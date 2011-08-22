
/*
 * Q931pdu.cpp
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
 * Fixed Progress indicator and Call state information element identifier coding.
 *
 * 2001/07/16 Huang-Ming Huang
 * Fixed the bug when parsing CallingPartyNumber and add ConnectedPartyNumberInformationElement
 * Thanks to Danail Kirov for providing this patch.
 *
 */

#include "h323_messages.h"
#include "q931pdu.h"
#include "perattacher.h"

class InformationElement
{
public:
	static InformationElement* Build(Q931Decoder& strm);

	InformationElement(const unsigned char* pFrame, int nSize = 1) : data(pFrame), len(nSize){};
	int getLength() const { return len; }
	virtual void attachProperties(HFRAME hFrame, HPROPERTY hProperty) const ; 
	virtual const char* getName() const { return ""; }
protected:
	const unsigned char* data;
	int len;
};

class VariableLengthInformationElement : public InformationElement
{
public:
	VariableLengthInformationElement(const unsigned char* pFrame) : InformationElement(pFrame, pFrame[1] +2 ){}
	virtual void attachProperties(HFRAME hFrame, HPROPERTY hProperty) const; 
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const;
};

class UserUserInformationElement : public InformationElement
{
public:
	UserUserInformationElement(const unsigned char* pFrame,
                                ASN1::CoderEnv* coderEnv)
     : InformationElement(pFrame, (pFrame[1] << 8) | pFrame[2] + 3 )
     , env(coderEnv){}
	virtual void attachProperties(HFRAME hFrame, HPROPERTY hProperty) const; 
	virtual const char* getName() const { return "User-User"; }
	bool decodeIE() const;
private:
    ASN1::CoderEnv* env;
};

class IA5StringInformationElement : public VariableLengthInformationElement
{
public:
	IA5StringInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
};

class DisplayInformationElement : public IA5StringInformationElement
{
public:
	DisplayInformationElement(const unsigned char* pFrame) : IA5StringInformationElement(pFrame){}
	virtual const char* getName() const { return "Display";}
};

class KeypadFacilityInformationElement : public IA5StringInformationElement
{
public:
	KeypadFacilityInformationElement(const unsigned char* pFrame) : IA5StringInformationElement(pFrame){}
	virtual const char* getName() const { return "Keypad Facility";}
};


class CauseInformationElement : public VariableLengthInformationElement
{
public:
	CauseInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const { return "Cause";}
};

class CalledPartyNumberInformationElement : public VariableLengthInformationElement
{
public:
	CalledPartyNumberInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const { return "Called Party Number";}
};

class CallingPartyNumberInformationElement : public VariableLengthInformationElement
{
public:
	CallingPartyNumberInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const { return "Calling Party Number";}
};

class ConnectedPartyNumberInformationElement : public VariableLengthInformationElement
{
public:
	ConnectedPartyNumberInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const { return "Connected Party Number";}
};

class ProgressInformationElement : public VariableLengthInformationElement
{
public:
	ProgressInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const { return "Progress";}
};

class BearerCapabilityInformationElement : public VariableLengthInformationElement
{
public:
	BearerCapabilityInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const { return "Bearer Capability";}
};

class CallStateInformationElement : public VariableLengthInformationElement
{
public:
	CallStateInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const { return "Call State";}
};

class SignalInformationElement : public VariableLengthInformationElement
{
public:
	SignalInformationElement(const unsigned char* pFrame) : VariableLengthInformationElement(pFrame){}
	virtual void attachContent(HFRAME hFrame, HPROPERTY hProperty) const ;
	virtual const char* getName() const { return "Signal";}
};






struct TableEntry
{
	int code;
	const char* str;
};


const char* FindStringFromTable(int code, const TableEntry* table, int tableSize)
{ // linear search 
	for (int i = 0; i < tableSize; ++i)
		if (table[i].code == code)
			return table[i].str;

	return "";
}

#define FindString(code) FindStringFromTable(code, code##Table, sizeof(code##Table))
 
void FormatBits(char* buf, int highBit, int lowBit, int value)
{
	for (int i = 7; i >= 0; --i)
	{
		if (i > highBit || i < lowBit)
			buf[7-i] = '.';
		else if ((value >> i) & 0x01 )
			buf[7-i] = '1';
		else 
			buf[7-i] = '0';
	}
}

 
InformationElement* InformationElement::Build(Q931Decoder& decoder)
{
	InformationElement* result = NULL;

	if (decoder.offset < decoder.size)
	{
		int discriminator = decoder.data[decoder.offset];
		if ((discriminator & 0x80) == 1)
			result = new InformationElement(&decoder.data[decoder.offset]);
		else 
		{
			switch (discriminator)
			{
		    case 0x04:
			    result = new BearerCapabilityInformationElement(&decoder.data[decoder.offset]);
				break;
			case 0x08:
				result = new CauseInformationElement(&decoder.data[decoder.offset]);
				break;
		    case 0x1E:
			    result = new ProgressInformationElement(&decoder.data[decoder.offset]);
				break;
			case 0x14:
				result = new CallStateInformationElement(&decoder.data[decoder.offset]);
				break;
			case 0x28:
				result = new DisplayInformationElement(&decoder.data[decoder.offset]);
				break;
		    case 0x2C:
				result = new KeypadFacilityInformationElement(&decoder.data[decoder.offset]);
				break;
		    case 0x34:
			    result = new SignalInformationElement(&decoder.data[decoder.offset]);
				break;
		    case 0x4C:
				result = new ConnectedPartyNumberInformationElement(&decoder.data[decoder.offset]);
				break;
		    case 0x6c:
				result = new CallingPartyNumberInformationElement(&decoder.data[decoder.offset]);
				break;
		    case 0x70:
				result = new CalledPartyNumberInformationElement(&decoder.data[decoder.offset]);
				break;
			case 0x7E:
				result = new UserUserInformationElement(&decoder.data[decoder.offset], decoder.env);
				break;
			default:
				result = new VariableLengthInformationElement(&decoder.data[decoder.offset]);
			}
		}

		decoder.offset += result->getLength();
	}

	return result;
}

void InformationElement::attachProperties(HFRAME hFrame, HPROPERTY hProperty) const
{
	char buf[80];
	wsprintf(buf, "%s Information Element", getName());
	AttachPropertyInstanceEx(hFrame, hProperty, len, (void*)data,
		strlen(buf)+1, buf, 0, 1, 0);

	wsprintf(buf, "Information Element Identifier = 0x%02x (%s)", data[0], getName());

	AttachPropertyInstanceEx(hFrame, hProperty, 1, (void*) data,
		strlen(buf) + 1, buf , 0, 2, 0);
}

const char* VariableLengthInformationElement::getName() const
{
	switch (data[0])
	{
    case 0x1c:
		return "Facility";
	}
	return "";
}




void VariableLengthInformationElement::attachProperties(HFRAME hFrame, HPROPERTY hProperty) const
{
	InformationElement::attachProperties(hFrame, hProperty);

	char buf[80];
	wsprintf(buf, "Information Element Content Length = %d", data[1]);

	AttachPropertyInstanceEx(hFrame, hProperty, 1,(void*) (data+1),
		strlen(buf) + 1, buf , 0, 2, 0);

	if (data[1] >0)
		attachContent(hFrame, hProperty);
}

void VariableLengthInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	AttachPropertyInstanceEx(hFrame, hProperty, (DWORD) data[1] , (void*) (data+2),
		28, "Information Element Content" , 0, 2, 0 );
}




void UserUserInformationElement::attachProperties(HFRAME hFrame, HPROPERTY hProperty) const
{
	InformationElement::attachProperties(hFrame, hProperty);

	char buf[80];
	wsprintf(buf, "Information Element Content Length = %d", len-3 );

	AttachPropertyInstanceEx(hFrame, hProperty, 2, (void*) (data+1),
		strlen(buf) + 1, buf , 0, 2, 0);

    H323_MESSAGES::H323_UserInformation userInformation;
    ASN1::PERDecoder decoder((char*)data+4, (char*)data+len, env);
    PERAttacher attacher(decoder, hFrame, hProperty, "H323_UserInformation ",2);
	userInformation.accept(attacher);
}

bool UserUserInformationElement::decodeIE() const
{

    H323_MESSAGES::H323_UserInformation userInformation;
	ASN1::PERDecoder decoder((char*)data+4, (char*)data+len);
	return userInformation.accept(decoder);
}

void IA5StringInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	char buf[80];
	int len;
	wsprintf(buf, "Information Element Content = \"");
	len = strlen(buf);
	memcpy(buf+len, data+2, data[1]);
	len += data[1];
	buf[len++] = '"';
	buf[len++] = 0;

	AttachPropertyInstanceEx(hFrame, hProperty, (DWORD) data[1] , (void*) (data+2),
		len, buf , 0, 2, 0 );

}

enum EXT_STATUS
{
	BOTH,
	FORCE_0,
	FORCE_1
};

char* extensionStringTable[][2] = 
{
	{" - Octet continues through the next octet", " - Last octet"},
	{"", " - Coding Error : This bit has to be 0" },
	{" - Coding Error : This bit has to be 1", "" }
};

void AttachExtensionIndicator(HFRAME hFrame, HPROPERTY hProperty, const unsigned char* Byte, enum EXT_STATUS status )
{
	char buf[80];

	// extension indicator
	bool ext = (Byte[0] & 0x80) > 1;
	wsprintf(buf, "%d....... = Extention Indicator %s", ext , extensionStringTable[status][ext]);
	AttachPropertyInstanceEx(hFrame, hProperty, 1 , (void*)Byte,
		strlen(buf)+1 , buf , 0, 2, 0 );

}


void AttachCodingStandard(HFRAME hFrame, HPROPERTY hProperty, const unsigned char* Byte , int startBit = 6)
{
	static const char* codeStandardString[] = 
	{
		"CCITT standardized coding",
		"ISO/IEC standard",
		"National standard",
		"Standard specific to identified location"
	};
	char buf[100];
	int codingStandard = (Byte[0] & 0x60) ;
	FormatBits(buf, startBit, startBit-1,codingStandard); 
	wsprintf(buf+8, " = Coding Standard - %s", codeStandardString[codingStandard >> (startBit-1)]);
	AttachPropertyInstanceEx(hFrame, hProperty, 1 , (void*) Byte,
		strlen(buf)+1 , buf , 0, 2, 0 );

}


void AttachLocation(HFRAME hFrame, HPROPERTY hProperty, const unsigned char* Byte)
{
	const char* locationString[] =
	{
		"User ",
		"Private network serving the local user",
		"Public network serving the local user",
		"Transit network",
		"Public network serving the remote user",
		"Private network serving the remote user",
		"International network",
		"Reserved",
		"Reserved",
		"Network beyond interworking point"
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
	};
	int location = (Byte[0] & 0x0f);
	char buf[100];

	FormatBits(buf, 3, 0, location);
	wsprintf(buf+8 , " = Location - %s", locationString[location]);
	AttachPropertyInstanceEx(hFrame, hProperty, 1 , (void*) Byte,
		strlen(buf)+1 , buf , 0, 2, 0 );

}

TableEntry recommendationTable[] = 
{
	{0, "Q.931"},
	{3, "X.21" },
	{4,"X.25"},
	{5,"Public land mobile networks, Q.1031/Q.1051"},
};

TableEntry causeTable[] = 
{
	{0x02,"No Route To Network"},
	{0x03,"No Route To Destination"},
	{0x06,"Channel Unacceptable"},
	{0x10,"Normal Call Clearing"},
	{0x11,"User Busy"},
	{0x12,"No Response"},
	{0x13,"No Answer"},
	{0x14,"Subscriber Absent"},
	{0x15,"Call Rejected"},
	{0x16,"Number Changed"},
	{0x17,"Redirection"},
	{0x1b,"Destination Out Of Order"},
	{0x1c,"Invalid Number Format"},
	{0x1e,"StatusEnquiryResponse"},
	{0x2a,"Congestion"},
	{0x51,"InvalidCallReference"}
};


void CauseInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	char buf[80];

	// extension indicator
	AttachExtensionIndicator(hFrame, hProperty, data+2, BOTH);
	AttachCodingStandard(hFrame, hProperty, data+2);
	AttachLocation(hFrame, hProperty, data+2);

	int pos = 3;

	if ((data[2]& 0x80) == 0)
	{
		AttachExtensionIndicator(hFrame, hProperty, data+3, FORCE_1);

		int recommendation = data[3] & 0x7F;
		FormatBits(buf, 6, 0, recommendation);
		wsprintf(buf+8, " = Recommendation - %s", FindString(recommendation) );

		AttachPropertyInstanceEx(hFrame, hProperty, 1 , (void*) (data+3),
			strlen(buf)+1 , buf , 0, 2, 0 );

		pos ++;
	}

	
	AttachExtensionIndicator(hFrame, hProperty, data+3, FORCE_0);

	int cause = data[pos] & 0x7F;
	FormatBits(buf, 6, 0, cause);
	wsprintf(buf+8, " = Cause Value (0x%02x) - %s", cause, FindString(cause) );

	AttachPropertyInstanceEx(hFrame, hProperty, 1 , (void*) (data+pos),
			strlen(buf)+1 , buf , 0, 2, 0 );

}

void AttachPartyNumber_TypeOfNumber(
	HFRAME					hFrame, 
	HPROPERTY				hProperty, 
	const unsigned char*	Byte
	)
{
	static const char* str[] = 
	{
		"Unknown",
		"International number",
		"National number",
		"Network specific number",
		"Subscriber number",
		"Reserved",
		"Abbreviated number",
		"Reserved for extension"
	};

	int i = Byte[0]&0x70;
	i >>= 4;

	char buf[80];

	int typeOfNumber = Byte[0]&0x70;
	FormatBits(buf, 6,4, typeOfNumber);
	wsprintf(buf+8," = Type of number - %s", str[typeOfNumber >> 4]);

	AttachPropertyInstanceEx(hFrame, hProperty, 1 , (void*)Byte,
			strlen(buf)+1 , buf , 0, 2, 0 );

}

TableEntry numberingPlanTable[] = 
{
	{0x00,"Unknown"},
	{0x01,"ISDN/telephony numbering plan (Recommendation E.164)"},
	{0x03,"Data numbering plan (Recommendation X.121)"},
	{0x04,"Telex numbering plan (Recommendation F.69)"},
	{0x08,"National standard numbering plan"},
	{0x09,"Private numbering plan"}
};

void 
AttachPartyNumber_NumberingPlanIndication(
	HFRAME					hFrame, 
	HPROPERTY				hProperty, 
	const unsigned char*	Byte
	)
{
	char buf[120];
	int numberingPlan = Byte[0]& 0x0F;
	FormatBits(buf, 3 , 0, numberingPlan);
	wsprintf(buf+8, " = Numbering plan indication - %s", 
		FindString(numberingPlan));

	AttachPropertyInstanceEx(hFrame, hProperty, 1 , (void*)Byte,
			strlen(buf)+1 , buf , 0, 2, 0 );

}

void
AttachPartyNumber_PresentationIndicator(
	HFRAME					hFrame, 
	HPROPERTY				hProperty, 
	const unsigned char*	Byte
	)
{
	char buf[100];
	const char* presentationStr[] = 
	{
		"Presentation allowed",
		"Presentation restricted",
		"Number not available due to interworking",
		"Reserved"
	};

	wsprintf(buf, ".%d%d..... = Presentation Indicator - %s", (Byte[0] & 0x40) > 1 
		, (Byte[0] & 0x20) > 1, presentationStr[(Byte[0] & 0x60) >> 5]);

	AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*)Byte,
		strlen(buf)+1 , buf , 0, 2, 0 );
}

void
AttachPartyNumber_ScreeningIndicator(
	HFRAME					hFrame, 
	HPROPERTY				hProperty, 
	const unsigned char*	Byte
	)
{
	char buf[100];
	const char* ScreeningStr[] = 
	{
		"User-provided, not screened",
		"User-provided, verified and passed",
		"User-provided, verified and failed",
		"Network provided"
	};

	wsprintf(buf, "......%d%d = Screening Indicator - %s", (Byte[0] & 0x02) > 1 
		, (Byte[0] & 0x01) , ScreeningStr[Byte[0] & 0x03 ]);

	AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*)Byte,
		strlen(buf)+1 , buf , 0, 2, 0 );
}

void AttachNumberDigits(HFRAME hFrame, HPROPERTY hProperty, const unsigned char* Byte, int length)
{
	char buf[100]="Number Digits = \"";
	int size;
	size = strlen(buf);
	memcpy(buf+size, Byte, length );
	size += length ;
	buf[size++] = '"';
	buf[size] = 0;

	AttachPropertyInstanceEx(hFrame, hProperty, length , (void*)Byte,
			strlen(buf)+1 , buf , 0, 2, 0 );
}

void
AttachPartyNumber(
	HFRAME					hFrame, 
	HPROPERTY				hProperty, 
	const unsigned char*	Byte
	)
{
	AttachExtensionIndicator(hFrame, hProperty, Byte+2, BOTH);
	AttachPartyNumber_TypeOfNumber(hFrame, hProperty, Byte+2);
	AttachPartyNumber_NumberingPlanIndication(hFrame, hProperty, Byte+2);

	int offset = 3;
	if( (Byte[2] & 0x80) == 0)
	{
		offset++;
		AttachExtensionIndicator(hFrame, hProperty, Byte+3, FORCE_1);
		
		AttachPartyNumber_PresentationIndicator(hFrame, hProperty, Byte+3);
		AttachPartyNumber_ScreeningIndicator(hFrame, hProperty, Byte+3);
	}

	AttachNumberDigits(hFrame, hProperty, Byte + offset, Byte[1] - offset +2);
}

void CalledPartyNumberInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	AttachPartyNumber(hFrame, hProperty, data);
}

void CallingPartyNumberInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	AttachPartyNumber(hFrame, hProperty, data);
}

void ConnectedPartyNumberInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	AttachPartyNumber(hFrame, hProperty, data);
}

void ProgressInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	AttachExtensionIndicator(hFrame, hProperty, data+2, FORCE_1);
	AttachCodingStandard(hFrame, hProperty, data+2);
	AttachLocation(hFrame, hProperty, data+2);
	AttachExtensionIndicator(hFrame, hProperty, data+3, FORCE_1);

	const char* str[] = 
	{
		"",
		"Call is not end-to-end ISDN; further call progress information may be available in?band",
		"Destination address is non ISDN",
		"Origination address is non ISDN",
		"Call has returned to the ISDN",
		"Interworking has occurred and has resulted in a telecommunication service change",
		"",
		"",
		"In-band information or an appropriate pattern is now available"
	};

	char buf [120];
	const char* description = "";
	if ((data[3] & 0x80) < 8)
		description = str[data[3] & 0x80];

	wsprintf(buf, "Progress description = 0x%02x %s",description);
	AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) (data+3),
			strlen(buf)+1 , buf , 0, 2, 0 );

}

TableEntry informationTransferCapabilityTable[] =
{
	{0x01,"Speech"},
	{0x08,"Unrestricted digital information"},
	{0x09,"Restricted digital information"},
	{0x10,"3.1 kHz audio"},
	{0x11,"Unrestricted digital information with tones/announcements"},
	{0x18,"Video"},

};

TableEntry transferRateTable[] = 
{
	{0x00,"This code shall be used for packet mode calls"},
	{0x10,"64 kbit/s"},
	{0x11,"2 * 64 kbit/s"},
	{0x13,"384 kbit/s"},
	{0x15,"1536 kbit/s"},
	{0x17,"1920 kbit/s"},
	{0x18,"Multirate (64 kbit/s base rate)"}
};

TableEntry userInformationLayer1ProtocolTable[] = 
{
	{0x01,"CCITT standardized rate adaption V.110 and X.30"},
	{0x02,"Recommendation G.711 U-law"},
	{0x03,"Recommendation G.711 A-law"},
	{0x04,"Recommendation G.721 32 kbit/s ADPCM and Recommendation I.460"},
	{0x05,"Recommendations H.221 and H.242"},
	{0x07,"Non-CCITT standardized rate adaption."},
	{0x08,"CCITT standardized rate adaption V.120"},
	{0x09,"CCITT standardized rate adaption X.31 HDLC flag stuffing"}
};

void BearerCapabilityInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	int len = data[1];
	const unsigned char* cur = data+2;

	AttachExtensionIndicator(hFrame, hProperty, cur, FORCE_1);
	AttachCodingStandard(hFrame, hProperty, cur);

	int informationTransferCapability = (*cur) & 0x1f;
	char buf[150];

	FormatBits(buf, 4, 0, informationTransferCapability);
	wsprintf(buf+8, " = Information transfer capability (0x%02x) - %s"
		, informationTransferCapability
		, FindString(informationTransferCapability));

	AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) cur,
		strlen(buf)+1 , buf , 0, 2, 0 );

	AttachExtensionIndicator(hFrame, hProperty, ++cur, FORCE_1);

	const char* transferModeStr[] = {"Circuit mode", "Error" ,"Packet mode", "Error"};
	int transferMode = (*cur) & 0x60 ;

	FormatBits(buf, 6,5, transferMode);
	wsprintf(buf+8, " = %s", transferModeStr[transferMode >> 5]);

	AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) cur,
		strlen(buf)+1 , buf , 0, 2, 0 );

	static const char* transferRateStr = "Reserved";
	int transferRate = (*cur) & 0x1F;

	FormatBits(buf, 4, 0, transferRate);
	wsprintf(buf+8, " = Transfer Rate - %s", 
		FindString(transferRate));

	AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) cur,
		strlen(buf)+1 , buf , 0, 2, 0 );

	
	if (transferRate == 0x18) // multirate, octet 4.1* shall be present
	{
		AttachExtensionIndicator(hFrame, hProperty, ++cur, FORCE_1);

		int rateMultiplier = (*cur) & 0x7F;

		FormatBits(buf, 6, 0, rateMultiplier);
		wsprintf(buf+8, " = Rate Multiplier - %d", rateMultiplier);

		AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) cur,
			strlen(buf)+1 , buf , 0, 2, 0 );
	}

	if (cur - data <= len) // octet 5* present
	{
		AttachExtensionIndicator(hFrame, hProperty, ++cur, BOTH);
		int layer1ID = (*cur) & 0x60;
		FormatBits(buf, 6, 5, layer1ID);
		wsprintf(buf+8, " = Layer 1 Identifer - shall be 01");

		AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) cur,
			strlen(buf)+1 , buf , 0, 2, 0 );

		const char* userInformationLayer1ProtocolStr = "Reserved";
		int userInformationLayer1Protocol = (*cur) & 0x1F;

		FormatBits(buf, 4, 0, userInformationLayer1Protocol);
		wsprintf(buf+8, " = %s", FindString(userInformationLayer1Protocol));

		AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) cur,
			strlen(buf)+1 , buf , 0, 2, 0 );
	}
}

TableEntry callStateTable[] = 
{
	{0x00,"Null"},
	{0x01,"Call initiated"},
	{0x02,"Overlap sending"},
	{0x03,"Outgoing call proceeding"},
	{0x04,"Call delivered"},
	{0x06,"Call present"},
	{0x07,"Call received"},
	{0x08,"Connect request"},
	{0x09,"Incoming call proceeding"},
	{0x10,"Active"},
	{0x11,"Disconnect request"},
	{0x12,"Disconnect indication"},
	{0x15,"Suspend request"},
	{0x17,"Resume request"},
	{0x19,"Release request"},
	{0x22,"Call abort"},
	{0x25,"Overlap receiving"},
	{0x3D,"Restart request"},
	{0x3E,"Restart"}
};

void CallStateInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	AttachCodingStandard(hFrame, hProperty, data+2, 7);
	const char* callStateStr = "Undefined";
	int callState = data[2] & 0x3F;

	char buf[100];
	FormatBits(buf, 6, 0, callState);
	wsprintf(buf+8, " = Call State - %s", FindString(callState));

	AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) (data+2),
		strlen(buf)+1 , buf , 0, 2, 0 );
}


void SignalInformationElement::attachContent(HFRAME hFrame, HPROPERTY hProperty) const
{
	static const char* SignalStrTable[] = 	{
		"Dial tone on",
		"Ring back tone on",
		"Intercept tone on",
		"Network congestion tone on",
		"Busy tone on",
		"Confirm tone on",
		"Answer tone on",
		"Call waiting tone",
		"Off-hook warning tone",
		"Preemption tone on"
	};

	char signalStrBuf[30];
	const char* signalStr = "Reserved";
	int signalValue = data[2];
	if ( signalValue < 10)
		signalStr = SignalStrTable[signalValue];
	else if (signalValue == 0x3F)
		signalStr = "Tones off";
	else if ((signalValue & 0xF8) == 0x60)
	{
		wsprintf(signalStrBuf, "Alerting on - pattern %d", signalValue & 0x07);
		signalStr = signalStrBuf;
	}
	else if (signalValue == 0x4F)
		signalStr = "Alerting off";

	char buf[80];
	wsprintf(buf,"Signal Value = %d (%s)", signalValue, signalStr);
	AttachPropertyInstanceEx(hFrame, hProperty, 1 ,(void*) (data+2),
		strlen(buf)+1 , buf , 0, 2, 0 );

}

Q931PDU::Q931PDU()
{}

Q931PDU::~Q931PDU()
{}


bool Q931PDU::accept(Q931Decoder& strm) 
{
  data = strm.data;

  if (strm.size < 5) 
	  return FALSE;

  if (data[0] != 0x08 || data[1] != 0x02)
	  return FALSE;

  if (getMessageTypeName() == NULL)
	  return FALSE;


  strm.offset = 5;

  while (true)
  {
	  InformationElement* element = InformationElement::Build(strm);
	  if (element != NULL)
	  {
		 ieList.push_back(element);
		 if (strcmp(element->getName(), "User-User") == 0)
		 {
			 UserUserInformationElement* uuie = static_cast<UserUserInformationElement*>(element);
			 if (uuie->decodeIE())
				 break;
			 else
				return FALSE;
		 }
	  }
	  else
		 break;
  }
  return strm.size >= (len = strm.offset);
}

void Q931PDU::attachProperties(HFRAME hFrame, HPROPERTY hProperty)
{
	char buf[80];

	wsprintf(buf,"Q.931 %s (Length = %d)", getMessageTypeName(), len);
	AttachPropertyInstanceEx(hFrame, hProperty, len , (void*)data,
		strlen(buf) + 1, buf , 0, 0, 0);

	AttachPropertyInstanceEx(hFrame, hProperty, 5, (void*)data, 
		19, "Fixed Q.931 Header", 0, 1, 0);

	char* discriminatorStr = "Protocol Discriminator = 0x08";
	AttachPropertyInstanceEx(hFrame, hProperty, 1, (void*)data, 
		strlen(discriminatorStr)+1, discriminatorStr, 0, 2, 0);

	AttachPropertyInstanceEx(hFrame, hProperty, 3,(void*)(data+1), 
		15, "Call Reference", 0, 2, 0);

	AttachPropertyInstanceEx(hFrame, hProperty, 1,(void*) (data+1), 
		26, "Call Reference Length = 2", 0, 3, 0);

	if (data[2] & 0x80)
		AttachPropertyInstanceEx(hFrame, hProperty, 1, (void*) (data+2), 
			28, "1....... = Destination Side", 0, 3, 0);
	else
		AttachPropertyInstanceEx(hFrame, hProperty, 1,(void*) (data+2), 
			28,   "0....... = Originating Side", 0, 3, 0);

	FormatBits(buf, 6,0, data[2]);
	buf[8] = ' ';
	FormatBits(buf+9, 7, 0, data[3]);
	wsprintf(buf+17, " = Call Reference Value - 0x%04x", (data[2] & 0x7F) << 8 | data[3] );

	AttachPropertyInstanceEx(hFrame, hProperty, 2, (void*)(data+2), 
		strlen(buf)+1, buf, 0, 3, 0);

	wsprintf(buf, "Message Type = 0x%02x (%s)", data[4], getMessageTypeName());
	AttachPropertyInstanceEx(hFrame, hProperty, 2, (void*)(data+4), 
		strlen(buf)+1, buf, 0, 3, 0);

	IEList::iterator b = ieList.begin(), e = ieList.end();
	for ( ; b!= e; ++b)
	{
		InformationElement* element = *b;
		element->attachProperties(hFrame, hProperty);
	}

}

TableEntry msgTable[] = 
{
	{0x00,"Escape"},
	{0x01,"Alerting"},
	{0x02,"CallProceeding"},
	{0x03,"Progress"},
	{0x05,"Setup"},
	{0x07,"Connect"},
	{0x0d,"SetupAck"},
	{0x0f,"ConnectAck"},
	{0x5a,"ReleaseComplete"},
	{0x62,"Facility"},
	{0x75,"StatusEnquiry"},
	{0x7b,"Information"},
	{0x7d,"Status"}
};

const char* Q931PDU::getMessageTypeName() const
{
	int msg = data[4];
	return FindString(msg);
}