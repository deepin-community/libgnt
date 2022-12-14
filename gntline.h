/*
 * GNT - The GLib Ncurses Toolkit
 *
 * GNT is the legal property of its developers, whose names are too numerous
 * to list here.  Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#ifndef GNT_LINE_H
#define GNT_LINE_H
/**
 * SECTION:gntline
 * @section_id: libgnt-gntline
 * @title: GntLine
 * @short_description: A widget that draws a horizontal or vertical line
 */

#include "gnt.h"
#include "gntcolors.h"
#include "gntkeys.h"
#include "gntwidget.h"

#define GNT_TYPE_LINE				(gnt_line_get_gtype())
#define GNT_LINE(obj)				(G_TYPE_CHECK_INSTANCE_CAST((obj), GNT_TYPE_LINE, GntLine))
#define GNT_LINE_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), GNT_TYPE_LINE, GntLineClass))
#define GNT_IS_LINE(obj)			(G_TYPE_CHECK_INSTANCE_TYPE((obj), GNT_TYPE_LINE))
#define GNT_IS_LINE_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), GNT_TYPE_LINE))
#define GNT_LINE_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), GNT_TYPE_LINE, GntLineClass))

#ifndef GNT_DISABLE_DEPRECATED
/**
 * GNT_LINE_FLAGS:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
#define GNT_LINE_FLAGS(obj)				(GNT_LINE(obj)->priv.flags)
/**
 * GNT_LINE_SET_FLAGS:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
#define GNT_LINE_SET_FLAGS(obj, flags)		(GNT_LINE_FLAGS(obj) |= flags)
/**
 * GNT_LINE_UNSET_FLAGS:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
#define GNT_LINE_UNSET_FLAGS(obj, flags)	(GNT_LINE_FLAGS(obj) &= ~(flags))
#endif

typedef struct _GntLine			GntLine;
typedef struct _GntLineClass		GntLineClass;
#ifndef GNT_DISABLE_DEPRECATED
/**
 * GntLinePriv:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
typedef struct _GntLinePriv GntLinePriv;
#endif

/**
 * GntLine:
 *
 * Access to any fields is deprecated. See inline comments for replacements.
 */
struct _GntLine
{
	GntWidget parent;

	gboolean GNTSEAL(vertical);
};

struct _GntLineClass
{
	GntWidgetClass parent;

	/*< private >*/
	void (*gnt_reserved1)(void);
	void (*gnt_reserved2)(void);
	void (*gnt_reserved3)(void);
	void (*gnt_reserved4)(void);
};

G_BEGIN_DECLS

/**
 * gnt_line_get_gtype:
 *
 * Returns: GType for GntLine.
 */
GType gnt_line_get_gtype(void);

#define gnt_hline_new() gnt_line_new(FALSE)
#define gnt_vline_new() gnt_line_new(TRUE)

/**
 * gnt_line_new:
 * @vertical:  %TRUE if the line should be vertical, %FALSE for a horizontal line.
 *
 * Create new line
 *
 * Returns:  The newly created line.
 */
GntWidget * gnt_line_new(gboolean vertical);

G_END_DECLS

#endif /* GNT_LINE_H */
