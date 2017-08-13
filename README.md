PHP bindings for fastText.
======================

Install fastText library
------

````
$ git clone https://github.com/Yujiro3/fastText.git
$ cd fastText
$ ./configure CXX="c++" CXXFLAGS="-O3 -funroll-loops"
$ make
$ sudo make install
````

Build
------

````
$ git clone https://github.com/Yujiro3/fastText-php.git
$ cd fastText-php
$ phpize
$ ./configure CC="gcc" CFLAGS="-O3 -funroll-loops" LIBS="-lfasttext -lpthread"
$ make
$ sudo make install
$ echo "extension=fasttext.so" > /etc/php/7.0/mods-available/fasttext.ini
$ cd /etc/php/7.0/cli/conf.d
$ sudo ln -s /etc/php/7.0/mods-available/fasttext.ini ./20-fasttext.ini
````
