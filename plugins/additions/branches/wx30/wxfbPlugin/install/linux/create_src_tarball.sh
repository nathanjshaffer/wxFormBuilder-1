#!/bin/bash
#*****************************************************************************
#* Copyright (C) 2007 Ryan Mulder
#*
#* This program is free software; you can redistribute it and/or
#* modify it under the terms of the GNU General Public License
#* as published by the Free Software Foundation; either version 2
#* of the License, or (at your option) any later version.
#*
#* This program is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#* GNU General Public License for more details.
#*
#* You should have received a copy of the GNU General Public License
#* along with this program; if not, write to the Free Software
#* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#*
#*****************************************************************************
# this function does the actual work of making the source package
# the version is passed to it as the first argument, below
function make_src_tarball
{
	set -e

	# root source dir
	basedir=.
	
	# create Makefiles

	  # Build premake
	  PREMAKE_DIR=sdk/premake
	  make -C$PREMAKE_DIR/src -f../build/Makefile

	  # Use premake to generate Makefiles
	  $PREMAKE_DIR/bin/premake --linux --target gnu --unicode --with-wx-shared

	  # remove premake, as it is no longer necessary
	  rm -rf $PREMAKE_DIR
	
	# use a temporary directory
	tmpdir=wxfb-wxadditions-$1 #.orig

	cp -R $basedir   ../$tmpdir
	cd ..

	tar czf wxfb-wxadditions_$1.orig.tar.gz $tmpdir
	rm -rf $tmpdir
}

changelog="install/linux/debian/changelog"

if [ ! -f $changelog ];
then
  echo "Sorry, could not find "$changelog". Need it to parse the version."
  exit 1
fi
echo "hihihi"
cat "$changelog" |
while read line;
do
 version=`expr match "$line" '.*\([0-9]\.[0-9]\{1,2\}\.[0-9]\+\)'`
 if [ -n "$version" ]
 then
 echo "$version"
   # because I redirected cat to the while loop, bash spawned a subshell
   # this means "version" will go out of scope at the end of the loop
   # so I need to do everything here
   
   make_src_tarball $version
   break
 fi
done

exit
