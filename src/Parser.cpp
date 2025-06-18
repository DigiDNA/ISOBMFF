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
 * @file        Parser.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <Parser.hpp>
#include <ContainerBox.hpp>
#include <BinaryFileStream.hpp>
#include <BinaryDataStream.hpp>
#include <FTYP.hpp>
#include <MVHD.hpp>
#include <TKHD.hpp>
#include <META.hpp>
#include <HDLR.hpp>
#include <MDHD.hpp>
#include <PITM.hpp>
#include <IINF.hpp>
#include <DREF.hpp>
#include <URL.hpp>
#include <URN.hpp>
#include <ILOC.hpp>
#include <IREF.hpp>
#include <INFE.hpp>
#include <IROT.hpp>
#include <HVCC.hpp>
#include <AVCC.hpp>
#include <DIMG.hpp>
#include <THMB.hpp>
#include <CDSC.hpp>
#include <COLR.hpp>
#include <ISPE.hpp>
#include <IPMA.hpp>
#include <PIXI.hpp>
#include <IPCO.hpp>
#include <STSD.hpp>
#include <STSS.hpp>
#include <STTS.hpp>
#include <CTTS.hpp>
#include <FRMA.hpp>
#include <SCHM.hpp>
#include <HVC1.hpp>
#include <AVC1.hpp>
#include <AV01.hpp>
#include <MP4A.hpp>
#include <map>
#include <stdexcept>
#include <cstring>

namespace ISOBMFF
{
    class Parser::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            void RegisterBox( const std::string & type, const std::function< std::shared_ptr< Box >() > & createBox );
            void RegisterContainerBox( const std::string & type );
            void RegisterDefaultBoxes();

