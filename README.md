ircd-chatd install howto
====

    libtoolize --ltdl
    autoconf
    ./configure --prefix=(where IRCd shall be installed to)
    make -j (cores in processor) all install

And if you were wondering how to change the prefixes for +Wwah from
blank, blank blank and blank to any character you desire...

Check reference.conf and/or example.conf.

If you are interested in meeting the developer(s), go to:

    ircs://irc.pitnet.ga:6697/lobby

Thankya!
