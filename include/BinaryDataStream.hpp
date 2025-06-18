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
 * @header      BinaryDataStream.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_BINARY_DATA_STREAM_HPP
#define ISOBMFF_BINARY_DATA_STREAM_HPP

#include <BinaryStream.hpp>
#include <string>
#include <iostream>
#include <cstdint>
#include <memory>
#include <algorithm>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT BinaryDataStream: public BinaryStream
    {
        public:

            BinaryDataStream();
            BinaryDataStream( const std::vector< uint8_t > & data );
            BinaryDataStream( const BinaryDataStream & o );
            BinaryDataStream( BinaryDataStream && o ) noexcept;

            virtual ~BinaryDataStream() override;

            BinaryDataStream & operator =( BinaryDataStream o );

            using BinaryStream::Read;

            void   Read( uint8_t * buf, size_t size )               override;
            void   Seek( std::streamoff offset, SeekDirection dir ) override;
            size_t Tell()                                     const override;

            ISOBMFF_EXPORT friend void swap( BinaryDataStream & o1, BinaryDataStream & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_BINARY_DATA_STREAM_HPP */
