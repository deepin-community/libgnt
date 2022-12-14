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

#ifndef GNT_FILE_SEL_H
#define GNT_FILE_SEL_H
/**
 * SECTION:gntfilesel
 * @section_id: libgnt-gntfilesel
 * @title: GntFileSel
 * @short_description: A widget for selecting a file or directory
 */

#include "gnt.h"
#include "gntcolors.h"
#include "gntkeys.h"
#include "gntwindow.h"

#define GNT_TYPE_FILE_SEL				(gnt_file_sel_get_gtype())
#define GNT_FILE_SEL(obj)				(G_TYPE_CHECK_INSTANCE_CAST((obj), GNT_TYPE_FILE_SEL, GntFileSel))
#define GNT_FILE_SEL_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), GNT_TYPE_FILE_SEL, GntFileSelClass))
#define GNT_IS_FILE_SEL(obj)			(G_TYPE_CHECK_INSTANCE_TYPE((obj), GNT_TYPE_FILE_SEL))
#define GNT_IS_FILE_SEL_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), GNT_TYPE_FILE_SEL))
#define GNT_FILE_SEL_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), GNT_TYPE_FILE_SEL, GntFileSelClass))

#ifndef GNT_DISABLE_DEPRECATED
/**
 * GNT_FILE_SEL_FLAGS:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
#define GNT_FILE_SEL_FLAGS(obj)				(GNT_FILE_SEL(obj)->priv.flags)
/**
 * GNT_FILE_SEL_SET_FLAGS:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
#define GNT_FILE_SEL_SET_FLAGS(obj, flags)		(GNT_FILE_SEL_FLAGS(obj) |= flags)
/**
 * GNT_FILE_SEL_UNSET_FLAGS:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
#define GNT_FILE_SEL_UNSET_FLAGS(obj, flags)	(GNT_FILE_SEL_FLAGS(obj) &= ~(flags))
#endif

typedef struct _GntFileSel			GntFileSel;
typedef struct _GntFileSelClass		GntFileSelClass;
#ifndef GNT_DISABLE_DEPRECATED
/**
 * GntFileSelPriv:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
typedef struct _GntFileSelPriv GntFileSelPriv;
/**
 * GntFile:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail. Use #GFile
 * from GIO for a similar abstraction.
 */
typedef struct _GntFile GntFile;
#endif

/**
 * GntFileSel:
 *
 * Access to any fields is deprecated. See inline comments for replacements.
 */
struct _GntFileSel
{
	GntWindow parent;

	GntWidget *GNTSEAL(dirs);     /* list of files */
	GntWidget *GNTSEAL(files);    /* list of directories */
	GntWidget *GNTSEAL(location); /* location entry */

	GntWidget *GNTSEAL(select);   /* select button */
	GntWidget *GNTSEAL(cancel);   /* cancel button */

	char *GNTSEAL(current); /* Full path of the current location */
	char *GNTSEAL(suggest); /* Suggested filename */
	/* XXX: someone should make these useful */
	gboolean GNTSEAL(must_exist); /* Make sure the selected file (the name entered in 'location') exists */
	gboolean GNTSEAL(dirsonly);   /* Show only directories */
	gboolean GNTSEAL(multiselect);
	GList *GNTSEAL(tags);         /* List of tagged files when multiselect is set */

	gboolean (*GNTSEAL(read_fn))(const char *path, GList **files, GError **error);
};

struct _GntFileSelClass
{
	GntWindowClass parent;

	void (*file_selected)(GntFileSel *sel, const char *path, const char *filename);
	void (*cancelled)(GntFileSel *sel);

	/*< private >*/
	void (*gnt_reserved1)(void);
	void (*gnt_reserved2)(void);
	void (*gnt_reserved3)(void);
};

#ifndef GNT_DISABLE_DEPRECATED
/**
 * GntFileType:
 *
 * Deprecated: 2.14.0: This is an internal implementation detail. Use #GFile
 * from GIO for a similar abstraction.
 */
typedef enum _GntFileType
{
	GNT_FILE_REGULAR,
	GNT_FILE_DIR
} GntFileType;

struct _GntFile
{
	char *GNTSEAL(fullpath);
	char *GNTSEAL(basename);
	GntFileType GNTSEAL(type);
	unsigned long GNTSEAL(size);
};
#endif

