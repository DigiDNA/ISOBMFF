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
 * @file        main.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/ISOBMFF.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

void SaveData( const std::vector< uint8_t > & bytes, uint64_t offset, uint64_t length, const std::string & file );
void PrintData( const std::vector< uint8_t > & bytes, uint64_t offset, uint64_t length );
void PrintDataLine( const std::vector< uint8_t > & bytes, uint64_t length );

template< typename _T_ >
std::vector< _T_ > Slice( const std::vector< _T_ > & v, uint64_t start, uint64_t length )
{
    std::vector< uint8_t >::difference_type s;
    std::vector< uint8_t >::difference_type l;
    
    s = static_cast< decltype( s ) >( start );
    l = static_cast< decltype( l ) >( length );
    
    if( v.begin() + s > v.end() )
    {
        return {};
    }
    
    if( v.begin() + s + l > v.end() )
    {
        return std::vector< uint8_t >( v.begin() + s, v.end() );
    }
    
    return std::vector< uint8_t >( v.begin() + s, v.begin() + s + l );
}

int main( int argc, const char * argv[] )
{
    ISOBMFF::Parser                  parser;
    std::shared_ptr< ISOBMFF::File > file;
    std::string                    path;
    int                            i;
    
    if( argc < 2 )
    {
        std::cerr << "Error: no input file provided" << std::endl;
        
        return EXIT_FAILURE;
    }
    
    for( i = 1; i < argc; i++ )
    {
        path = argv[ i ];
        
        if( path.length() == 0 )
        {
            std::cerr << "Error: no input file provided" << std::endl;
            
            return EXIT_FAILURE;
        }
        
        try
        {
            parser.Parse( path );
        }
        catch( const std::runtime_error & e )
        {
            std::cerr << e.what() << std::endl;
            
            return EXIT_FAILURE;
        }
        
        file = parser.GetFile();
        
        std::cout << *( file ) << std::endl << std::endl;
        
        {
            std::shared_ptr< ISOBMFF::FTYP > ftyp;
            std::shared_ptr< ISOBMFF::META > meta;
            std::shared_ptr< ISOBMFF::Box  > mdat;
            std::shared_ptr< ISOBMFF::IINF > iinf;
            std::shared_ptr< ISOBMFF::ILOC > iloc;
            std::shared_ptr< ISOBMFF::Box  > idat;
            std::shared_ptr< ISOBMFF::PITM > pitm;
            std::vector< uint8_t >         data;
            
            ftyp = file->GetTypedBox< ISOBMFF::FTYP >( "ftyp" );
            meta = file->GetTypedBox< ISOBMFF::META >( "meta" );
            mdat = file->GetBox( "mdat" );
            
            if
            (
                   ftyp                  == nullptr
                || meta                  == nullptr
                || mdat                  == nullptr
                || ftyp->GetMajorBrand() != "heic"
            )
            {
                continue;
            }
            
            iinf = meta->GetTypedBox< ISOBMFF::IINF >( "iinf" );
            iloc = meta->GetTypedBox< ISOBMFF::ILOC >( "iloc" );
            idat = meta->GetBox( "idat" );
            pitm = meta->GetTypedBox< ISOBMFF::PITM >( "pitm" );
            
            if( iloc == nullptr || iinf == nullptr || idat == nullptr || pitm == nullptr )
            {
                continue;
            }
            
            {
                std::ifstream           stream;
                std::ifstream::pos_type length;
                
                stream.open( path, std::ios::binary | std::ios::ate );
                
                if( stream.good() == false )
                {
                    continue;
                }
                
                length = stream.tellg();
                data   = std::vector< uint8_t >( static_cast< std::size_t >( length ) );
                
                stream.seekg( 0, std::ios::beg );
                stream.read( reinterpret_cast< char * >( &( data[ 0 ] ) ), length );
            }
            
            for( const auto & entry: iinf->GetEntries()  )
            {
                if( entry->GetItemID() == pitm->GetItemID() )
                {
                    {
                        std::shared_ptr< ISOBMFF::ILOC::Item::Extent > extent;
                        std::vector< uint8_t >                         itemData;
                        ISOBMFF::BinaryStream                          stream;
                        
                        for( const auto & item: iloc->GetItems() )
                        {
                            if
                            (
                                   item->GetItemID()         != entry->GetItemID()
                                || item->GetExtents().size() == 0
                            )
                            {
                                continue;
                            }
                            
                            std::cout << "Primary item info: " << std::endl << *( entry ) << std::endl << std::endl;
                            std::cout << "Primary item: " << std::endl << item       << std::endl << std::endl;
                            
                            extent = item->GetExtents()[ 0 ];
                            
                            if( item->GetConstructionMethod() == 0 )
                            {
                                itemData = Slice( data, extent->GetOffset(), extent->GetLength() );
                                stream   = ISOBMFF::BinaryStream( itemData );
                            }
                            else if( item->GetConstructionMethod() == 1 )
                            {
                                itemData = Slice( idat->GetData(), extent->GetOffset(), extent->GetLength() );
                                stream   = ISOBMFF::BinaryStream( itemData );
                            }
                            else if( item->GetConstructionMethod() == 2 )
                            {
                                /* ... */
                            }
                            
                            if( entry->GetItemType() == "hvc1" )
                            {
                                /* ... */
                            }
                            else if( entry->GetItemType() == "grid" )
                            {
                                {
                                    ISOBMFF::ImageGrid grid( stream );
                                    
                                    std::cout << "Image grid: " << std::endl << grid << std::endl << std::endl;
                                }
                            }
                        }
                    }
                }
                else if( entry->GetItemType() == "Exif" )
                {
                    {
                        std::shared_ptr< ISOBMFF::ILOC::Item::Extent > exif;
                        
                        for( const auto & item: iloc->GetItems() )
                        {
                            if
                            (
                                   item->GetItemID()         != entry->GetItemID()
                                || item->GetExtents().size() == 0
                            )
                            {
                                continue;
                            }
                            
                            exif = item->GetExtents()[ 0 ];
                            
                            if( exif->GetLength() > 0 )
                            {
                                std::cout << "Found EXIF data ( index = " << exif->GetIndex() << ", offset = " << exif->GetOffset() << ", length = " << exif->GetLength() << " ):" << std::endl;
                                std::cout << std::endl;
                                
                                PrintData( data, exif->GetOffset(), exif->GetLength() );
                                
                                std::cout << std::endl;
                            }
                        }
                    }
                }
                
                /*
                else if( entry->GetItemType() == "hvc1" )
                {
                    {
                        ISOBMFF::ILOC::Item::Extent hvc1;
                        
                        for( const auto & item: iloc->GetItems() )
                        {
                            if
                            (
                                   item.GetItemID()         == entry->GetItemID()
                                && item.GetExtents().size() != 0
                            )
                            {
                                hvc1 = item.GetExtents()[ 0 ];
                                
                                SaveData( data, hvc1.GetOffset(), hvc1.GetLength(), std::string( "/Users/macmade/Desktop/HVC1/" ) + std::to_string( item.GetItemID() ) + ".bin" );
                                
                                break;
                            }
                        }
                    }
                }
                */
            }
        }
    }
    
    return EXIT_SUCCESS;
}

