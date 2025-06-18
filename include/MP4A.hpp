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
 * @header      MP4A.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      https://github.com/leela9980
 */

#ifndef ISOBMFF_MP4A_HPP
#define ISOBMFF_MP4A_HPP

#include <memory>
#include <algorithm>
#include <Macros.hpp>
#include <FullBox.hpp>
#include <Container.hpp>
#include <string>
#include <cstdint>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT MP4A: public FullBox, public Container
    {
        public:

            MP4A();
            MP4A( const MP4A & o );
            MP4A( MP4A && o ) noexcept;
            virtual ~MP4A() override;

            MP4A & operator =( MP4A o );

            void   ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            uint16_t GetChannelCount() const;
            uint16_t GetSampleSize() const;
            uint32_t GetSampleRateRaw() const;
            float GetSampleRate() const;

            void SetChannelCount( uint16_t value );
            void SetSampleSize( uint16_t value );
            void SetSampleRateRaw( uint32_t value );

            void                                  AddBox( std::shared_ptr< Box > box ) override;
            std::vector< std::shared_ptr< Box > > GetBoxes() const override;
            ISOBMFF_EXPORT friend void swap( MP4A & o1, MP4A & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_MP4A_HPP */
