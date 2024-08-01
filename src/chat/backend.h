#pragma once

#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QObject>

#include "model.h"

namespace llm_chat {

class ChatBackend : public QObject {
  Q_OBJECT
  Q_PROPERTY(ChatModel *model READ model CONSTANT FINAL)

 public:
  explicit ChatBackend(QObject *parent = nullptr);
  [[nodiscard]] ChatModel *model() const;

 public slots:
  void sendMessage(const QString &message);
  void clearMessages();

 private:
  QScopedPointer<QNetworkAccessManager> m_Manager;
  QScopedPointer<ChatModel> m_Model;
  int m_CurrentMessageIndex;

  void sendRequestToOllama(const QString &prompt);
  void handleStreamResponse(QNetworkReply *reply);
};

}  // namespace llm_chat
