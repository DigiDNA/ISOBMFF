/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com
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
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com
 */

#include <IBMFF/BinaryStream.hpp>
#include <fstream>
#include <cmath>

template<>
class XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const std::string & path );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::ifstream _stream;
        std::string   _path;
};

#define XS_PIMPL_CLASS IBMFF::BinaryStream
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    BinaryStream::BinaryStream( void ): XS::PIMPL::Object< BinaryStream >()
    {}
    
    BinaryStream::BinaryStream( std::string path ): XS::PIMPL::Object< BinaryStream >( path )
    {}
    
    uint8_t BinaryStream::ReadUnsignedChar( void )
    {
        uint8_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< char * >( &n ), 1 );
        
        return n;
    }
    
    int8_t BinaryStream::ReadSignedChar( void )
    {
        int8_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< char * >( &n ), 1 );
        
        return n;
    }
    
    uint16_t BinaryStream::ReadUnsignedShort( void )
    {
        uint16_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< char * >( &n ), 2 );
        
        return n;
    }
    
    int16_t BinaryStream::ReadSignedShort( void )
    {
        int16_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< char * >( &n ), 2 );
        
        return n;
    }
    
    uint16_t BinaryStream::ReadBigEndianUnsignedShort( void )
    {
        uint8_t  c[ 2 ];
        uint16_t n;
        uint16_t n1;
        uint16_t n2;
        
        c[ 0 ] = 0;
        c[ 1 ] = 0;
        
        this->Read( reinterpret_cast< char * >( c ), 2 );
        
        n1 = static_cast< uint16_t >( c[ 0 ] );
        n2 = static_cast< uint16_t >( c[ 1 ] );
        
        n  = static_cast< uint16_t >( n1 << 8 )
           | n2;
        
        return n;
    }
    
    uint16_t BinaryStream::ReadLittleEndianUnsignedShort( void )
    {
        uint8_t  c[ 2 ];
        uint16_t n;
        uint16_t n1;
        uint16_t n2;
        
        c[ 0 ] = 0;
        c[ 1 ] = 0;
        
        this->Read( reinterpret_cast< char * >( c ), 2 );
        
        n1 = static_cast< uint16_t >( c[ 1 ] );
        n2 = static_cast< uint16_t >( c[ 0 ] );
        
        n  = static_cast< uint16_t >( n1 << 8 )
           | n2;
        
        return n;
    }
    
    uint32_t BinaryStream::ReadUnsignedInteger( void )
    {
        uint32_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< char * >( &n ), 4 );
        
        return n;
    }
    
    int32_t BinaryStream::ReadSignedInteger( void )
    {
        int32_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< char * >( &n ), 4 );
        
        return n;
    }
    
    uint32_t BinaryStream::ReadBigEndianUnsignedInteger( void )
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
        
        this->Read( reinterpret_cast< char * >( c ), 4 );
        
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
    
    uint32_t BinaryStream::ReadLittleEndianUnsignedInteger( void )
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
        
        this->Read( reinterpret_cast< char * >( c ), 4 );
        
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
    
    uint64_t BinaryStream::ReadUnsignedLong( void )
    {
        uint64_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< char * >( &n ), 8 );
        
        return n;
    }
    
    int64_t BinaryStream::ReadSignedLong( void )
    {
        int64_t n;
        
        n = 0;
        
        this->Read( reinterpret_cast< char * >( &n ), 8 );
        
        return n;
    }
    
    uint64_t BinaryStream::ReadBigEndianUnsignedLong( void )
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
        
        this->Read( reinterpret_cast< char * >( c ), 8 );
        
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
    
    uint64_t BinaryStream::ReadLittleEndianUnsignedLong( void )
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
        
        this->Read( reinterpret_cast< char * >( c ), 8 );
        
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
            n = this->ReadBigEndianUnsignedShort();
        }
        else
        {
            n = this->ReadBigEndianUnsignedInteger();
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
            n = this->ReadLittleEndianUnsignedShort();
        }
        else
        {
            n = this->ReadLittleEndianUnsignedInteger();
        }
        
        integer        = n >> fractionalLength;
        fractionalMask = static_cast< unsigned int >( pow( 2, fractionalLength ) - 1 );
        fractional     = ( n & fractionalMask ) / ( 1 << fractionalLength );
        
        return integer + fractional;
    }
    
    std::string BinaryStream::ReadNULLTerminatedString( void )
    {
        char        c;
        std::string s;
        
        while( 1 )
        {
            c = 0;
            
            this->Read( &c, 1 );
            
            if( c == 0 )
            {
                break;
            }
            
            s.append( 1, c );
        }
        
        return s;
    }
    
    bool BinaryStream::IsGood( void ) const
    {
        return this->impl->_stream.good();
    }
    
    bool BinaryStream::IsEOF( void ) const
    {
        return this->impl->_stream.eof();
    }
    
    bool BinaryStream::IsFail( void ) const
    {
        return this->impl->_stream.fail();
    }
    
    bool BinaryStream::IsBad( void ) const
    {
        return this->impl->_stream.bad();
    }
    
    int BinaryStream::Peek( void )
    {
        return this->impl->_stream.peek();
    }
    
    int BinaryStream::Get( void )
    {
        return this->impl->_stream.get();
    }
    
    int BinaryStream::Sync( void )
    {
        return this->impl->_stream.sync();
    }
    
    std::streampos BinaryStream::TellG( void )
    {
        return this->impl->_stream.tellg();
    }
    
    std::streamsize BinaryStream::ReadSome( char * s, std::streamsize n )
    {
        return this->impl->_stream.readsome( s, n );
    }
    
    std::streamsize BinaryStream::GCount( void ) const
    {
        return this->impl->_stream.gcount();
    }
    
    std::istream & BinaryStream::Get( char & c )
    {
        return this->impl->_stream.get( c );
    }
    
    std::istream & BinaryStream::Get( char * s, std::streamsize n )
    {
        return this->impl->_stream.get( s, n );
    }
    
    std::istream & BinaryStream::Get( char * s, std::streamsize n, char delim )
    {
        return this->impl->_stream.get( s, n, delim );
    }
    
    std::istream & BinaryStream::Get( std::streambuf & sb )
    {
        return this->impl->_stream.get( sb );
    }
    
    std::istream & BinaryStream::Get( std::streambuf & sb, char delim )
    {
        return this->impl->_stream.get( sb, delim );
    }
    
    std::istream & BinaryStream::GetLine( char * s, std::streamsize n )
    {
        return this->impl->_stream.getline( s, n );
    }
    
    std::istream & BinaryStream::GetLine( char * s, std::streamsize n, char delim )
    {
        return this->impl->_stream.getline( s, n, delim );
    }
    
    std::istream & BinaryStream::Ignore( std::streamsize n, int delim )
    {
        return this->impl->_stream.ignore( n, delim );
    }
    
    std::istream & BinaryStream::Read( char * s, std::streamsize n )
    {
        return this->impl->_stream.read( s, n );
    }
    
    std::istream & BinaryStream::PutBack( char c )
    {
        return this->impl->_stream.putback( c );
    }
    
    std::istream & BinaryStream::Unget( void )
    {
        return this->impl->_stream.unget();
    }
    
    std::istream & BinaryStream::SeekG( std::streampos pos )
    {
        return this->impl->_stream.seekg( pos );
    }
    
    std::istream & BinaryStream::SeekG( std::streamoff off, std::ios_base::seekdir dir )
    {
        return this->impl->_stream.seekg( off, dir );
    }
}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::IMPL( const std::string & path ):
    _path( path )
{
    this->_stream.open( this->_path, std::ios::binary | std::ios::in );
}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::IMPL( const IMPL & o ): IMPL( o._path )
{}

XS::PIMPL::Object< IBMFF::BinaryStream >::IMPL::~IMPL( void )
{
    if( this->_stream.is_open() )
    {
        this->_stream.close();
    }
}
