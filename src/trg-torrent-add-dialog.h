/*
 * transmission-remote-gtk - A GTK RPC client to Transmission
 * Copyright (C) 2011  Alan Fitton

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef TRG_TORRENT_ADD_DIALOG_H_
#define TRG_TORRENT_ADD_DIALOG_H_

#include <glib-object.h>
#include <gtk/gtk.h>

#include "trg-client.h"
#include "trg-main-window.h"

G_BEGIN_DECLS
#define TRG_TYPE_TORRENT_ADD_DIALOG trg_torrent_add_dialog_get_type()
#define TRG_TORRENT_ADD_DIALOG(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), TRG_TYPE_TORRENT_ADD_DIALOG, TrgTorrentAddDialog))
#define TRG_TORRENT_ADD_DIALOG_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), TRG_TYPE_TORRENT_ADD_DIALOG, TrgTorrentAddDialogClass))
#define TRG_IS_TORRENT_ADD_DIALOG(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TRG_TYPE_TORRENT_ADD_DIALOG))
#define TRG_IS_TORRENT_ADD_DIALOG_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), TRG_TYPE_TORRENT_ADD_DIALOG))
#define TRG_TORRENT_ADD_DIALOG_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), TRG_TYPE_TORRENT_ADD_DIALOG, TrgTorrentAddDialogClass))
    typedef struct {
    GtkDialog parent;
} TrgTorrentAddDialog;

typedef struct {
    GtkDialogClass parent_class;
} TrgTorrentAddDialogClass;

/* Use synchronous dispatch() in our dedicated thread function.
 * This means torrents are added in sequence, instead of dispatch_async()
 * working concurrently for each upload.
 */

struct add_torrent_threadfunc_args {
    GSList *list;
    TrgClient *client;
    gpointer cb_data;
    guint flags;
    gchar *dir;
    gint priority;
    gboolean extraArgs;
};

GType trg_torrent_add_dialog_get_type(void);

TrgTorrentAddDialog *trg_torrent_add_dialog_new(TrgMainWindow * win,
                                                TrgClient * client,
                                                GSList * filenames);
void trg_torrent_add_dialog(TrgMainWindow * win, TrgClient * client);
void launch_add_thread(struct add_torrent_threadfunc_args *args);

G_END_DECLS
#endif                          /* TRG_TORRENT_ADD_DIALOG_H_ */
