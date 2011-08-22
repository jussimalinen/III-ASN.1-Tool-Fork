/*
 * PERAttacher.h
 * 
 * Copyright (c) 2001 Institute for Information Industry, Taiwan, Republic of China 
 * (http://www.iii.org.tw/iiia/ewelcome.htm)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 1, or (at your option)
 * any later version.
 *
 * $Log: perattacher.h,v $
 * Revision 1.2  2005/12/02 03:40:19  mangelo
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2001/08/01 07:38:53  mangelo
 * Import to SourceForge
 *
 * Revision 1.1.1.1  2001/05/05 15:16:34  angelo
 * First CVS Version
 *
 *
 */

#ifndef PERATTACHER_H
#define PERATTACHER_H
#include <asn1.h>
#include <netmon.h>
#include <sstream>

class PERAttacher : public ASN1::Visitor
{
public:
    typedef ASN1::PERDecoder decoder_type;
	typedef decoder_type::memento_type memento_type;
    
    PERAttacher(ASN1::PERDecoder& coder, 
                 HFRAME			   hFrame,
	             HPROPERTY		   hProperty,
                 std::string       text,
                 int               level);
protected:
    bool attach(const char* startPosition);
private:
    bool do_visit(ASN1::AbstractData& value);
	bool do_visit(ASN1::Null& value);
	bool do_visit(ASN1::BOOLEAN& value);
	bool do_visit(ASN1::INTEGER& value);
	bool do_visit(ASN1::ENUMERATED& value);
	bool do_visit(ASN1::OBJECT_IDENTIFIER& value);
	bool do_visit(ASN1::BIT_STRING& value);
	bool do_visit(ASN1::OCTET_STRING& value);
	bool do_visit(ASN1::AbstractString& value);
	bool do_visit(ASN1::BMPString& value);
	bool do_visit(ASN1::GeneralizedTime& value);
	bool do_visit(ASN1::CHOICE& value);
	bool do_visit(ASN1::SEQUENCE_OF_Base& value);
	bool do_visit(ASN1::OpenData& value);
    bool do_revisit(ASN1::OpenData& value);
    bool do_visit(ASN1::TypeConstrainedOpenData& value);

	VISIT_SEQ_RESULT preVisitExtensionRoots(ASN1::SEQUENCE& value);
	VISIT_SEQ_RESULT visitExtensionRoot(ASN1::SEQUENCE& value, int index, int optional_id);
	VISIT_SEQ_RESULT preVisitExtensions(ASN1::SEQUENCE& value);
	VISIT_SEQ_RESULT visitKnownExtension(ASN1::SEQUENCE& value, int index, int optional_id);
	bool visitUnknownExtensions(ASN1::SEQUENCE& value);

    ASN1::PERDecoder& decoder;
    HFRAME				hFrame;
	HPROPERTY			hProperty;
	std::stringstream	strm;
	int					level;
	std::vector<decoder_type::memento_type> openDataPositions;
};

#endif
