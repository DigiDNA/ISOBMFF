ISOBMFF
=======

[![Build Status](https://img.shields.io/github/actions/workflow/status/DigiDNA/ISOBMFF/ci-mac-build.yaml?label=Build&logo=apple)](https://github.com/DigiDNA/ISOBMFF/actions/workflows/ci-mac-build.yaml)
[![Build Status](https://img.shields.io/github/actions/workflow/status/DigiDNA/ISOBMFF/ci-win-build.yaml?label=Build&logo=apple)](https://github.com/DigiDNA/ISOBMFF/actions/workflows/ci-win-build.yaml)
[![Issues](http://img.shields.io/github/issues/DigiDNA/ISOBMFF.svg?logo=github)](https://github.com/DigiDNA/ISOBMFF/issues)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?logo=git)
![License](https://img.shields.io/badge/license-mit-brightgreen.svg?logo=open-source-initiative)  
[![Contact](https://img.shields.io/badge/follow-@digidna-blue.svg?logo=twitter&style=social)](https://twitter.com/digidna)

C++ Library for ISO/IEC 14496-12 - ISO Base Media File Format (QuickTime, MPEG-4, HEIF, etc)
--------------------------------------------------------------------------------------------

About
-----

**ISOBMFF** is a cross-platform C++ library for reading/parsing files in the _**ISO Base Media File Format**_ (ISO/IEC 14496-12).

The ISO Base Media File Format is a container format, used by many file types, including:

 - **QuickTime** (`.mov`)
 - **MPEG-4** (`.m4v`, `.m4a`, etc)
 - **3GP** (`.3g2`)
 - **HEIF/HEIC** (`.heif`, `.heic`, etc)
 - ... and many others
 
Support for editing/writing files is not available at the moment, but the library has been designed for this goal in mind, so writing support will eventually become available.

### ISO Base Media File Format

> ISO base media file format (ISO/IEC 14496-12 - MPEG-4 Part 12) defines a general structure for time-based multimedia files such as video and audio.  
> It is designed as a flexible, extensible format that facilitates interchange, management, editing and presentation of the media.  
> The presentation may be local, or via a network or other stream delivery mechanism.  
> The file format is designed to be independent of any particular network protocol while enabling support for them in general.  
> It is used as the basis for other media file formats (e.g. container formats MP4 and 3GP).

Source: [Wikipedia](https://en.wikipedia.org/wiki/ISO_base_media_file_format)

Building
--------

### Fetch the submodules

After you have cloned the ISOBMFF project, you will need to fetch the submodules that are defined in the .gitmodules file.

`git submodule update --init --recursive`


### macOS

An Xcode project is provided for convenience, containing the following targets:

 - `ISOBMFF`: The main cross-platform C++ library.
 - `ISOBMFF-Dump`: A cross-platform command-line utility for dumping files.

Note that you can also build the library with `make`, on the command line.

### Windows

An VisualStudio solution is provided for convenience, containing the following targets:

 - `ISOBMFF Static v142`: A static library built with the V142 toolset (VS 2019)
 - `ISOBMFF Static v143`: A static library built with the V143 toolset (VS 2022)
 - `ISOBMFF DLL v142`: A dynamic library (DLL) built with the V142 toolset (VS 2019)
 - `ISOBMFF DLL v143`: A dynamic library (DLL) built with the V143 toolset (VS 2022)
 - `ISOBMFF-Dump`: A cross-platform command-line utility for dumping files.

### Linux/Unix

The library can be build with `make`, on the command line.

Library Usage
-------------

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
std::shared_ptr< ISOBMFF::Box > box = file->GetBox( "ftyp" );
```
    
If the box does not exist, it will return `nullptr`.

A typed box can be retrieved the following way:

```cpp
std::shared_ptr< ISOBMFF::FTYP > ftyp = file->GetTypedBox< ISOBMFF::FTYP >( "ftyp" );
```

Here, `nullptr` will be returned if the box does not exist, or is not of the correct type.

Container boxes acts just the same:

```cpp
std::shared_ptr< ISOBMFF::ContainerBox > moov = file->GetTypedBox< ISOBMFF::ContainerBox >( "moov" );
std::shared_ptr< ISOBMFF::MVHD         > mvhd = moov->GetTypedBox< ISOBMFF::MVHD         >( "mvhd" );
```

The parser also supports custom boxes:

```cpp
parser.RegisterBox( "abcd", [ = ]() -> std::shared_ptr< CustomBox > { return std::make_shared< CustomBox >(); } );
```

It will then create an instance of `CustomBox` when encountering an `abcd` box somewhere in the file.

The custom class needs at least to inherit from `Box`:

```cpp
class CustomBox: public ISOBMFF::Box
{
    public:
        
        CustomBox(): Box( "abcd" )
        {}
        
        void CustomBox::ReadData( Parser & parser, BinaryStream & stream )
        {
            /* Read box data here... */
        }
        
        std::vector< std::pair< std::string, std::string > > CustomBox::GetDisplayableProperties() const
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

    Owner:          DigiDNA
    Web:            www.digidna.net
    Blog:           imazing.com/blog
    Twitter:        @DigiDNA
    GitHub:         github.com/DigiDNA
