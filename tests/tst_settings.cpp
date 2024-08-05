#include <settings.h>

#include <QSignalSpy>
#include <QTest>

class SettingsTest : public QObject {
  Q_OBJECT

 private slots:
  void initTestCase() {
    // Called before the first test case is executed
    settings = new llm_chat::Settings();
  }

  void cleanupTestCase() {
    // Called after the last test case is executed
    delete settings;
  }

  void testDefaultValues() {
    QCOMPARE(settings->defaultLanguage(), QString("en_GB"));
    QCOMPARE(settings->defaultWindowOpacity(), 1.0);
    QCOMPARE(settings->defaultFpsVisible(), false);
    QCOMPARE(settings->defaultQuitShortcut(), QString("Ctrl+Q"));
    QCOMPARE(settings->defaultOptionsShortcut(), QString("Ctrl+O"));
    QCOMPARE(settings->defaultFullScreenShortcut(), QString("Ctrl+F"));
  }

  void testLanguage() {
    settings->setLanguage("fr");
    QCOMPARE(settings->language(), QString("fr"));
    QSignalSpy spy(settings, &llm_chat::Settings::languageChanged);
    settings->setLanguage("de");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(settings->language(), QString("de"));
  }

  void testWindowOpacity() {
    settings->setWindowOpacity(0.8);
    QCOMPARE(settings->windowOpacity(), 0.8);
    QSignalSpy spy(settings, &llm_chat::Settings::windowOpacityChanged);
    settings->setWindowOpacity(0.5);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(settings->windowOpacity(), 0.5);
  }

  void testFpsVisible() {
    settings->setFpsVisible(true);
    QCOMPARE(settings->isFpsVisible(), true);
    QSignalSpy spy(settings, &llm_chat::Settings::fpsVisibleChanged);
    settings->setFpsVisible(false);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(settings->isFpsVisible(), false);
  }

  void testShortcuts() {
    settings->setQuitShortcut("Ctrl+X");
    QCOMPARE(settings->quitShortcut(), QString("Ctrl+X"));
    QSignalSpy quitSpy(settings, &llm_chat::Settings::quitShortcutChanged);
    settings->setQuitShortcut("Ctrl+Q");
    QCOMPARE(quitSpy.count(), 1);
    QCOMPARE(settings->quitShortcut(), QString("Ctrl+Q"));

    settings->setOptionsShortcut("Ctrl+P");
    QCOMPARE(settings->optionsShortcut(), QString("Ctrl+P"));
    QSignalSpy optionsSpy(settings,
                          &llm_chat::Settings::optionsShortcutChanged);
    settings->setOptionsShortcut("Ctrl+O");
    QCOMPARE(optionsSpy.count(), 1);
    QCOMPARE(settings->optionsShortcut(), QString("Ctrl+O"));

    settings->setFullScreenShortcut("Ctrl+G");
    QCOMPARE(settings->fullScreenShortcut(), QString("Ctrl+G"));
    QSignalSpy fullScreenSpy(settings,
                             &llm_chat::Settings::fullScreenShortcutChanged);
    settings->setFullScreenShortcut("Ctrl+F");
    QCOMPARE(fullScreenSpy.count(), 1);
    QCOMPARE(settings->fullScreenShortcut(), QString("Ctrl+F"));
  }

  void testResetShortcutsToDefaults() {
    settings->setQuitShortcut("Ctrl+X");
    settings->setOptionsShortcut("Ctrl+P");
    settings->setFullScreenShortcut("Ctrl+G");
    settings->resetShortcutsToDefaults();
    QCOMPARE(settings->quitShortcut(), settings->defaultQuitShortcut());
    QCOMPARE(settings->optionsShortcut(), settings->defaultOptionsShortcut());
    QCOMPARE(settings->fullScreenShortcut(),
             settings->defaultFullScreenShortcut());
  }

 private:
  llm_chat::Settings* settings;
};

QTEST_MAIN(SettingsTest)
#include "tst_settings.moc"