#ifndef CHAT_MODEL_H
#define CHAT_MODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "message.h"

namespace llm_chat {

class ChatModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(QList<Message *> messages READ messages CONSTANT)

 public:
  enum MessageRoles { TextRole = Qt::UserRole + 1, IsUserRole };

  explicit ChatModel(QObject *parent = nullptr);

  [[nodiscard]] int rowCount(
      const QModelIndex &parent = QModelIndex()) const override;
  [[nodiscard]] QVariant data(const QModelIndex &index,
                              int role = Qt::DisplayRole) const override;
  [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void addMessage(const QString &text, bool is_user,
                              const QVector<QVariant> &context);
  void updateMessageText(int index, const QString &new_text);
  void updateMessageContext(int index, const QVector<QVariant> &new_context);

  [[nodiscard]] QList<Message *> messages() const;
  void clearMessages();

 private:
  QList<Message *> m_Messages;
};

}  // namespace llm_chat

#endif  // CHAT_MODEL_H