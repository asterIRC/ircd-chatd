ircd-chatd install howto
====

    libtoolize --ltdl
    autoconf
    ./configure --prefix=(where IRCd shall be installed to)
    make all install

on freebsd, last line is

    gmake all install

And if you were wondering how to change the prefixes for +Wwah from
blank, blank blank and blank to any character you desire...

Check reference.conf and/or example.conf.

If you are interested in meeting the developer(s), go to:

    ircs://irc.umbrellix.net:6697/cafe
    irc.umbrellix.net +6697 #cafe

Thankya!

ircd-chatd.c is the shalture protocol module for this ircd.
