#include <message.h>

#include <QTest>

class TestChatMessage : public QObject {
  Q_OBJECT

 private slots:
  void testConstructor() const;
  void testSetText() const;
  void testSetContext() const;
};

void TestChatMessage::testConstructor() const {
  llm_chat::Message message("Hello", true, {QVariant("context")});
  QCOMPARE(message.text(), "Hello");
  QCOMPARE(message.isUser(), true);
  QCOMPARE(message.context(), QVector<QVariant>({"context"}));
}

void TestChatMessage::testSetText() const {
  llm_chat::Message message("Hello", true, {});
  message.setText("World");
  QCOMPARE(message.text(), "World");
}

void TestChatMessage::testSetContext() const {
  llm_chat::Message message("Hello", true, {});
  message.setContext({QVariant("context")});
  QCOMPARE(message.context(), QVector<QVariant>({"context"}));
}

QTEST_MAIN(TestChatMessage)
#include "tst_chat_message.moc"