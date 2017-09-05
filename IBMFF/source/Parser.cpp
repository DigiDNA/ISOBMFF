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

#include <IBMFF/Parser.hpp>
#include <IBMFF/ContainerBox.hpp>
#include <IBMFF/BinaryStream.hpp>
#include <IBMFF/FTYP.hpp>
#include <IBMFF/MVHD.hpp>
#include <IBMFF/META.hpp>
#include <IBMFF/HDLR.hpp>
#include <IBMFF/PITM.hpp>
#include <IBMFF/IINF.hpp>
#include <IBMFF/DREF.hpp>
#include <IBMFF/IDAT.hpp>
#include <IBMFF/ILOC.hpp>
#include <IBMFF/IREF.hpp>
#include <map>
#include <stdexcept>

template<>
class XS::PIMPL::Object< IBMFF::Parser >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        void RegisterBox( const std::string & type, const std::function< std::shared_ptr< IBMFF::Box >( void ) > & createBox );
        void RegisterContainerBox( const std::string & type );
        void RegisterDefaultBoxes( void );
        
        std::shared_ptr< IBMFF::File >                                                  _file;
        std::string                                                                     _path;
        std::map< std::string, std::function< std::shared_ptr< IBMFF::Box >( void ) > > _types;
        IBMFF::Parser::StringType                                                       _stringType;
};

#define XS_PIMPL_CLASS IBMFF::Parser
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
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
}

XS::PIMPL::Object< IBMFF::Parser >::IMPL::IMPL( void ):
    _stringType( IBMFF::Parser::StringType::NULLTerminated )
{
    this->RegisterDefaultBoxes();
}

XS::PIMPL::Object< IBMFF::Parser >::IMPL::IMPL( const IMPL & o ):
    _file( o._file ),
    _path( o._path ),
    _types( o._types ),
    _stringType( o._stringType )
{
    this->RegisterDefaultBoxes();
}

XS::PIMPL::Object< IBMFF::Parser >::IMPL::~IMPL( void )
{}

void XS::PIMPL::Object< IBMFF::Parser >::IMPL::RegisterBox( const std::string & type, const std::function< std::shared_ptr< IBMFF::Box >( void ) > & createBox )
{
    if( type.size() != 4 )
    {
        throw std::runtime_error( "Box name should be 4 characters long" );
    }
    
    this->_types[ type ] = createBox;
}

void XS::PIMPL::Object< IBMFF::Parser >::IMPL::RegisterContainerBox( const std::string & type )
{
    return this->RegisterBox
    (
        type,
        [ = ]( void ) -> std::shared_ptr< IBMFF::Box >
        {
            return std::make_shared< IBMFF::ContainerBox >( type );
        }
    );
}

void XS::PIMPL::Object< IBMFF::Parser >::IMPL::RegisterDefaultBoxes( void )
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
    
    this->RegisterBox( "ftyp", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::FTYP >(); } );
    this->RegisterBox( "mvhd", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::MVHD >(); } );
    this->RegisterBox( "meta", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::META >(); } );
    this->RegisterBox( "hdlr", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::HDLR >(); } );
    this->RegisterBox( "pitm", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::PITM >(); } );
    this->RegisterBox( "iinf", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::IINF >(); } );
    this->RegisterBox( "dref", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::DREF >(); } );
    this->RegisterBox( "idat", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::IDAT >(); } );
    this->RegisterBox( "iloc", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::ILOC >(); } );
    this->RegisterBox( "iref", [ = ]( void ) -> std::shared_ptr< IBMFF::Box > { return std::make_shared< IBMFF::IREF >(); } );
}
