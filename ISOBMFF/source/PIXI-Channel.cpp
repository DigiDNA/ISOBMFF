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
 * @file        PIXI-Channel.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/PIXI.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::PIXI::Channel >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint8_t _bitsPerChannel;
};

#define XS_PIMPL_CLASS ISOBMFF::PIXI::Channel
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    PIXI::Channel::Channel( void )
    {}
    
    PIXI::Channel::Channel( BinaryStream & stream )
    {
        this->SetBitsPerChannel( stream.ReadUInt8() );
    }
    
    std::string PIXI::Channel::GetName( void ) const
    {
        return "Channel";
    }
    
    uint8_t PIXI::Channel::GetBitsPerChannel( void ) const
    {
        return this->impl->_bitsPerChannel;
    }
    
    void PIXI::Channel::SetBitsPerChannel( uint8_t value )
    {
        this->impl->_bitsPerChannel = value;
    }
    
    std::vector< std::pair< std::string, std::string > > PIXI::Channel::GetDisplayableProperties( void ) const
    {
        return
        {
            { "Bits per channel", std::to_string( this->GetBitsPerChannel() ) },
        };
    }
}

XS::PIMPL::Object< ISOBMFF::PIXI::Channel >::IMPL::IMPL( void ):
    _bitsPerChannel( 0 )
{}

XS::PIMPL::Object< ISOBMFF::PIXI::Channel >::IMPL::IMPL( const IMPL & o ):
    _bitsPerChannel( o._bitsPerChannel )
{}

XS::PIMPL::Object< ISOBMFF::PIXI::Channel >::IMPL::~IMPL( void )
{}

