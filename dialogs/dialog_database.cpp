#include "dialog_database.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QAction>
#include "various/resource_finder.h"
#include "various/helper.h"
#include "dialogs/dialog_search.h"
#include "viewController/database_index_model.h"
#include <QDebug>

DialogDatabase::DialogDatabase(GameModel *gameModel, QWidget* parent) :
    QDialog(parent)
{
    this->gameModel = gameModel;

    this->selectedIndex = -1;

    this->resizeTo(0.9);

    QToolBar *toolbar = new QToolBar(this);
    QSize iconSize = toolbar->iconSize() * this->devicePixelRatio()*2;

    QString resDir = ResourceFinder::getPath();

    QString stringOpen(resDir + "/res/icons/document-open.svg");
    QPixmap *tbNew = Helper::fromSvgToPixmap(iconSize,stringOpen, this->devicePixelRatio());
    QAction *tbActionOpen = toolbar->addAction(QIcon(*tbNew), this->tr("Open"));

    QString stringSave(resDir + "/res/icons/document-save.svg");
    QPixmap *tbSave = Helper::fromSvgToPixmap(iconSize,stringSave, this->devicePixelRatio());
    QAction *tbActionSave = toolbar->addAction(QIcon(*tbSave), this->tr("Save"));

    toolbar->addSeparator();

    QString stringSearch(resDir + "/res/icons/system-search.svg");
    QPixmap *tbSearch = Helper::fromSvgToPixmap(iconSize,stringSearch, this->devicePixelRatio());
    QAction *tbActionSearch = toolbar->addAction(QIcon(*tbSearch), this->tr("Search"));

    QString stringEdit(resDir + "/res/icons/document-properties.svg");
    QPixmap *tbEdit = Helper::fromSvgToPixmap(iconSize,stringEdit, this->devicePixelRatio());
    QAction *tbActionEdit = toolbar->addAction(QIcon(*tbEdit), this->tr("Edit Header"));

    QString stringDeleteGame(resDir + "/res/icons/mail-mark-junk.svg");
    QPixmap *tbDeleteGame = Helper::fromSvgToPixmap(iconSize,stringDeleteGame, this->devicePixelRatio());
    QAction *tbActionDeleteGame = toolbar->addAction(QIcon(*tbDeleteGame), this->tr("Delete Game"));

    QString stringUndeleteGame(resDir + "/res/icons/mail-mark-not-junk.svg");
    QPixmap *tbUndeleteGame = Helper::fromSvgToPixmap(iconSize,stringUndeleteGame, this->devicePixelRatio());
    QAction *tbActionUndeleteGame = toolbar->addAction(QIcon(*tbUndeleteGame), this->tr("Undelete Game"));

    toolbar->addSeparator();

    QString stringImport(resDir + "/res/icons/edit-undo.svg");
    QPixmap *tbImport = Helper::fromSvgToPixmap(iconSize,stringImport, this->devicePixelRatio());
    QAction *tbActionImport = toolbar->addAction(QIcon(*tbImport), this->tr("Import"));

    QString stringExport(resDir + "/res/icons/edit-redo.svg");
    QPixmap *tbExport = Helper::fromSvgToPixmap(iconSize,stringExport, this->devicePixelRatio());
    QAction *tbActionExport = toolbar->addAction(QIcon(*tbExport), this->tr("Export"));

    QString stringAddCurrent(resDir + "/res/icons/text-x-generic_with_pencil.svg");
    QPixmap *tbAddCurrent = Helper::fromSvgToPixmap(iconSize,stringAddCurrent, this->devicePixelRatio());
    QAction *tbActionAddCurrent = toolbar->addAction(QIcon(*tbAddCurrent), this->tr("Add Current Game"));

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer);

    QString stringHelp(resDir + "/res/icons/help-browser.svg");
    QPixmap *tbHelp = Helper::fromSvgToPixmap(iconSize, stringHelp, this->devicePixelRatio());
    QAction *tbActionHelp = toolbar->addAction(QIcon(*tbHelp), this->tr("About"));

    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolbar->setIconSize(iconSize);

    /*
    int rows = 10;
    int columns = 7;
    this->gameTable = new QTableWidget(rows, columns);

    this->gameTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->gameTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->gameTable->setSelectionMode(QAbstractItemView::SingleSelection);

    this->gameTableHeaders = new QStringList();
    this->gameTableHeaders->append("No.");
    this->gameTableHeaders->append("White");
    this->gameTableHeaders->append("Black");
    this->gameTableHeaders->append("Result");
    this->gameTableHeaders->append("Date");
    this->gameTableHeaders->append("ECO");
    this->gameTableHeaders->append("Site");

    this->gameTable->verticalHeader()->hide();
    this->gameTable->setShowGrid(false);

    //this->drawAllItems();
    this->gameTable->resizeColumnsToContents();;
    this->gameTable->horizontalHeader()->setStretchLastSection(true);
    this->gameTable->selectRow(0);
    */

    this->indexModel = new DatabaseIndexModel(this);
    this->indexModel->setDatabase(this->gameModel->database);

    this->tableView = new QTableView(this);
    this->tableView->setModel(indexModel);

    this->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //this->tableView->verticalHeader()->hide();
    this->tableView->setShowGrid(false);
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->tableView->selectRow(0);

    tableView->setWindowTitle(QObject::tr("Games"));
    tableView->resizeColumnsToContents();
    tableView->show();

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, this);

    this->btnOpenGame = new QPushButton(this);
    this->btnCancel = new QPushButton(this);

    this->btnOpenGame->setText(this->tr("Open Game"));
    this->btnCancel->setText(this->tr("Cancel"));

    buttonBox->addButton(btnOpenGame, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(btnCancel, QDialogButtonBox::RejectRole);

    // putting it all together

    QVBoxLayout *layoutAll = new QVBoxLayout(this);
    layoutAll->addWidget(toolbar);
    layoutAll->addWidget(this->tableView);

    //layoutAll->addStretch();

    layoutAll->addWidget(buttonBox);

    this->setLayout(layoutAll);

    connect(tbActionSearch, &QAction::triggered, this, &DialogDatabase::onClickSearch);
    connect(tbActionOpen, &QAction::triggered, this, &DialogDatabase::onClickOpen);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QItemSelectionModel *model = this->tableView->selectionModel();
    connect(model, &QItemSelectionModel::selectionChanged,
            this, &DialogDatabase::onRowChanged);

}

