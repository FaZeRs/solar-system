#pragma once

#include <qtmetamacros.h>
#include <qtypes.h>

#include <QSettings>
#include <QString>

class QObject;

namespace llm_chat {

class Settings : public QSettings {
  Q_OBJECT

  Q_PROPERTY(
      QString language READ language WRITE setLanguage NOTIFY languageChanged)
  Q_PROPERTY(qreal windowOpacity READ windowOpacity WRITE setWindowOpacity
                 NOTIFY windowOpacityChanged)
  Q_PROPERTY(bool fpsVisible READ isFpsVisible WRITE setFpsVisible NOTIFY
                 fpsVisibleChanged)

  Q_PROPERTY(QString newShortcut READ newShortcut WRITE setNewShortcut NOTIFY
                 newShortcutChanged)
  Q_PROPERTY(QString quitShortcut READ quitShortcut WRITE setQuitShortcut NOTIFY
                 quitShortcutChanged)
  Q_PROPERTY(QString optionsShortcut READ optionsShortcut WRITE
                 setOptionsShortcut NOTIFY optionsShortcutChanged)
  Q_PROPERTY(QString fullScreenShortcut READ fullScreenShortcut WRITE
                 setFullScreenShortcut NOTIFY fullScreenShortcutChanged)

 public:
  explicit Settings(QObject *parent = nullptr);

  [[nodiscard]] QString defaultLanguage() const;
  [[nodiscard]] QString language() const;
  void setLanguage(const QString &language);

  [[nodiscard]] qreal defaultWindowOpacity() const;
  [[nodiscard]] qreal windowOpacity() const;
  void setWindowOpacity(qreal opacity);

  [[nodiscard]] bool defaultFpsVisible() const;
  [[nodiscard]] bool isFpsVisible() const;
  void setFpsVisible(bool fpsVisible);

  Q_INVOKABLE void resetShortcutsToDefaults();

  [[nodiscard]] QString defaultNewShortcut() const;
  [[nodiscard]] QString newShortcut() const;
  void setNewShortcut(const QString &shortcut);

  [[nodiscard]] QString defaultQuitShortcut() const;
  [[nodiscard]] QString quitShortcut() const;
  void setQuitShortcut(const QString &shortcut);

  [[nodiscard]] QString defaultOptionsShortcut() const;
  [[nodiscard]] QString optionsShortcut() const;
  void setOptionsShortcut(const QString &shortcut);

  [[nodiscard]] QString defaultFullScreenShortcut() const;
  [[nodiscard]] QString fullScreenShortcut() const;
  void setFullScreenShortcut(const QString &shortcut);

 signals:
  void languageChanged();
  void windowOpacityChanged();
  void fpsVisibleChanged();

  void newShortcutChanged();
  void quitShortcutChanged();

  void optionsShortcutChanged();
  void fullScreenShortcutChanged();
};

}  // namespace llm_chat
