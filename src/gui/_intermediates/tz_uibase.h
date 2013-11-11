/************************************
 * /!\ GENERATED FILE - DO NOT EDIT *
*************************************
Generated Sun Nov 10 19:54:21 2013 by thblt@tehlap from:
 - xml/states.xml
 - xml/actions.xml
 - xml/menus.xml
*/

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtGui/QKeySequence>
#include <QtWidgets/QAction>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <unordered_map>

namespace tzgui {
	
	class TZMainWindow_Base : public QMainWindow {
		public:
		std::unordered_map<std::string, QAction*> actionStore;
		QAction *actionRepositoryCreate;
		QAction *actionRepositoryOpen;
		QAction *actionRepositorySave;
		QAction *actionRepositorySaveas;
		QAction *actionRepositoryClose;
		QAction *actionRepositoryConfigure;
		QAction *actionRepositoryExport;
		QAction *actionPageCreateSimple;
		QAction *actionPageCreateTemplated;
		QAction *actionPageCreatePopup;
		QAction *actionPageDelete;
		QAction *actionPagePrint;
		QAction *actionPageCategorize;
		QAction *actionCollectionCreateEmpty;
		QAction *actionCollectionCreateFromrules;
		QAction *actionCollectionCreateWithpages;
		QAction *actionEditionUndo;
		QAction *actionEditionRedo;
		QAction *actionEditionCut;
		QAction *actionEditionCopy;
		QAction *actionEditionPaste;
		QAction *actionEditionPastespecial;
		QAction *actionEditionSelectall;
		QAction *actionFormatCharacterEmphasis;
		QAction *actionFormatCharacterStrongemphasis;
		QAction *actionFormatBlockTitle1;
		QAction *actionSearchFind;
		QAction *actionSearchReplace;
		QAction *actionSearchFindnext;
		QAction *actionSearchFindprevious;
		QAction *actionAppAbout;
		QAction *actionAppPreferences;
		QAction *actionAppShconsole;
		QAction *actionAppUpdate;
		QAction *actionAppQuit;
		QAction *actionAppDocumentation;
		QAction *actionAppReportbug;
		QAction *actionWindowFullscreen;
		QAction *actionWindowLocationbar;
		QMenuBar* menuBar;
		
