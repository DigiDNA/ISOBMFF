ISOBMFF
=======

[![Build Status](https://img.shields.io/travis/macmade/ISOBMFF.svg?branch=master&style=flat)](https://travis-ci.org/macmade/ISOBMFF)
[![Coverage Status](https://img.shields.io/coveralls/macmade/ISOBMFF.svg?branch=master&style=flat)](https://coveralls.io/r/macmade/ISOBMFF?branch=master)
[![Issues](http://img.shields.io/github/issues/macmade/ISOBMFF.svg?style=flat)](https://github.com/macmade/ISOBMFF/issues)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)
![License](https://img.shields.io/badge/license-boost-brightgreen.svg?style=flat)
[![Contact](https://img.shields.io/badge/contact-@macmade-blue.svg?style=flat)](https://twitter.com/macmade)  
[![Donate-Patreon](https://img.shields.io/badge/donate-patreon-yellow.svg?style=flat)](https://patreon.com/macmade)
[![Donate-Gratipay](https://img.shields.io/badge/donate-gratipay-yellow.svg?style=flat)](https://www.gratipay.com/macmade)
[![Donate-Paypal](https://img.shields.io/badge/donate-paypal-yellow.svg?style=flat)](https://paypal.me/xslabs)

C++ Library for ISO/IEC 14496-12 - ISO Base Media File Format (QuickTime, MPEG-4, HEIF, etc)
--------------------------------------------------------------------------------------------

About
-----

**ISOBMFF** is a C++ library for reading/parsing files in the _**ISO Base Media File Format**_ (ISO/IEC 14496-12).

The ISO Base Media File Format is a container format, used by many file types, including:

 - **QuickTime** (`.mov`)
 - **MPEG-4** (`.m4v`, `.m4a`, etc)
 - **3GP** (`.3g2`)
 - **HEIF/HEIC** (`.heif`, `.heic`, etc)
 - ... and many others
 
Support for editing/writing files is not available at the moment, but the library has been designed for this goal in mind, so writing support will eventually become available.
 
### GUI Screenshots

![Screenshot 1](Assets/Screen-1.png "Screenshot 1")

### Building

#### macOS

An Xcode project is provided for convenience, containing the following targets:

 - `ISOBMFF`: The main cross-platform C++ library.
 - `ISOBMFF-Dump`: A cross-platform command-line utility for dumping files.

Note that you can also build the library with `make`, on the command line.

#### Windows

An VisualStudio solution is provided for convenience, containing the following targets:

 - `ISOBMFF Static v120xp`: A static library built with the V120XP toolset (VS 2013)
 - `ISOBMFF Static v140xp`: A static library built with the V140XP toolset (VS 2015)
 - `ISOBMFF DLL v120xp`: A dynamic library (DLL) built with the V120XP toolset (VS 2013)
 - `ISOBMFF DLL v140xp`: A dynamic library (DLL) built with the V140XP toolset (VS 2015)
 - `ISOBMFF-Dump`: A cross-platform command-line utility for dumping files.

#### Linux/Unix

The library can be build with `make`, on the command line.

### Library Usage

Parsing is done with the `ISOBMFF::Parser` class:

```cpp
ISOBMFF::Parser parser;

try
{
    parser.Parse( "path/to/some/file" );
}
catch( ... )
{}
```

When the parser is done, an instance of `ISOBMFF::File` can be retrieved:

```cpp
std::shared_ptr< ISOBMFF::File > file = parser.GetFile();
```

Boxes can then be retrieved the following way, from the file:

```cpp
std::shared_ptr< ISOBMFF::Box > box = file.GetBox( "ftyp" );
```
    
If the box does not exist, it will return `nullptr`.

A typed box can be retrieved the following way:

```cpp
std::shared_ptr< ISOBMFF::FTYP > ftyp = file.GetTypedBox< ISOBMFF::FTYP >( "ftyp" );
```

Here, `nullptr` will be returned if the box does not exist, or is not of the correct type.

Container boxes acts just the same:

```cpp
std::shared_ptr< ISOBMFF::ContainerBox > moov = file.GetTypedBox< ISOBMFF::ContainerBox >( "moov" );
std::shared_ptr< ISOBMFF::TRAK         > trak = moov.GetTypedBox< ISOBMFF::TRAK         >( "trak" );
```

The parser also supports custom boxes:

```cpp
parser.RegisterBox( "abcd", [ = ]( void ) -> std::shared_ptr< CustomBox > { return std::make_shared< CustomBox >(); } );
```

It will then create an instance of `CustomBox` when encountering an `abcd` box somewhere in the file.

The custom class needs at least to inherit from `Box`:

```cpp
class CustomBox: public ISOBMFF::Box
{
    public:
        
        CustomBox( void ): Box( "abcd" )
        {}
        
        void CustomBox::ReadData( Parser & parser, BinaryStream & stream )
        {
            /* Read box data here... */
        }
        
        std::vector< std::pair< std::string, std::string > > CustomBox::GetDisplayableProperties( void ) const
        {
            /* Returns box properties, to support output... */
            return {};
        }
};
```

License
-------

**ISOBMFF** is released under the terms of the MIT License.

Repository Infos
----------------

    Owner:          Jean-David Gadina - XS-Labs
    Web:            www.xs-labs.com
    Blog:           www.noxeos.com
    Twitter:        @macmade
    GitHub:         github.com/macmade
    LinkedIn:       ch.linkedin.com/in/macmade/
    StackOverflow:  stackoverflow.com/users/182676/macmade
