#! /bin/sh

sudo rm -v /usr/local/lib/libdbutil.so*
sudo rm -rv /usr/include/db_logging.h
sudo rm -rv /usr/include/db_utils.h
sudo rm -rv /usr/include/dbutils_internal.h
sudo ldconfig
