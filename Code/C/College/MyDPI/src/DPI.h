/*
 * DPI.h
 * Copyright (C) 2019 by jovi Hsu(jv.hsu@outlook.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


#ifndef _DPI_INCLUDED
#define _DPI_INCLUDED

#include "ipq_api.h"


typedef enum _MEM_STATE {
    INVALID = -1,
    DATA_PUT,
    DATA_ADD_UP,
    DATA_GET,
} MEM_STATE;

#endif /* _DPI_INCLUDED */
