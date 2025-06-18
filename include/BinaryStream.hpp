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
 * @header      BinaryStream.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_BINARY_STREAM_HPP
#define ISOBMFF_BINARY_STREAM_HPP

#include <string>
#include <cstdint>
#include <vector>
#include <type_traits>
#include <Casts.hpp>
#include <Macros.hpp>
#include <Matrix.hpp>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT BinaryStream
    {
        public:

            enum class SeekDirection
            {
                Current,
                Begin,
                End
            };

            virtual ~BinaryStream() = default;

            virtual void   Read( uint8_t * buf, size_t size )               = 0;
            virtual size_t Tell()                                     const = 0;
            virtual void   Seek( std::streamoff offset, SeekDirection dir ) = 0;

            bool   HasBytesAvailable();
            size_t AvailableBytes();

            void Seek( std::streamoff offset );

            template< typename T, typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value >::type * = nullptr >
            void Seek( T offset )
            {
                this->Seek( numeric_cast< std::streamoff >( offset ) );
            }

            template< typename T, typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value >::type * = nullptr >
            void Seek( T offset, SeekDirection dir )
            {
                this->Seek( numeric_cast< std::streamoff >( offset ), dir );
            }

            void Get( uint8_t * buf, uint64_t pos, size_t length );

            std::vector< uint8_t > Read( size_t size );
            std::vector< uint8_t > ReadAllData();

            uint8_t ReadUInt8();
            int8_t  ReadInt8();

            uint16_t ReadUInt16();
            uint16_t ReadBigEndianUInt16();
            uint16_t ReadLittleEndianUInt16();

            uint32_t ReadUInt32();
            uint32_t ReadBigEndianUInt32();
            uint32_t ReadLittleEndianUInt32();
            int32_t ReadBigEndianInt32();

            uint64_t ReadUInt64();
            uint64_t ReadBigEndianUInt64();
            uint64_t ReadLittleEndianUInt64();

            float ReadBigEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );
            float ReadLittleEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );

            std::string ReadFourCC();
            std::string ReadPascalString();
            std::string ReadString( size_t length );
            std::string ReadNULLTerminatedString();

            Matrix ReadMatrix();
    };
}

#endif /* ISOBMFF_BINARY_STREAM_HPP */
