/*
    This file is part of the KContacts framework.
    Copyright (c) 2015 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "resourcelocatorurltest.h"

#include "resourcelocatorurl.h"
#include "vcardtool.h"
#include <qtest.h>

using namespace KContacts;
ResourceLocatorUrlTest::ResourceLocatorUrlTest(QObject *parent)
    : QObject(parent)
{

}

ResourceLocatorUrlTest::~ResourceLocatorUrlTest()
{

}

void ResourceLocatorUrlTest::shouldHaveDefaultValue()
{
    ResourceLocatorUrl ResourceLocatorUrl;
    QVERIFY(!ResourceLocatorUrl.isValid());
    QVERIFY(ResourceLocatorUrl.url().isEmpty());
    QVERIFY(ResourceLocatorUrl.parameters().isEmpty());
}

void ResourceLocatorUrlTest::shouldAssignValue()
{
    QMap<QString, QStringList> params;
    params.insert(QStringLiteral("Foo1"), QStringList() << QStringLiteral("bla1") << QStringLiteral("blo1"));
    params.insert(QStringLiteral("Foo2"), QStringList() << QStringLiteral("bla2") << QStringLiteral("blo2"));
    ResourceLocatorUrl ResourceLocatorUrl;
    ResourceLocatorUrl.setParameters(params);
    QVERIFY(!ResourceLocatorUrl.isValid());
    QVERIFY(ResourceLocatorUrl.url().isEmpty());
    QVERIFY(!ResourceLocatorUrl.parameters().isEmpty());
    QCOMPARE(ResourceLocatorUrl.parameters(), params);
}

void ResourceLocatorUrlTest::shouldAssignExternal()
{
    ResourceLocatorUrl resourcelocatorurl;
    QUrl url = QUrl(QStringLiteral("https://www.kde.org"));
    resourcelocatorurl.setUrl(url);
    QVERIFY(!resourcelocatorurl.url().isEmpty());
    QCOMPARE(resourcelocatorurl.url(), url);
}

void ResourceLocatorUrlTest::shouldSerialized()
{
    ResourceLocatorUrl resourcelocatorurl;
    ResourceLocatorUrl result;
    QMap<QString, QStringList> params;
    params.insert(QStringLiteral("Foo1"), QStringList() << QStringLiteral("bla1") << QStringLiteral("blo1"));
    params.insert(QStringLiteral("Foo2"), QStringList() << QStringLiteral("bla2") << QStringLiteral("blo2"));
    resourcelocatorurl.setParameters(params);
    resourcelocatorurl.setUrl(QUrl(QStringLiteral("mailto:foo@kde.org")));

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);
    s << resourcelocatorurl;

    QDataStream t(&data, QIODevice::ReadOnly);
    t >> result;

    QVERIFY(resourcelocatorurl == result);
}

void ResourceLocatorUrlTest::shouldEqualResourceLocatorUrl()
{
    ResourceLocatorUrl resourcelocatorurl;
    ResourceLocatorUrl result;
    QMap<QString, QStringList> params;
    params.insert(QStringLiteral("Foo1"), QStringList() << QStringLiteral("bla1") << QStringLiteral("blo1"));
    params.insert(QStringLiteral("Foo2"), QStringList() << QStringLiteral("bla2") << QStringLiteral("blo2"));
    resourcelocatorurl.setUrl(QUrl(QStringLiteral("mailto:foo@kde.org")));
    resourcelocatorurl.setParameters(params);

    result = resourcelocatorurl;
    QVERIFY(resourcelocatorurl == result);
}

void ResourceLocatorUrlTest::shouldParseResourceLocatorUrl()
{
    QByteArray vcarddata("BEGIN:VCARD\n"
                         "VERSION:3.0\n"
                         "N:LastName;FirstName;;;\n"
                         "UID:c80cf296-0825-4eb0-ab16-1fac1d522a33@xxxxxx.xx\n"
                         "URL;PREF=1:https://firsturl\n"
                         "URL;PREF=1:https://sherlockholmes.com/calendar/sherlockholmes\n"
                         "REV:2015-03-14T09:24:45+00:00\n"
                         "FN:FirstName LastName\n"
                         "END:VCARD\n");

    KContacts::VCardTool vcard;
    const KContacts::AddresseeList lst = vcard.parseVCards(vcarddata);
    QCOMPARE(lst.count(), 1);
    QCOMPARE(lst.at(0).extraUrlList().count(), 2);
    const ResourceLocatorUrl calurl = lst.at(0).extraUrlList().at(0);
    QCOMPARE(calurl.url(), QUrl(QStringLiteral("https://firsturl")));
    QVERIFY(!calurl.parameters().isEmpty());
}

void ResourceLocatorUrlTest::shouldGenerateVCard4()
{
    KContacts::AddresseeList lst;
    KContacts::Addressee addr;
    addr.setEmails(QStringList() << QStringLiteral("foo@kde.org"));
    addr.setUid(QStringLiteral("testuid"));
    KContacts::ResourceLocatorUrl webpage;
    webpage.setUrl(QUrl(QStringLiteral("https://www.kde.org")));
    addr.setUrl(webpage);
    ResourceLocatorUrl url;
    url.setUrl(QUrl(QStringLiteral("https://sherlockholmes.com/calendar/sherlockholmes")));
    addr.insertExtraUrl(url);
    url.setUrl(QUrl(QStringLiteral("https://foo.kde.org")));
    addr.insertExtraUrl(url);
    lst << addr;
    KContacts::VCardTool vcard;
    const QByteArray ba = vcard.exportVCards(lst, KContacts::VCard::v4_0);
    QByteArray expected;
    expected = QByteArray("BEGIN:VCARD\r\n"
                          "VERSION:4.0\r\n"
                          "EMAIL:foo@kde.org\r\n"
                          "N:;;;;\r\n"
                          "UID:testuid\r\n"
                          "URL:https://www.kde.org\r\n"
                          "URL:https://sherlockholmes.com/calendar/sherlockholmes\r\n"
                          "URL:https://foo.kde.org\r\n"
                          "END:VCARD\r\n\r\n");

    QCOMPARE(ba, expected);
}

void ResourceLocatorUrlTest::shouldGenerateVCardWithParameter()
{
    KContacts::AddresseeList lst;
    KContacts::Addressee addr;
    addr.setEmails(QStringList() << QStringLiteral("foo@kde.org"));
    addr.setUid(QStringLiteral("testuid"));
    KContacts::ResourceLocatorUrl webpage;
    webpage.setUrl(QUrl(QStringLiteral("https://www.kde.org")));
    addr.setUrl(webpage);
    ResourceLocatorUrl url;
    url.setUrl(QUrl(QStringLiteral("https://sherlockholmes.com/calendar/sherlockholmes")));
    QMap<QString, QStringList> params;
    params.insert(QStringLiteral("Foo2"), QStringList() << QStringLiteral("bla2") << QStringLiteral("blo2"));
    url.setParameters(params);
    addr.insertExtraUrl(url);
    url.setUrl(QUrl(QStringLiteral("https://foo.kde.org")));
    QMap<QString, QStringList> params2;
    url.setParameters(params2);
    addr.insertExtraUrl(url);
    lst << addr;
    KContacts::VCardTool vcard;
    const QByteArray ba = vcard.exportVCards(lst, KContacts::VCard::v4_0);
    QByteArray expected;
    expected = QByteArray("BEGIN:VCARD\r\n"
                          "VERSION:4.0\r\n"
                          "EMAIL:foo@kde.org\r\n"
                          "N:;;;;\r\n"
                          "UID:testuid\r\n"
                          "URL:https://www.kde.org\r\n"
                          "URL;FOO2=bla2,blo2:https://sherlockholmes.com/calendar/sherlockholmes\r\n"
                          "URL:https://foo.kde.org\r\n"
                          "END:VCARD\r\n\r\n");

    QCOMPARE(ba, expected);
}

void ResourceLocatorUrlTest::shouldGenerateVCard3()
{
    KContacts::AddresseeList lst;
    KContacts::Addressee addr;
    addr.setEmails(QStringList() << QStringLiteral("foo@kde.org"));
    addr.setUid(QStringLiteral("testuid"));
    KContacts::ResourceLocatorUrl webpage;
    webpage.setUrl(QUrl(QStringLiteral("https://www.kde.org")));
    addr.setUrl(webpage);
    ResourceLocatorUrl url;
    url.setUrl(QUrl(QStringLiteral("https://sherlockholmes.com/calendar/sherlockholmes")));
    QMap<QString, QStringList> params;
    params.insert(QStringLiteral("Foo2"), QStringList() << QStringLiteral("bla2") << QStringLiteral("blo2"));
    url.setParameters(params);
    addr.insertExtraUrl(url);
    url.setUrl(QUrl(QStringLiteral("https://foo.kde.org")));
    QMap<QString, QStringList> params2;
    url.setParameters(params2);
    addr.insertExtraUrl(url);
    lst << addr;
    KContacts::VCardTool vcard;
    const QByteArray ba = vcard.exportVCards(lst, KContacts::VCard::v3_0);
    QByteArray expected;
    expected = QByteArray("BEGIN:VCARD\r\n"
                          "VERSION:3.0\r\n"
                          "EMAIL:foo@kde.org\r\n"
                          "N:;;;;\r\n"
                          "UID:testuid\r\n"
                          "URL:https://www.kde.org\r\n"
                          "URL;FOO2=bla2,blo2:https://sherlockholmes.com/calendar/sherlockholmes\r\n"
                          "URL:https://foo.kde.org\r\n"
                          "END:VCARD\r\n\r\n");

    QCOMPARE(ba, expected);

}

QTEST_MAIN(ResourceLocatorUrlTest)

