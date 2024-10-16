#include "settings.h"

#include <QKeySequence>
#include <QLatin1String>
#include <QObject>
#include <QVariant>
#include <QVector>

namespace solar_system {

Settings::Settings(QObject *parent) : QSettings(parent) {}

QString Settings::defaultLanguage() const { return "en_GB"; }

QString Settings::language() const {
  return contains("language") ? value("language").toString()
                              : defaultLanguage();
}

void Settings::setLanguage(const QString &language) {
  if (language == value("language", defaultLanguage()).toString()) return;

  setValue("language", language);
  emit languageChanged();
}

qreal Settings::defaultWindowOpacity() const { return 1.0; }

qreal Settings::windowOpacity() const {
  return contains("windowOpacity") ? value("windowOpacity").toReal()
                                   : defaultWindowOpacity();
}

void Settings::setWindowOpacity(const qreal opacity) {
  if (windowOpacity() == opacity) return;

  setValue("windowOpacity", opacity);
  emit windowOpacityChanged();
}

bool Settings::defaultFpsVisible() const { return false; }

bool Settings::isFpsVisible() const {
  return contains("fpsVisible") ? value("fpsVisible").toBool()
                                : defaultFpsVisible();
}

void Settings::setFpsVisible(const bool fps_visible) {
  if (fps_visible == value("fpsVisible", defaultFpsVisible()).toBool()) return;

  setValue("fpsVisible", fps_visible);
  emit fpsVisibleChanged();
}

void Settings::resetShortcutsToDefaults() {
  static QVector<QString> all_shortcuts;
  if (all_shortcuts.isEmpty()) {
    all_shortcuts.append(QLatin1String("quitShortcut"));
    all_shortcuts.append(QLatin1String("optionsShortcut"));
    all_shortcuts.append(QLatin1String("fullScreenShortcut"));
  }

  foreach (const QString &shortcut, all_shortcuts) {
    remove(shortcut);
  }
}

#define GET_SHORTCUT(shortcut_name, defaultValueFunction)          \
  return contains(shortcut_name) ? value(shortcut_name).toString() \
                                 : defaultValueFunction();

#define SET_SHORTCUT(shortcut_name, defaultValueFunction, notifySignal) \
  const QVariant existing_value = value(shortcut_name);                 \
  QString existing_string_value = defaultValueFunction();               \
  if (contains(shortcut_name)) {                                        \
    existing_string_value = existing_value.toString();                  \
  }                                                                     \
                                                                        \
  if (shortcut == existing_string_value) return;                        \
                                                                        \
  setValue(shortcut_name, shortcut);                                    \
  emit notifySignal();

QString Settings::defaultQuitShortcut() const {
  return QKeySequence(Qt::CTRL | Qt::Key_Q).toString();
}

QString Settings::quitShortcut() const {
  GET_SHORTCUT("quitShortcut", defaultQuitShortcut)
}
void Settings::setQuitShortcut(const QString &shortcut){
    SET_SHORTCUT("quitShortcut", defaultQuitShortcut, quitShortcutChanged)}

QString Settings::defaultOptionsShortcut() const {
  return QKeySequence(Qt::CTRL | Qt::Key_O).toString();
}

QString Settings::optionsShortcut() const {
  GET_SHORTCUT("optionsShortcut", defaultOptionsShortcut)
}

void Settings::setOptionsShortcut(const QString &shortcut){
    SET_SHORTCUT("optionsShortcut", defaultOptionsShortcut,
                 optionsShortcutChanged)}

QString Settings::defaultFullScreenShortcut() const {
  return QKeySequence(Qt::CTRL | Qt::Key_F).toString();
}

QString Settings::fullScreenShortcut() const {
  GET_SHORTCUT("fullScreenShortcut", defaultFullScreenShortcut)
}

void Settings::setFullScreenShortcut(const QString &shortcut) {
  SET_SHORTCUT("fullScreenShortcut", defaultFullScreenShortcut,
               fullScreenShortcutChanged)
}

}  // namespace solar_system
