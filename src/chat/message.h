#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>

namespace llm_chat {

class Message : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString text READ text CONSTANT)
  Q_PROPERTY(bool isUser READ isUser CONSTANT)
  Q_PROPERTY(QVector<QVariant> context READ context CONSTANT)

 public:
  Message(const QString text, const bool is_user,
          const QVector<QVariant> &context, QObject *parent = nullptr);

  [[nodiscard]] QString text() const;
  void setText(const QString text);
  [[nodiscard]] bool isUser() const;
  [[nodiscard]] QVector<QVariant> context() const;
  void setContext(const QVector<QVariant> &context);

 private:
  QString m_Text;
  bool m_IsUser;
  QVector<QVariant> m_Context;
};

}  // namespace llm_chat

Q_DECLARE_METATYPE(llm_chat::Message *)

#endif  // MESSAGE_H