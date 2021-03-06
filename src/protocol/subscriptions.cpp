/// @author Alexander Rykovanov 2012
/// @email rykovanov.as@gmail.com
/// @brief Opc Ua Binary. Subscription services structs.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)
///

#include "binary_serialization.h"

#include <opc/ua/protocol/binary/stream.h>
#include <opc/ua/protocol/subscriptions.h>
#include <opc/ua/protocol/monitored_items.h>

namespace OpcUa
{
  ////////////////////////////////////////////////////////
  // SubscriptionParameters
  ////////////////////////////////////////////////////////

  SubscriptionParameters::SubscriptionParameters()
    : RequestedPublishingInterval(500)
    , RequestedLifetimeCount(3000)
    , RequestedMaxKeepAliveCount(10000)
    , MaxNotificationsPerPublish(0)
    , PublishingEnabled(true)
    , Priority(0)
  {
  }

  ////////////////////////////////////////////////////////
  // CreateSubscriptionRequest
  ////////////////////////////////////////////////////////

  CreateSubscriptionRequest::CreateSubscriptionRequest()
    : TypeID(CREATE_SUBSCRIPTION_REQUEST)
  {
  }

  ////////////////////////////////////////////////////////
  // DeleteSubscriptionRequest
  ////////////////////////////////////////////////////////

  DeleteSubscriptionRequest::DeleteSubscriptionRequest()
    : TypeID(DELETE_SUBSCRIPTION_REQUEST)
  {
  }

  DeleteSubscriptionResponse::DeleteSubscriptionResponse()
    : TypeID(DELETE_SUBSCRIPTION_RESPONSE)
  {
  }


  ////////////////////////////////////////////////////////
  // SubscriptionData
  ////////////////////////////////////////////////////////

  SubscriptionData::SubscriptionData()
    : RevisedPublishingInterval(100)
    , RevisedLifetimeCount(30) //Should be 3 times keepalive
    , RevizedMaxKeepAliveCount(10)
  {
  }

  ////////////////////////////////////////////////////////
  // CreateSubscriptionResponse
  ////////////////////////////////////////////////////////

  CreateSubscriptionResponse::CreateSubscriptionResponse()
    : TypeID(CREATE_SUBSCRIPTION_RESPONSE)
  {
  }

  ////////////////////////////////////////////////////////
  // SubscriptionAcknowledgement
  ////////////////////////////////////////////////////////

  SubscriptionAcknowledgement::SubscriptionAcknowledgement()
    : SequenceNumber(0)
  {
  }

  ////////////////////////////////////////////////////////
  // PublishRequest
  ////////////////////////////////////////////////////////

  PublishRequest::PublishRequest()
    : TypeID(PUBLISH_REQUEST)
  {
  }

  ////////////////////////////////////////////////////////
  // PublishResult
  ////////////////////////////////////////////////////////

  PublishResult::PublishResult()
    : MoreNotifications(false)
  {
  }

  ////////////////////////////////////////////////////////
  // PublishResponse
  ////////////////////////////////////////////////////////

  PublishResponse::PublishResponse()
    : TypeID(PUBLISH_RESPONSE)
  {
  }


  ////////////////////////////////////////////////////////
  // NotificationData
  ////////////////////////////////////////////////////////

    NotificationData::NotificationData(DataChangeNotification notification) : DataChange(notification)
    {
      //Header.TypeID  = ObjectID::DataChangeNotification; 
      Header.TypeID  = ExpandedObjectID::DataChangeNotification;
      Header.Encoding  = static_cast<ExtensionObjectEncoding>(Header.Encoding | ExtensionObjectEncoding::HAS_BINARY_BODY);
    }

    NotificationData::NotificationData(EventNotificationList notification) : Events(notification)
    {
      Header.TypeID  = ExpandedObjectID::EventNotificationList; 
      Header.Encoding  = static_cast<ExtensionObjectEncoding>(Header.Encoding | ExtensionObjectEncoding::HAS_BINARY_BODY);
    }

