#ifndef PASSWORDUTIL_H
#define PASSWORDUTIL_H

#include <QString>
#include <QCryptographicHash>

// A utility namespace — just a collection of helper functions.
// No class needed, no instance needed. Call it like:
//   PasswordUtil::hash("mypassword")

namespace PasswordUtil {

// Takes a plain-text password, returns its SHA-256 hash as a hex string.
// SHA-256 is a one-way function: you can go from password → hash,
// but you CANNOT go from hash → password.
// This means even if someone reads your .db file, passwords are safe.
inline QString hash(const QString& password) {
    return QString(QCryptographicHash::hash(
                       password.toUtf8(),
                       QCryptographicHash::Sha256
                       ).toHex());
}

// To verify a login: hash(entered) == stored_hash
inline bool verify(const QString& entered, const QString& stored) {
    return hash(entered) == stored;
}
}

#endif
