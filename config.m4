PHP_ARG_ENABLE([emailhash64],[whether to enable emailhash64 support],[AS_HELP_STRING([--enable-emailhash64],[Enable emailhash64 support])],[no])

if test "$PHP_EMAILHASH64" != "no"; then
	AC_DEFINE(HAVE_EMAILHASH64, 1, [ Have emailhash64 support ])
	PHP_NEW_EXTENSION(emailhash64, emailhash64.c, $ext_shared)
fi
