#include "backend.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

namespace llm_chat {

ChatBackend::ChatBackend(QObject *parent)
    : QObject(parent),
      m_Manager(new QNetworkAccessManager(this)),
      m_Model(new ChatModel(this)) {}

ChatModel *ChatBackend::model() const { return m_Model.get(); }

void ChatBackend::sendMessage(const QString &message) {
  m_Model->addMessage(message, true, {});
  sendRequestToOllama(message);
}

void ChatBackend::sendRequestToOllama(const QString &prompt) {
  QNetworkRequest request(QUrl("http://localhost:11434/api/generate"));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  // Get all the messages from the model that were sent by AI
  QJsonArray context;
  for (const Message *message : m_Model->messages()) {
    if (!message->isUser()) {
      const auto message_context = message->context();
      for (const auto &context_item : message_context) {
        context.append(QJsonValue::fromVariant(context_item));
      }
    }
  }

  QJsonObject json;
  json["model"] = "llama3.1:8b";
  json["prompt"] = prompt;
  json["stream"] = true;
  json["context"] = context;

  QNetworkReply *reply = m_Manager->post(request, QJsonDocument(json).toJson());

  m_CurrentMessageIndex = m_Model->rowCount();
  m_Model->addMessage("", false, {});

  connect(reply, &QNetworkReply::readyRead, this,
          [this, reply]() { handleStreamResponse(reply); });

  connect(reply, &QNetworkReply::finished, this, [this, reply]() {
    if (reply->error() != QNetworkReply::NoError) {
      QString errorMessage = "Error: " + reply->errorString();
      m_Model->updateMessageText(m_CurrentMessageIndex, errorMessage);
    }
    reply->deleteLater();
  });
}

void ChatBackend::handleStreamResponse(QNetworkReply *reply) {
  QByteArray data = reply->readAll();
  QStringList lines = QString(data).split("\n", Qt::SkipEmptyParts);

  for (const QString &line : lines) {
    QJsonDocument json_response = QJsonDocument::fromJson(line.toUtf8());
    if (const auto content = json_response.object()["response"].toString();
        !content.isEmpty()) {
      m_Model->updateMessageText(m_CurrentMessageIndex, content);
    }
    if (const auto context =
            json_response.object()["context"].toArray().toVariantList();
        !context.isEmpty()) {
      m_Model->updateMessageContext(m_CurrentMessageIndex, context);
    }
  }
}

}  // namespace llm_chat