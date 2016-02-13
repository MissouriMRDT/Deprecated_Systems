#if !defined( MACROS_H )
#define MACROS_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************
*                                   INLCUDES                               *
***************************************************************************/

/***************************************************************************
*                             LITERAL CONSTANTS                            *
***************************************************************************/

/***************************************************************************
*                                   MACROS                                 *
***************************************************************************/

/*-----------------------------------
Casting
-----------------------------------*/
#define cast_stc( type, value )     static_cast< (type) >( value )
#define cast_s16( value )           static_cast< int16_t >( value )
#define cast_u16( value )           static_cast< uint16_t >( value )
#define cast_s8( value )            static_cast< int8_t >( value )
#define cast_u8( value )            static_cast< uint8_t >( value )

/*-----------------------------------
General
-----------------------------------*/
#define maxval( x, y )              ( (a) > (b) ? (a) : (b) )
#define minval( x, y )              ( (a) < (b) ? (a) : (b) )
#define swap( x, y )                \
( {                                 \
    typeof(x) _z_ = x;              \
    x = y;                          \
    y = _z_;                        \
} )
#define unless( x )                 if( !(x) )
#define until( x )                  while( !(x) )

/*-----------------------------------
Bit
-----------------------------------*/
#define bitmsk( pos )               ( 1 << (pos) )
#define clrbit( var, pos )          ( (var) &= ( 1 << (pos) ) )
#define chkbit( var, pos )          ( ( (var) >> (pos) ) & 1 )
#define setbit( var, pos )          ( (var) |= ( 1 << (pos) ) )
#define set8bit( var, val1, val2, val3, val4, val5, val6, val7, val8 ) \
                                    ( (var) = (val1) << 0 + (val2) << 1 + (val3) << 2 + (val4) << 3 + (val5) << 4 + (val6) << 5 + (val7) << 6 + (val8) << 7 )
#define tglbit( var, pos )          ( (var) ^= ( 1 << (pos) ) )

/*-----------------------------------
Array / struct related
-----------------------------------*/
#define cnt_of_arr( a )             ( ( sizeof(a) / sizeof( 0[a]) ) / ( (size_t)( !( sizeof(a) % sizeof( 0[a] ) ) ) ) ) )
#define memclr( a )                 ( memset( (a), 0, sizeof(a) ) )
#define memset( a, v )              ( memset( (a), (v), sizeof(a) ) )

/*-----------------------------------
Random number generation
-----------------------------------*/
#define random_i01()                ( rand() % 2 )
#define random_i0y( y )             ( rand() % (y) )
#define random_ixy( x, y )          ( ( rand() % ( (y) - (x) ) ) + (x) )
#define random_f01()                ( static_cast<float>( rand() ) / static_cast <float>( RAND_MAX ) )
#define random_f0y( y )             ( static_cast<float>( rand() ) / ( static_cast <float>( RAND_MAX / (y) ) ) )
#define random_fxy( x, y )          ( (x) + static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( (y) - (x) ) ) ) )

/***************************************************************************
*                                    TYPES                                 *
***************************************************************************/

/***************************************************************************
*                              MEMORY CONSTANTS                            *
***************************************************************************/

/***************************************************************************
*                                   CLASSES                                *
***************************************************************************/

/***************************************************************************
*                                  VARIABLES                               *
***************************************************************************/

/***************************************************************************
*                                 PROCEDURES                               *
***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
