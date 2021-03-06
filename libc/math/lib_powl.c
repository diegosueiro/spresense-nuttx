/****************************************************************************
 * libc/math/lib_powl.c
 *
 * This file is a part of NuttX:
 *
 *   Copyright (C) 2012 Gregory Nutt. All rights reserved.
 *   Ported by: Darcy Gong
 *   Copyright 2018 Sony Semiconductor Solutions Corporation
 *
 * It derives from the Rhombus OS math library by Nick Johnson which has
 * a compatibile, MIT-style license:
 *
 * Copyright (C) 2009, 2010 Nick Johnson <nickbjohnson4224 at gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <math.h>
#include <stdint.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

#ifdef CONFIG_HAVE_LONG_DOUBLE
long double powl(long double b, long double e)
{
  long double ret;
  long double ip;

  if (e == 0.0)
    {
      return 1.0;
    }

  if ((b == -1.0) && ((e == INFINITY) || (e == -INFINITY)))
    {
      return 1.0;
    }

  if (b == 1.0)
    {
      return b;
    }
  else if (b > 0.0)
    {
      return expl(e * logl(b));
    }
  else
    {
      modfl(e, &ip);

      if (b < 0.0)
        {
          if (e == ip)
            {
              ret = expl(e * logl(-b));
              return ((int64_t)e % 2) ? -ret : ret;
            }
        }
      else if (b == 0.0)
        {
          if (e > 0.0)
            {
              return b;
            }
          else if (e < 0.0)
            {
              if (e == ip)
                {
                  union
                  {
                    long double f;
                    struct
                    {
                      uint64_t m;
                      uint16_t se;
                    } i;
                  } u = { b };
                  return (u.i.se >> 15) ? -INFINITY : INFINITY;
                }
            }
        }
    }
  return NAN;
}
#endif
