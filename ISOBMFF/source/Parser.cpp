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
 * @file        Parser.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/ContainerBox.hpp>
#include <ISOBMFF/BinaryStream.hpp>
#include <ISOBMFF/FTYP.hpp>
#include <ISOBMFF/MVHD.hpp>
#include <ISOBMFF/TKHD.hpp>
#include <ISOBMFF/META.hpp>
#include <ISOBMFF/HDLR.hpp>
#include <ISOBMFF/PITM.hpp>
#include <ISOBMFF/IINF.hpp>
#include <ISOBMFF/DREF.hpp>
#include <ISOBMFF/URL.hpp>
#include <ISOBMFF/URN.hpp>
#include <ISOBMFF/ILOC.hpp>
#include <ISOBMFF/IREF.hpp>
#include <ISOBMFF/INFE.hpp>
#include <ISOBMFF/IROT.hpp>
#include <ISOBMFF/HVCC.hpp>
#include <ISOBMFF/DIMG.hpp>
#include <ISOBMFF/THMB.hpp>
#include <ISOBMFF/CDSC.hpp>
#include <ISOBMFF/COLR.hpp>
#include <ISOBMFF/ISPE.hpp>
#include <ISOBMFF/IPMA.hpp>
#include <ISOBMFF/PIXI.hpp>
#include <ISOBMFF/IPCO.hpp>
#include <ISOBMFF/STSD.hpp>
#include <map>
#include <stdexcept>

template<>
class XS::PIMPL::Object< ISOBMFF::Parser >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        void RegisterBox( const std::string & type, const std::function< std::shared_ptr< ISOBMFF::Box >( void ) > & createBox );
        void RegisterContainerBox( const std::string & type );
        void RegisterDefaultBoxes( void );
        
        std::shared_ptr< ISOBMFF::File >                                                  _file;
        std::string                                                                       _path;
        std::map< std::string, std::function< std::shared_ptr< ISOBMFF::Box >( void ) > > _types;
        ISOBMFF::Parser::StringType                                                       _stringType;
        uint64_t                                                                          _options;
        std::map< std::string, void * >                                                   _info;
};

#define XS_PIMPL_CLASS ISOBMFF::Parser
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    Parser::Parser( void ): XS::PIMPL::Object< Parser >()
    {}
    
    Parser::Parser( const std::string & path ): XS::PIMPL::Object< Parser >()
    {
        this->Parse( path );
    }
    
    void Parser::RegisterContainerBox( const std::string & type )
    {
        this->impl->RegisterContainerBox( type );
    }
    
    void Parser::RegisterBox( const std::string & type, const std::function< std::shared_ptr< Box >( void ) > & createBox )
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
    
    void Parser::Parse( const std::string & path ) ISOBMFF_NOEXCEPT( false )
    {
        char         n[ 4 ] = { 0, 0, 0, 0 };
        BinaryStream stream( path );
        
        if( stream.HasBytesAvailable() == false )
        {
            throw std::runtime_error( std::string( "Cannot read file: " ) + path );
        }
        
        try
        {
            stream.Get( reinterpret_cast< uint8_t * >( n ), 4, 4 );
        }
        catch( ... )
        {}
        
        if( strncmp( n, "ftyp", 4 ) != 0 )
        {
            throw std::runtime_error( std::string( "File is not an ISO media file: " ) + path );
        }
        
        this->impl->_path = path;
        this->impl->_file = std::make_shared< File >();
        
        if( stream.HasBytesAvailable() )
        {
            this->impl->_file->ReadData( *( this ), stream );
        }
    }
    
    std::shared_ptr< File > Parser::GetFile( void ) const
    {
        return this->impl->_file;
    }
    
    Parser::StringType Parser::GetPreferredStringType( void ) const
    {
        return this->impl->_stringType;
    }
    
    void Parser::SetPreferredStringType( StringType value )
    {
        this->impl->_stringType = value;
    }
    
    uint64_t Parser::GetOptions( void ) const
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
}

XS::PIMPL::Object< ISOBMFF::Parser >::IMPL::IMPL( void ):
    _stringType( ISOBMFF::Parser::StringType::NULLTerminated ),
    _options( 0 )
{
    this->RegisterDefaultBoxes();
}

XS::PIMPL::Object< ISOBMFF::Parser >::IMPL::IMPL( const IMPL & o ):
    _file( o._file ),
    _path( o._path ),
    _types( o._types ),
    _stringType( o._stringType ),
    _options( o._options ),
    _info( o._info )
{
    this->RegisterDefaultBoxes();
}

XS::PIMPL::Object< ISOBMFF::Parser >::IMPL::~IMPL( void )
{}

void XS::PIMPL::Object< ISOBMFF::Parser >::IMPL::RegisterBox( const std::string & type, const std::function< std::shared_ptr< ISOBMFF::Box >( void ) > & createBox )
{
    if( type.size() != 4 )
    {
        throw std::runtime_error( "Box name should be 4 characters long" );
    }
    
    this->_types[ type ] = createBox;
}

void XS::PIMPL::Object< ISOBMFF::Parser >::IMPL::RegisterContainerBox( const std::string & type )
{
    return this->RegisterBox
    (
        type,
        [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box >
        {
            return std::make_shared< ISOBMFF::ContainerBox >( type );
        }
    );
}

void XS::PIMPL::Object< ISOBMFF::Parser >::IMPL::RegisterDefaultBoxes( void )
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
    this->RegisterContainerBox( "skip" );
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
    
    this->RegisterBox( "ftyp", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::FTYP >(); } );
    this->RegisterBox( "mvhd", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::MVHD >(); } );
    this->RegisterBox( "tkhd", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::TKHD >(); } );
    this->RegisterBox( "meta", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::META >(); } );
    this->RegisterBox( "hdlr", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::HDLR >(); } );
    this->RegisterBox( "pitm", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::PITM >(); } );
    this->RegisterBox( "iinf", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IINF >(); } );
    this->RegisterBox( "dref", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::DREF >(); } );
    this->RegisterBox( "url ", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::URL >(); } );
    this->RegisterBox( "urn ", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::URN >(); } );
    this->RegisterBox( "iloc", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::ILOC >(); } );
    this->RegisterBox( "iref", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IREF >(); } );
    this->RegisterBox( "infe", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::INFE >(); } );
    this->RegisterBox( "irot", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IROT >(); } );
    this->RegisterBox( "hvcC", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::HVCC >(); } );
    this->RegisterBox( "dimg", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::DIMG >(); } );
    this->RegisterBox( "thmb", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::THMB >(); } );
    this->RegisterBox( "cdsc", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::CDSC >(); } );
    this->RegisterBox( "colr", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::COLR >(); } );
    this->RegisterBox( "ispe", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::ISPE >(); } );
    this->RegisterBox( "ipma", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IPMA >(); } );
    this->RegisterBox( "pixi", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::PIXI >(); } );
    this->RegisterBox( "ipco", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IPCO >(); } );
    this->RegisterBox( "stsd", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::STSD >(); } );
}
