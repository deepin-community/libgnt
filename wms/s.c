#include "gntinternal.h"

#include <string.h>
#include <sys/types.h>

#include "gnt.h"
#include "gntbox.h"
#include "gntmenu.h"
#include "gntstyle.h"
#include "gntwm.h"
#include "gntwindow.h"
#include "gntlabel.h"

#define TYPE_S				(s_get_gtype())

#ifdef _S
#undef _S
#endif

typedef struct _S
{
	GntWM inherit;
} S;

typedef struct _SClass
{
	GntWMClass inherit;
} SClass;

GType s_get_gtype(void);
void gntwm_init(GntWM **wm);

static void (*org_new_window)(GntWM *wm, GntWidget *win);

static void
envelope_main_window(GntWidget *win)
{
	int w, h;
	gnt_widget_get_size(win, &w, &h);
	wresize(win->window, h, w + 1);
	mvwvline(win->window, 0, w, ACS_VLINE | COLOR_PAIR(GNT_COLOR_NORMAL), h);
	touchwin(win->window);
}

static void
envelope_normal_window(GntWidget *win)
{
	int w, h;

	if (!gnt_widget_get_has_border(win) || gnt_widget_get_transient(win))
		return;

	gnt_widget_get_size(win, &w, &h);
	wbkgdset(win->window, ' ' | COLOR_PAIR(GNT_COLOR_NORMAL));
	mvwprintw(win->window, 0, w - 4, "[X]");
}

static void
s_decorate_window(GntWM *wm, GntWidget *win)
{
	const char *name;

	name = gnt_widget_get_name(win);
	if (name && strcmp(name, "MainWindow") == 0) {
		envelope_main_window(win);
	} else {
		envelope_normal_window(win);
	}
}

static void
s_window_update(GntWM *wm, GntNode *node)
{
	s_decorate_window(wm, node->me);
}

static void
s_new_window(GntWM *wm, GntWidget *win)
{
	int x, y, w, h;
	int maxx, maxy;
	const char *name;
	gboolean main_window = FALSE;

	if (!GNT_IS_MENU(win)) {
		getmaxyx(stdscr, maxy, maxx);

		gnt_widget_get_position(win, &x, &y);
		gnt_widget_get_size(win, &w, &h);

		name = gnt_widget_get_name(win);

		if (name && strcmp(name, "MainWindow") == 0) {
			/* The MainWindow doesn't have no border nor nothing! */
			x = 0;
			y = 0;
			h = maxy - 1;
			main_window = TRUE;

			gnt_box_set_toplevel(GNT_BOX(win), FALSE);
			gnt_widget_set_take_focus(win, TRUE);

			gnt_widget_set_position(win, x, y);
			mvwin(win->window, y, x);

			gnt_widget_set_size(win, -1, h + 2);  /* XXX: Why is the +2 needed here? -- sadrul */
		} else if (!gnt_widget_get_transient(win)) {
			const char *title = GNT_BOX(win)->title;
			if (title == NULL || !g_hash_table_lookup(wm->positions, title)) {
				/* In the middle of the screen */
				x = (maxx - w) / 2;
				y = (maxy - h) / 2;

				gnt_widget_set_position(win, x, y);
				mvwin(win->window, y, x);
			}
		}
	}
	org_new_window(wm, win);

	if (main_window)
		gnt_wm_raise_window(wm, win);
}

static GntWidget *
find_widget(GntWM *wm, const char *wname)
{
	GList *iter = wm->cws->list;
	for (; iter; iter = iter->next) {
		GntWidget *widget = iter->data;
		const char *name = gnt_widget_get_name(widget);
		if (name && strcmp(name, wname) == 0) {
			return widget;
		}
	}
	return NULL;
}

static gboolean
s_mouse_clicked(GntWM *wm, GntMouseEvent event, int cx, int cy, GntWidget *widget)
{
	int x, y, w, h;

	if (!widget)
		return FALSE;
		/* This might be a place to bring up a context menu */

	if (event != GNT_LEFT_MOUSE_DOWN || !gnt_widget_get_has_border(widget))
		return FALSE;

	gnt_widget_get_position(widget, &x, &y);
	gnt_widget_get_size(widget, &w, &h);

	if (cy == y && cx == x + w - 3) {
		gnt_widget_destroy(widget);
		return TRUE;
	}

	return FALSE;
}

static gboolean
raise_main_window(GntBindable *bindable, GList *null)
{
	GntWM *wm = GNT_WM(bindable);
	GntWidget *main_window = find_widget(wm, "MainWindow");
	if (main_window)
		gnt_wm_raise_window(wm, main_window);
	return TRUE;
}

static void
s_class_init(SClass *klass)
{
	GntWMClass *pclass = GNT_WM_CLASS(klass);

	org_new_window = pclass->new_window;

	pclass->new_window = s_new_window;
	pclass->decorate_window = s_decorate_window;
	pclass->window_update = s_window_update;
	pclass->mouse_clicked = s_mouse_clicked;

	gnt_bindable_class_register_action(GNT_BINDABLE_CLASS(klass),
			"raise-main-window", raise_main_window,
			"\033" "b", NULL);
	gnt_style_read_actions(G_OBJECT_CLASS_TYPE(klass), GNT_BINDABLE_CLASS(klass));
	GNTDEBUG;
}

void gntwm_init(GntWM **wm)
{
	*wm = g_object_new(TYPE_S, NULL);
}

GType s_get_gtype(void)
{
	static GType type = 0;

	if(type == 0) {
		static const GTypeInfo info = {
			sizeof(SClass),
			NULL,					/* base_init		*/
			NULL,					/* base_finalize	*/
			(GClassInitFunc)s_class_init,
			NULL,
			NULL,                   /* class_data		*/
			sizeof(S),
			0,                      /* n_preallocs		*/
			NULL,	            /* instance_init	*/
			NULL
		};

		type = g_type_register_static(GNT_TYPE_WM,
									  "GntS",
									  &info, 0);
	}

	return type;
}

