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
void ConvertHEVCData( const std::vector< uint8_t > & data );
void ExtractItem( uint32_t itemID, const std::vector< uint8_t > & fileData, const ISOBMFF::IINF & iinf, const ISOBMFF::ILOC & iloc, const ISOBMFF::IPMA & ipma, const ISOBMFF::IPCO & ipco );

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
        
        {
            std::shared_ptr< ISOBMFF::FTYP >               ftyp;
            std::shared_ptr< ISOBMFF::META >               meta;
            std::shared_ptr< ISOBMFF::Box  >               mdat;
            std::shared_ptr< ISOBMFF::IINF >               iinf;
            std::shared_ptr< ISOBMFF::ContainerBox >       iprp;
            std::shared_ptr< ISOBMFF::IPCO >               ipco;
            std::shared_ptr< ISOBMFF::IPMA >               ipma;
            std::shared_ptr< ISOBMFF::ILOC >               iloc;
            std::shared_ptr< ISOBMFF::IREF >               iref;
            std::shared_ptr< ISOBMFF::Box  >               idat;
            std::shared_ptr< ISOBMFF::PITM >               pitm;
            std::shared_ptr< ISOBMFF::THMB >               thmbRef;
            std::vector< uint8_t >                         data;
            std::shared_ptr< ISOBMFF::INFE >               infe;
            std::shared_ptr< ISOBMFF::ILOC::Item >         item;
            std::vector< std::shared_ptr< ISOBMFF::Box > > props;
            std::shared_ptr< ISOBMFF::ILOC::Item::Extent > extent;
            std::shared_ptr< ISOBMFF::IPMA::Entry >        entry;
            std::vector< uint8_t >                         itemData;
            ISOBMFF::BinaryStream                          stream;
            
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
            iprp = meta->GetTypedBox< ISOBMFF::ContainerBox >( "iprp" );
            iref = meta->GetTypedBox< ISOBMFF::IREF >( "iref" );
            idat = meta->GetBox( "idat" );
            pitm = meta->GetTypedBox< ISOBMFF::PITM >( "pitm" );
            
            if
            (
                   iloc == nullptr
                || iinf == nullptr
                || idat == nullptr
                || pitm == nullptr
                || iprp == nullptr
                || iref == nullptr
            )
            {
                continue;
            }
            
            ipco = iprp->GetTypedBox< ISOBMFF::IPCO >( "ipco" );
            ipma = iprp->GetTypedBox< ISOBMFF::IPMA >( "ipma" );
            
            if( ipco == nullptr || ipma == nullptr )
            {
                continue;
            }
            
            {
                std::ifstream           fstream;
                std::ifstream::pos_type length;
                
                fstream.open( path, std::ios::binary | std::ios::ate );
                
                if( fstream.good() == false )
                {
                    continue;
                }
                
                length = fstream.tellg();
                data   = std::vector< uint8_t >( static_cast< std::size_t >( length ) );
                
                fstream.seekg( 0, std::ios::beg );
                fstream.read( reinterpret_cast< char * >( &( data[ 0 ] ) ), length );
            }
            
            infe = iinf->GetItemInfo( pitm->GetItemID() );
            
            if( infe == nullptr )
            {
                continue;
            }
            
            item = iloc->GetItem( pitm->GetItemID() );
            
            if( infe == nullptr )
            {
                continue;
            }
            
            entry = ipma->GetEntry( pitm->GetItemID() );
            
            if( entry == nullptr )
            {
                continue;
            }
            
            props = ipco->GetProperties( *( entry ) );
            
            if( props.size() == 0 )
            {
                continue;
            }
            
            if( item->GetExtents().size() == 0 )
            {
                continue;
            }
            
            std::cout << "Primary item info: " << *( infe ) << std::endl << std::endl;
            std::cout << "Primary item: "      << *( item ) << std::endl << std::endl;
            std::cout << "Item properties:"    << std::endl;
            
            for( const auto & prop: props )
            {
                std::cout << *( prop ) << std::endl;
            }
            
            std::cout << std::endl;
            
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
            
            if( infe->GetItemType() == "hvc1" )
            {
                /* ... */
            }
            else if( infe->GetItemType() == "grid" )
            {
                {
                    ISOBMFF::ImageGrid grid( stream );
                    
                    std::cout << "Image grid: " << grid << std::endl;
                }
            }
            
            std::cout << std::endl;
            
            for( const auto & b: iref->GetBoxes() )
            {
                thmbRef = std::dynamic_pointer_cast< ISOBMFF::THMB >( b );
                
                if( thmbRef == nullptr )
                {
                    continue;
                }
                
                {
                    auto linked( thmbRef->GetToItemIDs() );
                    
                    if( std::find( linked.begin(), linked.end(), pitm->GetItemID() ) != linked.end() )
                    {
                        break;
                    }
                    
                    thmbRef = nullptr;
                }
            }
            
            if( thmbRef != nullptr )
            {
                ExtractItem( thmbRef->GetFromItemID(), data, *( iinf ), *( iloc ), *( ipma ), *( ipco ) );
            }
            else
            {
                continue;
            }
        }
    }
    
    return EXIT_SUCCESS;
}

