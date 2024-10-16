#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "settings.h"

namespace solar_system {

/// @brief The main application class.
class Application {
 public:
  Application(int& argc, char** argv);
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;
  ~Application() = default;

  /// @brief Runs the application.
  /// @return The exit code.
  [[nodiscard]] int run() const;

  /// @brief Returns the QML Application Engine instance.
  /// @return The QML Application Engine instance.
  [[nodiscard]] QQmlApplicationEngine* qmlEngine() const;
  /// @brief Returns the Settings instance.
  /// @return The Settings instance.
  [[nodiscard]] Settings* settings() const;

 private:
  /// @brief Initializes Sentry for error reporting.
  static void initializeSentry();
  /// @brief Registers the QML types.
  void registerQmlTypes() const;
  /// @brief Adds the fonts.
  void addFonts() const;

  QScopedPointer<QGuiApplication> m_Application;
  QScopedPointer<Settings> m_Settings{new Settings()};
  QScopedPointer<QQmlApplicationEngine> m_Engine{new QQmlApplicationEngine};
};

}  // namespace solar_system