    NotificationData::NotificationData(StatusChangeNotification notification) : StatusChange(notification)
    {
      Header.TypeID  = ExpandedObjectID::StatusChangeNotification; 
      Header.Encoding  = static_cast<ExtensionObjectEncoding>(Header.Encoding | ExtensionObjectEncoding::HAS_BINARY_BODY);
    }


  ////////////////////////////////////////////////////////
  // NotificationMessage
  ////////////////////////////////////////////////////////

  NotificationMessage::NotificationMessage()
    : SequenceID(0)
    , PublishTime(CurrentDateTime())
  {
  }

  ////////////////////////////////////////////////////////
  // PublishingModeParameters
  ////////////////////////////////////////////////////////

  PublishingModeParameters::PublishingModeParameters()
    : Enabled(false)
  {
  }

  ////////////////////////////////////////////////////////
  // SetPublishingModeRequest
  ////////////////////////////////////////////////////////

  SetPublishingModeRequest::SetPublishingModeRequest()
    : TypeID(SET_PUBLISHING_MODE_REQUEST)
  {
  }

  ////////////////////////////////////////////////////////
  // SetPublishingModeResponse
  ////////////////////////////////////////////////////////

  SetPublishingModeResponse::SetPublishingModeResponse()
    : TypeID(OpcUa::SET_PUBLISHING_MODE_RESPONSE)
  {
  }

  ////////////////////////////////////////////////////////

  namespace Binary
  {
    ////////////////////////////////////////////////////////
    // SubscriptionParameters
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize<SubscriptionParameters>(const SubscriptionParameters& params)
    {
      return RawSize(params.RequestedPublishingInterval) +
          RawSize(params.RequestedLifetimeCount) +
          RawSize(params.RequestedMaxKeepAliveCount) +
          RawSize(params.MaxNotificationsPerPublish) +
          RawSize(params.PublishingEnabled) +
          RawSize(params.Priority);
    }

    template<>
    void DataDeserializer::Deserialize<SubscriptionParameters>(SubscriptionParameters& params)
    {
      *this >> params.RequestedPublishingInterval;
      *this >> params.RequestedLifetimeCount;
      *this >> params.RequestedMaxKeepAliveCount;
      *this >> params.MaxNotificationsPerPublish;
      *this >> params.PublishingEnabled;
      *this >> params.Priority;
    }

    template<>
    void DataSerializer::Serialize<SubscriptionParameters>(const SubscriptionParameters& params)
    {
      *this << params.RequestedPublishingInterval;
      *this << params.RequestedLifetimeCount;
      *this << params.RequestedMaxKeepAliveCount;
      *this << params.MaxNotificationsPerPublish;
      *this << params.PublishingEnabled;
      *this << params.Priority;
    }

    ////////////////////////////////////////////////////////
    // DelteSubscriptionRequest
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const DeleteSubscriptionRequest& request)
    {
      return RawSize(request.TypeID) +
        RawSize(request.Header) +
        RawSizeContainer(request.SubscriptionsIds);
    }

    template<>
    void DataDeserializer::Deserialize<DeleteSubscriptionRequest>(DeleteSubscriptionRequest& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.SubscriptionsIds;
    }

    template<>
    void DataSerializer::Serialize<DeleteSubscriptionRequest>(const DeleteSubscriptionRequest& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.SubscriptionsIds;
    }