void ExtractItem( uint32_t itemID, const std::vector< uint8_t > & fileData, const ISOBMFF::IINF & iinf, const ISOBMFF::ILOC & iloc, const ISOBMFF::IPMA & ipma, const ISOBMFF::IPCO & ipco )
{
    std::shared_ptr< ISOBMFF::INFE >               infe;
    std::shared_ptr< ISOBMFF::ILOC::Item >         item;
    std::vector< std::shared_ptr< ISOBMFF::Box > > props;
    std::shared_ptr< ISOBMFF::ILOC::Item::Extent > extent;
    std::shared_ptr< ISOBMFF::IPMA::Entry >        entry;
    std::shared_ptr< ISOBMFF::HVCC >               hvcc;
    
    infe = iinf.GetItemInfo( itemID );
    
    if( infe == nullptr )
    {
        return;
    }
                
    item = iloc.GetItem( itemID );
    
    if( infe == nullptr )
    {
        return;
    }
    
    entry = ipma.GetEntry( itemID );
    
    if( entry == nullptr )
    {
        return;
    }
    
    props = ipco.GetProperties( *( entry ) );
    
    if( props.size() == 0 )
    {
        return;
    }
    
    if( item->GetExtents().size() == 0 )
    {
        return;
    }
    
    extent = item->GetExtents()[ 0 ];
    
    std::cout << "Item info: " << *( infe ) << std::endl << std::endl;
    std::cout << "Item: "      << *( item ) << std::endl << std::endl;
    std::cout << "Item properties:" << std::endl;
    
    for( const auto & prop: props )
    {
        std::cout << *( prop ) << std::endl;
    }
    
    std::cout << std::endl;
    
    for( const auto & b: props )
    {
        if( std::dynamic_pointer_cast< ISOBMFF::HVCC >( b ) != nullptr )
        {
            hvcc = std::dynamic_pointer_cast< ISOBMFF::HVCC >( b );
            
            break;
        }
    }
    
    if( hvcc == nullptr )
    {
        return;
    }
    
    {
        std::vector< uint8_t > hevcData;
        std::vector< uint8_t > sliceData;
        std::vector< uint8_t > nal;
        uint8_t                b1[ 4 ] = { 0, 0, 0, 1 };
        uint8_t                b2[ 3 ] = { 0, 0, 1 };
        size_t                 i;
        
        for( i = 0; i < 2; i++ )
        {
            for( const auto & array: hvcc->GetArrays() )
            {
                for( const auto & unit: array->GetNALUnits() )
                {
                    nal = unit->GetData();
                    
                    if( nal.size() == 0 )
                    {
                        continue;
                    }
                    
                    std::copy( b1, b1 + sizeof( b1 ),  std::back_inserter( hevcData ) );
                    std::copy( nal.begin(), nal.end(), std::back_inserter( hevcData ) );
                }
            }
        }
        
        sliceData = Slice( fileData, extent->GetOffset() + 4, extent->GetLength() - 4 );
        
        std::copy( b2, b2 + sizeof( b2 ), std::back_inserter( hevcData ) );
        std::copy( sliceData.begin(), sliceData.end(), std::back_inserter( hevcData ) );
        
        //SaveData( hevcData, 0, hevcData.size(), "/Users/macmade/Desktop/HEVC.bin" );
        ConvertHEVCData( hevcData );
    }
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wdocumentation"

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}

#pragma clang diagnostic pop

void ConvertHEVCData( const std::vector< uint8_t > & data )
{
    AVCodec        * codec;
    AVCodecContext * context;
    
    std::cout << "Decoding HEVC data: " << data.size() << "  bytes" << std::endl;
    
    av_register_all();
    
    codec = avcodec_find_decoder( AV_CODEC_ID_H265 );
    
    if( codec == nullptr )
    {
        std::cout << "H265 codec not found" << std::endl;
        
        return;
    }
    
    context = avcodec_alloc_context3( codec );
    
    if( avcodec_open2( context, codec, NULL) < 0 )
    {
        std::cout << "Cannot open H265 codec" << std::endl;
        
        return;
    }
}
