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
 * @header      BinaryStream.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com
 */

#ifndef IBMFF_BINARY_STREAM_HPP
#define IBMFF_BINARY_STREAM_HPP

#include <string>
#include <iostream>
#include <cstdint>
#include <XS/PIMPL/Object.hpp>

namespace IBMFF
{
    class BinaryStream: XS::PIMPL::Object< BinaryStream >
    {
        public:
            
            using XS::PIMPL::Object< BinaryStream >::impl;
            
            BinaryStream( void );
            BinaryStream( std::string path );
            
            uint8_t ReadUnsignedChar( void );
            int8_t  ReadSignedChar( void );
            
            uint16_t ReadUnsignedShort( void );
            int16_t  ReadSignedShort( void );
            uint16_t ReadBigEndianUnsignedShort( void );
            uint16_t ReadLittleEndianUnsignedShort( void );
            
            uint32_t ReadUnsignedInteger( void );
            int32_t  ReadSignedInteger( void );
            uint32_t ReadBigEndianUnsignedInteger( void );
            uint32_t ReadLittleEndianUnsignedInteger( void );
            
            uint64_t ReadUnsignedLong( void );
            int64_t  ReadSignedLong( void );
            uint64_t ReadBigEndianUnsignedLong( void );
            uint64_t ReadLittleEndianUnsignedLong( void );
            
            float ReadBigEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );
            float ReadLittleEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );
            
            std::string ReadNULLTerminatedString( void );
            
            bool IsGood( void ) const;
            bool IsEOF( void ) const;
            bool IsFail( void ) const;
            bool IsBad( void ) const;
            
            int Peek( void );
            int Get( void );
            int Sync( void );
            
            std::streampos TellG( void );
            
            std::streamsize ReadSome( char * s, std::streamsize n );
            std::streamsize GCount( void ) const;
            
            std::istream & Get( char & c );
            std::istream & Get( char * s, std::streamsize n );
            std::istream & Get( char * s, std::streamsize n, char delim );
            std::istream & Get( std::streambuf & sb );
            std::istream & Get( std::streambuf & sb, char delim );
            std::istream & GetLine( char * s, std::streamsize n );
            std::istream & GetLine( char * s, std::streamsize n, char delim );
            std::istream & Ignore( std::streamsize n = 1, int delim = EOF );
            std::istream & Read( char * s, std::streamsize n );
            std::istream & PutBack( char c );
            std::istream & Unget( void );
            std::istream & SeekG( std::streampos pos );
            std::istream & SeekG( std::streamoff off, std::ios_base::seekdir dir );
    };
}

#endif /* IBMFF_BINARY_STREAM_HPP */