void SaveData( const std::vector< uint8_t > & bytes, uint64_t offset, uint64_t length, const std::string & file )
{
    std::vector< uint8_t > data;
    std::ofstream          out( file, std::ios::out | std::ios::binary );
    
    data = Slice( bytes, offset, length );
    
    if( data.size() && out.good() )
    {
        out.write( reinterpret_cast< const char * >( &data[ 0 ] ), static_cast< std::streamsize >( data.size() ) );
        out.close();
    }
}

void PrintData( const std::vector< uint8_t > & bytes, uint64_t offset, uint64_t length )
{
    std::vector< uint8_t > data;
    std::vector< uint8_t > part;
    uint64_t               i;
    
    data = Slice( bytes, offset, length );
    
    if( data.size() )
    {
        i = 0;
        
        while( 1 )
        {
            part = Slice( data, i, 30 );
            
            if( part.size() == 0 )
            {
                break;
            }
            
            PrintDataLine( part, 30 );
            
            i += 20;
        }
    }
}

void PrintDataLine( const std::vector< uint8_t > & bytes, uint64_t length )
{
    uint64_t i;
    
    for( auto byte: bytes )
    {
        {
            std::stringstream ss;
            
            ss << std::hex
               << std::uppercase
               << std::setfill( '0' )
               << std::setw( 2 )
               << static_cast< uint32_t >( byte );
            
            std::cout << ss.str() << " ";
        }
    }
    
    if( bytes.size() < length )
    {
        for( i = 0; i < length - bytes.size(); i++ )
        {
            std::cout << "   ";
        }
    }
    
    std::cout << "| ";
    
    for( auto byte: bytes )
    {
        if( isprint( byte ) && !isspace( byte ) )
        {
            std::cout << byte;
        }
        else
        {
            std::cout << ".";
        }
    }
    
    std::cout << std::endl;
}
