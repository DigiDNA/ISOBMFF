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
 * @header      TKHD.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_TKHD_HPP
#define ISOBMFF_TKHD_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <ISOBMFF/Matrix.hpp>
#include <cstdint>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT TKHD: public FullBox, public XS::PIMPL::Object< TKHD >
    {
        public:
            
            using XS::PIMPL::Object< TKHD >::impl;
            
            TKHD( void );
            
            void                                                 ReadData( Parser & parser, BinaryStream & stream ) override;
            std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const override;
            
            uint64_t GetCreationTime( void )     const;
            uint64_t GetModificationTime( void ) const;
            uint32_t GetTrackID( void )          const;
            uint64_t GetDuration( void )         const;
            uint16_t GetLayer( void )            const;
            uint16_t GetAlternateGroup( void )   const;
            uint16_t GetVolume( void )           const;
            Matrix   GetMatrix( void )           const;
            float    GetWidth( void )            const;
            float    GetHeight( void )           const;
            
            void SetCreationTime( uint64_t value );
            void SetModificationTime( uint64_t value );
            void SetTrackID( uint32_t value );
            void SetDuration( uint64_t value );
            void SetLayer( uint16_t value );
            void SetAlternateGroup( uint16_t value );
            void SetVolume( uint16_t value );
            void SetMatrix( Matrix value );
            void SetWidth( float value );
            void SetHeight( float value );
    };
}

#endif /* ISOBMFF_TKHD_HPP */
