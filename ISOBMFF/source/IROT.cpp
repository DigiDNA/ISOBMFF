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
 * @file        IROT.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/IROT.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::IROT >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint8_t _angle;
};

#define XS_PIMPL_CLASS ISOBMFF::IROT
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    IROT::IROT( void ): ISOBMFF::Box( "irot" )
    {}
    
    void IROT::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint8_t u8;
        
        ( void )parser;
        
        u8 = stream.ReadUInt8();
        
        this->SetAngle( u8 & 0x3 );
    }
    
    void IROT::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string i( ( indentLevel + 1 ) * 4, ' ' );
        
        Box::WriteDescription( os, indentLevel );
        
        os << std::endl << i << "- Angle: " << static_cast< uint32_t >( this->GetAngle() ) * 90 << "°";
    }
    
    uint8_t IROT::GetAngle( void ) const
    {
        return this->impl->_angle;
    }
    
    void IROT::SetAngle( uint8_t value ) const
    {
        this->impl->_angle = value;
    }
}

XS::PIMPL::Object< ISOBMFF::IROT >::IMPL::IMPL( void ):
    _angle( 0 )
{}

XS::PIMPL::Object< ISOBMFF::IROT >::IMPL::IMPL( const IMPL & o ):
    _angle( o._angle )
{}

XS::PIMPL::Object< ISOBMFF::IROT >::IMPL::~IMPL( void )
{}