            std::shared_ptr< File >                                            _file;
            std::string                                                        _path;
            std::map< std::string, std::function< std::shared_ptr< Box >() > > _types;
            Parser::StringType                                                 _stringType;
            uint64_t                                                           _options;
            std::map< std::string, void * >                                    _info;
    };

    Parser::Parser():
        impl( std::make_unique< IMPL >() )
    {}

    Parser::Parser( const std::string & path ):
        impl( std::make_unique< IMPL >() )
    {
        this->Parse( path );
    }

    Parser::Parser( const std::vector< uint8_t > & data ):
        impl( std::make_unique< IMPL >() )
    {
        this->Parse( data );
    }

    Parser::Parser( BinaryStream & stream ):
        impl( std::make_unique< IMPL >() )
    {
        this->Parse( stream );
    }

    Parser::Parser( const Parser & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    Parser::Parser( Parser && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    Parser::~Parser()
    {}

    Parser & Parser::operator =( Parser o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( Parser & o1, Parser & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    void Parser::RegisterContainerBox( const std::string & type )
    {
        this->impl->RegisterContainerBox( type );
    }

    void Parser::RegisterBox( const std::string & type, const std::function< std::shared_ptr< Box >() > & createBox )
    {
        this->impl->RegisterBox( type, createBox );
    }

    std::shared_ptr< Box > Parser::CreateBox( const std::string & type ) const
    {
        for( const auto & p: this->impl->_types )
        {
            if( p.first == type && p.second != nullptr )
            {
                return p.second();
            }
        }

        return std::make_shared< Box >( type );
    }

    void Parser::Parse( const std::string & path ) noexcept( false )
    {
        BinaryFileStream stream( path );

        this->Parse( stream );

        this->impl->_path = path;
    }

    void Parser::Parse( const std::vector< uint8_t > & data ) noexcept( false )
    {
        BinaryDataStream stream( data );

        this->Parse( stream );
    }

    void Parser::Parse( BinaryStream & stream ) noexcept( false )
    {
        char n[ 4 ] = { 0, 0, 0, 0 };

        if( stream.HasBytesAvailable() == false )
        {
            throw std::runtime_error( std::string( "Cannot read file" ) );
        }

        try
        {
            stream.Get( reinterpret_cast< uint8_t * >( n ), 4, 4 );
        }
        catch( ... )
        {}

        if
        (
               memcmp( n, "ftyp", 4 ) != 0
            && memcmp( n, "sinf", 4 ) != 0
            && memcmp( n, "wide", 4 ) != 0
            && memcmp( n, "free", 4 ) != 0
            && memcmp( n, "skip", 4 ) != 0
            && memcmp( n, "mdat", 4 ) != 0
            && memcmp( n, "moov", 4 ) != 0
            && memcmp( n, "pnot", 4 ) != 0
        )
        {
            throw std::runtime_error( std::string( "Data is not an ISO media file" ) );
        }

        this->impl->_path = "";
        this->impl->_file = std::make_shared< File >();

        if( stream.HasBytesAvailable() )
        {
            this->impl->_file->ReadData( *( this ), stream );
        }
    }

    std::shared_ptr< File > Parser::GetFile() const
    {
        return this->impl->_file;
    }

    Parser::StringType Parser::GetPreferredStringType() const
    {
        return this->impl->_stringType;
    }

    void Parser::SetPreferredStringType( StringType value )
    {
        this->impl->_stringType = value;
    }

    uint64_t Parser::GetOptions() const
    {
        return this->impl->_options;
    }

    void Parser::SetOptions( uint64_t value )
    {
        this->impl->_options = value;
    }

    void Parser::AddOption( Options option )
    {
        this->impl->_options |= static_cast< uint64_t >( option );
    }

    void Parser::RemoveOption( Options option )
    {
        this->impl->_options &= ~static_cast< uint64_t >( option );
    }

    bool Parser::HasOption( Options option )
    {
        return ( this->GetOptions() & static_cast< uint64_t >( option ) ) != 0;
    }

    const void * Parser::GetInfo( const std::string & key )
    {
        if( this->impl->_info.find( key ) == this->impl->_info.end() )
        {
            return nullptr;
        }

        return this->impl->_info[ key ];
    }

    void Parser::SetInfo( const std::string & key, void * value )
    {
        if( value == nullptr )
        {
            this->impl->_info.erase( key );
        }
        else
        {
            this->impl->_info[ key ] = value;
        }
    }

    Parser::IMPL::IMPL():
        _stringType( Parser::StringType::NULLTerminated ),
        _options( 0 )
    {
        this->RegisterDefaultBoxes();
    }

    Parser::IMPL::IMPL( const IMPL & o ):
        _file( o._file ),
        _path( o._path ),
        _types( o._types ),
        _stringType( o._stringType ),
        _options( o._options ),
        _info( o._info )
    {
        this->RegisterDefaultBoxes();
    }

    Parser::IMPL::~IMPL()
    {}

    void Parser::IMPL::RegisterBox( const std::string & type, const std::function< std::shared_ptr< Box >() > & createBox )
    {
        if( type.size() != 4 )
        {
            throw std::runtime_error( "Box name should be 4 characters long" );
        }

        this->_types[ type ] = createBox;
    }

    void Parser::IMPL::RegisterContainerBox( const std::string & type )
    {
        return this->RegisterBox
        (
            type,
            [ = ]() -> std::shared_ptr< Box >
            {
                return std::make_shared< ContainerBox >( type );
            }
        );
    }

    void Parser::IMPL::RegisterDefaultBoxes()
    {
        this->RegisterContainerBox( "moov" );
        this->RegisterContainerBox( "trak" );
        this->RegisterContainerBox( "edts" );
        this->RegisterContainerBox( "mdia" );
        this->RegisterContainerBox( "minf" );
        this->RegisterContainerBox( "stbl" );
        this->RegisterContainerBox( "mvex" );
        this->RegisterContainerBox( "moof" );
        this->RegisterContainerBox( "traf" );
        this->RegisterContainerBox( "mfra" );
        this->RegisterContainerBox( "meco" );
        this->RegisterContainerBox( "mere" );
        this->RegisterContainerBox( "dinf" );
        this->RegisterContainerBox( "ipro" );
        this->RegisterContainerBox( "sinf" );
        this->RegisterContainerBox( "iprp" );
        this->RegisterContainerBox( "fiin" );
        this->RegisterContainerBox( "paen" );
        this->RegisterContainerBox( "strk" );
        this->RegisterContainerBox( "tapt" );
        this->RegisterContainerBox( "schi" );

        this->RegisterBox( "ftyp", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< FTYP >(); } );
        this->RegisterBox( "mvhd", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< MVHD >(); } );
        this->RegisterBox( "tkhd", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< TKHD >(); } );
        this->RegisterBox( "meta", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< META >(); } );
        this->RegisterBox( "hdlr", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< HDLR >(); } );
        this->RegisterBox( "mdhd", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< MDHD >(); } );
        this->RegisterBox( "pitm", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< PITM >(); } );
        this->RegisterBox( "iinf", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< IINF >(); } );
        this->RegisterBox( "dref", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< DREF >(); } );
        this->RegisterBox( "url ", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< URL  >(); } );
        this->RegisterBox( "urn ", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< URN  >(); } );
        this->RegisterBox( "iloc", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< ILOC >(); } );
        this->RegisterBox( "iref", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< IREF >(); } );
        this->RegisterBox( "infe", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< INFE >(); } );
        this->RegisterBox( "irot", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< IROT >(); } );
        this->RegisterBox( "hvcC", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< HVCC >(); } );
        this->RegisterBox( "avcC", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< AVCC >(); } );
        this->RegisterBox( "dimg", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< DIMG >(); } );
        this->RegisterBox( "thmb", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< THMB >(); } );
        this->RegisterBox( "cdsc", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< CDSC >(); } );
        this->RegisterBox( "colr", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< COLR >(); } );
        this->RegisterBox( "ispe", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< ISPE >(); } );
        this->RegisterBox( "ipma", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< IPMA >(); } );
        this->RegisterBox( "pixi", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< PIXI >(); } );
        this->RegisterBox( "ipco", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< IPCO >(); } );
        this->RegisterBox( "stsd", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< STSD >(); } );
        this->RegisterBox( "stss", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< STSS >(); } );
        this->RegisterBox( "stts", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< STTS >(); } );
        this->RegisterBox( "ctts", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< CTTS >(); } );
        this->RegisterBox( "frma", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< FRMA >(); } );
        this->RegisterBox( "schm", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< SCHM >(); } );
        this->RegisterBox( "hvc1", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< HVC1 >(); } );
        this->RegisterBox( "avc1", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< AVC1 >(); } );
        this->RegisterBox( "av01", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< AV01 >(); } );
        this->RegisterBox( "mp4a", [ = ]() -> std::shared_ptr< Box > { return std::make_shared< MP4A >(); } );
    }
}
