/*-----------------------------------------------------------------------------
 * Filename: OEM_SMBUS.H
 * Function: OEM_SMBUS.C Include Definition
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_SHA1_H
#define OEM_SHA1_H

/*-----------------------------------------------------------------------------
 * Parameter Definition
 *---------------------------------------------------------------------------*/
//#define SHA1_CMD	0x2F
#define SHA1_RCMD	0x28
#define SHA1_WCMD	0x27
#define SHA1_MASK	0x0000000F

/*-----------------------------------------------------------------------------
 * External Calling Process
 *---------------------------------------------------------------------------*/
extern void OEM_BAT_Authentication(void);

/*-----------------------------------------------------------------------------
 * Internal Process Definition
 *---------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
#endif