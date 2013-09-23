/*
  This file is part of the kabc library.
  Copyright (c) 2006-2007 Allen Winter <winter@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#ifndef KABC_EXPORT_H
#define KABC_EXPORT_H

#include <kdemacros.h>

#ifndef KABC_EXPORT
# if defined(KDEPIM_STATIC_LIBS)
   /* No export/import for static libraries */
#  define KABC_EXPORT
# elif defined(MAKE_KABC_LIB)
   /* We are building this library */
#  define KABC_EXPORT KDE_EXPORT
# else
   /* We are using this library */
#  define KABC_EXPORT KDE_IMPORT
# endif
#endif

# ifndef KABC_EXPORT_DEPRECATED
#  if !defined( WANT_DEPRECATED_KABC_API )
#    define KABC_EXPORT_DEPRECATED KDE_DEPRECATED KABC_EXPORT
#    define KABC_DEPRECATED_EXPORT KDE_DEPRECATED KABC_EXPORT
#    define KABC_DEPRECATED KDE_DEPRECATED
#  else
#    define KABC_EXPORT_DEPRECATED KABC_EXPORT
#    define KABC_DEPRECATED_EXPORT KABC_EXPORT
#    define KABC_DEPRECATED
#  endif
# endif

#endif
