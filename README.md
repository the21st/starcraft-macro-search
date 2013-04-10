## Download

To download the source code, use Mercurial: `hg clone https://the21st@bitbucket.org/the21st/starcraft-macro-search`

## Prerequisites

Starcraft Macro Search was maintained using Visual Studio 2012. Visual Studio 2008 or newer can be used to compile the source, however, VS Solutions and Projects are for the 2012 version.

List of Prerequisites for compiling:

* [Visual Studio 2010][vs2010] OR [Windows SDK v7.1][winSDK] (required for VS2012 to get v90 support)
* [Visual Studio 2012][vs2012] (any version)
* [BWAPI 3.7.4][bwapi] (or higher)
* [BOOST 1.47.0][boost] (or higher) 

The Starcraft Macro Search project files use Windows Environment Variables to point to their required libraries.

[vs2010]: http://www.microsoft.com/visualstudio/eng/downloads
[vs2012]: http://www.microsoft.com/visualstudio/11/en-us
[winSDK]: http://www.microsoft.com/en-us/download/details.aspx?id=8279
[bwapi]: http://code.google.com/p/bwapi/
[boost]: http://www.boost.org/

List of Required Windows System Environment Variables:

* BWAPI_DIR - BWAPI root directory
* BOOST_DIR - BOOST root directory 

To edit these in Windows 7 right click "My Computer" > Properties > Advanced System Settings > Environment Variables:

NOTE: These variables CANNOT CONTAIN SPACES! (VS limitation)

## Compile

1. Open `MacroSearchWithUAB.sln` in VS 2012
2. Choose not to upgrade the projects (bwapi requires v90).
3. Build solution.