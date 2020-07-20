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
 * @header      ILOC.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_ILOC_HPP
#define ISOBMFF_ILOC_HPP

#include <XS/PIMPL/Object.hpp>
#include <memory>
#include <algorithm>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <ISOBMFF/DisplayableObjectContainer.hpp>
#include <cstdint>
#include <vector>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT ILOC: public FullBox, public DisplayableObjectContainer, public XS::PIMPL::Object< ILOC >
    {
        public:
            
            using XS::PIMPL::Object< ILOC >::impl;
            
            ILOC();
            
            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            
            virtual std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;
            
            uint8_t GetOffsetSize()     const;
            uint8_t GetLengthSize()     const;
            uint8_t GetBaseOffsetSize() const;
            uint8_t GetIndexSize()      const;
            
            void SetOffsetSize( uint8_t value );
            void SetLengthSize( uint8_t value );
            void SetBaseOffsetSize( uint8_t value );
            void SetIndexSize( uint8_t value );
            
            class ISOBMFF_EXPORT Item: public XS::PIMPL::Object< Item >, public DisplayableObject, public DisplayableObjectContainer
            {
                public:
                    
                    using XS::PIMPL::Object< Item >::impl;
                    
                    Item();
                    Item( BinaryStream & stream, const ILOC & iloc );
                    
                    std::string GetName() const override;
                    
                    uint32_t GetItemID()             const;
                    uint8_t  GetConstructionMethod() const;
                    uint16_t GetDataReferenceIndex() const;
                    uint64_t GetBaseOffset()         const;
                    
                    void SetItemID( uint32_t value );
                    void SetConstructionMethod( uint8_t value );
                    void SetDataReferenceIndex( uint16_t value );
                    void SetBaseOffset( uint64_t value );
                    
                    void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
                    
                    std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;
                    std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;
                    
                    class ISOBMFF_EXPORT Extent: public XS::PIMPL::Object< Extent >, public DisplayableObject
                    {
                        public:
                            
                            using XS::PIMPL::Object< Extent >::impl;
                            
                            Extent();
                            Extent( BinaryStream & stream, const ILOC & iloc );
                            
                            std::string GetName() const override;
                            
                            uint64_t GetIndex()  const;
                            uint64_t GetOffset() const;
                            uint64_t GetLength() const;
                            
                            void SetIndex( uint64_t value );
                            void SetOffset( uint64_t value );
                            void SetLength( uint64_t value );
                            
                            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;
                    };
                    
                    std::vector< std::shared_ptr< Extent > > GetExtents() const;
                    void                                     AddExtent( std::shared_ptr< Extent > extent );
            };
            
            std::vector< std::shared_ptr< Item > > GetItems()                 const;
            std::shared_ptr< Item >                GetItem( uint32_t itemID ) const;
            void                                   AddItem( std::shared_ptr< Item > item );
    };
}

#endif /* ISOBMFF_ILOC_HPP */
