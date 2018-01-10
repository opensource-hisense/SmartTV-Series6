/*============================================================================
 * $Workfile:   example.c  $
 * $Archive:   //VMServer/TVSoft/archives/codebase2005/oss/cutest/1.4/cutest/example/src/example.c-arc  $
 *----------------------------------------------------------------------------
 */ /**
 * @file example.c
 * Example for use of the unit testing framework (cutest), version 1.4
 * 
 * <Description>
 *
 * @author Dr. Vladimir Vinarski
 *
 *----------------------------------------------------------------------------
 * Copyright (c) 2006 LOEWE Opta GmbH, Kronach. All rights reserved.
 *----------------------------------------------------------------------------
 * $Revision:   1.0  $
 * $Date:   Jul 04 2006 16:27:14  $
 * $Modtime:   Jul 04 2006 16:22:04  $
 *----------------------------------------------------------------------------
 * $Log:   //VMServer/TVSoft/archives/codebase2005/oss/cutest/1.4/cutest/example/src/example.c-arc  $
 * 
 *    Rev 1.0   Jul 04 2006 16:27:14   vinarski
 * Initial revision.
 *----------------------------------------------------------------------------
 */

// Includes ==================================================================

// ANSI C include files ------------------------------------------------------

#include <stdio.h>

// System-specific C include files -------------------------------------------

// C utility libraries include files -----------------------------------------

// Project-specific C include files ------------------------------------------

// Module-specific C include files ------------------------------------------

#include <cutest/cutest.h>

// Defines ===================================================================

// Types =====================================================================

// Globals ===================================================================

// Locals ====================================================================

// Functions =================================================================

// C functions ===============================================================


unsigned factorial( unsigned n )
{
    if( (n == 0) || (n == 1) )
    {
        return 1;
    }
    else
    {
        return n*factorial( n -1 );
    }
}


unsigned absValue( int value )
{
    if( value >= 0 )
    {
        return value;
    }
    else
    {
        return (-value);
    }
}


unsigned getQuadrat( int value )
{
    return value*value;
}


void testQuadratFunction( CuTest *tc )
{
    CuAssertTrue( tc, (getQuadrat( 5 ) == 26) );    
}


void testFactorialFunction( CuTest *tc )
{
    CuAssertTrue( tc, (factorial( 5 ) == 120) );
}


void testAbsFunction( CuTest *tc )
{
    CuAssertTrue( tc, ( absValue( -13 ) == 13) );
}


CuSuite *getMathSuite( void )
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST( suite, testFactorialFunction );
    SUITE_ADD_TEST( suite, testAbsFunction );
    SUITE_ADD_TEST( suite, testQuadratFunction );
    
    return suite;
}


void doTest( void )
{
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();
    CuSuiteAddSuite( suite, getMathSuite() );
    
    // run suite
    CuSuiteRun( suite );
    CuSuiteSummary( suite, output );
    printf( "%s\n", output->buffer);
    CuSuiteDetails( suite, output );
    printf( "%s\n", output->buffer);
}


int main( void )
{
    doTest();
    
    return 0;
}


