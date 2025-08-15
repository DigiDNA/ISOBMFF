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
 * @author      Boris Conforty - www.digidna.net
 */

#include <fstream>
#include <cmath>
#include <BinaryStream.hpp>

namespace ISOBMFF
{
    bool BinaryStream::HasBytesAvailable()
    {
        return this->AvailableBytes() > 0;
    }

    size_t BinaryStream::AvailableBytes()
    {
        size_t cur( this->Tell() );
        size_t pos;

        this->Seek( 0, SeekDirection::End );

        pos = this->Tell();

        this->Seek( numeric_cast< std::streamoff >( cur ), SeekDirection::Begin );

        return pos - cur;
    }

    void BinaryStream::Seek( std::streamoff offset )
    {
        this->Seek( offset, SeekDirection::Current );
    }

    void BinaryStream::Get( uint8_t * buf, uint64_t pos, size_t length )
    {
        size_t cur = this->Tell();

        this->Seek( pos, SeekDirection::Current );
        this->Read( buf, length );
        this->Seek( cur, SeekDirection::Begin );
    }

    std::vector< uint8_t > BinaryStream::Read( size_t size )
    {
        if (size > AvailableBytes())
        {
            throw std::runtime_error("Insufficient data available for read");
        }

        std::vector< uint8_t > data( size, 0 );

        if( size > 0 )
        {
            this->Read( &( data[ 0 ] ), size );
        }

        return data;
    }

    std::vector< uint8_t > BinaryStream::ReadAllData()
    {
        return this->Read( this->AvailableBytes() );
    }

    uint8_t BinaryStream::ReadUInt8()
    {
        uint8_t n;

        n = 0;

        this->Read( reinterpret_cast< uint8_t * >( &n ), 1 );

        return n;
    }

    int8_t BinaryStream::ReadInt8()
    {
        int8_t n;

        n = 0;

        this->Read( reinterpret_cast< uint8_t * >( &n ), 1 );

        return n;
    }

    uint16_t BinaryStream::ReadUInt16()
    {
        uint16_t n;

        n = 0;

        this->Read( reinterpret_cast< uint8_t * >( &n ), 2 );

        return n;
    }

    uint16_t BinaryStream::ReadBigEndianUInt16()
    {
        uint8_t  c[ 2 ];
        uint16_t n;
        uint16_t n1;
        uint16_t n2;

        c[ 0 ] = 0;
        c[ 1 ] = 0;

        this->Read( reinterpret_cast< uint8_t * >( c ), 2 );

        n1 = numeric_cast< uint16_t >( c[ 0 ] );
        n2 = numeric_cast< uint16_t >( c[ 1 ] );

        n  = numeric_cast< uint16_t >( n1 << 8 )
           | n2;

        return n;
    }

    uint16_t BinaryStream::ReadLittleEndianUInt16()
    {
        uint8_t  c[ 2 ];
        uint16_t n;
        uint16_t n1;
        uint16_t n2;

        c[ 0 ] = 0;
        c[ 1 ] = 0;

        this->Read( reinterpret_cast< uint8_t * >( c ), 2 );

        n1 = numeric_cast< uint16_t >( c[ 1 ] );
        n2 = numeric_cast< uint16_t >( c[ 0 ] );

        n  = numeric_cast< uint16_t >( n1 << 8 )
           | n2;

        return n;
    }

    uint32_t BinaryStream::ReadUInt32()
    {
        uint32_t n;

        n = 0;

        this->Read( reinterpret_cast< uint8_t * >( &n ), 4 );

        return n;
    }

    uint32_t BinaryStream::ReadBigEndianUInt32()
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

        n1 = numeric_cast< uint32_t >( c[ 0 ] );
        n2 = numeric_cast< uint32_t >( c[ 1 ] );
        n3 = numeric_cast< uint32_t >( c[ 2 ] );
        n4 = numeric_cast< uint32_t >( c[ 3 ] );

        n  = numeric_cast< uint32_t >( n1 << 24 )
           | numeric_cast< uint32_t >( n2 << 16 )
           | numeric_cast< uint32_t >( n3 << 8 )
           | n4;

