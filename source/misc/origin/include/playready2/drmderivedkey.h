/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMDERIVEDKEY_H__
#define __DRMDERIVEDKEY_H__

ENTER_PK_NAMESPACE;

/*
** Macro that defines the location prefix:
** Each bit of '1' represents a path leg from the root to the
** key tree node that is represented by the location. All
** other bits are 0. In other words, the prefix is a bit mask
** with all bits before the stop bit be 1 and all bits from the
stop bit be 0.
*/
#define LP( x )     ( ~( ( x ) ^ ( ( x ) -1 ) ) )

/*
** Macro that defines the stop bit mask which is a bit mask with
** all bits except the stop bit be 0.
*/
#define SBM( x )    ( ( ( ~LP( x ) ) >> 1 ) + 1 )

/*
** Macro to check whether a key tree node with location x is the
** ancestor of another key tree node with location y. x is an ancestor
** of y means x and y are at the same branch from the root and x is
** located closer to the root than y does.
*/
#define IsAncestor( x, y )  ( SBM( x ) >= SBM( y ) && ( y  & LP( x ) ) == ( x & LP( x ) ) )

/*
** The maximum depth of the stack that is used to store the intermediate keys
** during derivation. It should be the maximum depth of any subtree in the
** whole key tree.
*/
#define MAX_KEY_STACK   20

EXIT_PK_NAMESPACE;

#endif /* __DRMDERIVEDKEY_H__ */