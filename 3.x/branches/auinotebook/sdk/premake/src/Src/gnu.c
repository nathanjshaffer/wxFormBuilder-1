/**********************************************************************
 * Premake - gnu.c
 * The GNU makefile target
 *
 * Copyright (c) 2002-2005 Jason Perkins and the Premake project
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License in the file LICENSE.txt for details.
 **********************************************************************/

#include <stdio.h>
#include <string.h>
#include "premake.h"
#include "arg.h"
#include "gnu.h"

static int writeRootMakefile();
static const char* listInterPackageDeps(const char* name);


int gnu_generate()
{
	int i;

	puts("Generating GNU makefiles:");

	if (!writeRootMakefile())
		return 0;

	for (i = 0; i < prj_get_numpackages(); ++i)
	{
		int result;

		prj_select_package(i);

		printf("...%s\n", prj_get_pkgname());

		if (prj_is_lang("c#"))
		{
			result = gnu_cs();
		}
		else if (prj_is_lang("c++") || prj_is_lang("c"))
		{
			result = gnu_cpp();
		}
		else
		{
			printf("** Error: unrecognized language '%s'\n", prj_get_language());
			return 0;
		}

		if (!result)
			return 0;
	}

	return 1;
}



static int writeRootMakefile()
{
	const char* arg;
	int i;

	if (!io_openfile(path_join(prj_get_path(), "Makefile", "")))
		return 0;

	/* Print the file header, showing the possible build configurations */
	io_print("# Makefile autogenerated by premake\n");
	io_print("# Don't edit this file! Instead edit `premake.lua` then rerun `make`\n");
	io_print("# Options:\n");
	io_print("#   CONFIG=[");
	prj_select_package(0);
	for (i = 0; i < prj_get_numconfigs(); ++i)
	{
		prj_select_config(i);
		if (i > 0)
			io_print("|");
		io_print(prj_get_cfgname());
	}
	io_print("]\n\n");
	
	/* Set a default build config if none specified */
	prj_select_config(0);
	io_print("ifndef CONFIG\n");
	io_print("  CONFIG=%s\n", prj_get_cfgname());
	io_print("endif\n\n");
	io_print("export CONFIG\n\n");

	/* List all of the available make targets */
	io_print(".PHONY: all clean");
	for (i = 0; i < prj_get_numpackages(); ++i)
	{
		prj_select_package(i);
		io_print(" %s", prj_get_pkgname());
	}
	io_print("\n\n");

	/* Make rules */
	io_print("all:");
	for (i = 0; i < prj_get_numpackages(); ++i)
	{
		prj_select_package(i);
		io_print(" %s", prj_get_pkgname());
	}
	io_print("\n\n");

	/* Target to regenerate the makefiles when the premake scripts change */
	strcpy(g_buffer, path_build(prj_get_path(), "."));
	io_print("Makefile: %s", path_combine(g_buffer, prj_get_script()));
	for (i = 0; i < prj_get_numpackages(); ++i)
	{
		prj_select_package(i);
		if (!matches(prj_get_script(), prj_get_pkgscript()))
		{
			strcpy(g_buffer, path_build(prj_get_path(), "."));
			io_print(" %s", path_combine(g_buffer, prj_get_pkgscript()));
		}
	}
	io_print("\n");
	io_print("\t@echo ==== Regenerating Makefiles ====\n");
	io_print("\t@premake --file $^");
	arg_reset();
	arg = arg_getflag();
	while (arg != NULL)
	{
		if (matches(arg, "--file"))
		{
			arg_getflagarg();
		}
		else
		{
			io_print(" %s", arg);
		}
		arg = arg_getflag();
	}
	io_print("\n\n");

	/* Individual package targets */
	for (i = 0; i < prj_get_numpackages(); ++i)
	{
		prj_select_package(i);
		prj_select_config(0);

		io_print("%s:", prj_get_pkgname());
		print_list(prj_get_links(), " ", "", "", listInterPackageDeps);
		io_print("\n");

		io_print("\t@echo ==== Building %s ====\n", prj_get_pkgname());
		io_print("\t@$(MAKE) ");
		io_print("--no-print-directory -C %s", path_build(prj_get_path(), prj_get_pkgpath()));
		if (!gnu_pkgOwnsPath())
			io_print(" -f %s.%s", prj_get_pkgname(), DOT_MAKE);
		io_print("\n\n");
	}

	io_print("clean:\n");
	for (i = 0; i < prj_get_numpackages(); ++i)
	{
		prj_select_package(i);

		io_print("\t@$(MAKE) ");
		io_print("--no-print-directory -C %s", path_build(prj_get_path(), prj_get_pkgpath()));
		if (!gnu_pkgOwnsPath())
			io_print(" -f %s.%s", prj_get_pkgname(), DOT_MAKE);
		io_print(" clean\n");
	}
	
	io_closefile();
	return 1;
}


/************************************************************************
 * Checks if a package link matches the name of a sibling package. This
 * is used to generate a Makefile dependency on the sibling.
 ***********************************************************************/

static const char* listInterPackageDeps(const char* name)
{
	int i;
	for (i = 0; i < prj_get_numpackages(); ++i)
	{
		if (matches(name, prj_get_pkgname_for(i)))
			return name;
	}
	return NULL;
}

