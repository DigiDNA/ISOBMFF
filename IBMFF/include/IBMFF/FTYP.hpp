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
 * @header      FTYP.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef IBMFF_FTYP_HPP
#define IBMFF_FTYP_HPP

#include <XS/PIMPL/Object.hpp>
#include <IBMFF/Box.hpp>
#include <string>
#include <vector>
#include <cstdint>

namespace IBMFF
{
    class FTYP: public Box, public XS::PIMPL::Object< FTYP >
    {
        public:
            
            using XS::PIMPL::Object< FTYP >::impl;
            
            FTYP( void );
            
            void ReadData( const Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            
            std::string                GetMajorBrand( void )       const;
            uint32_t                   GetMinorVersion( void )     const;
            std::vector< std::string > GetCompatibleBrands( void ) const;
            
            void SetMajorBrand( const std::string & value );
            void SetMinorVersion( uint32_t value );
            void SetCompatibleBrands( const std::vector< std::string > & value );
            void AddCompatibleBrand( const std::string & value );
    };
}

#endif /* IBMFF_FTYP_HPP */
