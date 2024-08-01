#pragma once

#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QObject>

#include "model.h"

namespace llm_chat {

/// @brief The ChatBackend class handles the communication with the Ollama
/// server.
class ChatBackend : public QObject {
  Q_OBJECT
  Q_PROPERTY(ChatModel *model READ model CONSTANT FINAL)

 public:
  /// @brief Constructs a new ChatBackend object.
  /// @param parent The parent object.
  explicit ChatBackend(QObject *parent = nullptr);
  /// @brief Returns the model that holds the chat messages.
  /// @return The chat model.
  [[nodiscard]] ChatModel *model() const;

 public slots:
  /// @brief Sends a message to the Ollama server.
  /// @param message The message to send.
  void sendMessage(const QString &message);
  /// @brief Clears the chat messages.
  void clearMessages();

 private:
  QScopedPointer<QNetworkAccessManager> m_Manager;
  QScopedPointer<ChatModel> m_Model;
  int m_CurrentMessageIndex;

  /// @brief Sends a request to the Ollama server.
  /// @param prompt The prompt to send.
  void sendRequestToOllama(const QString &prompt);
  /// @brief Handles the response from the Ollama server.
  /// @param reply The response from the Ollama server.
  void handleStreamResponse(QNetworkReply *reply);
};

}  // namespace llm_chat