void DialogDatabase::resizeTo(float ratio) {

    int height = 0;
    int width = 0;
    if(this->parentWidget() != 0) {
        int w_height = this->parentWidget()->size().height();
        height = w_height * ratio;
        //width = (w_width * ratio);
        width = height * 1.8;
    } else {
        QDesktopWidget *desktop = qApp->desktop();
        QSize availableSize = desktop->availableGeometry().size();
        int w_height = availableSize.height();
        height = w_height * (ratio*0.8);
        //width = w_width * (ratio*0.6);
        width = height * 1.8;
    }
    QSize newSize( width, height );
    this->resize(newSize);
}

void DialogDatabase::onClickSearch() {

    DialogSearch *dlg = new DialogSearch(this->gameModel, this);
    dlg->show();

}

void DialogDatabase::onClickOpen() {

    this->gameModel->database->open(this);

    this->indexModel->setDatabase(this->gameModel->database);
    this->indexModel->layoutChanged();
    this->tableView->resizeColumnsToContents();
    if(this->gameModel->database->countGames() > 0) {
        this->tableView->selectRow(0);
    }
    this->setWindowTitle(this->gameModel->database->filenameIndex);

}

void DialogDatabase::onRowChanged() {
    QItemSelectionModel *select = this->tableView->selectionModel();
    if(select->hasSelection()) {
        QModelIndexList selected_rows = select->selectedRows();
        if(selected_rows.size() > 0) {
            int row_index = selected_rows.at(0).row();
            this->selectedIndex = row_index;
        }
    }
}


