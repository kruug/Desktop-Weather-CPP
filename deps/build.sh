cd deps

wget https://github.com/bagder/curl/archive/master.tar.gz --nv
tar -xf master.tar.gz

cd curl-master

./buildconf

./configure --prefix=`pwd`/../../deps/32 --disable-ftp --disable-file --disable-ldap --disable-dict --disable-telnet --disable-tftp --disable-rtsp --disable-pop3 --disable-imap --disable-smtp --disable-gopher --disable-ares --disable-debug --with-winssl --without-zlib --without-libidn --host=i686-w64-mingw32 --disable-shared
make
make install

./configure --prefix=`pwd`/../../deps/64 --disable-ftp --disable-file --disable-ldap --disable-dict --disable-telnet --disable-tftp --disable-rtsp --disable-pop3 --disable-imap --disable-smtp --disable-gopher --disable-ares --disable-debug --with-winssl --without-zlib --without-libidn --host=x86_64-w64-mingw32 --disable-shared
make
make install
