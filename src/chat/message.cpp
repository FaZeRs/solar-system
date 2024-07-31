#include "message.h"

namespace llm_chat {

Message::Message(const QString text, const bool is_user,
                 const QVector<QVariant> &context, QObject *parent)
    : QObject(parent), m_Text(text), m_IsUser(is_user), m_Context(context) {}

QString Message::text() const { return m_Text; }

void Message::setText(const QString text) { m_Text = text; }

bool Message::isUser() const { return m_IsUser; }

QVector<QVariant> Message::context() const { return m_Context; }

void Message::setContext(const QVector<QVariant> &context) {
  m_Context = context;
}

}  // namespace llm_chat