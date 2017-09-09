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
 * @file        COLR.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/COLR.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::COLR >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::string _colourType;
};

#define XS_PIMPL_CLASS ISOBMFF::COLR
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    COLR::COLR( void ): Box( "colr" )
    {}
    
    void COLR::ReadData( Parser & parser, BinaryStream & stream )
    {
        this->SetColourType( stream.ReadFourCC() );
        
        Box::ReadData( parser, stream );
    }
    
    void COLR::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string i( ( indentLevel + 1 ) * 4, ' ' );
        
        Box::WriteDescription( os, indentLevel );
        
        os << std::endl << i << "- Colour type: " << this->GetColourType();
    }
    
    std::string COLR::GetColourType( void ) const
    {
        return this->impl->_colourType;
    }
    
    void COLR::SetColourType( const std::string & value )
    {
        this->impl->_colourType = value;
    }
}

XS::PIMPL::Object< ISOBMFF::COLR >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< ISOBMFF::COLR >::IMPL::IMPL( const IMPL & o ):
    _colourType( o._colourType )
{}

XS::PIMPL::Object< ISOBMFF::COLR >::IMPL::~IMPL( void )
{}

