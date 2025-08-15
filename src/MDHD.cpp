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
 * @file        MDHD.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <MDHD.hpp>

namespace ISOBMFF
{
    class MDHD::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint64_t _creationTime;
            uint64_t _modificationTime;
            uint32_t _timescale;
            uint64_t _duration;
            uint8_t  _pad;
            uint8_t  _language0;
            uint8_t  _language1;
            uint8_t  _language2;
            uint16_t _predefined;
    };

    MDHD::MDHD():
        FullBox( "mdhd" ),
        impl( std::make_unique< IMPL >() )
    {}

    MDHD::MDHD( const MDHD & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    MDHD::MDHD( MDHD && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    MDHD::~MDHD()
    {}

    MDHD & MDHD::operator =( MDHD o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( MDHD & o1, MDHD & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void MDHD::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint64_t u64;
        uint32_t u32;
        uint16_t u16;

        FullBox::ReadData( parser, stream );

        if( this->GetVersion() == 1 )
        {
            u64 = stream.ReadBigEndianUInt64();
        }
        else
        {
            u64 = stream.ReadBigEndianUInt32();
        }

        this->SetCreationTime( u64 );

        if( this->GetVersion() == 1 )
        {
            u64 = stream.ReadBigEndianUInt64();
        }
        else
        {
            u64 = stream.ReadBigEndianUInt32();
        }

        this->SetModificationTime( u64 );

        u32 = stream.ReadBigEndianUInt32();

        this->SetTimescale( u32 );

        if( this->GetVersion() == 1 )
        {
            u64 = stream.ReadBigEndianUInt64();
        }
        else
        {
            u64 = stream.ReadBigEndianUInt32();
        }

        this->SetDuration( u64 );

       u16 = stream.ReadBigEndianUInt16();

       this->SetPad( u16 >> 15 );
       this->SetLanguage0( ( u16 >> 10 ) & 0b11111 );
       this->SetLanguage1( ( u16 >>  5 ) & 0b11111 );
       this->SetLanguage2( ( u16 >>  0 ) & 0b11111 );

       u16 = stream.ReadBigEndianUInt16();

       this->SetPredefined( u16 );
    }

    void MDHD::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        FullBox::WriteDescription( os, indentLevel );
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }

    std::vector< std::shared_ptr< DisplayableObject > > MDHD::GetDisplayableObjects() const
    {
        return std::vector< std::shared_ptr< DisplayableObject > >{};
    }

    std::vector< std::pair< std::string, std::string > > MDHD::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

         props.push_back( { "Creation time",      std::to_string( this->GetCreationTime() ) } );
         props.push_back( { "Modification time",  std::to_string( this->GetModificationTime() ) } );
         props.push_back( { "Timescale",          std::to_string( this->GetTimescale() ) } );
         props.push_back( { "Duration",           std::to_string( this->GetDuration() ) } );
         props.push_back( { "Pad",                std::to_string( this->GetPad() ) } );
         props.push_back( { "Language0",          std::to_string( this->GetLanguage0() ) } );
         props.push_back( { "Language1",          std::to_string( this->GetLanguage1() ) } );
         props.push_back( { "Language2",          std::to_string( this->GetLanguage2() ) } );
         props.push_back( { "Predefined",         std::to_string( this->GetPredefined() ) } );

        return props;
    }

    uint64_t MDHD::GetCreationTime() const
    {
        return this->impl->_creationTime;
    }

    uint64_t MDHD::GetModificationTime() const
    {
        return this->impl->_modificationTime;
    }

    uint32_t MDHD::GetTimescale() const
    {
        return this->impl->_timescale;
    }

    uint64_t MDHD::GetDuration() const
    {
        return this->impl->_duration;
    }

    uint8_t MDHD::GetPad() const
    {
        return this->impl->_pad;
    }

    uint8_t MDHD::GetLanguage0() const
    {
        return this->impl->_language0;
    }

    uint8_t MDHD::GetLanguage1() const
    {
        return this->impl->_language1;
    }

    uint8_t MDHD::GetLanguage2() const
    {
        return this->impl->_language2;
    }

    uint16_t MDHD::GetPredefined() const
    {
        return this->impl->_predefined;
    }

    void MDHD::SetCreationTime( uint64_t value )
    {
        this->impl->_creationTime = value;
    }

    void MDHD::SetModificationTime( uint64_t value )
    {
        this->impl->_modificationTime = value;
    }

    void MDHD::SetTimescale( uint32_t value )
    {
        this->impl->_timescale = value;
    }

    void MDHD::SetDuration( uint64_t value )
    {
        this->impl->_duration = value;
    }

    void MDHD::SetPad( uint8_t value )
    {
        this->impl->_pad = value;
    }

    void MDHD::SetLanguage0( uint8_t value )
    {
        this->impl->_language0 = value;
    }

    void MDHD::SetLanguage1( uint8_t value )
    {
        this->impl->_language1 = value;
    }

    void MDHD::SetLanguage2( uint8_t value )
    {
        this->impl->_language2 = value;
    }

    void MDHD::SetPredefined( uint16_t value )
    {
        this->impl->_predefined = value;
    }


    MDHD::IMPL::IMPL():
        _creationTime( 0 ),
        _modificationTime( 0 ),
        _timescale( 0 ),
        _duration( 0 ),
        _pad( 0 ),
        _language0( 0 ),
        _language1( 0 ),
        _language2( 0 ),
        _predefined( 0 )
    {}

    MDHD::IMPL::IMPL( const IMPL & o ):
        _creationTime( o._creationTime ),
        _modificationTime( o._modificationTime ),
        _timescale( o._timescale ),
        _duration( o._duration ),
        _pad( o._pad ),
        _language0( o._language0 ),
        _language1( o._language1 ),
        _language2( o._language2 ),
        _predefined( o._predefined )
    {}

    MDHD::IMPL::~IMPL()
    {}
}
