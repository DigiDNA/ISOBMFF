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
 * @file        PIXI.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/PIXI.hpp>
#include <ISOBMFF/Utils.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::PIXI >::IMPL
{
    public:
        
        IMPL();
        IMPL( const IMPL & o );
        ~IMPL();
        
        std::vector< std::shared_ptr< ISOBMFF::PIXI::Channel > > _channels;
};

#define XS_PIMPL_CLASS ISOBMFF::PIXI
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    PIXI::PIXI(): FullBox( "pixi" )
    {}
    
    void PIXI::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint8_t count;
        uint8_t i;
        
        FullBox::ReadData( parser, stream );
        
        count = stream.ReadUInt8();
        
        for( i = 0; i < count; i++ )
        {
            this->AddChannel( std::make_shared< Channel >( stream ) );
        }
    }
    
    void PIXI::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        FullBox::WriteDescription( os, indentLevel );
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }
    
    std::vector< std::shared_ptr< DisplayableObject > > PIXI::GetDisplayableObjects() const
    {
        auto v( this->GetChannels() );
        
        return std::vector< std::shared_ptr< DisplayableObject > >( v.begin(), v.end() );
    }
    
    std::vector< std::pair< std::string, std::string > > PIXI::GetDisplayableProperties() const
    {
        auto props( Box::GetDisplayableProperties() );
        
        props.push_back( { "Channels", std::to_string( this->GetChannels().size() ) } );
        
        return props;
    }
    
    std::vector< std::shared_ptr< PIXI::Channel > > PIXI::GetChannels() const
    {
        return this->impl->_channels;
    }
    
    void PIXI::AddChannel( std::shared_ptr< Channel > array )
    {
        this->impl->_channels.push_back( array );
    }
}

XS::PIMPL::Object< ISOBMFF::PIXI >::IMPL::IMPL()
{}

XS::PIMPL::Object< ISOBMFF::PIXI >::IMPL::IMPL( const IMPL & o ):
    _channels( o._channels )
{}

XS::PIMPL::Object< ISOBMFF::PIXI >::IMPL::~IMPL()
{}

