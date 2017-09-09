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
 * @header      IPMA.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_IPMA_HPP
#define ISOBMFF_IPMA_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <vector>

namespace ISOBMFF
{
    class IPMA: public FullBox, public XS::PIMPL::Object< IPMA >
    {
        public:
            
            using XS::PIMPL::Object< IPMA >::impl;
            
            IPMA( void );
            
            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            
            class Entry: public XS::PIMPL::Object< Entry >
            {
                public:
                    
                    using XS::PIMPL::Object< Entry >::impl;
                    
                    Entry( void );
                    Entry( BinaryStream & stream, const IPMA & ipma );
                    
                    void WriteDescription( std::ostream & os, std::size_t indentLevel ) const;
                    
                    friend std::ostream & operator << ( std::ostream & os, const Entry & entry );
            };
            
            std::vector< Entry > GetEntries( void ) const;
            void                 AddEntry( const Entry & entry );
    };
}

#endif /* ISOBMFF_IPMA_HPP */
