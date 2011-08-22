/*
 * PERAttacher.cpp
 * 
 * Copyright (c) 2001 Institute for Information Industry, Taiwan, Republic of China 
 * (http://www.iii.org.tw/iiia/ewelcome.htm)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 1, or (at your option)
 * any later version.
 *
 * $Log: perattacher.cpp,v $
 * Revision 1.3  2005/12/02 03:40:19  mangelo
 * *** empty log message ***
 *
 * Revision 1.2  2002/12/01 07:36:10  mangelo
 * Fixed problem with BIT_STRING
 *
 * Revision 1.1.1.1  2001/08/01 07:39:00  mangelo
 * Import to SourceForge
 *
 * Revision 1.1.1.1  2001/05/05 15:16:34  angelo
 * First CVS Version
 *
 */

#include "perattacher.h"

PERAttacher::PERAttacher(ASN1::PERDecoder& coder, 
             HFRAME			   frame,
             HPROPERTY		   property,
             std::string       text,
             int               lvl)
: ASN1::Visitor(coder.get_env())
, decoder(coder)
, hFrame(frame)
, hProperty(property)
, level(lvl)
{
    strm << text;
}

bool PERAttacher::attach(const char* startPosition)
{
    strm << std::ends;
    std::string& str = strm.str();
	return AttachPropertyInstanceEx( hFrame,
		hProperty,
		decoder.getNextPosition()  - startPosition,
		(void*)startPosition,
		(DWORD) str.size()+1,
		(void*) str.c_str(), 
		0, level, 0) != 0;
}

bool PERAttacher::do_visit(ASN1::AbstractData& value)
{
	const char* startPos = decoder.getPosition();

	if (value.accept(decoder))
	{
        strm << std::ends;
        std::string& str = strm.str();
        int len = str.find_first_of('\0');
        strm.seekp(-1, std::ios::cur);
        if (len > 2 && str[len-2] != ':')
            strm << "= ";
		strm << value;
		return attach(startPos);
	}
	return false;
}

bool PERAttacher::do_visit(ASN1::Null& value)
{
    return do_visit(static_cast<ASN1::AbstractData&>(value));
}

bool PERAttacher::do_visit(ASN1::BOOLEAN& value)
{
    return do_visit(static_cast<ASN1::AbstractData&>(value));
}

bool PERAttacher::do_visit(ASN1::INTEGER& value)
{
    return do_visit(static_cast<ASN1::AbstractData&>(value));
}

bool PERAttacher::do_visit(ASN1::ENUMERATED& value)
{
    return do_visit(static_cast<ASN1::AbstractData&>(value));
}


bool PERAttacher::do_visit(ASN1::OBJECT_IDENTIFIER& value)
{
    return do_visit(static_cast<ASN1::AbstractData&>(value));
}

bool PERAttacher::do_visit(ASN1::BIT_STRING& value)
{
	if (value.size() <= 16)
		return do_visit(static_cast<ASN1::AbstractData&>(value));

    const char* startPos = decoder.getPosition();
    
    if (value.accept(decoder))
    {
		strm << " (length = " << value.size() << " bits)";
        if (attach(startPos)) 
        {
            strm.seekp(0, std::ios::beg);
			strm << "Number of data bits remaining = " 
				    << value.size();
			level++;
			bool result = attach(decoder.getPosition()-value.size()/8);
            level--;
            return result;
		}
    }
    return false;    
}

bool PERAttacher::do_visit(ASN1::OCTET_STRING& value)
{
    const char* startPos = decoder.getPosition();
    
    if (value.accept(decoder))
    {
		strm << " (length = " << value.size() << ")";
        if (attach(startPos)) 
        {
            strm.seekp(0, std::ios::beg);
            if (value.getLowerLimit() == 4 && value.getUpperLimit() == 4)
            {
                for (int i = 0; i < 4 ; ++i)
                {
                    strm << (unsigned)(unsigned char)value[i];
                    if (i !=3) strm << '.';
                }
            }
            else if (value.size() <= 16)
            {
                strm << std::uppercase << value;
            }
            else
			    strm << "Number of data bytes remaining = " 
				    << value.size() << " (0x" << std::hex << value.size() 
                    << ")" << std::dec;
			level++;
			bool result = attach(decoder.getPosition()-value.size());
            level--;
            return result;
		}
    }
    return false;    
}

bool PERAttacher::do_visit(ASN1::AbstractString& value)
{
    return do_visit(static_cast<ASN1::AbstractData&>(value));
}

bool PERAttacher::do_visit(ASN1::BMPString& value)
{
    return do_visit(static_cast<ASN1::AbstractData&>(value));
}

bool PERAttacher::do_visit(ASN1::GeneralizedTime& value)
{
    return do_visit(static_cast<ASN1::AbstractData&>(value));
}

