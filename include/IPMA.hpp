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
 * @header      IPMA.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_IPMA_HPP
#define ISOBMFF_IPMA_HPP

#include <memory>
#include <algorithm>
#include <Macros.hpp>
#include <FullBox.hpp>
#include <DisplayableObject.hpp>
#include <DisplayableObjectContainer.hpp>
#include <vector>
#include <cstdint>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT IPMA: public FullBox, public DisplayableObjectContainer
    {
        public:

            IPMA();
            IPMA( const IPMA & o );
            IPMA( IPMA && o ) noexcept;
            virtual ~IPMA() override;

            IPMA & operator =( IPMA o );

            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

            std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;
            std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;

            class ISOBMFF_EXPORT Entry: public DisplayableObject, public DisplayableObjectContainer
            {
                public:

                    Entry();
                    Entry( BinaryStream & stream, const IPMA & ipma );
                    Entry( const Entry & o );
                    Entry( Entry && o ) noexcept;
                    virtual ~Entry() override;

                    Entry & operator =( Entry o );

                    std::string GetName() const override;

                    uint32_t GetItemID() const;
                    void     SetItemID( uint32_t value );

                    void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

                    std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;
                    std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;

                    class ISOBMFF_EXPORT Association: public DisplayableObject
                    {
                        public:

                            Association();
                            Association( BinaryStream & stream, const IPMA & ipma );
                            Association( const Association & o );
                            Association( Association && o ) noexcept;
                            virtual ~Association() override;

                            Association & operator =( Association o );

                            std::string GetName() const override;

                            bool     GetEssential()     const;
                            uint16_t GetPropertyIndex() const;

                            void SetEssential( bool value );
                            void SetPropertyIndex( uint16_t value );

                            std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

                            ISOBMFF_EXPORT friend void swap( Association & o1, Association & o2 );

                        private:

                            class IMPL;

                            std::unique_ptr< IMPL > impl;
                    };

                    std::vector< std::shared_ptr< Association > > GetAssociations() const;
                    void                                          AddAssociation( std::shared_ptr< Association > association );

                    ISOBMFF_EXPORT friend void swap( Entry & o1, Entry & o2 );

                private:

                    class IMPL;

                    std::unique_ptr< IMPL > impl;
            };

            std::vector< std::shared_ptr< Entry > > GetEntries()                const;
            std::shared_ptr< Entry >                GetEntry( uint32_t itemID ) const;
            void                                    AddEntry( std::shared_ptr< Entry > entry );

            ISOBMFF_EXPORT friend void swap( IPMA & o1, IPMA & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_IPMA_HPP */
