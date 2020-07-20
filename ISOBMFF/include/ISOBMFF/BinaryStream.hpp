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
#include <iostream>
#include <cstdint>
#include <vector>
#include <XS/PIMPL/Object.hpp>
#include <memory>
#include <algorithm>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/Matrix.hpp>

namespace ISOBMFF
{
    /*!
     * @class       BinaryStream
     * @abstract    Represents a stream of bytes, allowing reading/writing operations.
     * @discussion  Streams can either be backed by a standard C++ file stream,
     *              or by plain data.
     */
    class ISOBMFF_EXPORT BinaryStream: public XS::PIMPL::Object< BinaryStream >
    {
        public:
            
            using XS::PIMPL::Object< BinaryStream >::impl;
            
            /*!
             * @function    BinaryStream
             * @abstract    Default constructor - Creates an empty stream.
             */
            BinaryStream();
            
            /*!
             * @function    BinaryStream
             * @abstract    Creates a stream representing an existing file.
             */
            BinaryStream( const std::string & path );
            
            /*!
             * @function    BinaryStream
             * @abstract    Creates a stream from data bytes.
             * @param       bytes   The data bytes from which to create the stream.
             */
            BinaryStream( const std::vector< uint8_t > & bytes );
            
            /*!
             * @function    BinaryStream
             * @abstract    Creates a stream with data bytes from another stream.
             * @param       stream  The source stream.
             * @param       length  The number of bytes to read from the source stream.
             * @discussion  Bytes from the source-stream will be consumed.
             */
            BinaryStream( BinaryStream & stream, uint64_t length );
            
            /*!
             * @function    HasBytesAvailable
             * @abstract    Tests whether the stream has bytes available to read.
             * @result      True if the stream has bytes available, otherwise false.
             */
            bool HasBytesAvailable() const;
            
            /*!
             * @function    ReadUInt8
             * @abstract    Reads an 8-bits unsigned integer value from the stream.
             * @result      An 8-bits unsigned integer value.
             */
            uint8_t ReadUInt8();
            
            /*!
             * @function    ReadInt8
             * @abstract    Reads an 8-bits signed integer value from the stream.
             * @result      An 8-bits signed integer value.
             */
            int8_t ReadInt8();
            
            /*!
             * @function    ReadUInt16
             * @abstract    Reads a 16-bits unsigned integer value from the stream.
             * @result      A 16-bits unsigned integer value.
             * @discussion  Byte order is platform-specific.
             * @see         ReadBigEndianUInt16
             * @see         ReadLittleEndianUInt16
             */
            uint16_t ReadUInt16();
            
            /*!
             * @function    ReadInt16
             * @abstract    Reads a 16-bits signed integer value from the stream.
             * @result      A 16-bits signed integer value.
             * @discussion  Byte order is platform-specific.
             */
            int16_t ReadInt16();
            
            /*!
             * @function    ReadBigEndianUInt16
             * @abstract    Reads a 16-bits big-endian signed integer value from the stream.
             * @result      A 16-bits signed big-endian integer value.
             " @see         ReadLittleEndianUInt16
             */
            uint16_t ReadBigEndianUInt16();
            
            /*!
             * @function    ReadLittleEndianUInt16
             * @abstract    Reads a 16-bits little-endian signed integer value from the stream.
             * @result      A 16-bits signed little-endian integer value.
             " @see         ReadBigEndianUInt16
             */
            uint16_t ReadLittleEndianUInt16();
            
            /*!
             * @function    ReadUInt32
             * @abstract    Reads a 32-bits unsigned integer value from the stream.
             * @result      A 32-bits unsigned integer value.
             * @discussion  Byte order is platform-specific.
             * @see         ReadBigEndianUInt32
             * @see         ReadLittleEndianUInt32
             */
            uint32_t ReadUInt32();
            
            /*!
             * @function    ReadInt32
             * @abstract    Reads a 32-bits signed integer value from the stream.
             * @result      A 32-bits signed integer value.
             * @discussion  Byte order is platform-specific.
             */
            int32_t ReadInt32();
            
            /*!
             * @function    ReadBigEndianUInt32
             * @abstract    Reads a 32-bits big-endian unsigned integer value from the stream.
             * @result      A 32-bits unsigned integer value.
             * @see         ReadLittleEndianUInt32
             */
            uint32_t ReadBigEndianUInt32();
            
