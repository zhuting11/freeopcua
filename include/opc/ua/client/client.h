/******************************************************************************
 *   Copyright (C) 2014-2014 by Sintef Raufoss Manufacturing                  *
 *   olivier.roulet@gmail.com                  *
 *                                          *
 *   This library is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License as          *
 *   published by the Free Software Foundation; version 3 of the License.     *
 *                                          *
 *   This library is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.              *
 *                                          *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this library; if not, write to the                  *
 *   Free Software Foundation, Inc.,                          *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
 ******************************************************************************/


#pragma once

#include <opc/ua/node.h>
#include <opc/ua/services/services.h>
#include <opc/ua/subscription.h>
#include <opc/ua/client/binary_server.h>


namespace OpcUa
{

  class NotConnectedError : public std::runtime_error 
  {
    public:
      NotConnectedError() : std::runtime_error("NotConnectedError") { }
  };


  class RemoteClient
  {
  public:
    RemoteClient(bool debug=false) : Debug(debug) {}
    explicit RemoteClient(const std::string& endpoint, bool debug=false) : Endpoint(endpoint), Debug(debug) {}
    ~RemoteClient() {}

    RemoteClient(const RemoteClient&&) = delete;
    RemoteClient(const RemoteClient&) = delete;
    RemoteClient& operator=(const RemoteClient&) = delete;

    void SetSessionName(const std::string& str) { SessionName = str; }
    std::string GetSessionName() const { return SessionName; }

    std::string GetURI() const { return Uri; }
    void SetURI(std::string uri) { Uri = uri; }

    std::string  GetEndpoint() const { return Endpoint; }
    void SetEndpoint(std::string endpoint) { Endpoint = endpoint; }

    void SetSecurityPolicy(std::string sec) {SecurityPolicy = sec;}
    std::string GetSecurityPolicy() const { return SecurityPolicy; }

    Node GetRootNode() const;
    Node GetObjectsNode() const;
    Node GetServerNode() const;
    Node GetNode(NodeID nodeid) const;

    void Connect();
    void Disconnect();

    std::unique_ptr<Subscription> CreateSubscription(unsigned int period, SubscriptionClient& client);

  private:
    std::string Endpoint = "opc.tcp:://localhost:4841";
    std::string SessionName = "Open source OPC-UA Client Session";
    std::string Uri = "https://freeopcua.github.io/opcua-client";
    std::string ConfigPath=".";
    std::string SecurityPolicy = "none";
    bool Debug = false; 

  protected:
    Services::SharedPtr Server;

  };

} // namespace OpcUa
