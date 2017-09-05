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
 * @file        ILOC.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <IBMFF/ILOC.hpp>
#include <IBMFF/Parser.hpp>
#include <cstdint>

template<>
class XS::PIMPL::Object< IBMFF::ILOC >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
};

#define XS_PIMPL_CLASS IBMFF::ILOC
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    ILOC::ILOC( void ): IBMFF::FullBox( "iloc" )
    {}
    
    void ILOC::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );
        
        if( this->GetVersion() == 0 )
        {
            
        }
        else
        {
            
        }
    }
    
    void ILOC::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string i( ( indentLevel + 1 ) * 4, ' ' );
        
        FullBox::WriteDescription( os, indentLevel );
    }
}

XS::PIMPL::Object< IBMFF::ILOC >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< IBMFF::ILOC >::IMPL::IMPL( const IMPL & o )
{
    ( void )o;
}

XS::PIMPL::Object< IBMFF::ILOC >::IMPL::~IMPL( void )
{}

