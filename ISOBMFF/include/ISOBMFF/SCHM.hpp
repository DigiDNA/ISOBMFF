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
 * @header      SCHM.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_SCHM_HPP
#define ISOBMFF_SCHM_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <string>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT SCHM: public FullBox, public XS::PIMPL::Object< SCHM >
    {
        public:
            
            using XS::PIMPL::Object< SCHM >::impl;
            
            SCHM( void );
            
            void                                                 ReadData( Parser & parser, BinaryStream & stream ) override;
            std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const override;
            
            std::string GetSchemeType( void )    const;
            uint32_t    GetSchemeVersion( void ) const;
            std::string GetSchemeURI( void )     const;
            
            void SetSchemeType( const std::string & value );
            void SetSchemeVersion( uint32_t value );
            void SetSchemeURI( const std::string & value );
    };
}

#endif /* ISOBMFF_SCHM_HPP */
