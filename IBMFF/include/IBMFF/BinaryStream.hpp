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
 * @header      BinaryStream.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef IBMFF_BINARY_STREAM_HPP
#define IBMFF_BINARY_STREAM_HPP

#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <XS/PIMPL/Object.hpp>
#include <IBMFF/Matrix.hpp>

namespace IBMFF
{
    class BinaryStream: public XS::PIMPL::Object< BinaryStream >
    {
        public:
            
            using XS::PIMPL::Object< BinaryStream >::impl;
            
            BinaryStream( void );
            BinaryStream( std::string path );
            BinaryStream( BinaryStream & stream, uint64_t length );
            
            bool HasBytesAvailable( void ) const;
            
            uint8_t ReadUInt8( void );
            int8_t  ReadInt8( void );
            
            uint16_t ReadUInt16( void );
            int16_t  ReadInt16( void );
            uint16_t ReadBigEndianUInt16( void );
            uint16_t ReadLittleEndianUInt16( void );
            
            uint32_t ReadUInt32( void );
            int32_t  ReadInt32( void );
            uint32_t ReadBigEndianUInt32( void );
            uint32_t ReadLittleEndianUInt32( void );
            
            uint64_t ReadUInt64( void );
            int64_t  ReadInt64( void );
            uint64_t ReadBigEndianUInt64( void );
            uint64_t ReadLittleEndianUInt64( void );
            
            float ReadBigEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );
            float ReadLittleEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );
            
            std::string ReadFourCC( void );
            std::string ReadNULLTerminatedString( void );
            std::string ReadPascalString( void );
            
            Matrix ReadMatrix( void );
            
            std::vector< uint8_t > ReadAllData( void );
            
            void Read( uint8_t * buf, uint64_t length );
            void Get( uint8_t * buf, uint64_t pos, uint64_t length );
            void DeleteBytes( uint64_t length );
    };
}

#endif /* IBMFF_BINARY_STREAM_HPP */
