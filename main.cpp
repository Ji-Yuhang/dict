#include <QCoreApplication>
#include <QStringList>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QTextCodec>
//#include <QLabel>
//#include <QApplication>
//#include <QTextEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
//#include <QtWidgets/QLabel>
#include <iostream>
struct word_info
{
};
word_info getWord(const QString& word)
{    
    word_info info;

    QNetworkAccessManager manager_;
//    QString url = QString("https://api.shanbay.com/bdc/search/?word={%1}").arg(word);
    QString url = QString("https://api.shanbay.com/bdc/search/?word=%1").arg(word);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QString tokenStr = QString("Bearer %1").arg("kIFgt2b3QJwkmZ8hpi0QwvCCs6m59c");
    request.setRawHeader("Authorization",tokenStr.toLatin1());
    QNetworkReply* reply = manager_.get(request);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    QTimer::singleShot(3000, &loop, SLOT(quit()));
    loop.exec();
    QByteArray data = reply->readAll();
    if (!data.isEmpty()) {
        QString text = QString::fromUtf8(data);
        QTextCodec* codec = QTextCodec::codecForHtml(data,QTextCodec::codecForName("UTF-16"));
        QString text2 = codec->toUnicode(data);
//        qDebug() << text<<endl<< data<<endl;//<<data.toHex()<<endl<<text2;
        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &error);
        if (error.error == QJsonParseError::NoError)
        {
            QString doubleJson = jsonDocument.toJson();
//            qDebug() << doubleJson<< endl;
            if (jsonDocument.isObject()) {
                QJsonObject json = jsonDocument.object();
                if (json.contains("data")) {
                    QJsonValue datavalue = json.value("data");
                    QJsonObject obj =  datavalue.toObject();
                    QJsonValue cnValue = obj.value("definition");
                    QString wordcn = cnValue.toString();
//                    qDebug() << wordcn<< endl;
                    std::cout<< wordcn.toUtf8().data() << std::endl;
                }
            }
        }
//        QLabel* l = new QLabel;
//        l->resize(400,400);
//        l->showNormal();
//        l->setText(data);
//        QTextEdit* e = new QTextEdit;
//        e->resize(400,400);
        
//        e->showNormal();
//        e->setHtml(data);
//        loop.exec();
        return info;
    } else
        return info;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    if (args.size() < 2 ) return 0;
    QString word = args.at(1);
    word_info info = getWord(word);
//    qDebug() << "this is word's meaning" << endl;
//    getchar();
    a.quit();
    return 0;

    return a.exec();
}
