#-------------------------------------------------------------------------------
# The MIT License (MIT)
# 
# Copyright (c) 2017 DigiDNA - www.digidna.net
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#-------------------------------------------------------------------------------

_HAS_XSDOCGEN := $(shell if [ -f "/usr/local/bin/XSDocgen" ]; then echo true; else echo false; fi )

.PHONY: all clean doc headers

all: doc
	
	@:

clean:
	
	@rm -rf tmp/*

headers:
	
	@cp -r ../ISOBMFF/include tmp
	@find . -name "*.hpp" -exec bash -c 'mv "$$1" "$${1%.hpp}".h' - '{}' \;
	
doc: headers
	
ifeq ($(_HAS_XSDOCGEN),true)
	@/usr/local/bin/XSDocgen \
	@    --clear \
	@    --source tmp/include \
	@    --output web \
	@    --source-root-prefix "/ISOBMFF/" \
	@    --project-name "ISOBMFF" \
	@    --project-copyright "DigiDNA &copy; %Y - All Rights Reserved" \
	@    --project-version "0.0.0-0" \
	@    --project-timezone "Europe/Zurich" \
	@    --company-name "DigiDNA" \
	@    --company-url "https://www.digidna.net/"
endif
	
