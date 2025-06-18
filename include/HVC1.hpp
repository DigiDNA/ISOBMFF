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
 * @header      HVC1.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_HVC1_HPP
#define ISOBMFF_HVC1_HPP

#include <memory>
#include <algorithm>
#include <Macros.hpp>
#include <FullBox.hpp>
#include <Container.hpp>
#include <cstdint>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT HVC1: public FullBox, public Container
    {
        public:

            HVC1();
            HVC1( const HVC1 & o );
            HVC1( HVC1 && o ) noexcept;
            virtual ~HVC1() override;

            HVC1 & operator =( HVC1 o );

            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

            std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            uint16_t    GetDataReferenceIndex() const;
            uint16_t    GetWidth()              const;
            uint16_t    GetHeight()             const;
            uint32_t    GetHorizResolution()    const;
            uint32_t    GetVertResolution()     const;
            uint16_t    GetFrameCount()         const;
            std::string GetCompressorName()     const;
            uint16_t    GetDepth()              const;

            void SetDataReferenceIndex( uint16_t value );
            void SetWidth( uint16_t value );
            void SetHeight( uint16_t value );
            void SetHorizResolution( uint32_t value );
            void SetVertResolution( uint32_t value );
            void SetFrameCount( uint16_t value );
            void SetCompressorName( std::string value );
            void SetDepth( uint16_t value );

            void                                  AddBox( std::shared_ptr< Box > box ) override;
            std::vector< std::shared_ptr< Box > > GetBoxes() const override;

            ISOBMFF_EXPORT friend void swap( HVC1 & o1, HVC1 & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_HVC1_HPP */
