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
 * @file        INFE.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <INFE.hpp>
#include <Parser.hpp>

namespace ISOBMFF
{
    class INFE::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint32_t    _itemID;
            uint16_t    _itemProtectionIndex;
            std::string _itemType;
            std::string _itemName;
            std::string _contentType;
            std::string _contentEncoding;
            std::string _itemURIType;
    };

    INFE::INFE():
        FullBox( "infe" ),
        impl( std::make_unique< IMPL >() )
    {}

    INFE::INFE( const INFE & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    INFE::INFE( INFE && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    INFE::~INFE()
    {}

    INFE & INFE::operator =( INFE o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( INFE & o1, INFE & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void INFE::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );

        if( this->GetVersion() == 0 || this->GetVersion() == 1 )
        {
            this->SetItemID( stream.ReadBigEndianUInt16() );
            this->SetItemProtectionIndex( stream.ReadBigEndianUInt16() );

            if( parser.GetPreferredStringType() == Parser::StringType::Pascal )
            {
                this->SetItemName( stream.ReadPascalString() );
                this->SetContentType( stream.ReadPascalString() );
                this->SetContentEncoding( stream.ReadPascalString() );
            }
            else
            {
                this->SetItemName( stream.ReadNULLTerminatedString() );
                this->SetContentType( stream.ReadNULLTerminatedString() );
                this->SetContentEncoding( stream.ReadNULLTerminatedString() );
            }
        }

        /*
        if( version == 1 )
        {
            unsigned int( 32 ) extension_type;   // optional
            ItemInfoExtension( extension_type ); // optional
        }

        aligned( 8 ) class ItemInfoExtension( unsigned int( 32 ) extension_type )
        {}

        aligned( 8 ) class FDItemInfoExtension() extends ItemInfoExtension ( 'fdel' )
        {
            string             content_location;
            string             content_MD5;
            unsigned int( 64 ) content_length;
            unsigned int( 64 ) transfer_length;
            unsigned int( 8 )  entry_count;

            for( i = 1; i <= entry_count; i++ )
            {
                unsigned int( 32 ) group_id;
            }
        }
        */

        if( this->GetVersion() >= 2 )
        {
            if( this->GetVersion() == 2 )
            {
                this->SetItemID( stream.ReadBigEndianUInt16() );
            }
            else if( this->GetVersion() == 3 )
            {
                this->SetItemID( stream.ReadBigEndianUInt32() );
            }

            this->SetItemProtectionIndex( stream.ReadBigEndianUInt16() );
            this->SetItemType( stream.ReadFourCC() );

            if( parser.GetPreferredStringType() == Parser::StringType::Pascal )
            {
                if( this->GetItemType() == "mime" )
                {
                    this->SetContentType( stream.ReadPascalString() );
                    this->SetContentEncoding( stream.ReadPascalString() );
                }
                else if( this->GetItemType() == "uri " )
                {
                    this->SetItemURIType( stream.ReadPascalString() );
                }
            }
            else
            {
                if( this->GetItemType() == "mime" )
                {
                    this->SetContentType( stream.ReadNULLTerminatedString() );
                    this->SetContentEncoding( stream.ReadNULLTerminatedString() );
                }
                else if( this->GetItemType() == "uri " )
                {
                    this->SetItemURIType( stream.ReadNULLTerminatedString() );
                }
            }
        }
    }

    std::vector< std::pair< std::string, std::string > > INFE::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

        props.push_back( { "Item ID",               std::to_string( this->GetItemID() ) } );
        props.push_back( { "Item protection index", std::to_string( this->GetItemProtectionIndex() ) } );
        props.push_back( { "Item type",             this->GetItemType() } );
        props.push_back( { "Item name",             this->GetItemName() } );
        props.push_back( { "Content type",          this->GetContentType() } );
        props.push_back( { "Content encoding",      this->GetContentEncoding() } );
        props.push_back( { "Item URI type",         this->GetItemURIType() } );

        return props;
    }

    uint32_t INFE::GetItemID() const
    {
        return this->impl->_itemID;
    }

    uint16_t INFE::GetItemProtectionIndex() const
    {
        return this->impl->_itemProtectionIndex;
    }

    std::string INFE::GetItemType() const
    {
        return this->impl->_itemType;
    }

    std::string INFE::GetItemName() const
    {
        return this->impl->_itemName;
    }

    std::string INFE::GetContentType() const
    {
        return this->impl->_contentType;
    }

    std::string INFE::GetContentEncoding() const
    {
        return this->impl->_contentEncoding;
    }

    std::string INFE::GetItemURIType() const
    {
        return this->impl->_itemURIType;
    }

    void INFE::SetItemID( uint32_t value )
    {
        this->impl->_itemID = value;
    }

    void INFE::SetItemProtectionIndex( uint16_t value )
    {
        this->impl->_itemProtectionIndex = value;
    }

    void INFE::SetItemType( const std::string & value )
    {
        this->impl->_itemType = value;
    }

    void INFE::SetItemName( const std::string & value )
    {
        this->impl->_itemName = value;
    }

    void INFE::SetContentType( const std::string & value )
    {
        this->impl->_contentType = value;
    }

    void INFE::SetContentEncoding( const std::string & value )
    {
        this->impl->_contentEncoding = value;
    }

    void INFE::SetItemURIType( const std::string & value )
    {
        this->impl->_itemURIType = value;
    }

    INFE::IMPL::IMPL():
        _itemID( 0 ),
        _itemProtectionIndex( 0 )
    {}

    INFE::IMPL::IMPL( const IMPL & o ):
        _itemID( o._itemID ),
        _itemProtectionIndex( o._itemProtectionIndex ),
        _itemType( o._itemType ),
        _itemName( o._itemName ),
        _contentType( o._contentType ),
        _contentEncoding( o._contentEncoding ),
        _itemURIType( o._itemURIType )
    {}

    INFE::IMPL::~IMPL()
    {}
}