		void tzSetupUi () {
			// repository>create
			actionRepositoryCreate = new QAction(QStringLiteral("actionRepositoryCreate"), this);
			actionStore["repository.create"] = actionRepositoryCreate;
			actionRepositoryCreate->setShortcut(QKeySequence(this->trUtf8("Ctrl+Alt+Shift+N", "Core actions and menus (generated from XML)")));
			actionRepositoryCreate->setText(this->trUtf8("&New repository…", "Core actions and menus (generated from XML)"));
			// repository>open
			actionRepositoryOpen = new QAction(QStringLiteral("actionRepositoryOpen"), this);
			actionStore["repository.open"] = actionRepositoryOpen;
			actionRepositoryOpen->setShortcut(QKeySequence::Open);
			actionRepositoryOpen->setText(this->trUtf8("&Open…", "Core actions and menus (generated from XML)"));
			// repository>save
			actionRepositorySave = new QAction(QStringLiteral("actionRepositorySave"), this);
			actionStore["repository.save"] = actionRepositorySave;
			actionRepositorySave->setShortcut(QKeySequence::Save);
			actionRepositorySave->setText(this->trUtf8("&Save", "Core actions and menus (generated from XML)"));
			// repository>saveAs
			actionRepositorySaveas = new QAction(QStringLiteral("actionRepositorySaveas"), this);
			actionStore["repository.saveAs"] = actionRepositorySaveas;
			actionRepositorySaveas->setShortcut(QKeySequence::SaveAs);
			actionRepositorySaveas->setText(this->trUtf8("Save &as…", "Core actions and menus (generated from XML)"));
			// repository>close
			actionRepositoryClose = new QAction(QStringLiteral("actionRepositoryClose"), this);
			actionStore["repository.close"] = actionRepositoryClose;
			actionRepositoryClose->setShortcut(QKeySequence::Close);
			actionRepositoryClose->setText(this->trUtf8("&Close", "Core actions and menus (generated from XML)"));
			// repository>configure
			actionRepositoryConfigure = new QAction(QStringLiteral("actionRepositoryConfigure"), this);
			actionStore["repository.configure"] = actionRepositoryConfigure;
			actionRepositoryConfigure->setMenuRole(QAction::NoRole);
			actionRepositoryConfigure->setText(this->trUtf8("Configure repository", "Core actions and menus (generated from XML)"));
			// repository>export
			actionRepositoryExport = new QAction(QStringLiteral("actionRepositoryExport"), this);
			actionStore["repository.export"] = actionRepositoryExport;
			actionRepositoryExport->setText(this->trUtf8("E&xport…", "Core actions and menus (generated from XML)"));
			// page>create>simple
			actionPageCreateSimple = new QAction(QStringLiteral("actionPageCreateSimple"), this);
			actionStore["page.create.simple"] = actionPageCreateSimple;
			actionPageCreateSimple->setShortcut(QKeySequence::New);
			actionPageCreateSimple->setText(this->trUtf8("S&imple", "Core actions and menus (generated from XML)"));
			// page>create>templated
			actionPageCreateTemplated = new QAction(QStringLiteral("actionPageCreateTemplated"), this);
			actionStore["page.create.templated"] = actionPageCreateTemplated;
			actionPageCreateTemplated->setText(this->trUtf8("From &template…", "Core actions and menus (generated from XML)"));
			// page>create>popup
			actionPageCreatePopup = new QAction(QStringLiteral("actionPageCreatePopup"), this);
			actionStore["page.create.popup"] = actionPageCreatePopup;
			actionPageCreatePopup->setIcon(QIcon(QPixmap(":/actions/pageCreatePopup")));
			// page>delete
			actionPageDelete = new QAction(QStringLiteral("actionPageDelete"), this);
			actionStore["page.delete"] = actionPageDelete;
			actionPageDelete->setText(this->trUtf8("Delete page", "Core actions and menus (generated from XML)"));
			// page>print
			actionPagePrint = new QAction(QStringLiteral("actionPagePrint"), this);
			actionStore["page.print"] = actionPagePrint;
			actionPagePrint->setShortcut(QKeySequence::Print);
			actionPagePrint->setText(this->trUtf8("Print", "Core actions and menus (generated from XML)"));
			// page>categorize
			actionPageCategorize = new QAction(QStringLiteral("actionPageCategorize"), this);
			actionStore["page.categorize"] = actionPageCategorize;
			actionPageCategorize->setShortcut(QKeySequence(this->trUtf8("Ctrl+K", "Core actions and menus (generated from XML)")));
			actionPageCategorize->setText(this->trUtf8("Ca&tegorize", "Core actions and menus (generated from XML)"));
			// collection>create>empty
			actionCollectionCreateEmpty = new QAction(QStringLiteral("actionCollectionCreateEmpty"), this);
			actionStore["collection.create.empty"] = actionCollectionCreateEmpty;
			actionCollectionCreateEmpty->setShortcut(QKeySequence(this->trUtf8("Meta+C", "Core actions and menus (generated from XML)")));
			actionCollectionCreateEmpty->setText(this->trUtf8("Empty", "Core actions and menus (generated from XML)"));
			// collection>create>fromRules
			actionCollectionCreateFromrules = new QAction(QStringLiteral("actionCollectionCreateFromrules"), this);
			actionStore["collection.create.fromRules"] = actionCollectionCreateFromrules;
			actionCollectionCreateFromrules->setShortcut(QKeySequence(this->trUtf8("Meta+Shift+C", "Core actions and menus (generated from XML)")));
			actionCollectionCreateFromrules->setText(this->trUtf8("From current rules", "Core actions and menus (generated from XML)"));
			// collection>create>withPages
			actionCollectionCreateWithpages = new QAction(QStringLiteral("actionCollectionCreateWithpages"), this);
			actionStore["collection.create.withPages"] = actionCollectionCreateWithpages;
			actionCollectionCreateWithpages->setShortcut(QKeySequence(this->trUtf8("Meta+Ctrl+N", "Core actions and menus (generated from XML)")));
			actionCollectionCreateWithpages->setText(this->trUtf8("With currently visible pages", "Core actions and menus (generated from XML)"));
			// edition>undo
			actionEditionUndo = new QAction(QStringLiteral("actionEditionUndo"), this);
			actionStore["edition.undo"] = actionEditionUndo;
			actionEditionUndo->setShortcut(QKeySequence::Undo);
			actionEditionUndo->setText(this->trUtf8("&Undo", "Core actions and menus (generated from XML)"));
			// edition>redo
			actionEditionRedo = new QAction(QStringLiteral("actionEditionRedo"), this);
			actionStore["edition.redo"] = actionEditionRedo;
			actionEditionRedo->setShortcut(QKeySequence::Redo);
			actionEditionRedo->setText(this->trUtf8("&Redo", "Core actions and menus (generated from XML)"));
			// edition>cut
			actionEditionCut = new QAction(QStringLiteral("actionEditionCut"), this);
			actionStore["edition.cut"] = actionEditionCut;
			actionEditionCut->setShortcut(QKeySequence::Cut);
			actionEditionCut->setText(this->trUtf8("&Cut", "Core actions and menus (generated from XML)"));
			// edition>copy
			actionEditionCopy = new QAction(QStringLiteral("actionEditionCopy"), this);
			actionStore["edition.copy"] = actionEditionCopy;
			actionEditionCopy->setShortcut(QKeySequence::Copy);
			actionEditionCopy->setText(this->trUtf8("C&opy", "Core actions and menus (generated from XML)"));
			// edition>paste
			actionEditionPaste = new QAction(QStringLiteral("actionEditionPaste"), this);
			actionStore["edition.paste"] = actionEditionPaste;
			actionEditionPaste->setShortcut(QKeySequence::Paste);
			actionEditionPaste->setText(this->trUtf8("&Paste", "Core actions and menus (generated from XML)"));
			// edition>pasteSpecial
			actionEditionPastespecial = new QAction(QStringLiteral("actionEditionPastespecial"), this);
			actionStore["edition.pasteSpecial"] = actionEditionPastespecial;
			actionEditionPastespecial->setShortcut(QKeySequence(this->trUtf8("Ctrl+Shift+V", "Core actions and menus (generated from XML)")));
			actionEditionPastespecial->setText(this->trUtf8("Pa&ste special…", "Core actions and menus (generated from XML)"));
			// edition>selectAll
			actionEditionSelectall = new QAction(QStringLiteral("actionEditionSelectall"), this);
			actionStore["edition.selectAll"] = actionEditionSelectall;
			actionEditionSelectall->setShortcut(QKeySequence::SelectAll);
			actionEditionSelectall->setText(this->trUtf8("Select &all", "Core actions and menus (generated from XML)"));
			// format>character>emphasis
			actionFormatCharacterEmphasis = new QAction(QStringLiteral("actionFormatCharacterEmphasis"), this);
			actionStore["format.character.emphasis"] = actionFormatCharacterEmphasis;
			actionFormatCharacterEmphasis->setShortcut(QKeySequence::Italic);
			actionFormatCharacterEmphasis->setText(this->trUtf8("&Emphasis", "Core actions and menus (generated from XML)"));
			// format>character>strongEmphasis
			actionFormatCharacterStrongemphasis = new QAction(QStringLiteral("actionFormatCharacterStrongemphasis"), this);
			actionStore["format.character.strongEmphasis"] = actionFormatCharacterStrongemphasis;
			actionFormatCharacterStrongemphasis->setShortcut(QKeySequence::Bold);
			actionFormatCharacterStrongemphasis->setText(this->trUtf8("&Strong emphasis", "Core actions and menus (generated from XML)"));
			// format>block>title1
			actionFormatBlockTitle1 = new QAction(QStringLiteral("actionFormatBlockTitle1"), this);
			actionStore["format.block.title1"] = actionFormatBlockTitle1;
			actionFormatBlockTitle1->setShortcut(QKeySequence::Italic);
			actionFormatBlockTitle1->setText(this->trUtf8("&Emphasis", "Core actions and menus (generated from XML)"));
			// search>find
			actionSearchFind = new QAction(QStringLiteral("actionSearchFind"), this);
			actionStore["search.find"] = actionSearchFind;
			actionSearchFind->setShortcut(QKeySequence::Find);
			actionSearchFind->setText(this->trUtf8("&Find…", "Core actions and menus (generated from XML)"));
			// search>replace
			actionSearchReplace = new QAction(QStringLiteral("actionSearchReplace"), this);
			actionStore["search.replace"] = actionSearchReplace;
			actionSearchReplace->setShortcut(QKeySequence::Replace);
			actionSearchReplace->setText(this->trUtf8("&Replace", "Core actions and menus (generated from XML)"));
			// search>findNext
			actionSearchFindnext = new QAction(QStringLiteral("actionSearchFindnext"), this);
			actionStore["search.findNext"] = actionSearchFindnext;
			actionSearchFindnext->setShortcut(QKeySequence::FindNext);
			actionSearchFindnext->setText(this->trUtf8("Find &next", "Core actions and menus (generated from XML)"));
			// search>findPrevious
			actionSearchFindprevious = new QAction(QStringLiteral("actionSearchFindprevious"), this);
			actionStore["search.findPrevious"] = actionSearchFindprevious;
			actionSearchFindprevious->setShortcut(QKeySequence::FindPrevious);
			actionSearchFindprevious->setText(this->trUtf8("Find &previous", "Core actions and menus (generated from XML)"));
			// app>about
			actionAppAbout = new QAction(QStringLiteral("actionAppAbout"), this);
			actionStore["app.about"] = actionAppAbout;
			actionAppAbout->setText(this->trUtf8("About Tkacz", "Core actions and menus (generated from XML)"));
			// app>preferences
			actionAppPreferences = new QAction(QStringLiteral("actionAppPreferences"), this);
			actionStore["app.preferences"] = actionAppPreferences;
			actionAppPreferences->setMenuRole(QAction::PreferencesRole);
			actionAppPreferences->setText(this->trUtf8("Preferences…", "Core actions and menus (generated from XML)"));
			// app>shConsole
			actionAppShconsole = new QAction(QStringLiteral("actionAppShconsole"), this);
			actionStore["app.shConsole"] = actionAppShconsole;
			actionAppShconsole->setText(this->trUtf8("console", "Core actions and menus (generated from XML)"));
			// app>update
			actionAppUpdate = new QAction(QStringLiteral("actionAppUpdate"), this);
			actionStore["app.update"] = actionAppUpdate;
			actionAppUpdate->setMenuRole(QAction::PreferencesRole);
			actionAppUpdate->setText(this->trUtf8("Check for updates…", "Core actions and menus (generated from XML)"));
			// app>quit
			actionAppQuit = new QAction(QStringLiteral("actionAppQuit"), this);
			actionStore["app.quit"] = actionAppQuit;
			actionAppQuit->setShortcut(QKeySequence::Quit);
			actionAppQuit->setText(this->trUtf8("&Quit", "Core actions and menus (generated from XML)"));
			// app>documentation
			actionAppDocumentation = new QAction(QStringLiteral("actionAppDocumentation"), this);
			actionStore["app.documentation"] = actionAppDocumentation;
			actionAppDocumentation->setShortcut(QKeySequence::HelpContents);
			actionAppDocumentation->setText(this->trUtf8("Tkacz &documentation", "Core actions and menus (generated from XML)"));
			// app>reportbug
			actionAppReportbug = new QAction(QStringLiteral("actionAppReportbug"), this);
			actionStore["app.reportbug"] = actionAppReportbug;
			actionAppReportbug->setText(this->trUtf8("&Report a bug…", "Core actions and menus (generated from XML)"));
			// window>fullscreen
			actionWindowFullscreen = new QAction(QStringLiteral("actionWindowFullscreen"), this);
			actionStore["window.fullscreen"] = actionWindowFullscreen;
			actionWindowFullscreen->setShortcut(QKeySequence(this->trUtf8("Ctrl+Shift+F", "Core actions and menus (generated from XML)")));
			actionWindowFullscreen->setCheckable(true);
			actionWindowFullscreen->setIcon(QIcon(QPixmap(":/actions/windowFullscreen")));
			actionWindowFullscreen->setText(this->trUtf8("&Full screen", "Core actions and menus (generated from XML)"));
			// window>locationbar
			actionWindowLocationbar = new QAction(QStringLiteral("actionWindowLocationbar"), this);
			actionStore["window.locationbar"] = actionWindowLocationbar;
			actionWindowLocationbar->setShortcut(QKeySequence(this->trUtf8("Ctrl+L", "Core actions and menus (generated from XML)")));
			menuBar = new QMenuBar(this);
			QMenu* menu0 = new QMenu(menuBar);
			menu0->setObjectName(QStringLiteral("menu0")); menu0->setTitle(this->trUtf8("&File","Generated menu code"));
			menuBar->addAction(menu0->menuAction());
			menu0->addAction(actionRepositoryCreate);
			menu0->addAction(actionRepositoryOpen);
			menu0->addSeparator();
			QAction *title0 = new QAction(this->trUtf8("Add page", "Generated menu code"), this); title0->setEnabled(false); menu0->addAction(title0);
			menu0->addAction(actionPageCreateSimple);
			menu0->addAction(actionPageCreateTemplated);
			menu0->addSeparator();
			QAction *title1 = new QAction(this->trUtf8("Add collection", "Generated menu code"), this); title1->setEnabled(false); menu0->addAction(title1);
			menu0->addAction(actionCollectionCreateEmpty);
			menu0->addAction(actionCollectionCreateFromrules);
			menu0->addAction(actionCollectionCreateWithpages);
			menu0->addSeparator();
			menu0->addAction(actionRepositoryClose);
			menu0->addAction(actionRepositorySave);
			menu0->addAction(actionRepositorySaveas);
			menu0->addAction(actionRepositoryExport);
			menu0->addSeparator();
			menu0->addAction(actionRepositoryConfigure);
			menu0->addSeparator();
			menu0->addAction(actionPagePrint);
			menu0->addSeparator();
			menu0->addAction(actionAppQuit);
			QMenu* menu1 = new QMenu(menuBar);
			menu1->setObjectName(QStringLiteral("menu1")); menu1->setTitle(this->trUtf8("&Edit","Generated menu code"));
			menuBar->addAction(menu1->menuAction());
			menu1->addAction(actionEditionUndo);
			menu1->addAction(actionEditionRedo);
			menu1->addSeparator();
			menu1->addAction(actionEditionCut);
			menu1->addAction(actionEditionCopy);
			menu1->addAction(actionEditionPaste);
			menu1->addAction(actionEditionPastespecial);
			menu1->addSeparator();
			menu1->addAction(actionSearchFind);
			menu1->addAction(actionSearchReplace);
			menu1->addAction(actionSearchFindnext);
			menu1->addAction(actionSearchFindprevious);
			menu1->addSeparator();
			menu1->addAction(actionAppPreferences);
			QMenu* menu2 = new QMenu(menuBar);
			menu2->setObjectName(QStringLiteral("menu2")); menu2->setTitle(this->trUtf8("&Format","Generated menu code"));
			menuBar->addAction(menu2->menuAction());
			menu2->addAction(actionFormatCharacterEmphasis);
			menu2->addAction(actionFormatCharacterStrongemphasis);
			menu2->addAction(actionFormatCharacterStrongemphasis);
			QMenu* menu3 = new QMenu(menuBar);
			menu3->setObjectName(QStringLiteral("menu3")); menu3->setTitle(this->trUtf8("&View","Generated menu code"));
			menuBar->addAction(menu3->menuAction());
			menu3->addAction(actionWindowFullscreen);
			QMenu* menu4 = new QMenu(menuBar);
			menu4->setObjectName(QStringLiteral("menu4")); menu4->setTitle(this->trUtf8("&Help","Generated menu code"));
			menuBar->addAction(menu4->menuAction());
			menu4->addAction(actionAppDocumentation);
			menu4->addSeparator();
			menu4->addAction(actionAppShconsole);
			menu4->addAction(actionAppReportbug);
			menu4->addSeparator();
			menu4->addAction(actionAppUpdate);
			menu4->addAction(actionAppAbout);
		}; /* void tzSetupUi () */
	}; /* class TZMainWindow_Base : public QMainWindow */
}; /* namespace tzgui */