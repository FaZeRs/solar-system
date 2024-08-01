#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../chat/backend.h"
#include "settings.h"

namespace llm_chat {

class Application {
 public:
  Application(int& argc, char** argv);
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;
  ~Application() = default;

  [[nodiscard]] int run() const;

  [[nodiscard]] QQmlApplicationEngine* qmlEngine() const;
  [[nodiscard]] Settings* settings() const;

 private:
  static void initializeSentry();
  void registerQmlTypes() const;
  void addFonts() const;

  QScopedPointer<QGuiApplication> m_Application;
  QScopedPointer<Settings> m_Settings{new Settings()};
  QScopedPointer<ChatBackend> m_ChatBackend{new ChatBackend()};
  QScopedPointer<QQmlApplicationEngine> m_Engine{new QQmlApplicationEngine};
};

}  // namespace llm_chat
