/**************************** vpnagent.h **********************************

Code for the user agent registered on DBus.  When the connman vpn daemon
needs to communicate with the user it does so through this agent.

Copyright (C) 2016-2022
by: Andrew J. Bibb
License: MIT 

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"),to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions: 

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
***********************************************************************/  


# ifndef CONNMAN_VPN_AGENT
# define CONNMAN_VPN_AGENT

# include <QObject>
# include <QString>
# include <QMap>
# include <QVariant>
# include <QVariantMap>
# include <QtDBus/QDBusObjectPath>
# include <QtDBus/QDBusContext>

# include "./code/vpn_agent/vpnagent_dialog.h"

# define VPN_AGENT_SERVICE "org.cmst"
# define VPN_AGENT_INTERFACE "net.connman.vpn.Agent"
# define VPN_AGENT_OBJECT "/org/cmst/VPNAgent"

class ConnmanVPNAgent : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", VPN_AGENT_INTERFACE)
 
    public:
      ConnmanVPNAgent(QObject*);      
      inline void setLogInputRequest(bool b) {b_loginputrequest = b;}
 
    public Q_SLOTS:
      void Release();
      void ReportError(QDBusObjectPath, QString);
      QVariantMap RequestInput(QDBusObjectPath, QMap<QString,QVariant>);
      void Cancel();
     
    private:
      VPNAgentDialog* uiDialog;   
      QMap<QString,QString> input_map;
      bool b_loginputrequest;    
      void createInputMap(const QMap<QString,QVariant>&); 
      
    public:
      inline void setWhatsThisIcon(QIcon icon) {uiDialog->setWhatsThisIcon(icon);}  
};    

#endif
