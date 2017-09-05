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
 * @file        IDAT.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <IBMFF/IDAT.hpp>
#include <IBMFF/Parser.hpp>
#include <sstream>
#include <iomanip>

template<>
class XS::PIMPL::Object< IBMFF::IDAT >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
};

#define XS_PIMPL_CLASS IBMFF::IDAT
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    IDAT::IDAT( void ): IBMFF::Box( "idat" )
    {}
    
    void IDAT::ReadData( Parser & parser, BinaryStream & stream )
    {
        Box::ReadData( parser, stream );
    }
    
    void IDAT::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string            i( ( indentLevel + 1 ) * 4, ' ' );
        std::vector< uint8_t > data;
        
        Box::WriteDescription( os, indentLevel );
        
        data = this->GetData();
        
        if( data.size() > 0 )
        {
            os << std::endl
               << i << "- Bytes:";
            
            for( auto byte: data )
            {
                {
                    std::stringstream ss;
                    
                    ss << std::hex
                       << std::uppercase
                       << std::setfill( '0' )
                       << std::setw( 2 )
                       << static_cast< uint32_t >( byte );
                    os << " " << ss.str();
                }
            }
        }
    }
}

XS::PIMPL::Object< IBMFF::IDAT >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< IBMFF::IDAT >::IMPL::IMPL( const IMPL & o )
{
    ( void )o;
}

XS::PIMPL::Object< IBMFF::IDAT >::IMPL::~IMPL( void )
{}