bool PERAttacher::do_visit(ASN1::CHOICE& value)
{
	const char* savedPosition = decoder.getPosition();
    memento_type memento;
    bool ok = false;
    if (decoder.decodeChoicePreamle(value,memento))
    {
        if (!value.isUnknownSelection())
		{
			strm << value.getSelectionName() << " : ";
			if (!value.getSelection()->accept(*this))
				ok = false;
			decoder.rollback(memento);
            ok = true;
		}
		else
		{
			decoder.rollback(memento);
			strm << "[Unknown]";
			attach(savedPosition);
            ok = true;
		}
    }
    return ok;
}

bool PERAttacher::do_visit(ASN1::SEQUENCE_OF_Base& value)
{
  const char* savedPosition = decoder.getPosition();
  value.clear();

  unsigned size, i;
  if (decoder.decodeConstrainedLength(value, size) < 0)
    return false;

  memento_type memento = decoder.get_memento();
  for (i = 0; i < (unsigned)size; i++) {
	std::auto_ptr<ASN1::AbstractData> obj(value.createElement());
    if (!obj->accept(decoder))
      return false;
  }
  attach(savedPosition);

  decoder.rollback(memento);
  level++;
  bool ok = true;
  for (i = 0; i < (unsigned)size; i++) {
	std::auto_ptr<ASN1::AbstractData> obj(value.createElement());
    strm.seekp(0, std::ios::beg);
	strm << "[" << i << "] " ; 
    if (!obj->accept(*this))
    {
      ok = false;
      break;
    }
	value.push_back(obj.release());
  }
  level--;
  return ok;
}

bool PERAttacher::do_visit(ASN1::OpenData& value)
{
    memento_type memento = decoder.get_memento();

    if (value.accept(decoder))
	{
		if (decoder.get_env())
			openDataPositions.push_back(memento);
		return attach(memento.bytePosition);
	}
	return false;
}

bool PERAttacher::do_revisit(ASN1::OpenData& value)
{
	bool ok = false;;
	if (value.has_data())
	{
		memento_type memento = decoder.get_memento();
		decoder.rollback(openDataPositions.back());
		unsigned nBytes;
		if (decoder.decodeLength(0, INT_MAX, nBytes) >= 0)
		{
			level++;
			strm.seekp(0, std::ios::beg);
			ok = value.get_data().accept(*this);
			level--;
		}
		decoder.rollback(memento);
	}
	openDataPositions.pop_back();
	return ok;
}

bool PERAttacher::do_visit(ASN1::TypeConstrainedOpenData& value)
{
    assert(value.has_data());
	unsigned len;
    if (decoder.decodeLength(0, INT_MAX, len) != 0)
       return false;
	const char* nextPosition = decoder.getPosition() + len;
	bool ok = value.get_data().accept(*this);
	decoder.setPosition(nextPosition);
	return ok;
}


ASN1::Visitor::VISIT_SEQ_RESULT PERAttacher::preVisitExtensionRoots(ASN1::SEQUENCE& value)
{
	memento_type memento = decoder.get_memento();
	if (value.accept(decoder))
	{
		if (attach(memento.bytePosition))
		{
			decoder.rollback(memento);
			return decoder.preVisitExtensionRoots(value);
		}
	}
	return FAIL;
}

ASN1::Visitor::VISIT_SEQ_RESULT PERAttacher::visitExtensionRoot(ASN1::SEQUENCE& value, int index, int optional_id)
{
	if (optional_id == -1 || value.hasOptionalField(optional_id))
	{
        if (value.getField(index) == NULL)
            value.includeOptionalField(optional_id, index);
		if (value.getField(index) == NULL)
			return FAIL;
		strm.seekp(0, std::ios::beg);
		level++;
		strm << value.getFieldName(index) << ' ';
		if (!value.getField(index)->accept(*this))
			return FAIL;
		level--;
	}
	return CONTINUE;	
}

ASN1::Visitor::VISIT_SEQ_RESULT PERAttacher::preVisitExtensions(ASN1::SEQUENCE& value)
{
	return decoder.preVisitExtensions(value);
}

ASN1::Visitor::VISIT_SEQ_RESULT PERAttacher::visitKnownExtension(ASN1::SEQUENCE& value, int index, int optional_id)
{
  if (!value.hasOptionalField(optional_id))
    return CONTINUE;

  unsigned len;
  if (decoder.decodeLength(0, INT_MAX, len) != 0)
    return FAIL;

  const char* nextExtensionPosition = decoder.getPosition() + len;
  bool ok = true;
  if (value.getField(index) == NULL)
    value.includeOptionalField(optional_id, index);
  if (value.getField(index) != NULL)
  {
	 strm.seekp(0, std::ios::beg);
	 level++;
	 strm << value.getFieldName(index) << ' ';
	 ok = value.getField(index)->accept(*this);
	 level--;
  }
  decoder.setPosition(nextExtensionPosition);
  return ok ? CONTINUE : FAIL;
}

bool PERAttacher::visitUnknownExtensions(ASN1::SEQUENCE& value)
{
	return decoder.visitUnknownExtensions(value);
}