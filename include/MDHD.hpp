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
 * @header      MDHD.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_MDHD_HPP
#define ISOBMFF_MDHD_HPP

#include <memory>
#include <algorithm>
#include <Macros.hpp>
#include <FullBox.hpp>
#include <DisplayableObjectContainer.hpp>
#include <cstdint>
#include <vector>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT MDHD: public FullBox, public DisplayableObjectContainer
    {
        public:

            MDHD();
            MDHD( const MDHD & o );
            MDHD( MDHD && o ) noexcept;
            virtual ~MDHD() override;

            MDHD & operator =( MDHD o );

            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

            virtual std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            uint64_t GetCreationTime()     const;
            uint64_t GetModificationTime() const;
            uint32_t GetTimescale()        const;
            uint64_t GetDuration()         const;
            uint8_t  GetPad()              const;
            uint8_t  GetLanguage0()        const;
            uint8_t  GetLanguage1()        const;
            uint8_t  GetLanguage2()        const;
            uint16_t GetPredefined()       const;

            void SetCreationTime( uint64_t value );
            void SetModificationTime( uint64_t value );
            void SetTimescale( uint32_t value );
            void SetDuration( uint64_t value );
            void SetPad( uint8_t value );
            void SetLanguage0( uint8_t value );
            void SetLanguage1( uint8_t value );
            void SetLanguage2( uint8_t value );
            void SetPredefined( uint16_t value );

            ISOBMFF_EXPORT friend void swap( MDHD & o1, MDHD & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_MDHD_HPP */
