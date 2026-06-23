#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include<QString>
class SessionManager
{private:
    int m_userid;
    QString m_email;
    bool m_Loggedin;
    SessionManager()
    {
        m_userid=-1;
        m_email="";
        m_Loggedin=false;
    };

public:
    static SessionManager& instance()
    {
        static SessionManager inst;
        return inst;
    }
    SessionManager(const SessionManager&)=delete;
    SessionManager operator=(const SessionManager&)=delete;
    const bool isLoggedin()
   {
        return m_Loggedin;
   }
   const int userid()
   {return m_userid;}
   const QString email()
   {
       return m_email;
   }


     void setUser (int id, QString email)
    {
        m_userid=id;
        m_email=email;
        m_Loggedin=true;

    }
    void clear()
    {   m_userid=0;
        m_email.clear();
        m_Loggedin=false;
    }

};

#endif // SESSIONMANAGER_H
