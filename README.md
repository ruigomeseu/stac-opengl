Install on Mac OS X
-------------------

First you need Xcode, and the Xcode command line tools. After Xcode install, open Xcode, Preferences, Downloads, Install Command Line Tools.

Install brew from http://mxcl.github.com/homebrew/

```
ruby -e "$(curl -fsSL https://raw.github.com/mxcl/homebrew/go)"
```

Install Glui and Glew from brew

```
brew install glui
brew install glew
```

Compile using make
```
make
```

Using Xcode
-----------

You can use xcode to compile instead of make/gcc. Open the CGF project, and build. Now you need to right click on Products/libCGF.a, show in Finder and copy it to the CGFlib/lib directory.

Now you can open CGFExample and compile it. Remember, you need glui and glew installed (which means the libraries will be in /usr/local/lib and headers in /usr/local/include).

Now you can use the debugger in Xcode ;)
