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
 * @header      ILOC.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_ILOC_HPP
#define ISOBMFF_ILOC_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <cstdint>
#include <vector>

namespace ISOBMFF
{
    class ILOC: public FullBox, public XS::PIMPL::Object< ILOC >
    {
        public:
            
            using XS::PIMPL::Object< ILOC >::impl;
            
            ILOC( void );
            
            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            
            uint8_t GetOffsetSize( void )     const;
            uint8_t GetLengthSize( void )     const;
            uint8_t GetBaseOffsetSize( void ) const;
            uint8_t GetIndexSize( void )      const;
            
            void SetOffsetSize( uint8_t value );
            void SetLengthSize( uint8_t value );
            void SetBaseOffsetSize( uint8_t value );
            void SetIndexSize( uint8_t value );
            
            class Item: public XS::PIMPL::Object< Item >
            {
                public:
                    
                    using XS::PIMPL::Object< Item >::impl;
                    
                    Item( void );
                    Item( BinaryStream & stream, const ILOC & iloc );
                    
                    uint32_t GetItemID( void )             const;
                    uint8_t  GetConstructionMethod( void ) const;
                    uint16_t GetDataReferenceIndex( void ) const;
                    uint64_t GetBaseOffset( void )         const;
                    
                    void SetItemID( uint32_t value );
                    void SetConstructionMethod( uint8_t value );
                    void SetDataReferenceIndex( uint16_t value );
                    void SetBaseOffset( uint64_t value );
                    
                    void WriteDescription( std::ostream & os, std::size_t indentLevel ) const;
                    
                    friend std::ostream & operator << ( std::ostream & os, const Item & item );
                    
                    class Extent: public XS::PIMPL::Object< Extent >
                    {
                        public:
                            
                            using XS::PIMPL::Object< Extent >::impl;
                            
                            Extent( void );
                            Extent( BinaryStream & stream, const ILOC & iloc );
                            
                            uint64_t GetIndex( void )  const;
                            uint64_t GetOffset( void ) const;
                            uint64_t GetLength( void ) const;
                            
                            void SetIndex( uint64_t value );
                            void SetOffset( uint64_t value );
                            void SetLength( uint64_t value );
                            
                            friend std::ostream & operator << ( std::ostream & os, const Extent & extent );
                    };
                    
                    std::vector< Extent > GetExtents( void ) const;
                    void                  AddExtent( const Extent & extent );
            };
            
            std::vector< Item > GetItems( void ) const;
            void                AddItem( const Item & item );
    };
}

#endif /* ISOBMFF_ILOC_HPP */