        return n;
    }

    int32_t BinaryStream::ReadBigEndianInt32()
    {
        // read the value as uint
        uint32_t uint_value = ReadBigEndianUInt32();
        // cast it to int
        // extract the sign bit
        int32_t sign_bit = (uint_value & 0x80000000) ? -1 : 0;
        // Convert the uint32_t to int32_t
        int32_t int_value = (int32_t)(uint_value & 0x7FFFFFFF);
        // Apply the sign bit
        if (sign_bit == -1) {
            int_value = -int_value;
        }
        return int_value;
    }

    uint32_t BinaryStream::ReadLittleEndianUInt32()
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

        n1 = numeric_cast< uint32_t >( c[ 3 ] );
        n2 = numeric_cast< uint32_t >( c[ 2 ] );
        n3 = numeric_cast< uint32_t >( c[ 1 ] );
        n4 = numeric_cast< uint32_t >( c[ 0 ] );

        n  = numeric_cast< uint32_t >( n1 << 24 )
           | numeric_cast< uint32_t >( n2 << 16 )
           | numeric_cast< uint32_t >( n3 << 8 )
           | n4;

        return n;
    }

    uint64_t BinaryStream::ReadUInt64()
    {
        uint64_t n;

        n = 0;

        this->Read( reinterpret_cast< uint8_t * >( &n ), 8 );

        return n;
    }

    uint64_t BinaryStream::ReadBigEndianUInt64()
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

        n1 = numeric_cast< uint64_t >( c[ 0 ] );
        n2 = numeric_cast< uint64_t >( c[ 1 ] );
        n3 = numeric_cast< uint64_t >( c[ 2 ] );
        n4 = numeric_cast< uint64_t >( c[ 3 ] );
        n5 = numeric_cast< uint64_t >( c[ 4 ] );
        n6 = numeric_cast< uint64_t >( c[ 5 ] );
        n7 = numeric_cast< uint64_t >( c[ 6 ] );
        n8 = numeric_cast< uint64_t >( c[ 7 ] );

        n  = numeric_cast< uint64_t >( n1 << 56 )
           | numeric_cast< uint64_t >( n2 << 48 )
           | numeric_cast< uint64_t >( n3 << 40 )
           | numeric_cast< uint64_t >( n4 << 32 )
           | numeric_cast< uint64_t >( n5 << 24 )
           | numeric_cast< uint64_t >( n6 << 16 )
           | numeric_cast< uint64_t >( n7 << 8 )
           | n8;

        return n;
    }

    uint64_t BinaryStream::ReadLittleEndianUInt64()
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

        n1 = numeric_cast< uint64_t >( c[ 7 ] );
        n2 = numeric_cast< uint64_t >( c[ 6 ] );
        n3 = numeric_cast< uint64_t >( c[ 5 ] );
        n4 = numeric_cast< uint64_t >( c[ 4 ] );
        n5 = numeric_cast< uint64_t >( c[ 3 ] );
        n6 = numeric_cast< uint64_t >( c[ 2 ] );
        n7 = numeric_cast< uint64_t >( c[ 1 ] );
        n8 = numeric_cast< uint64_t >( c[ 0 ] );

        n  = numeric_cast< uint64_t >( n1 << 56 )
           | numeric_cast< uint64_t >( n2 << 48 )
           | numeric_cast< uint64_t >( n3 << 40 )
           | numeric_cast< uint64_t >( n4 << 32 )
           | numeric_cast< uint64_t >( n5 << 24 )
           | numeric_cast< uint64_t >( n6 << 16 )
           | numeric_cast< uint64_t >( n7 << 8 )
           | n8;

        return n;
    }

    float BinaryStream::ReadBigEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength )
    {
        uint32_t     n;
        unsigned int integer;
        unsigned int fractionalMask;
        float        fractional;

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
        fractional     = static_cast< float >( n & fractionalMask ) / static_cast< float >( 1 << fractionalLength );

        return static_cast< float >( integer ) + fractional;
    }

    float BinaryStream::ReadLittleEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength )
    {
        uint32_t     n;
        unsigned int integer;
        unsigned int fractionalMask;
        float        fractional;

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
        fractional     = static_cast< float >( n & fractionalMask ) / static_cast< float >( 1 << fractionalLength );

        return static_cast< float >( integer ) + fractional;
    }

    std::string BinaryStream::ReadFourCC()
    {
        uint8_t s[ 4 ];

        this->Read( s, 4 );

        return std::string( reinterpret_cast< char * >( s ), 4 );
    }

    std::string BinaryStream::ReadPascalString()
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

    std::string BinaryStream::ReadString( size_t length )
    {
        std::vector< char > cp( length + 1, 0 );

        this->Read( reinterpret_cast< uint8_t * >( &( cp[ 0 ] ) ), length );

        return &( cp[ 0 ] );
    }

    std::string BinaryStream::ReadNULLTerminatedString()
    {
        char        c;
        std::string s;

        while( 1 )
        {
            c = 0;

            this->Read( reinterpret_cast< uint8_t * >( &c ), 1 );

            if( c == 0 )
            {
                break;
            }

            s.append( 1, c );
        }

        return s;
    }

    Matrix BinaryStream::ReadMatrix()
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
}
