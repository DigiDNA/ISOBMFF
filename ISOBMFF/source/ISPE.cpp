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
 * @file        ISPE.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/ISPE.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::ISPE >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint32_t _displayWidth;
        uint32_t _displayHeight;
};

#define XS_PIMPL_CLASS ISOBMFF::ISPE
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    ISPE::ISPE( void ): FullBox( "ispe" )
    {}
    
    void ISPE::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );
        
        this->SetDisplayWidth( stream.ReadBigEndianUInt32() );
        this->SetDisplayHeight( stream.ReadBigEndianUInt32() );
    }
    
	std::vector< std::pair< std::string, std::string > > ISPE::GetDisplayableProperties( void ) const
    {
        auto props( FullBox::GetDisplayableProperties() );
        
        props.push_back( { "Display width",  std::to_string( this->GetDisplayWidth() ) } );
        props.push_back( { "Display height", std::to_string( this->GetDisplayHeight() ) } );
        
        return props;
    }
    
    uint32_t ISPE::GetDisplayWidth( void ) const
    {
        return this->impl->_displayWidth;
    }
    
    uint32_t ISPE::GetDisplayHeight( void ) const
    {
        return this->impl->_displayHeight;
    }
    
    void ISPE::SetDisplayWidth( uint32_t value )
    {
        this->impl->_displayWidth = value;
    }
    
    void ISPE::SetDisplayHeight( uint32_t value )
    {
        this->impl->_displayHeight = value;
    }
}

XS::PIMPL::Object< ISOBMFF::ISPE >::IMPL::IMPL( void ):
    _displayWidth( 0 ),
    _displayHeight( 0 )
{}

XS::PIMPL::Object< ISOBMFF::ISPE >::IMPL::IMPL( const IMPL & o ):
    _displayWidth( o._displayWidth ),
    _displayHeight( o._displayHeight )
{}

XS::PIMPL::Object< ISOBMFF::ISPE >::IMPL::~IMPL( void )
{}

