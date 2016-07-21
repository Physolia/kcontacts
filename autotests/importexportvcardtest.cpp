/*
    This file is part of the KContacts framework.
    Copyright (c) 2016 Laurent Montel <montel@kde.org>

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

#include "importexportvcardtest.h"
#include <QTest>
#include "vcardtool.h"


ImportExportVCardTest::ImportExportVCardTest(QObject *parent)
    : QObject(parent)
{

}

ImportExportVCardTest::~ImportExportVCardTest()
{

}

void ImportExportVCardTest::shouldExportFullTestVcard4()
{
    QByteArray vcarddata("BEGIN:VCARD\r\n"
                         "VERSION:4.0\r\n"
                         "FN:Sherlock Holmes\r\n"
                         "TEL;VALUE=uri;PREF=1;TYPE=\"voice,home\":tel:+44-555-555-5555;ext=5555\r\n"
                         "TEL;VALUE=uri;TYPE=\"voice,cell,text\":tel:+44-555-555-6666\r\n"
                         "TEL;VALUE=uri;TYPE=\"voice,work\":tel:+44-555-555-7777\r\n"
                         "N:Holmes;Sherlock;;Mr;;\r\n"
                         "KIND:individual\r\n"
                         "NICKNAME:Shirley\r\n"
                         "PHOTO:\r\n"
                         "BDAY:19531015T231000Z\r\n"
                         "ANNIVERSARY:19960415\r\n"
                         "GENDER:M\r\n"
                         "ADR;GEO=\"geo:51.5237,0.1585\";LABEL=\"Mr Sherlock Holmes, 221B Baker Street, London NW1, England, United Kingdom\":;;221B Baker Street;London;;NW1;United Kingdom\r\n"
                         "EMAIL;TYPE=home:sherlock.holmes@gmail.com\r\n"
                         "EMAIL;PREF=1;TYPE=work:detective@sherlockholmes.com\r\n"
                         "IMPP;PREF=1:xmpp:detective@sherlockholmes.com\r\n"
                         "LANG;TYPE=work;PREF=1:en\r\n"
                         "LANG;TYPE=work;PREF=2:fr\r\n"
                         "TZ:London/Europe\r\n"
                         "GEO:geo:51.5237,0.1585\r\n"
                         "TITLE:Detective\r\n"
                         "ROLE:Detective\r\n"
                         "UID:urn:uuid:b8767877-b4a1-4c70-9acc-505d3819e519\r\n"
                         "CATEGORIES:FICTION,LITERATURE\r\n"
                         "PRODID:-//KADDRESSBOOK//NONSGML Version 1//EN\r\n"
                         "REV:2014722T222710Z\r\n"
                         "URL:https://sherlockholmes.com\r\n"
                         "KEY;MEDIATYPE=application/pgp-keys:https://sherlockholmes.com/sherlock-holmes.pub.asc\r\n"
                         "CALURI;PREF=1:https://sherlockholmes.com/calendar/sherlockholmes\r\n"
                         "FBURL;PREF=1:https://sherlockholmes.com/busy/detective\r\n"
                         "CALADRURI;PREF=1:mailto:detective@sherlockholmes.com\r\n"
                         "END:VCARD\r\n\r\n");
    QByteArray vcardexpected("BEGIN:VCARD\r\n"
                             "VERSION:4.0\r\n"
                             "ADR;GEO=\"geo:51.523701,0.158500\";LABEL=\"Mr Sherlock Holmes\";TYPE:;;221B Bak\r\n"
                             " er Street;London;;NW1;United Kingdom\r\n"
                             "ANNIVERSARY:19960415T000000\r\n"
                             "BDAY:19531015T231000Z\r\n"
                             "CALADRURI;PREF=1:mailto:detective@sherlockholmes.com\r\n"
                             "CALURI;PREF=1:https://sherlockholmes.com/calendar/sherlockholmes\r\n"
                             "EMAIL;TYPE=home:sherlock.holmes@gmail.com\r\n"
                             "EMAIL;PREF=1;TYPE=work:detective@sherlockholmes.com\r\n"
                             "FBURL;PREF=1:https://sherlockholmes.com/busy/detective\r\n"
                             "FN:Sherlock Holmes\r\n"
                             "GENDER:M\r\n"
                             "GEO:geo:51.523701,0.158500\r\n"
                             "IMPP;X-SERVICE-TYPE=xmpp;PREF=1:detective@sherlockholmes.com\r\n"
                             "KEY;MEDIATYPE=application/pgp-keys:https://sherlockholmes.com/sherlock-holm\r\n"
                             " es.pub.asc\r\n"
                             "KIND:individual\r\n"
                             "LANG;PREF=1;TYPE=work:en\r\n"
                             "LANG;PREF=2;TYPE=work:fr\r\n"
                             "N:Holmes;Sherlock;;Mr;\r\n"
                             "NICKNAME:Shirley\r\n"
                             "PRODID:-//KADDRESSBOOK//NONSGML Version 1//EN\r\n"
                             "ROLE:Detective\r\n"
                             "TEL:ext=5555\r\n"
                             "TEL;TYPE=\"cell,voice\":tel:+44-555-555-6666\r\n"
                             "TEL;TYPE=\"voice,work\":tel:+44-555-555-7777\r\n"
                             "TITLE:Detective\r\n"
                             "TZ:+00:00\r\n"
                             "UID:urn:uuid:b8767877-b4a1-4c70-9acc-505d3819e519\r\n"
                             "URL:https://sherlockholmes.com\r\n"
                             "END:VCARD\r\n\r\n");
    KContacts::VCardTool vcard;
    const KContacts::AddresseeList lst = vcard.parseVCards(vcarddata);

    const QByteArray result = vcard.exportVCards(lst, KContacts::VCard::v4_0);
    qDebug() << " result "<< result;
    QCOMPARE(result, vcardexpected);

}

QTEST_MAIN(ImportExportVCardTest)
