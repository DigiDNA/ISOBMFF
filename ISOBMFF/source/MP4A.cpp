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
 * @file        MP4A.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      https://github.com/leela9980
 */

#include <ISOBMFF/MP4A.hpp>
#include <ISOBMFF/ContainerBox.hpp>

namespace ISOBMFF
{
    class MP4A::IMPL
    {
        public:
            
            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();
            
            uint16_t    _channelcount;
            uint16_t    _samplesize;
            uint32_t    _samplerate;
            std::vector< std::shared_ptr< Box > > _boxes;
    };  
    
    MP4A::MP4A():
        FullBox( "mp4a" ),
        impl( std::make_unique< IMPL >() )
    {}
    
    MP4A::MP4A( const MP4A & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}
    
    MP4A::MP4A( MP4A && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }
    
    MP4A::~MP4A()
    {}
    
    MP4A & MP4A::operator =( MP4A o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );
        
        return *( this );
    }
    
    void swap( MP4A & o1, MP4A & o2 )
    {
        using std::swap;
        
        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }
    
    void MP4A::ReadData( Parser & parser, BinaryStream & stream )
    {
        ContainerBox container( "????" );
        
        // const unsigned int(8)[6] reserved = 0;
        stream.ReadUInt8();
        stream.ReadUInt8();
        stream.ReadUInt8();
        stream.ReadUInt8();
        stream.ReadUInt8();
        stream.ReadUInt8();
        // const unsigned int(16) data_reference_index;
        stream.ReadUInt16();
        // const unsigned int(32)[2] reserved = 0;
        stream.ReadUInt32();
        stream.ReadUInt32();

        // unsigned int(16) channelcount;
        SetChannelCount( stream.ReadBigEndianUInt16() );
        // template unsigned int(16) samplesize = 16;
        SetSampleSize( stream.ReadBigEndianUInt16() );

        // unsigned int(16) pre_defined = 0;
        stream.ReadUInt16();
        // unsigned int(16) reserved = 0;
        stream.ReadUInt16();

        // template unsigned int(32) samplerate = { default samplerate of media } << 16;
        uint32_t sampleRateFixed =  stream.ReadBigEndianUInt32();
        SetSampleRate( (sampleRateFixed >> 16) + ((sampleRateFixed & 0xFFFF) / 65536) );

        container.ReadData( parser, stream );
        this->impl->_boxes = container.GetBoxes();
    }
    
    std::vector< std::pair< std::string, std::string > > MP4A::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );
        
        props.push_back( { "Channel Count", std::to_string(this->GetChannelCount()) } );
        props.push_back( { "Sample Size", std::to_string(this->GetSampleSize()) } );
        props.push_back( { "Sample Rate", std::to_string(this->GetSampleRate()) } );
        
        return props;
    }

    void MP4A::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        FullBox::WriteDescription( os, indentLevel );
        Container::WriteBoxes( os, indentLevel );
    }
    
    uint16_t MP4A::GetChannelCount() const
    {
        return this->impl->_channelcount;
    }
    
    uint16_t MP4A::GetSampleSize() const
    {
        return this->impl->_samplesize;
    }
    
    uint32_t MP4A::GetSampleRate() const
    {
        return this->impl->_samplerate;
    }

    void MP4A::SetChannelCount( uint16_t channelcount )
    {
        this->impl->_channelcount = channelcount;
    }

    void MP4A::SetSampleSize( uint16_t samplesize )
    {
        this->impl->_samplesize = samplesize;
    }

    void MP4A::SetSampleRate( uint32_t samplerate )
    {
        this->impl->_samplerate = samplerate;
    }

    void MP4A::AddBox( std::shared_ptr< Box > box )
    {
        if( box != nullptr )
        {
            this->impl->_boxes.push_back( box );
        }
    }

    std::vector< std::shared_ptr< Box > > MP4A::GetBoxes() const
    {
        return this->impl->_boxes;
    }

    MP4A::IMPL::IMPL():
        _channelcount( 0 ),
        _samplesize( 0 ),
        _samplerate( 0 )
    {
    }

    MP4A::IMPL::IMPL( const IMPL & o ):
        _channelcount( o._channelcount ),
        _samplesize( o._samplesize ),
        _samplerate( o._samplerate )
    {
    }

    MP4A::IMPL::~IMPL()
    {}
}
