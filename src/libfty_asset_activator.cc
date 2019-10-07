/*  =========================================================================
    libfty_asset_activator - Interface for fty-asset-activator library

    Copyright (C) 2019 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

/*
@header
    libfty_asset_activator - Interface for fty-asset-activator library
@discuss
@end
*/

#include "fty_asset_activator_classes.h"

//  Structure of our class

struct _libfty_asset_activator_t {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new libfty_asset_activator

libfty_asset_activator_t *
libfty_asset_activator_new (void)
{
    libfty_asset_activator_t *self = (libfty_asset_activator_t *) zmalloc (sizeof (libfty_asset_activator_t));
    assert (self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the libfty_asset_activator

void
libfty_asset_activator_destroy (libfty_asset_activator_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        libfty_asset_activator_t *self = *self_p;
        //  Free class properties here
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