    ////////////////////////////////////////////////////////
    // DeleteSubscriptionResponse
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const DeleteSubscriptionResponse& request)
    {
      return RawSize(request.TypeID) +
        RawSize(request.Header) +
        RawSizeContainer(request.Results) +
        RawSizeContainer(request.Diagnostic);
    }

    template<>
    void DataDeserializer::Deserialize<DeleteSubscriptionResponse>(DeleteSubscriptionResponse& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.Results;
      *this >> request.Diagnostic;
    }

    template<>
    void DataSerializer::Serialize<DeleteSubscriptionResponse>(const DeleteSubscriptionResponse& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.Results;
      *this << request.Diagnostic;
    }


    ////////////////////////////////////////////////////////
    // CreateSubscriptionRequest
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const CreateSubscriptionRequest& request)
    {
      return RawSize(request.TypeID) +
        RawSize(request.Header) +
        RawSize(request.Parameters);
    }

    template<>
    void DataDeserializer::Deserialize<CreateSubscriptionRequest>(CreateSubscriptionRequest& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.Parameters;
    }

    template<>
    void DataSerializer::Serialize<CreateSubscriptionRequest>(const CreateSubscriptionRequest& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.Parameters;
    }

    ////////////////////////////////////////////////////////
    // SubscriptionData
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const SubscriptionData& data)
    {
      return RawSize(data.ID) +
        RawSize(data.RevisedPublishingInterval) +
        RawSize(data.RevisedLifetimeCount) +
        RawSize(data.RevizedMaxKeepAliveCount);
    }

    template<>
    void DataDeserializer::Deserialize<SubscriptionData>(SubscriptionData& data)
    {
      *this >> data.ID;
      *this >> data.RevisedPublishingInterval;
      *this >> data.RevisedLifetimeCount;
      *this >> data.RevizedMaxKeepAliveCount;
    }

    template<>
    void DataSerializer::Serialize<SubscriptionData>(const SubscriptionData& data)
    {
      *this << data.ID;
      *this << data.RevisedPublishingInterval;
      *this << data.RevisedLifetimeCount;
      *this << data.RevizedMaxKeepAliveCount;
    }

    ////////////////////////////////////////////////////////
    // CreateSubscriptionResponse
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const CreateSubscriptionResponse& response)
    {
      return RawSize(response.TypeID) +
        RawSize(response.Header) +
        RawSize(response.Data);
    }

    template<>
    void DataDeserializer::Deserialize<CreateSubscriptionResponse>(CreateSubscriptionResponse& response)
    {
      *this >> response.TypeID;
      *this >> response.Header;
      *this >> response.Data;
    }

    template<>
    void DataSerializer::Serialize<CreateSubscriptionResponse>(const CreateSubscriptionResponse& response)
    {
      *this << response.TypeID;
      *this << response.Header;
      *this << response.Data;
    }

    ////////////////////////////////////////////////////////
    // SubscriptionAcknowledgement
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const SubscriptionAcknowledgement& ack)
    {
      return RawSize(ack.SubscriptionID) + RawSize(ack.SequenceNumber);
    }

    template<>
    void DataDeserializer::Deserialize<SubscriptionAcknowledgement>(SubscriptionAcknowledgement& ack)
    {
      *this >> ack.SubscriptionID;
      *this >> ack.SequenceNumber;
    }

    template<>
    void DataSerializer::Serialize<SubscriptionAcknowledgement>(const SubscriptionAcknowledgement& ack)
    {
      *this << ack.SubscriptionID;
      *this << ack.SequenceNumber;
    }

    template<>
    std::size_t RawSize(const std::vector<SubscriptionAcknowledgement>& ack)
    {
      return RawSizeContainer(ack);
    }

    template<>
    void DataDeserializer::Deserialize<std::vector<SubscriptionAcknowledgement>>(std::vector<SubscriptionAcknowledgement>& ack)
    {
      DeserializeContainer(*this, ack);
    }

    template<>
    void DataSerializer::Serialize<std::vector<SubscriptionAcknowledgement>>(const std::vector<SubscriptionAcknowledgement>& ack)
    {
      SerializeContainer(*this, ack);
    }


    ////////////////////////////////////////////////////////
    // PublishParameters
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishParameters& params)
    {
      return RawSizeContainer(params.Acknowledgements);
    }

    template<>
    void DataDeserializer::Deserialize<PublishParameters>(PublishParameters& params)
    {
      *this >> params.Acknowledgements;
    }

    template<>
    void DataSerializer::Serialize<PublishParameters>(const PublishParameters& params)
    {
      *this << params.Acknowledgements;
    }

    ////////////////////////////////////////////////////////
    // PublishRequest
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishRequest& request)
    {
      return RawSize(request.TypeID) + RawSize(request.Header) + RawSize(request.Parameters);
    }

    template<>
    void DataDeserializer::Deserialize<PublishRequest>(PublishRequest& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.Parameters;
    }

    template<>
    void DataSerializer::Serialize<PublishRequest>(const PublishRequest& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.Parameters;
    }

    ////////////////////////////////////////////////////////
    // MonitoredItems
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const MonitoredItems& request)
    {
      return RawSize(request.ClientHandle) + RawSize(request.Value);
    }

    template<>
    void DataDeserializer::Deserialize<MonitoredItems>(MonitoredItems& request)
    {
      *this >> request.ClientHandle;
      *this >> request.Value;
    }

    template<>
    void DataSerializer::Serialize<MonitoredItems>(const MonitoredItems& request)
    {
      *this << request.ClientHandle;
      *this << request.Value;
    }

    template<>
    void DataSerializer::Serialize<std::vector<MonitoredItems>>(const std::vector<MonitoredItems>& targets)
    {
      SerializeContainer(*this, targets);
    }

    template<>
    void DataDeserializer::Deserialize<std::vector<MonitoredItems>>(std::vector<MonitoredItems>& targets)
    {
      DeserializeContainer(*this, targets);
    }

    ////////////////////////////////////////////////////////
    // StatusChangeNotification
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const StatusChangeNotification& request)
    {
      return 4 + RawSize(request.Status) + RawSize(request.Diagnostic);
    }

    template<>
    void DataDeserializer::Deserialize<StatusChangeNotification>(StatusChangeNotification& request)
    {
      uint32_t tmp;
      *this >> tmp; //it seems we do not need the size
      *this >> request.Status;
      *this >> request.Diagnostic;
    }

    template<>
    void DataSerializer::Serialize<StatusChangeNotification>(const StatusChangeNotification& request)
    {
      *this << (uint32_t) RawSize(request);
      *this << request.Status;
      *this << request.Diagnostic;
    }


    ////////////////////////////////////////////////////////
    // EventNotificationList
    ////////////////////////////////////////////////////////

    template<>
    void DataSerializer::Serialize<std::vector<EventFieldList>>(const std::vector<EventFieldList>& targets)
    {
      SerializeContainer(*this, targets);
    }

    template<>
    void DataDeserializer::Deserialize<std::vector<EventFieldList>>(std::vector<EventFieldList>& targets)
    {
      DeserializeContainer(*this, targets);
    }

    template<>
    std::size_t RawSize(const EventFieldList& request)
    {
      return RawSize(request.ClientHandle) + RawSizeContainer(request.EventFields); 
    }

    template<>
    void DataDeserializer::Deserialize<EventFieldList>(EventFieldList& request)
    {
      *this >> request.ClientHandle; 
      *this >> request.EventFields;
    }

    template<>
    void DataSerializer::Serialize<EventFieldList>(const EventFieldList& request)
    {
      *this << request.ClientHandle;
      *this << request.EventFields;
    }

    template<>
    std::size_t RawSize(const EventNotificationList& request)
    {
      return 4 + RawSizeContainer(request.Events); 
    }

    template<>
    void DataDeserializer::Deserialize<EventNotificationList>(EventNotificationList& request)
    {
      uint32_t tmp;
      *this >> tmp; //it seems we do not need the size
      *this >> request.Events;
    }

    template<>
    void DataSerializer::Serialize<EventNotificationList>(const EventNotificationList& request)
    {
      *this << (uint32_t) RawSize(request);
      *this << request.Events;
    }



    ////////////////////////////////////////////////////////
    // DataChangeNotification
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const DataChangeNotification& request)
    {
      return 4 + RawSizeContainer(request.Notification) + RawSize(request.Diagnostic);
    }

    template<>
    void DataDeserializer::Deserialize<DataChangeNotification>(DataChangeNotification& request)
    {
      uint32_t tmp;
      *this >> tmp; //it seems we do not need the size
      *this >> request.Notification;
      *this >> request.Diagnostic;
    }

    template<>
    void DataSerializer::Serialize<DataChangeNotification>(const DataChangeNotification& request)
    {
      *this << (uint32_t) RawSize(request);
      *this << request.Notification;
      *this << request.Diagnostic;
    }


    ////////////////////////////////////////////////////////
    // NotificationData
    ////////////////////////////////////////////////////////


    template<>
    std::size_t RawSize(const NotificationData& data)
    {
      size_t total = 0;
      total += RawSize(data.Header);
      if ( data.Header.TypeID == ExpandedObjectID::DataChangeNotification) 
      {
        total += RawSize(data.DataChange);
      }
      else if ( data.Header.TypeID == ExpandedObjectID::EventNotificationList) 
      {
        total += RawSize(data.Events);
      }
      else if ( data.Header.TypeID == ExpandedObjectID::StatusChangeNotification) 
      {
        total += RawSize(data.StatusChange);
      }
      else
      {
        //Unknown type, we just ignore it
        //throw std::runtime_error("Uknown notificationData type" );
      }
      return total;
    }

    template<>
    void DataDeserializer::Deserialize<NotificationData>(NotificationData& data)
    {
      *this >> data.Header;
      if ( data.Header.TypeID == ExpandedObjectID::DataChangeNotification ) 
      {
          *this >> data.DataChange;
      }
      else if ( data.Header.TypeID == ExpandedObjectID::EventNotificationList ) 
      {
          *this >> data.Events;
      }
      else if ( data.Header.TypeID == ExpandedObjectID::StatusChangeNotification ) 
      {
          *this >> data.StatusChange;
      }
      else
      {
        //Unknown type, we just ignore it
        //throw std::runtime_error("Uknown notification data type found in NotificationData");
      }
    }

    template<>
    void DataSerializer::Serialize<NotificationData>(const NotificationData& data)
    {
      *this << data.Header;
      if ( data.Header.TypeID == ExpandedObjectID::DataChangeNotification ) 
      {
        *this << data.DataChange;
      }
      else if ( data.Header.TypeID == ExpandedObjectID::EventNotificationList ) 
      {
        *this << data.Events;
      }
      else if ( data.Header.TypeID == ExpandedObjectID::StatusChangeNotification ) 
      {
        *this << data.StatusChange;
      }
      else
      {
        //Unknown type, we just ignore it
        //throw std::runtime_error("Uknown notification data type found in NotificationData");// + itos(data.Header.TypeID.FourByteData.Identifier) );
      }
    }

    ////////////////////////////////////////////////////////
    // NotificationMessage
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const NotificationMessage& message)
    {
      return RawSize(message.SequenceID) +
        RawSize(message.PublishTime) +
        RawSizeContainer(message.Data);
    }

    template<>
    void DataDeserializer::Deserialize<NotificationMessage>(NotificationMessage& message)
    {
      *this >> message.SequenceID;
      *this >> message.PublishTime;
      DeserializeContainer(*this, message.Data);
    }

    template<>
    void DataSerializer::Serialize<NotificationMessage>(const NotificationMessage& message)
    {
      *this << message.SequenceID;
      *this << message.PublishTime;
      SerializeContainer(*this, message.Data, 0);
    }

    ////////////////////////////////////////////////////////
    // PublishResult
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishResult& result)
    {
      return RawSize(result.SubscriptionID) +
        RawSizeContainer(result.AvailableSequenceNumber) +
        RawSize(result.MoreNotifications) +
        RawSize(result.Message) +
        RawSizeContainer(result.Statuses) +
        RawSizeContainer(result.Diagnostics);
    }

    template<>
    void DataDeserializer::Deserialize<PublishResult>(PublishResult& result)
    {
      *this >> result.SubscriptionID;
      DeserializeContainer(*this, result.AvailableSequenceNumber);
      *this >> result.MoreNotifications;
      *this >> result.Message;
      DeserializeContainer(*this, result.Statuses);
      DeserializeContainer(*this, result.Diagnostics);
    }

    template<>
    void DataSerializer::Serialize<PublishResult>(const PublishResult& result)
    {
      *this << result.SubscriptionID;
      SerializeContainer(*this, result.AvailableSequenceNumber, 0);
      *this << result.MoreNotifications;
      *this << result.Message;
      SerializeContainer(*this, result.Statuses, 0);
      SerializeContainer(*this, result.Diagnostics, 0);
    }

    ////////////////////////////////////////////////////////
    // PublishResponse
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishResponse& response)
    {
      return RawSize(response.TypeID) + RawSize(response.Header) + RawSize(response.Result);
    }

    template<>
    void DataDeserializer::Deserialize<PublishResponse>(PublishResponse& response)
    {
      *this >> response.TypeID;
      *this >> response.Header;
      *this >> response.Result;
    }

    template<>
    void DataSerializer::Serialize<PublishResponse>(const PublishResponse& response)
    {
      *this << response.TypeID;
      *this << response.Header;
      *this << response.Result;
    }

    ////////////////////////////////////////////////////////
    // PublishingModeParameters
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishingModeParameters& params)
    {
      return RawSize(params.Enabled) + RawSizeContainer(params.SubscriptionIDs);
    }

    template<>
    void DataDeserializer::Deserialize<PublishingModeParameters>(PublishingModeParameters& params)
    {
      *this >> params.Enabled;
      DeserializeContainer(*this, params.SubscriptionIDs);
    }

    template<>
    void DataSerializer::Serialize<PublishingModeParameters>(const PublishingModeParameters& params)
    {
      *this << params.Enabled;
      SerializeContainer(*this, params.SubscriptionIDs, 0);
    }

    ////////////////////////////////////////////////////////
    // SetPublishingModeRequest
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const SetPublishingModeRequest& request)
    {
      return RawSize(request.TypeID) + RawSize(request.Header) + RawSize(request.Parameters);
    }

    template<>
    void DataDeserializer::Deserialize<SetPublishingModeRequest>(SetPublishingModeRequest& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.Parameters;
    }

    template<>
    void DataSerializer::Serialize<SetPublishingModeRequest>(const SetPublishingModeRequest& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.Parameters;
    }

    ////////////////////////////////////////////////////////
    // SetPublishingModeResult
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishingModeResult& result)
    {
      return RawSizeContainer(result.Statuses) + RawSizeContainer(result.Diagnostics);
    }

    template<>
    void DataDeserializer::Deserialize<PublishingModeResult>(PublishingModeResult& result)
    {
      DeserializeContainer(*this, result.Statuses);
      DeserializeContainer(*this, result.Diagnostics);
    }

    template<>
    void DataSerializer::Serialize<PublishingModeResult>(const PublishingModeResult& result)
    {
      SerializeContainer(*this, result.Statuses, 0);
      SerializeContainer(*this, result.Diagnostics, 0);
    }

    ////////////////////////////////////////////////////////
    // SetPublishingModeResponse
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const SetPublishingModeResponse& response)
    {
      return RawSize(response.TypeID) + RawSize(response.Header) + RawSize(response.Result);
    }

    template<>
    void DataDeserializer::Deserialize<SetPublishingModeResponse>(SetPublishingModeResponse& response)
    {
      *this >> response.TypeID;
      *this >> response.Header;
      *this >> response.Result;
    }

    template<>
    void DataSerializer::Serialize<SetPublishingModeResponse>(const SetPublishingModeResponse& response)
    {
      *this << response.TypeID;
      *this << response.Header;
      *this << response.Result;
    }



  } // namespace Binary
} // namespace OpcUa
