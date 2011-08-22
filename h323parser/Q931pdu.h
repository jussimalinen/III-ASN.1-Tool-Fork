/*
 * Q931Pdu.h
 * 
 * Copyright (c) 2001 Institute for Information Industry, Taiwan, Republic of China 
 * (http://www.iii.org.tw/iiia/ewelcome.htm)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 1, or (at your option)
 * any later version.
 *
 * $Log: Q931pdu.h,v $
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

#ifndef Q931PDU_H
#define Q931PDU_H

#include <list>
#include "pointainer.h"
#include <netmon.h>

namespace ASN1 {
class CoderEnv;
}

struct Q931Decoder
{
    Q931Decoder(LPBYTE pFrame, int byteLeft, ASN1::CoderEnv* coderEnv) 
		: data(pFrame), size(byteLeft), offset(0), env(coderEnv){}
	int getPosition() const { return offset;}
	const unsigned char* data;
	int size;
	int offset;
    ASN1::CoderEnv* env;
};


class InformationElement;
class Q931PDU
{
public:
  public:
	Q931PDU();
	~Q931PDU();
    bool accept(Q931Decoder& decoder);
	void attachProperties(HFRAME hFrame, HPROPERTY hProperty);
    const char* getMessageTypeName() const;
  private:
	  typedef pointainer< std::list<InformationElement*> > IEList;
	  const unsigned char* data;
	  int len;
	  IEList ieList;
};

#endif