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
 * @header      Matrix.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_MATRIX_HPP
#define ISOBMFF_MATRIX_HPP

#include <memory>
#include <algorithm>
#include <Macros.hpp>
#include <DisplayableObject.hpp>
#include <cstdint>

namespace ISOBMFF
{
    /*!
     * @class       Matrix
     * @abstract    Represents a transformation of video images for presentation.
     */
    class ISOBMFF_EXPORT Matrix: public DisplayableObject
    {
        public:

            /*!
             * @function    Matrix
             * @abstract    Default constructor.
             */
            Matrix();

            /*!
             * @function    Matrix
             * @abstract    Creates a Matrix object.
             * @param       a   The matrix A coordinate.
             * @param       b   The matrix B coordinate.
             * @param       u   The matrix U coordinate.
             * @param       c   The matrix C coordinate.
             * @param       d   The matrix D coordinate.
             * @param       v   The matrix V coordinate.
             * @param       x   The matrix X coordinate.
             * @param       y   The matrix Y coordinate.
             * @param       w   The matrix W coordinate.
             */
            Matrix( uint32_t a, uint32_t b, uint32_t u, uint32_t c, uint32_t d, uint32_t v, uint32_t x, uint32_t y, uint32_t w );

            /*!
             * @function    Matrix
             * @abstract    Copy constructor.
             * @param       o   The object to copy from.
             */
            Matrix( const Matrix & o );

            /*!
             * @function    Matrix
             * @abstract    Move constructor.
             * @param       o   The object to move from.
             */
            Matrix( Matrix && o ) noexcept;

            /*!
             * @function    ~Matrix
             * @abstract    Destructor.
             */
            virtual ~Matrix() override;

            /*!
             * @function    operator=
             * @abstract    Assignment operator.
             * @param       o   The object to assign from.
             */
            Matrix & operator =( Matrix o );

            /*!
             * @function    GetName
             * @abstract    Gets the object's name.
             * @result      The object's name
             * @see         DisplayableObject
             */
            std::string GetName() const override;

            /*!
             * @function    GetA
             * @abstract    Gets the matrix A coordinate.
             * @result      The matrix A coordinate.
             */
            uint32_t GetA() const;

            /*!
             * @function    GetB
             * @abstract    Gets the matrix B coordinate.
             * @result      The matrix B coordinate.
             */
            uint32_t GetB() const;

            /*!
             * @function    GetU
             * @abstract    Gets the matrix U coordinate.
             * @result      The matrix U coordinate.
             */
            uint32_t GetU() const;

            /*!
             * @function    GetC
             * @abstract    Gets the matrix C coordinate.
             * @result      The matrix C coordinate.
             */
            uint32_t GetC() const;

            /*!
             * @function    GetD
             * @abstract    Gets the matrix D coordinate.
             * @result      The matrix D coordinate.
             */
            uint32_t GetD() const;

            /*!
             * @function    GetV
             * @abstract    Gets the matrix V coordinate.
             * @result      The matrix V coordinate.
             */
            uint32_t GetV() const;

            /*!
             * @function    GetX
             * @abstract    Gets the matrix X coordinate.
             * @result      The matrix X coordinate.
             */
            uint32_t GetX() const;

            /*!
             * @function    GetY
             * @abstract    Gets the matrix Y coordinate.
             * @result      The matrix Y coordinate.
             */
            uint32_t GetY() const;

            /*!
             * @function    GetW
             * @abstract    Gets the matrix W coordinate.
             * @result      The matrix W coordinate.
             */
            uint32_t GetW() const;

            /*!
             * @function    SetA
             * @abstract    Sets the matrix A coordinate.
             * @param       value   The matrix A coordinate to set.
             */
            void SetA( uint32_t value );

            /*!
             * @function    SetWB
             * @abstract    Sets the matrix B coordinate.
             * @param       value   The matrix B coordinate to set.
             */
            void SetB( uint32_t value );

            /*!
             * @function    SetU
             * @abstract    Sets the matrix U coordinate.
             * @param       value   The matrix U coordinate to set.
             */
            void SetU( uint32_t value );

            /*!
             * @function    SetC
             * @abstract    Sets the matrix C coordinate.
             * @param       value   The matrix C coordinate to set.
             */
            void SetC( uint32_t value );

            /*!
             * @function    SetD
             * @abstract    Sets the matrix D coordinate.
             * @param       value   The matrix D coordinate to set.
             */
            void SetD( uint32_t value );

            /*!
             * @function    SetV
             * @abstract    Sets the matrix V coordinate.
             * @param       value   The matrix V coordinate to set.
             */
            void SetV( uint32_t value );

            /*!
             * @function    SetX
             * @abstract    Sets the matrix X coordinate.
             * @param       value   The matrix X coordinate to set.
             */
            void SetX( uint32_t value );

            /*!
             * @function    SetY
             * @abstract    Sets the matrix Y coordinate.
             * @param       value   The matrix Y coordinate to set.
             */
            void SetY( uint32_t value );

            /*!
             * @function    SetW
             * @abstract    Sets the matrix W coordinate.
             * @param       value   The matrix W coordinate to set.
             */
            void SetW( uint32_t value );

            /*!
             * @function    WriteDescription
             * @abstract    Writes the matrix description to an output stream.
             * @param       os              The output stream in which to write the description.
             * @param       indentLevel     The requested indent level.
             * @see         DisplayableObject
             */
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

            /*!
             * @function    GetDisplayableProperties
             * @abstract    Gets the matrix displayable properties.
             * @result      The matrix displayable properties.
             * @see         DisplayableObject
             */
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            /*!
             * @function    swap
             * @abstract    Swap two objects.
             * @param       o1  The first object to swap.
             * @param       o2  The second object to swap.
             */
            ISOBMFF_EXPORT friend void swap( Matrix & o1, Matrix & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_MATRIX_HPP */
