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
 * @file        ImageGrid.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/ImageGrid.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::ImageGrid >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint8_t  _version;
        uint8_t  _flags;
        uint8_t  _rows;
        uint8_t  _columns;
        uint64_t _outputWidth;
        uint64_t _outputHeight;
};

#define XS_PIMPL_CLASS ISOBMFF::ImageGrid
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    ImageGrid::ImageGrid( void )
    {}
    
    ImageGrid::ImageGrid( BinaryStream & stream )
    {
        uint8_t s;
        
        this->SetVersion( stream.ReadUInt8() );
        this->SetFlags( stream.ReadUInt8() );
        this->SetRows( stream.ReadUInt8() );
        this->SetColumns( stream.ReadUInt8() );
        
        s = ( ( this->GetFlags() & 1 ) + 1 ) * 2;
        
        if( s == 1 )
        {
            this->SetOutputWidth( stream.ReadUInt8() );
            this->SetOutputHeight( stream.ReadUInt8() );
        }
        else if( s == 2 )
        {
            this->SetOutputWidth( stream.ReadBigEndianUInt16() );
            this->SetOutputHeight( stream.ReadBigEndianUInt16() );
        }
        else if( s == 4 )
        {
            this->SetOutputWidth( stream.ReadBigEndianUInt32() );
            this->SetOutputHeight( stream.ReadBigEndianUInt32() );
        }
        else if( s == 8 )
        {
            this->SetOutputWidth( stream.ReadBigEndianUInt64() );
            this->SetOutputHeight( stream.ReadBigEndianUInt64() );
        }
    }
    
    std::string ImageGrid::GetName( void ) const
    {
        return "ImageGrid";
    }
    
    uint8_t ImageGrid::GetVersion( void ) const
    {
        return this->impl->_version;
    }
    
    uint8_t ImageGrid::GetFlags( void ) const
    {
        return this->impl->_flags;
    }
    
    uint8_t ImageGrid::GetRows( void ) const
    {
        return this->impl->_rows;
    }
    
    uint8_t ImageGrid::GetColumns( void ) const
    {
        return this->impl->_columns;
    }
    
    uint64_t ImageGrid::GetOutputWidth( void ) const
    {
        return this->impl->_outputWidth;
    }
    
    uint64_t ImageGrid::GetOutputHeight( void ) const
    {
        return this->impl->_outputHeight;
    }
    
    void ImageGrid::SetVersion( uint8_t value )
    {
        this->impl->_version = value;
    }
    
    void ImageGrid::SetFlags( uint8_t value )
    {
        this->impl->_flags = value;
    }
    
    void ImageGrid::SetRows( uint8_t value )
    {
        this->impl->_rows = value;
    }
    
    void ImageGrid::SetColumns( uint8_t value )
    {
        this->impl->_columns = value;
    }
    
    void ImageGrid::SetOutputWidth( uint64_t value )
    {
        this->impl->_outputWidth = value;
    }
    
    void ImageGrid::SetOutputHeight( uint64_t value )
    {
        this->impl->_outputHeight = value;
    }
    
    std::vector< std::pair< std::string, std::string > > ImageGrid::GetDisplayableProperties( void ) const
    {
        return
        {
            { "Version",       std::to_string( this->GetVersion() ) },
            { "Flags",         std::to_string( this->GetFlags() ) },
            { "Rows",          std::to_string( this->GetRows() ) },
            { "Columns",       std::to_string( this->GetColumns() ) },
            { "Output width",  std::to_string( this->GetOutputWidth() ) },
            { "Output height", std::to_string( this->GetOutputHeight() ) },
        };
    }
}

XS::PIMPL::Object< ISOBMFF::ImageGrid >::IMPL::IMPL( void ):
    _version( 0 ),
    _flags( 0 ),
    _rows( 0 ),
    _columns( 0 ),
    _outputWidth( 0 ),
    _outputHeight( 0 )
{}

XS::PIMPL::Object< ISOBMFF::ImageGrid >::IMPL::IMPL( const IMPL & o ):
    _version( o._version ),
    _flags( o._flags ),
    _rows( o._rows ),
    _columns( o._columns ),
    _outputWidth( o._outputWidth ),
    _outputHeight( o._outputHeight )
{}

XS::PIMPL::Object< ISOBMFF::ImageGrid >::IMPL::~IMPL( void )
{}

