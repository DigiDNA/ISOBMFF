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
#include <ISOBMFF/META.hpp>
#include <ISOBMFF/HDLR.hpp>
#include <ISOBMFF/PITM.hpp>
#include <ISOBMFF/IINF.hpp>
#include <ISOBMFF/DREF.hpp>
#include <ISOBMFF/URL.hpp>
#include <ISOBMFF/URN.hpp>
#include <ISOBMFF/IDAT.hpp>
#include <ISOBMFF/ILOC.hpp>
#include <ISOBMFF/IREF.hpp>
#include <ISOBMFF/INFE.hpp>
#include <ISOBMFF/IROT.hpp>
#include <ISOBMFF/HVCC.hpp>
#include <ISOBMFF/DIMG.hpp>
#include <ISOBMFF/THMB.hpp>
#include <ISOBMFF/CDSC.hpp>
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
    
    void Parser::Parse( const std::string & path )
    {
        BinaryStream stream( path );
        
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
    _stringType( ISOBMFF::Parser::StringType::NULLTerminated )
{
    this->RegisterDefaultBoxes();
}

XS::PIMPL::Object< ISOBMFF::Parser >::IMPL::IMPL( const IMPL & o ):
    _file( o._file ),
    _path( o._path ),
    _types( o._types ),
    _stringType( o._stringType ),
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
    this->RegisterContainerBox( "ipco" );
    this->RegisterContainerBox( "fiin" );
    this->RegisterContainerBox( "paen" );
    this->RegisterContainerBox( "strk" );
    
    this->RegisterBox( "ftyp", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::FTYP >(); } );
    this->RegisterBox( "mvhd", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::MVHD >(); } );
    this->RegisterBox( "meta", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::META >(); } );
    this->RegisterBox( "hdlr", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::HDLR >(); } );
    this->RegisterBox( "pitm", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::PITM >(); } );
    this->RegisterBox( "iinf", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IINF >(); } );
    this->RegisterBox( "dref", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::DREF >(); } );
    this->RegisterBox( "url ", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::URL >(); } );
    this->RegisterBox( "urn ", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::URN >(); } );
    this->RegisterBox( "idat", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IDAT >(); } );
    this->RegisterBox( "iloc", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::ILOC >(); } );
    this->RegisterBox( "iref", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IREF >(); } );
    this->RegisterBox( "infe", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::INFE >(); } );
    this->RegisterBox( "irot", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::IROT >(); } );
    this->RegisterBox( "hvcC", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::HVCC >(); } );
    this->RegisterBox( "dimg", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::DIMG >(); } );
    this->RegisterBox( "thmb", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::THMB >(); } );
    this->RegisterBox( "cdsc", [ = ]( void ) -> std::shared_ptr< ISOBMFF::Box > { return std::make_shared< ISOBMFF::CDSC >(); } );
}
