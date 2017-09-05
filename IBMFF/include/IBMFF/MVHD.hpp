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
 * @header      MVHD.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef IBMFF_MVHD_HPP
#define IBMFF_MVHD_HPP

#include <XS/PIMPL/Object.hpp>
#include <IBMFF/FullBox.hpp>
#include <IBMFF/Matrix.hpp>

namespace IBMFF
{
    class MVHD: public FullBox, public XS::PIMPL::Object< MVHD >
    {
        public:
            
            using XS::PIMPL::Object< MVHD >::impl;
            
            MVHD( void );
            
            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            
            uint64_t GetCreationTime( void )     const;
            uint64_t GetModificationTime( void ) const;
            uint32_t GetTimescale( void )        const;
            uint64_t GetDuration( void )         const;
            uint32_t GetRate( void )             const;
            uint16_t GetVolume( void )           const;
            Matrix   GetMatrix( void )           const;
            uint32_t GetNextTrackID( void )      const;
            
            void SetCreationTime( uint64_t value );
            void SetModificationTime( uint64_t value );
            void SetTimescale( uint32_t value );
            void SetDuration( uint64_t value );
            void SetRate( uint32_t value );
            void SetVolume( uint16_t value );
            void SetMatrix( const Matrix & value );
            void SetNextTrackID( uint32_t value );
    };
}

#endif /* IBMFF_MVHD_HPP */