G_BEGIN_DECLS

/**
 * gnt_file_sel_get_gtype:
 *
 * Returns: GType for GntFileSel.
 */
GType gnt_file_sel_get_gtype(void);

/**
 * gnt_file_sel_new:
 *
 * Create a new file selector.
 *
 * Returns:  The newly created file selector.
 */
GntWidget * gnt_file_sel_new(void);

/**
 * gnt_file_sel_set_current_location:
 * @sel:   The file selector.
 * @path:  The current path of the selector.
 *
 * Set the current location of the file selector.
 *
 * Returns: %TRUE if the current location was successfully changed, %FALSE otherwise.
 */
gboolean gnt_file_sel_set_current_location(GntFileSel *sel, const char *path);

/**
 * gnt_file_sel_set_dirs_only:
 * @sel:    The file selector.
 * @dirs:   %TRUE if only directories can be selected, %FALSE if files
 *               can also be selected.
 *
 * Set wheter to only allow selecting directories.
 */
void gnt_file_sel_set_dirs_only(GntFileSel *sel, gboolean dirs);

/**
 * gnt_file_sel_get_dirs_only:
 * @sel:  The file selector.
 *
 * Check whether the file selector allows only selecting directories.
 *
 * Returns:  %TRUE if only directories can be selected.
 */
gboolean gnt_file_sel_get_dirs_only(GntFileSel *sel);

/**
 * gnt_file_sel_set_must_exist:
 * @sel:   The file selector.
 * @must:  %TRUE if the selected file must exist.
 *
 * Set whether a selected file must exist.
 */
void gnt_file_sel_set_must_exist(GntFileSel *sel, gboolean must);

/**
 * gnt_file_sel_get_must_exist:
 * @sel:  The file selector.
 *
 * Check whether the selector allows selecting non-existent files.
 *
 * Returns:  %TRUE if the selected file must exist, %FALSE if a non-existent
 *          file can be selected.
 */
gboolean gnt_file_sel_get_must_exist(GntFileSel *sel);

/**
 * gnt_file_sel_get_selected_file:
 * @sel:  The file selector.
 *
 * Get the selected file in the selector.
 *
 * Returns: The path of the selected file. The caller should g_free the returned
 *         string.
 */
char * gnt_file_sel_get_selected_file(GntFileSel *sel);

/**
 * gnt_file_sel_get_selected_multi_files:
 * @sel:  The file selector.
 *
 * Get the list of selected files in the selector.
 *
 * Returns: (transfer full) (element-type filename): A list of paths for the
 *          selected files. The caller must g_free() the contents of the list,
 *          and g_list_free() the list.
 */
GList * gnt_file_sel_get_selected_multi_files(GntFileSel *sel);

/**
 * gnt_file_sel_set_multi_select:
 * @sel:  The file selector.
 * @set:  %TRUE if selecting multiple files should be allowed.
 *
 * Allow selecting multiple files.
 */
void gnt_file_sel_set_multi_select(GntFileSel *sel, gboolean set);

/**
 * gnt_file_sel_set_suggested_filename:
 * @sel:      The file selector.
 * @suggest:  The suggested filename.
 *
 * Set the suggested file to have selected at startup.
 */
void gnt_file_sel_set_suggested_filename(GntFileSel *sel, const char *suggest);

#ifndef GNT_DISABLE_DEPRECATED
/**
 * gnt_file_sel_set_read_fn:
 * @sel:      The file selector.
 * @read_fn:  The custom read function.
 *
 * Set custom functions to read the names of files.
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
void gnt_file_sel_set_read_fn(GntFileSel *sel, gboolean (*read_fn)(const char *path, GList **files, GError **error));

/**
 * gnt_file_new:
 * @name:   The name of the file.
 * @size:   The size of the file.
 *
 * Create a new GntFile.
 *
 * Returns:  The newly created GntFile.
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
GntFile* gnt_file_new(const char *name, unsigned long size);

/**
 * gnt_file_new_dir:
 * @name:  The name of the directory.
 *
 * Create a new GntFile for a directory.
 *
 * Returns:  The newly created GntFile.
 *
 * Deprecated: 2.14.0: This is an internal implementation detail.
 */
GntFile* gnt_file_new_dir(const char *name);
#endif

G_END_DECLS

#endif /* GNT_FILE_SEL_H */