            /*!
             * @function    ReadLittleEndianUInt32
             * @abstract    Reads a 32-bits little-endian unsigned integer value from the stream.
             * @result      A 32-bits unsigned integer value.
             * @see         ReadBigEndianUInt32
             */
            uint32_t ReadLittleEndianUInt32();
            
            /*!
             * @function    ReadUInt64
             * @abstract    Reads a 64-bits unsigned integer value from the stream.
             * @result      A 64-bits unsigned integer value.
             * @discussion  Byte order is platform-specific.
             * @see         ReadBigEndianUInt64
             * @see         ReadLittleEndianUInt64
             */
            uint64_t ReadUInt64();
            
            /*!
             * @function    ReadInt64
             * @abstract    Reads a 64-bits signed integer value from the stream.
             * @result      A 64-bits signed integer value.
             * @discussion  Byte order is platform-specific
             */
            int64_t ReadInt64();
            
            /*!
             * @function    ReadBigEndianUInt64
             * @abstract    Reads a 64-bits big-endian unsigned integer value from the stream.
             * @result      A 64-bits unsigned integer value.
             * @see         ReadLittleEndianUInt64
             */
            uint64_t ReadBigEndianUInt64();
            
            /*!
             * @function    ReadLittleEndianUInt64
             * @abstract    Reads a 64-bits little-endian unsigned integer value from the stream.
             * @result      A 64-bits unsigned integer value.
             * @see         ReadBigEndianUInt64
             */
            uint64_t ReadLittleEndianUInt64();
            
            /*!
             * @function    ReadBigEndianFixedPoint
             * @abstract    Reads a big-endian fixed-point value from the stream.
             * @param       integerLength       The length of the integral part.
             * @param       fractionalLength    The length of the fractional part.
             * @result      The number as a floating-point value.
             */
            float ReadBigEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );
            
            /*!
             * @function    ReadLittleEndianFixedPoint
             * @abstract    Reads a little-endian fixed-point value from the stream.
             * @param       integerLength       The length of the integral part.
             * @param       fractionalLength    The length of the fractional part.
             * @result      The number as a floating-point value.
             */
            float ReadLittleEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );
            
            /*!
             * @function    ReadFourCC
             * @abstract    Reads a four-character code from the stream.
             * @result      The four-character code as a string.
             * @discussion  Four-character codes are 32-bits.
             */
            std::string ReadFourCC();
            
            /*!
             * @function    ReadNULLTerminatedString
             * @abstract    Reads a NULL-terminated string from the stream.
             * @result      The string value.
             */
            std::string ReadNULLTerminatedString();
            
            /*!
             * @function    ReadPascalString
             * @abstract    Reads a pascal string (length-prefixed) from the stream.
             * @result      The string value.
             */
            std::string ReadPascalString();
            
            /*!
             * @function    ReadMatrix
             * @abstract    Reads a Matrix object from the stream.
             * @result      The Matrix object.
             * @see         Matrix
             */
            Matrix ReadMatrix();
            
            /*!
             * @function    ReadAllData
             * @abstract    Reads all the data available in the stream.
             * @result      A vector of bytes remaining in the stream.
             */
            std::vector< uint8_t > ReadAllData();
            
            /*!
             * @function    Read
             * @abstract    Reads bytes from the stream.
             * @param       buf     The byte buffer to fill.
             * @param       length  The number of bytes to read from the stream.
             */
            void Read( uint8_t * buf, uint64_t length );
            
            /*!
             * @function    Get
             * @abstract    Gets bytes from the stream.
             * @param       buf     The byte buffer to fill.
             * @param       length  The number of bytes to get from the stream.
             * @discussion  When using this method, bytes won't be consumed.
             *              If the stream is backed by a file stream, this
             *              will seek back to the stream position before the
             *              call.
             */
            void Get( uint8_t * buf, uint64_t pos, uint64_t length );
            
            /*!
             * @function    DeleteBytes
             * @abstract    Removes bytes from the stream.
             * @param       length  The number of bytes to remove.
             * @discussion  If the stream is backed by a file stream, this
             *              will seek from the current positio.
             */
            void DeleteBytes( uint64_t length );
    };
}

#endif /* ISOBMFF_BINARY_STREAM_HPP */
