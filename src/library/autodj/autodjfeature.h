// AutoDJfeature.h
// FORK FORK FORK on 11/1/2009 by Albert Santoni (alberts@mixxx.org)
// Created 8/23/2009 by RJ Ryan (rryan@mit.edu)

#ifndef AUTODJFEATURE_H
#define AUTODJFEATURE_H

#include <QObject>
#include <QStringListModel>
#include <QVariant>
#include <QIcon>
#include <QUrl>
#include <QList>
#include <QModelIndex>
#include <QPoint>
#include <QAction>
#include <QSignalMapper>

#include "library/libraryfeature.h"
#include "preferences/usersettings.h"
#include "library/treeitemmodel.h"

#include "library/dao/autodjcratesdao.h"
#include "widget/wtracktableview.h"

class DlgAutoDJ;
class Library;
class PlayerManagerInterface;
class TrackCollection;
class AutoDJProcessor;

class AutoDJFeature : public LibraryFeature {
    Q_OBJECT
  public:
    AutoDJFeature(UserSettingsPointer pConfig,
                  Library* pLibrary,
                  QObject* parent,
                  PlayerManagerInterface* pPlayerManager,
                  TrackCollection* pTrackCollection);
    virtual ~AutoDJFeature();

    QVariant title();
    QIcon getIcon();
    virtual QString getViewName();

    bool dropAccept(QList<QUrl> urls, QObject* pSource);
    bool dragMoveAccept(QUrl url);

    void bindPaneWidget(WLibrary* pLibraryWidget, KeyboardEventFilter*pKeyboard, int paneId);
    QWidget* createPaneWidget(KeyboardEventFilter* pKeyboard, int paneId);
    void bindSidebarWidget(WBaseLibrary *pSidebarWidget, KeyboardEventFilter*);

    TreeItemModel* getChildModel();

  public slots:
    void activate();

    // Temporary, until WCrateTableView can be written.
    void onRightClickChild(const QPoint& globalPos, QModelIndex index);

  private:
    UserSettingsPointer m_pConfig;
    Library* m_pLibrary;
    TrackCollection* m_pTrackCollection;
    CrateDAO& m_crateDao;
    PlaylistDAO& m_playlistDao;
    // The id of the AutoDJ playlist.
    int m_iAutoDJPlaylistId;
    AutoDJProcessor* m_pAutoDJProcessor;
    const static QString m_sAutoDJViewName;
    TreeItemModel m_childModel;
    QPointer<DlgAutoDJ> m_pAutoDJView;
    QHash<int, WTrackTableView*> m_trackTables;

    // Initialize the list of crates loaded into the auto-DJ queue.
    void constructCrateChildModel();

    // The "Crates" tree-item under the "Auto DJ" tree-item.
    TreeItem* m_pCratesTreeItem;

    // The crate ID and name of all loaded crates.
    // Its indices correspond one-to-one with tree-items contained by the
    // "Crates" tree-item.
    QList<QPair<int, QString> > m_crateList;

    // How we access the auto-DJ-crates database.
    AutoDJCratesDAO m_autoDjCratesDao;

    // The model-index of the last tree-item that was right-clicked on.
    // Only stored for tree-items contained by the "Crates" tree-item.
    QModelIndex m_lastRightClickedIndex;

    // A context-menu item that allows crates to be removed from the
    // auto-DJ list.
    QAction *m_pRemoveCrateFromAutoDj;

    // Used to map menu-item signals.
    QSignalMapper m_crateMapper;

  private slots:
    // Add a crate to the auto-DJ queue.
    void slotAddCrateToAutoDj(int crateId);

    // Implements the context-menu item.
    void slotRemoveCrateFromAutoDj();

    // Signaled by the crate DAO when a crate is added.
    void slotCrateAdded(int crateId);

    // Signaled by the crate DAO when a crate is renamed.
    void slotCrateRenamed(int crateId, QString newName);

    // Signaled by the crate DAO when a crate is deleted.
    void slotCrateDeleted(int crateId);

    // Signaled by the crate DAO when a crate's auto-DJ status changes.
    void slotCrateAutoDjChanged(int crateId, bool added);

    // Adds a random track from all loaded crates to the auto-DJ queue.
    void slotAddRandomTrack(bool);

    // Adds a random track from the queue upon hitting minimum number
    // of tracks in the playlist
    void slotRandomQueue(int);

};


#endif /* AUTODJFEATURE_H */
