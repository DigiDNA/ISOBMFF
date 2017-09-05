/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com / www.imazing.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        BinaryStream.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <IBMFF/BinaryStream.hpp>
#include <fstream>
#include <cmath>
#include <cstdint>

template<>
class XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const std::string & path );
        IMPL( IBMFF::BinaryStream & stream, uint64_t length );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< uint8_t > _bytes;
};

#define XS_PIMPL_CLASS IBMFF::BinaryStream
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    BinaryStream::BinaryStream( void ): XS::PIMPL::Object< BinaryStream >()
    {}
    
    BinaryStream::BinaryStream( std::string path ): XS::PIMPL::Object< BinaryStream >( path )
    {}
    
    BinaryStream::BinaryStream( BinaryStream & stream, uint64_t length ): XS::PIMPL::Object< BinaryStream >( stream, length )
    {}
    
    bool BinaryStream::HasBytesAvailable( void ) const
    {
        return this->impl->_bytes.size() > 0;
    }
    
    uint8_t BinaryStream::ReadUInt8( void )
    {
        uint8_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( &n ), 1 );
        
        return n;
    }
    
    int8_t BinaryStream::ReadInt8( void )
    {
        int8_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( &n ), 1 );
        
        return n;
    }
    
    uint16_t BinaryStream::ReadUInt16( void )
    {
        uint16_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( &n ), 2 );
        
        return n;
    }
    
    int16_t BinaryStream::ReadInt16( void )
    {
        int16_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( &n ), 2 );
        
        return n;
    }
    
    uint16_t BinaryStream::ReadBigEndianUInt16( void )
    {
        uint8_t  c[ 2 ];
        uint16_t n;
        uint16_t n1;
        uint16_t n2;
        
        c[ 0 ] = 0;
        c[ 1 ] = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( c ), 2 );
        
        n1 = static_cast< uint16_t >( c[ 0 ] );
        n2 = static_cast< uint16_t >( c[ 1 ] );
        
        n  = static_cast< uint16_t >( n1 << 8 )
           | n2;
        
        return n;
    }
    
    uint16_t BinaryStream::ReadLittleEndianUInt16( void )
    {
        uint8_t  c[ 2 ];
        uint16_t n;
        uint16_t n1;
        uint16_t n2;
        
        c[ 0 ] = 0;
        c[ 1 ] = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( c ), 2 );
        
        n1 = static_cast< uint16_t >( c[ 1 ] );
        n2 = static_cast< uint16_t >( c[ 0 ] );
        
        n  = static_cast< uint16_t >( n1 << 8 )
           | n2;
        
        return n;
    }
    
    uint32_t BinaryStream::ReadUInt32( void )
    {
        uint32_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( &n ), 4 );
        
        return n;
    }
    
    int32_t BinaryStream::ReadInt32( void )
    {
        int32_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( &n ), 4 );
        
        return n;
    }
    
    uint32_t BinaryStream::ReadBigEndianUInt32( void )
    {
        uint8_t  c[ 4 ];
        uint32_t n;
        uint32_t n1;
        uint32_t n2;
        uint32_t n3;
        uint32_t n4;
        
        c[ 0 ] = 0;
        c[ 1 ] = 0;
        c[ 2 ] = 0;
        c[ 3 ] = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( c ), 4 );
        
        n1 = static_cast< uint32_t >( c[ 0 ] );
        n2 = static_cast< uint32_t >( c[ 1 ] );
        n3 = static_cast< uint32_t >( c[ 2 ] );
        n4 = static_cast< uint32_t >( c[ 3 ] );
        
        n  = static_cast< uint32_t >( n1 << 24 )
           | static_cast< uint32_t >( n2 << 16 )
           | static_cast< uint32_t >( n3 << 8 )
           | n4;
        
        return n;
    }
    
    uint32_t BinaryStream::ReadLittleEndianUInt32( void )
    {
        uint8_t  c[ 4 ];
        uint32_t n;
        uint32_t n1;
        uint32_t n2;
        uint32_t n3;
        uint32_t n4;
        
        c[ 0 ] = 0;
        c[ 1 ] = 0;
        c[ 2 ] = 0;
        c[ 3 ] = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( c ), 4 );
        
        n1 = static_cast< uint32_t >( c[ 3 ] );
        n2 = static_cast< uint32_t >( c[ 2 ] );
        n3 = static_cast< uint32_t >( c[ 1 ] );
        n4 = static_cast< uint32_t >( c[ 0 ] );
        
        n  = static_cast< uint32_t >( n1 << 24 )
           | static_cast< uint32_t >( n2 << 16 )
           | static_cast< uint32_t >( n3 << 8 )
           | n4;
        
        return n;
    }
    
    uint64_t BinaryStream::ReadUInt64( void )
    {
        uint64_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( &n ), 8 );
        
        return n;
    }
    
    int64_t BinaryStream::ReadInt64( void )
    {
        int64_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( &n ), 8 );
        
        return n;
    }
    
    uint64_t BinaryStream::ReadBigEndianUInt64( void )
    {
        uint8_t  c[ 8 ];
        uint64_t n;
        uint64_t n1;
        uint64_t n2;
        uint64_t n3;
        uint64_t n4;
        uint64_t n5;
        uint64_t n6;
        uint64_t n7;
        uint64_t n8;
        
        c[ 0 ] = 0;
        c[ 1 ] = 0;
        c[ 2 ] = 0;
        c[ 3 ] = 0;
        c[ 4 ] = 0;
        c[ 5 ] = 0;
        c[ 6 ] = 0;
        c[ 7 ] = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( c ), 8 );
        
        n1 = static_cast< uint64_t >( c[ 0 ] );
        n2 = static_cast< uint64_t >( c[ 1 ] );
        n3 = static_cast< uint64_t >( c[ 2 ] );
        n4 = static_cast< uint64_t >( c[ 3 ] );
        n5 = static_cast< uint64_t >( c[ 4 ] );
        n6 = static_cast< uint64_t >( c[ 5 ] );
        n7 = static_cast< uint64_t >( c[ 6 ] );
        n8 = static_cast< uint64_t >( c[ 7 ] );
        
        n  = static_cast< uint64_t >( n1 << 56 )
           | static_cast< uint64_t >( n2 << 48 )
           | static_cast< uint64_t >( n3 << 40 )
           | static_cast< uint64_t >( n4 << 32 )
           | static_cast< uint64_t >( n5 << 24 )
           | static_cast< uint64_t >( n6 << 16 )
           | static_cast< uint64_t >( n7 << 8 )
           | n8;
        
        return n;
    }
    
    uint64_t BinaryStream::ReadLittleEndianUInt64( void )
    {
        uint8_t  c[ 8 ];
        uint64_t n;
        uint64_t n1;
        uint64_t n2;
        uint64_t n3;
        uint64_t n4;
        uint64_t n5;
        uint64_t n6;
        uint64_t n7;
        uint64_t n8;
        
        c[ 0 ] = 0;
        c[ 1 ] = 0;
        c[ 2 ] = 0;
        c[ 3 ] = 0;
        c[ 4 ] = 0;
        c[ 5 ] = 0;
        c[ 6 ] = 0;
        c[ 7 ] = 0;
        
        this->Read( reinterpret_cast< uint8_t * >( c ), 8 );
        
        n1 = static_cast< uint64_t >( c[ 7 ] );
        n2 = static_cast< uint64_t >( c[ 6 ] );
        n3 = static_cast< uint64_t >( c[ 5 ] );
        n4 = static_cast< uint64_t >( c[ 4 ] );
        n5 = static_cast< uint64_t >( c[ 3 ] );
        n6 = static_cast< uint64_t >( c[ 2 ] );
        n7 = static_cast< uint64_t >( c[ 1 ] );
        n8 = static_cast< uint64_t >( c[ 0 ] );
        
        n  = static_cast< uint64_t >( n1 << 56 )
           | static_cast< uint64_t >( n2 << 48 )
           | static_cast< uint64_t >( n3 << 40 )
           | static_cast< uint64_t >( n4 << 32 )
           | static_cast< uint64_t >( n5 << 24 )
           | static_cast< uint64_t >( n6 << 16 )
           | static_cast< uint64_t >( n7 << 8 )
           | n8;
        
        return n;
    }
    
    float BinaryStream::ReadBigEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength )
    {
        uint32_t     n;
        unsigned int integer;
        unsigned int fractionalMask;
        unsigned int fractional;
        
        if( integerLength + fractionalLength == 16 )
        {
            n = this->ReadBigEndianUInt16();
        }
        else
        {
            n = this->ReadBigEndianUInt32();
        }
        
        integer        = n >> fractionalLength;
        fractionalMask = static_cast< unsigned int >( pow( 2, fractionalLength ) - 1 );
        fractional     = ( n & fractionalMask ) / ( 1 << fractionalLength );
        
        return integer + fractional;
    }
    
    float BinaryStream::ReadLittleEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength )
    {
        uint32_t     n;
        unsigned int integer;
        unsigned int fractionalMask;
        unsigned int fractional;
        
        if( integerLength + fractionalLength == 16 )
        {
            n = this->ReadLittleEndianUInt16();
        }
        else
        {
            n = this->ReadLittleEndianUInt32();
        }
        
        integer        = n >> fractionalLength;
        fractionalMask = static_cast< unsigned int >( pow( 2, fractionalLength ) - 1 );
        fractional     = ( n & fractionalMask ) / ( 1 << fractionalLength );
        
        return integer + fractional;
    }
    
    std::string BinaryStream::ReadFourCC( void )
    {
        std::string s( reinterpret_cast< const char * >( &( this->impl->_bytes[ 0 ] ) ), 4 );
        
        this->DeleteBytes( 4 );
        
        return s;
    }
    
    std::string BinaryStream::ReadNULLTerminatedString( void )
    {
        uint64_t    length;
        std::string ret;
        
        length = 0;
        
        for( const auto b: this->impl->_bytes )
        {
            length++;
            
            if( b == 0 )
            {
                break;
            }
        }
        
        ret = std::string( length, ' ' );
        
        this->Read( reinterpret_cast< uint8_t * >( &( ret[ 0 ] ) ), length );
        
        return ret;
    }
    
    std::string BinaryStream::ReadPascalString( void )
    {
        uint8_t     length;
        std::string ret;
        
        length = this->ReadUInt8();
        
        if( length == 0 )
        {
            return "";
        }
        
        ret = std::string( length, ' ' );
        
        this->Read( reinterpret_cast< uint8_t * >( &( ret[ 0 ] ) ), length );
        
        return ret;
    }
    
    Matrix BinaryStream::ReadMatrix( void )
    {
        return Matrix
        (
            this->ReadBigEndianUInt32(),
            this->ReadBigEndianUInt32(),
            this->ReadBigEndianUInt32(),
            this->ReadBigEndianUInt32(),
            this->ReadBigEndianUInt32(),
            this->ReadBigEndianUInt32(),
            this->ReadBigEndianUInt32(),
            this->ReadBigEndianUInt32(),
            this->ReadBigEndianUInt32()
        );
    }
    
    std::vector< uint8_t > BinaryStream::ReadAllData( void )
    {
        std::vector< uint8_t > v;
        
        swap( v, this->impl->_bytes );
        
        return v;
    }
    
    void BinaryStream::Read( uint8_t * buf, uint64_t length )
    {
        memcpy( static_cast< void * >( buf ), static_cast< const void * >( &( this->impl->_bytes[ 0 ] ) ), length );
        this->DeleteBytes( length );
    }
    
    void BinaryStream::Get( uint8_t * buf, uint64_t pos, uint64_t length )
    {
        memcpy( static_cast< void * >( buf ), static_cast< const void * >( &( this->impl->_bytes[ pos ] ) ), length );
    }
    
    void BinaryStream::DeleteBytes( uint64_t length )
    {
        std::vector< uint8_t >( this->impl->_bytes.begin() + static_cast< std::vector< uint8_t >::difference_type >( length ), this->impl->_bytes.end() ).swap( this->impl->_bytes );
    }
}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::IMPL( const std::string & path )
{
    std::ifstream           stream;
    std::ifstream::pos_type length;
    
    stream.open( path, std::ios::binary | std::ios::ate );
    
    if( stream.good() == false )
    {
        return;
    }
    
    length       = stream.tellg();
    this->_bytes = std::vector< uint8_t >( static_cast< std::size_t >( length ) );
    
    stream.seekg( 0, std::ios::beg );
    stream.read( reinterpret_cast< char * >( &( this->_bytes[ 0 ] ) ), length );
}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::IMPL( IBMFF::BinaryStream & stream, uint64_t length ):
    _bytes( length )
{
    stream.Read( &( this->_bytes[ 0 ] ), length );
}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::IMPL( const IMPL & o ):
    _bytes( o._bytes )
{}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::~IMPL( void )
{}
