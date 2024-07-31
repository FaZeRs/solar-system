#pragma once

#include <QCoreApplication>
#include <QQmlApplicationEngine>

#include "../chat/backend.h"
#include "base.h"
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

  Scope<QCoreApplication> m_Application;
  Scope<QQmlApplicationEngine> m_Engine = CreateScope<QQmlApplicationEngine>();
  Scope<Settings> m_Settings = CreateScope<Settings>();
  Scope<ChatBackend> m_ChatBackend = CreateScope<ChatBackend>();
};

}  // namespace llm_chat
