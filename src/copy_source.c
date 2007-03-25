/* jbc_marray/copy_source.c
 * 
 * Copyright (C) 2002, 2003, 2004, 2005 Jordi Burguet-Castell
 * based on the gsl_matrix code from Gerard Jungman, Brian Gough
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include <string.h>  /* to use memcpy() */


/*
 * Overwrites dest with the contents of jbc_marray src.
 */
int
FUNCTION (jbc_marray, memcpy) (TYPE (jbc_marray) * dest,
                               const TYPE (jbc_marray) * src)
{
  unsigned int i;

  if (dest->rank != src->rank)
    GSL_ERROR ("jbc_marrays have different number of indices", GSL_EBADLEN);

  for (i = 0; i < src->rank; i++)
    if (dest->dimension[i] != src->dimension[i])
      GSL_ERROR ("jbc_marray sizes are different", GSL_EBADLEN);

  memcpy(dest->data, src->data, sizeof(BASE) * src->size);

  return GSL_SUCCESS;
}


/*
 * Interchanges the values of jbc_marrays t1 and t2
 */
int
FUNCTION (jbc_marray, swap) (TYPE (jbc_marray) * t1, TYPE (jbc_marray) * t2)
{
  unsigned int i;

  if (t1->rank != t2->rank)
    GSL_ERROR ("jbc_marrays have different number of indices", GSL_EBADLEN);

  for (i = 0; i < t1->rank; i++)
    {
      if (t1->dimension[i] != t2->dimension[i])
        GSL_ERROR ("jbc_marray sizes are different", GSL_EBADLEN);
    }

  {
    size_t i, j;
    size_t n = t1->size;

    for (i = 0; i < n; i++)
      for (j = 0; j < MULTIPLICITY; j++)
	{
	  ATOMIC tmp = t1->data[MULTIPLICITY * i + j];
	  
	  t1->data[MULTIPLICITY * i + j] = t2->data[MULTIPLICITY * i + j];

	  t2->data[MULTIPLICITY * i + j] = tmp ;
	}
  }

  return GSL_SUCCESS;
}
