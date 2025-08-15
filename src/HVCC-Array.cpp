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
 * @file        HVCC-Array.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <HVCC.hpp>

namespace ISOBMFF
{
    class HVCC::Array::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            bool                                             _arrayCompleteness;
            uint8_t                                          _nalUnitType;
            std::vector< std::shared_ptr< Array::NALUnit > > _nalUnits;
    };

    HVCC::Array::Array():
        impl( std::make_unique< IMPL >() )
    {}

    HVCC::Array::Array( BinaryStream & stream ):
        impl( std::make_unique< IMPL >() )
    {
        uint8_t  u8;
        uint16_t count;
        uint16_t i;

        u8 = stream.ReadUInt8();

        this->SetArrayCompleteness( ( u8 & 0x80 ) != 0 );
        this->SetNALUnitType( u8 & 0x3F );

        count = stream.ReadBigEndianUInt16();

        for( i = 0; i < count; i++ )
        {
            this->AddNALUnit( std::make_shared< NALUnit >( stream ) );
        }
    }

    HVCC::Array::Array( const HVCC::Array & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    HVCC::Array::Array( HVCC::Array && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    HVCC::Array::~Array()
    {}

    HVCC::Array & HVCC::Array::operator =( HVCC::Array o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( HVCC::Array & o1, HVCC::Array & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string HVCC::Array::GetName() const
    {
        return "Array";
    }

    bool HVCC::Array::GetArrayCompleteness() const
    {
        return this->impl->_arrayCompleteness;
    }

    uint8_t HVCC::Array::GetNALUnitType() const
    {
        return this->impl->_nalUnitType;
    }

    void HVCC::Array::SetArrayCompleteness( bool value )
    {
        this->impl->_arrayCompleteness = value;
    }

    void HVCC::Array::SetNALUnitType( uint8_t value )
    {
        this->impl->_nalUnitType = value;
    }

    void HVCC::Array::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        DisplayableObject::WriteDescription( os, indentLevel );
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }

    std::vector< std::shared_ptr< HVCC::Array::NALUnit > > HVCC::Array::GetNALUnits() const
    {
        return this->impl->_nalUnits;
    }

    void HVCC::Array::AddNALUnit( std::shared_ptr< NALUnit > unit )
    {
        this->impl->_nalUnits.push_back( unit );
    }

    std::vector< std::shared_ptr< DisplayableObject > > HVCC::Array::GetDisplayableObjects() const
    {
        auto v( this->GetNALUnits() );

        return std::vector< std::shared_ptr< DisplayableObject > >( v.begin(), v.end() );
    }

    std::vector< std::pair< std::string, std::string > > HVCC::Array::GetDisplayableProperties() const
    {
        return
        {
            { "Array completeness", ( this->GetArrayCompleteness() ) ? "yes" : "no" },
            { "NAL unit type",      std::to_string( this->GetNALUnitType() ) },
            { "NAL units",          std::to_string( this->GetNALUnits().size() ) }
        };
    }

    HVCC::Array::IMPL::IMPL():
        _arrayCompleteness( false ),
        _nalUnitType( 0 )
    {}

    HVCC::Array::IMPL::IMPL( const IMPL & o ):
        _arrayCompleteness( o._arrayCompleteness ),
        _nalUnitType( o._nalUnitType ),
        _nalUnits( o._nalUnits )
    {}

    HVCC::Array::IMPL::~IMPL()
    {}
}
