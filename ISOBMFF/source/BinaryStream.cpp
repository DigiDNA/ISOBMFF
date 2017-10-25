/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 DigiDNA - www.digidna.net
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
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/BinaryStream.hpp>
#include <fstream>
#include <cmath>
#include <cstdint>

#ifdef _WIN32
#include <ISOBMFF/WIN32.hpp>
#endif

template<>
class XS::PIMPL::Object< ISOBMFF::BinaryStream >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const std::string & path );
        IMPL( const std::vector< uint8_t > & bytes );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< uint8_t > _bytes;
        mutable std::ifstream  _stream;
        std::string            _path;
};

#define XS_PIMPL_CLASS ISOBMFF::BinaryStream
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    BinaryStream::BinaryStream( void )
    {}
    
	BinaryStream::BinaryStream( const std::string & path ): XS::PIMPL::Object< BinaryStream >( path )
    {}
    
	BinaryStream::BinaryStream( const std::vector< uint8_t > & bytes ): XS::PIMPL::Object< BinaryStream >( bytes )
	{}
    
    BinaryStream::BinaryStream( BinaryStream & stream, uint64_t length ): BinaryStream( std::vector< uint8_t >( static_cast< size_t >( length ) ) )
    {
        if( length > 0 )
        {
            stream.Read( &( this->impl->_bytes[ 0 ] ), length );
        }
    }
    
    bool BinaryStream::HasBytesAvailable( void ) const
    {
        if( this->impl->_stream.is_open() )
        {
            {
                std::streampos cur;
                std::streampos end;
                
                cur = this->impl->_stream.tellg();
                
                this->impl->_stream.seekg( 0, std::ios::end );
                
                end = this->impl->_stream.tellg();
                
                this->impl->_stream.seekg( cur, std::ios::beg );
                
                return cur < end;
            }
        }
        else
        {
            return this->impl->_bytes.size() > 0;
        }
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
        
        return static_cast< float >( integer + fractional );
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
        
        return static_cast< float >( integer + fractional );
    }
    
    std::string BinaryStream::ReadFourCC( void )
    {
        uint8_t s[ 4 ];
        
        this->Read( s, 4 );
        
        return std::string( reinterpret_cast< char * >( s ), 4 );
    }
    
    std::string BinaryStream::ReadNULLTerminatedString( void )
    {
        std::vector< uint8_t > bytes;
        uint8_t                b;
        
        do
        {
            b = this->ReadUInt8();
            
            bytes.push_back( b );
        }
        while( b != 0 );
        
        return std::string( reinterpret_cast< char * >( &( bytes[ 0 ] ) ), bytes.size() );
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
        
        if( this->impl->_stream.is_open() )
        {
            {
                std::ifstream::pos_type cur;
                std::ifstream::pos_type length;
                
                cur = this->impl->_stream.tellg();
                
                this->impl->_stream.seekg( 0, std::ios::end );
                
                length = this->impl->_stream.tellg();
                v      = std::vector< uint8_t >( static_cast< std::size_t >( length ) );
                
                this->impl->_stream.seekg( cur, std::ios::beg );
                this->impl->_stream.read( reinterpret_cast< char * >( &( v[ 0 ] ) ), length );
            }
        }
        else
        {
            swap( v, this->impl->_bytes );
        }
        
        return v;
    }
    
    void BinaryStream::Read( uint8_t * buf, uint64_t length )
    {
        if( this->impl->_stream.is_open() )
        {
            this->impl->_stream.read( reinterpret_cast< char * >( buf ), static_cast< std::streamsize >( length ) );
        }
        else
        {
            memcpy( static_cast< void * >( buf ), static_cast< const void * >( &( this->impl->_bytes[ 0 ] ) ), static_cast< size_t >( length ) );
            this->DeleteBytes( length );
        }
    }
    
    void BinaryStream::Get( uint8_t * buf, uint64_t pos, uint64_t length )
    {
        if( this->impl->_stream.is_open() )
        {
            {
                std::ifstream::pos_type cur;
                
                cur = this->impl->_stream.tellg();
                
                this->impl->_stream.seekg( static_cast< std::ifstream::off_type >( pos ), std::ios::cur );
                this->impl->_stream.read( reinterpret_cast< char * >( buf ), static_cast< std::streamsize >( length ) );
                this->impl->_stream.seekg( cur, std::ios::beg );
            }
        }
        else
        {
            memcpy( static_cast< void * >( buf ), static_cast< const void * >( &( this->impl->_bytes[ static_cast< size_t >( pos ) ] ) ), static_cast< size_t >( length ) );
        }
    }
    
    void BinaryStream::DeleteBytes( uint64_t length )
    {
        if( this->impl->_stream.is_open() )
        {
            this->impl->_stream.seekg( static_cast< std::ifstream::off_type >( length ), std::ios::cur );
        }
        else
        {
            std::vector< uint8_t >( this->impl->_bytes.begin() + static_cast< std::vector< uint8_t >::difference_type >( length ), this->impl->_bytes.end() ).swap( this->impl->_bytes );
        }
    }
}

XS::PIMPL::Object< ISOBMFF::BinaryStream >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< ISOBMFF::BinaryStream >::IMPL::IMPL( const std::string & path ):
    _path( path )
{
	#ifdef _WIN32
	this->_stream.open( ISOBMFF::StringToWideString( path ), std::ios::binary );
	#else
    this->_stream.open( path, std::ios::binary );
	#endif
}

XS::PIMPL::Object< ISOBMFF::BinaryStream >::IMPL::IMPL( const std::vector< uint8_t > & bytes ):
    _bytes( bytes )
{}

XS::PIMPL::Object< ISOBMFF::BinaryStream >::IMPL::IMPL( const IMPL & o ):
    _bytes( o._bytes ),
    _path( o._path )
{
    std::ifstream::pos_type pos;
    
    if( o._stream.is_open() )
    {
		#ifdef _WIN32
		this->_stream.open( ISOBMFF::StringToWideString( this->_path ), std::ios::binary );
		#else
        this->_stream.open( this->_path, std::ios::binary );
		#endif

        if( this->_stream.good() == false )
        {
            return;
        }
        
        pos = o._stream.tellg();
        
        this->_stream.seekg( pos, std::ios::beg );
    }
}

XS::PIMPL::Object< ISOBMFF::BinaryStream >::IMPL::~IMPL( void )
{
    if( this->_stream.is_open() )
    {
        this->_stream.close();
    }
}
