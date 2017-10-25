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
 * @header      ISOBMFF.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_HPP
#define ISOBMFF_HPP

#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/Utils.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/BinaryStream.hpp>
#include <ISOBMFF/DisplayableObject.hpp>
#include <ISOBMFF/DisplayableObjectContainer.hpp>
#include <ISOBMFF/Box.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <ISOBMFF/Container.hpp>
#include <ISOBMFF/ContainerBox.hpp>
#include <ISOBMFF/File.hpp>
#include <ISOBMFF/Matrix.hpp>
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
#include <ISOBMFF/SingleItemTypeReferenceBox.hpp>
#include <ISOBMFF/DIMG.hpp>
#include <ISOBMFF/THMB.hpp>
#include <ISOBMFF/CDSC.hpp>
#include <ISOBMFF/COLR.hpp>
#include <ISOBMFF/ISPE.hpp>
#include <ISOBMFF/IPMA.hpp>
#include <ISOBMFF/PIXI.hpp>
#include <ISOBMFF/IPCO.hpp>
#include <ISOBMFF/ImageGrid.hpp>
#include <ISOBMFF/STSD.hpp>
#include <ISOBMFF/FRMA.hpp>
#include <ISOBMFF/SCHM.hpp>

#ifdef _WIN32
#include <ISOBMFF/WIN32.hpp>
#endif

#endif /* ISOBMFF_HPP */

