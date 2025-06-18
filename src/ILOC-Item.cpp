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
 * @file        ILOC-Item.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ILOC.hpp>

namespace ISOBMFF
{
    class ILOC::Item::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint32_t                                 _itemID;
            uint8_t                                  _constructionMethod;
            uint16_t                                 _dataReferenceIndex;
            uint64_t                                 _baseOffset;
            std::vector< std::shared_ptr< Extent > > _extents;
    };

    ILOC::Item::Item():
        impl( std::make_unique< IMPL >() )
    {}

    ILOC::Item::Item( BinaryStream & stream, const ILOC & iloc ):
        impl( std::make_unique< IMPL >() )
    {
        uint16_t count;
        uint16_t i;

        if( iloc.GetVersion() < 2 )
        {
            this->SetItemID( stream.ReadBigEndianUInt16() );
        }
        else if( iloc.GetVersion() == 2 )
        {
            this->SetItemID( stream.ReadBigEndianUInt32() );
        }

        if( iloc.GetVersion() == 1 || iloc.GetVersion() == 2 )
        {
            this->SetConstructionMethod( static_cast< uint8_t >( stream.ReadBigEndianUInt16() & 0xF ) );
        }

        this->SetDataReferenceIndex( stream.ReadBigEndianUInt16() );

        if( iloc.GetBaseOffsetSize() == 2 )
        {
            this->SetBaseOffset( stream.ReadBigEndianUInt16() );
        }
        else if( iloc.GetBaseOffsetSize() == 4 )
        {
            this->SetBaseOffset( stream.ReadBigEndianUInt32() );
        }
        else if( iloc.GetBaseOffsetSize() == 8 )
        {
            this->SetBaseOffset( stream.ReadBigEndianUInt64() );
        }

        count = stream.ReadBigEndianUInt16();

        this->impl->_extents.clear();

        for( i = 0; i < count; i++ )
        {
            this->AddExtent( std::make_shared< Extent >( stream, iloc ) );
        }
    }

    ILOC::Item::Item( const ILOC::Item & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    ILOC::Item::Item( ILOC::Item && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    ILOC::Item::~Item()
    {}

    ILOC::Item & ILOC::Item::operator =( ILOC::Item o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( ILOC::Item & o1, ILOC::Item & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string ILOC::Item::GetName() const
    {
        return "Item";
    }

    uint32_t ILOC::Item::GetItemID() const
    {
        return this->impl->_itemID;
    }

    uint8_t ILOC::Item::GetConstructionMethod() const
    {
        return this->impl->_constructionMethod;
    }

    uint16_t ILOC::Item::GetDataReferenceIndex() const
    {
        return this->impl->_dataReferenceIndex;
    }

    uint64_t ILOC::Item::GetBaseOffset() const
    {
        return this->impl->_baseOffset;
    }

    void ILOC::Item::SetItemID( uint32_t value )
    {
        this->impl->_itemID = value;
    }

    void ILOC::Item::SetConstructionMethod( uint8_t value )
    {
        this->impl->_constructionMethod = value;
    }

    void ILOC::Item::SetDataReferenceIndex( uint16_t value )
    {
        this->impl->_dataReferenceIndex = value;
    }

    void ILOC::Item::SetBaseOffset( uint64_t value )
    {
        this->impl->_baseOffset = value;
    }

    std::vector< std::shared_ptr< ILOC::Item::Extent > > ILOC::Item::GetExtents() const
    {
        return this->impl->_extents;
    }

    void ILOC::Item::AddExtent( std::shared_ptr< Extent > extent )
    {
        this->impl->_extents.push_back( extent );
    }

    void ILOC::Item::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        DisplayableObject::WriteDescription( os, indentLevel );
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }

    std::vector< std::shared_ptr< DisplayableObject > > ILOC::Item::GetDisplayableObjects() const
    {
        auto v( this->GetExtents() );

        return std::vector< std::shared_ptr< DisplayableObject > >( v.begin(), v.end() );
    }

    std::vector< std::pair< std::string, std::string > > ILOC::Item::GetDisplayableProperties() const
    {
        return
        {
            { "Item ID",              std::to_string( this->GetItemID() ) },
            { "Construction method",  std::to_string( this->GetConstructionMethod() ) },
            { "Data reference index", std::to_string( this->GetDataReferenceIndex() ) },
            { "Base offset",          std::to_string( this->GetBaseOffset() ) },
            { "Extent count",         std::to_string( this->GetExtents().size() ) }
        };
    }

    ILOC::Item::IMPL::IMPL():
        _itemID( 0 ),
        _constructionMethod( 0 ),
        _dataReferenceIndex( 0 ),
        _baseOffset( 0 )
    {}

    ILOC::Item::IMPL::IMPL( const IMPL & o ):
        _itemID( o._itemID ),
        _constructionMethod( o._constructionMethod ),
        _dataReferenceIndex( o._dataReferenceIndex ),
        _baseOffset( o._baseOffset ),
        _extents( o._extents )
    {}

    ILOC::Item::IMPL::~IMPL()
    {}
}
