/*                                         *
*            Server Framework              *
*                                          *
*    Developed by: Cmaranec (Kennny)       *
*                                          *
*    Copyright (c) 2011                    *
*                                          */

#ifndef __OPCODES_H_
#define __OPCODES_H_

#define FAIL 0
#define OK 1

enum Opcodes
{
    MSG_NONE                       = 0x00,
    CMSG_INITIATE_SESSION          = 0x01,
    SMSG_INITIATE_SESSION_RESPONSE = 0x02,
    SMSG_SERVER_BROADCAST          = 0x03,
};

#endif
