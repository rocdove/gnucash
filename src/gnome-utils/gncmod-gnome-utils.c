/*********************************************************************
 * gncmod-gnome-utils.c
 * module definition/initialization for the gnome utilities 
 * 
 * Copyright (c) 2001 Linux Developers Group, Inc. 
 *********************************************************************/

#include "config.h"

#include <stdio.h>
#include <glib.h>
#include <libguile.h>
#include "guile-mappings.h"

#include "gnc-module.h"
#include "gnc-module-api.h"

#include "dialog-options.h"
#include "gnc-html.h"
#include "gnc-engine-util.h"
#include "gnc-err-popup.h"
#include "gnc-gui-query.h"

/* version of the gnc module system interface we require */
int libgncmod_gnome_utils_LTX_gnc_module_system_interface = 0;

/* module versioning uses libtool semantics. */
int libgncmod_gnome_utils_LTX_gnc_module_current  = 0;
int libgncmod_gnome_utils_LTX_gnc_module_revision = 0;
int libgncmod_gnome_utils_LTX_gnc_module_age      = 0;

/* forward references */
char *libgncmod_gnome_utils_LTX_gnc_module_path(void);
char *libgncmod_gnome_utils_LTX_gnc_module_description(void);
int libgncmod_gnome_utils_LTX_gnc_module_init(int refcount);
int libgncmod_gnome_utils_LTX_gnc_module_end(int refcount);


char *
libgncmod_gnome_utils_LTX_gnc_module_path(void) {
  return g_strdup("gnucash/gnome-utils");
}

char * 
libgncmod_gnome_utils_LTX_gnc_module_description(void) {
  return g_strdup("Utilities for using Gnome/Gtk with GnuCash");
}

static void
lmod(char * mn) 
{
  char * form = g_strdup_printf("(use-modules %s)\n", mn);
  scm_c_eval_string(form);
  g_free(form);
}

int
libgncmod_gnome_utils_LTX_gnc_module_init(int refcount) {
  /* load the engine (we depend on it) */
  if(!gnc_module_load("gnucash/engine", 0)) {
    return FALSE;
  }

  /* load the calculation module (we depend on it) */
  if(!gnc_module_load("gnucash/calculation", 0)) {
    return FALSE;
  }

  /* load the calculation module (we depend on it) */
  if(!gnc_module_load("gnucash/network-utils", 0)) {
    return FALSE;
  }

  /* load the calculation module (we depend on it) */
  if(!gnc_module_load("gnucash/app-utils", 0)) {
    return FALSE;
  }

  /* publish g-wrapped bindings */
  lmod("(g-wrapped gw-gnome-utils)");
  lmod("(gnucash gnome-utils)");
  
  /* Initialize the options-ui database */
  if (refcount == 0) {
    gnc_options_ui_initialize ();
    gnc_html_initialize ();
  }

  gnc_set_warning_message(gnc_warning_dialog_va);
  gnc_set_error_message(gnc_error_dialog_va);
  return TRUE;
}

int
libgncmod_gnome_utils_LTX_gnc_module_end(int refcount)
{
  gnc_set_warning_message(NULL);
  gnc_set_error_message(NULL);
  return TRUE;
}