#include <model.h>

#include <QTest>

class TestChatModel : public QObject {
  Q_OBJECT

 private slots:
  void testAddMessage() const;
  void testUpdateMessageText() const;
  void testUpdateMessageContext() const;
  void testClearMessages() const;
};

void TestChatModel::testAddMessage() const {
  llm_chat::ChatModel model;
  QCOMPARE(model.rowCount(), 0);

  model.addMessage("Hello", true, {});
  QCOMPARE(model.rowCount(), 1);
  QCOMPARE(
      model.data(model.index(0, 0), llm_chat::ChatModel::TextRole).toString(),
      "Hello");
  QCOMPARE(
      model.data(model.index(0, 0), llm_chat::ChatModel::IsUserRole).toBool(),
      true);

  model.addMessage("World", false, {QVariant("context")});
  QCOMPARE(model.rowCount(), 2);
  QCOMPARE(
      model.data(model.index(1, 0), llm_chat::ChatModel::TextRole).toString(),
      "World");
  QCOMPARE(
      model.data(model.index(1, 0), llm_chat::ChatModel::IsUserRole).toBool(),
      false);
  QCOMPARE(
      model.data(model.index(1, 0), llm_chat::ChatModel::ContextRole).toList(),
      QVariantList({"context"}));
}

void TestChatModel::testUpdateMessageText() const {
  llm_chat::ChatModel model;
  model.addMessage("Hello", true, {});

  model.updateMessageText(0, " World");
  QCOMPARE(
      model.data(model.index(0, 0), llm_chat::ChatModel::TextRole).toString(),
      "Hello World");
}

void TestChatModel::testUpdateMessageContext() const {
  llm_chat::ChatModel model;
  model.addMessage("Hello", true, {});

  model.updateMessageContext(0, {QVariant("context")});
  QCOMPARE(
      model.data(model.index(0, 0), llm_chat::ChatModel::ContextRole).toList(),
      QVariantList({"context"}));
}

void TestChatModel::testClearMessages() const {
  llm_chat::ChatModel model;
  model.addMessage("Hello", true, {});
  model.addMessage("World", false, {});
  QCOMPARE(model.rowCount(), 2);

  model.clearMessages();
  QCOMPARE(model.rowCount(), 0);
}

QTEST_MAIN(TestChatModel)
#include "tst_chat_model.moc"