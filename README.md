ircd-chatd install howto
====

   libtoolize --ltdl
   autoconf
   ./configure --prefix=(where IRCd shall be installed to)
   make -j (cores in processor) all install
