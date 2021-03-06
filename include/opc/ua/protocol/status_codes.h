/// @author Alexander Rykovanov 2013
/// @email rykovanov.as@gmail.com
/// @brief OpcUa Error codes.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)
///


#ifndef opc_ua_errors_h
#define opc_ua_errors_h

#include <stdint.h>

//macro adapted from http://blogs.msdn.com/b/oldnewthing/archive/2006/11/03/942851.aspx
//The result does not match with other tested sdk
//#define FACILITY_WIN32 0
//#define HRESULT(x) (x <= 0 ? (x) : ((x & 0x0000FFFF) | (FACILITY_WIN32 << 16) | 0x80000000))
// so we use our own stupid macro
#define HRESULT(x) (x <= 0 ? (x) : ( (x & 0x0000FFFF) << 16 | 0x80000000 ) )
//#define HRESULT(x) ( (x & 0x0000FFFF) << 16 | 0x80000000 ) 

namespace OpcUa
{

  enum class StatusCode : uint32_t
  {
    Good                  = 0,
    //BadAttributeIdInvalid = 0x80390000,
    //BadNotImplemented     = 0x80440000,
    //BadNotReadable        = 0x806F0000,
    //BadWriteNotSupported  = 0x80730000,
    //BadNotWritable        = 0x80750000,
    BadUnexpectedError = HRESULT(1),
    BadInternalError = HRESULT(2),
    BadOutOfMemory = HRESULT(3),
    BadResourceUnavailable = HRESULT(4),
    BadCommunicationError = HRESULT(5),
    BadEncodingError = HRESULT(6),
    BadDecodingError = HRESULT(7),
    BadEncodingLimitsExceeded = HRESULT(8),
    BadUnknownResponse = HRESULT(9),
    BadTimeout = HRESULT(10),
    BadServiceUnsupported = HRESULT(11),
    BadShutdown = HRESULT(12),
    BadServerNotConnected = HRESULT(13),
    BadServerHalted = HRESULT(14),
    BadNothingToDo = HRESULT(15),
    BadTooManyOperations = HRESULT(16),
    BadDataTypeIdUnknown = HRESULT(17),
    BadCertificateInvalid = HRESULT(18),
    BadSecurityChecksFailed = HRESULT(19),
    BadCertificateTimeInvalid = HRESULT(20),
    BadCertificateIssuerTimeInvalid = HRESULT(21),
    BadCertificateHostNameInvalid = HRESULT(22),
    BadCertificateUriInvalid = HRESULT(23),
    BadCertificateUseNotAllowed = HRESULT(24),
    BadCertificateIssuerUseNotAllowed = HRESULT(25),
    BadCertificateUntrusted = HRESULT(26),
    BadCertificateRevocationUnknown = HRESULT(27),
    BadCertificateIssuerRevocationUnknown = HRESULT(28),
    BadCertificateRevoked = HRESULT(29),
    BadCertificateIssuerRevoked = HRESULT(30),
    BadUserAccessDenied = HRESULT(31),
    BadIdentityTokenInvalid = HRESULT(32),
    BadIdentityTokenRejected = HRESULT(33),
    BadSecureChannelIdInvalid = HRESULT(34),
    BadInvalidTimestamp = HRESULT(35),
    BadNonceInvalid = HRESULT(36),
    BadSessionIdInvalid = HRESULT(37),
    BadSessionClosed = HRESULT(38),
    BadSessionNotActivated = HRESULT(39),
    BadSubscriptionIdInvalid = HRESULT(40),
    BadRequestHeaderInvalid = HRESULT(42),
    BadTimestampsToReturnInvalid = HRESULT(43),
    BadRequestCancelledByClient = HRESULT(44),
    GoodSubscriptionTransferred = HRESULT(45),
    GoodCompletesAsynchronously = HRESULT(46),
    GoodOverload = HRESULT(47),
    GoodClamped = HRESULT(48),
    BadNoCommunication = HRESULT(49),
    BadWaitingForInitialData = HRESULT(50),
    BadNodeIdInvalid = HRESULT(51),
    BadNodeIdUnknown = HRESULT(52),
    BadAttributeIdInvalid = HRESULT(53),
    BadIndexRangeInvalid = HRESULT(54),
    BadIndexRangeNoData = HRESULT(55),
    BadDataEncodingInvalid = HRESULT(56),
    BadDataEncodingUnsupported = HRESULT(57),
    BadNotReadable = HRESULT(58),
    BadNotWritable = HRESULT(59),
    BadOutOfRange = HRESULT(60),
    BadNotSupported = HRESULT(61),
    BadNotFound = HRESULT(62),
    BadObjectDeleted = HRESULT(63),
    BadNotImplemented = HRESULT(64),
    BadMonitoringModeInvalid = HRESULT(65),
    BadMonitoredItemIdInvalid = HRESULT(66),
    BadMonitoredItemFilterInvalid = HRESULT(67),
    BadMonitoredItemFilterUnsupported = HRESULT(68),
    BadFilterNotAllowed = HRESULT(69),
    BadStructureMissing = HRESULT(70),
    BadEventFilterInvalid = HRESULT(71),
    BadContentFilterInvalid = HRESULT(72),
    BadFilterOperandInvalid = HRESULT(73),
    BadContinuationPointInvalid = HRESULT(74),
    BadNoContinuationPoints = HRESULT(75),
    BadReferenceTypeIdInvalid = HRESULT(76),
    BadBrowseDirectionInvalid = HRESULT(77),
    BadNodeNotInView = HRESULT(78),
    BadServerUriInvalid = HRESULT(79),
    BadServerNameMissing = HRESULT(80),
    BadDiscoveryUrlMissing = HRESULT(81),
    BadSempahoreFileMissing = HRESULT(82),
    BadRequestTypeInvalid = HRESULT(83),
    BadSecurityModeRejected = HRESULT(84),
    BadSecurityPolicyRejected = HRESULT(85),
    BadTooManySessions = HRESULT(86),
    BadUserSignatureInvalid = HRESULT(87),
    BadApplicationSignatureInvalid = HRESULT(88),
    BadNoValidCertificates = HRESULT(89),
    BadRequestCancelledByRequest = HRESULT(90),
    BadParentNodeIdInvalid = HRESULT(91),
    BadReferenceNotAllowed = HRESULT(92),
    BadNodeIdRejected = HRESULT(93),
    BadNodeIdExists = HRESULT(94),
    BadNodeClassInvalid = HRESULT(95),
    BadBrowseNameInvalid = HRESULT(96),
    BadBrowseNameDuplicated = HRESULT(97),
    BadNodeAttributesInvalid = HRESULT(98),
    BadTypeDefinitionInvalid = HRESULT(99),
    BadSourceNodeIdInvalid = HRESULT(100),
    BadTargetNodeIdInvalid = HRESULT(101),
    BadDuplicateReferenceNotAllowed = HRESULT(102),
    BadInvalidSelfReference = HRESULT(103),
    BadReferenceLocalOnly = HRESULT(104),
    BadNoDeleteRights = HRESULT(105),
    BadServerIndexInvalid = HRESULT(106),
    BadViewIdUnknown = HRESULT(107),
    Uncertain_ReferenceOutOfServer = HRESULT(108),
    BadTooManyMatches = HRESULT(109),
    BadQueryTooComplex = HRESULT(110),
    BadNoMatch = HRESULT(111),
    BadMaxAgeInvalid = HRESULT(112),
    BadHistoryOperationInvalid = HRESULT(113),
    BadHistoryOperationUnsupported = HRESULT(114),
    BadWriteNotSupported = HRESULT(115),
    BadTypeMismatch = HRESULT(116),
    BadMethodInvalid = HRESULT(117),
    BadArgumentsMissing = HRESULT(118),
    BadTooManySubscriptions = HRESULT(119),
    BadTooManyPublishRequests = HRESULT(120),
    BadNoSubscription = HRESULT(121),
    BadSequenceNumberUnknown = HRESULT(122),
    BadMessageNotAvailable = HRESULT(123),
    BadInsufficientClientProfile = HRESULT(124),
    BadTcpServerTooBusy = HRESULT(125),
    BadTcpMessageTypeInvalid = HRESULT(126),
    BadTcpSecureChannelUnknown = HRESULT(127),
    BadTcpMessageTooLarge = HRESULT(128),
    BadTcpNotEnoughResources = HRESULT(129),
    BadTcpInternalError = HRESULT(130),
    BadTcpEndpointUrlInvalid = HRESULT(131),
    BadRequestInterrupted = HRESULT(132),
    BadRequestTimeout = HRESULT(133),
    BadSecureChannelClosed = HRESULT(134),
    BadSecureChannelTokenUnknown = HRESULT(135),
    BadSequenceNumberInvalid = HRESULT(136),
    BadConfigurationError = HRESULT(137),
    BadNotConnected = HRESULT(138),
    BadDeviceFailure = HRESULT(139),
    BadSensorFailure = HRESULT(140),
    BadOutOfService = HRESULT(141),
    BadDeadbandFilterInvalid = HRESULT(142),
    Uncertain_NoCommunicationLastUsableValue = HRESULT(143),
    Uncertain_LastUsableValue = HRESULT(144),
    Uncertain_SubstituteValue = HRESULT(145),
    Uncertain_InitialValue = HRESULT(146),
    Uncertain_SensorNotAccurate = HRESULT(147),
    Uncertain_EngineeringUnitsExceeded = HRESULT(148),
    Uncertain_SubNormal = HRESULT(149),
    GoodLocalOverride = HRESULT(150),
    BadRefreshInProgress = HRESULT(151),
    BadConditionAlreadyDisabled = HRESULT(152),
    BadConditionDisabled = HRESULT(153),
    BadEventIdUnknown = HRESULT(154),
    BadNoData = HRESULT(155),
    BadNoBound = HRESULT(156),
    BadDataLost = HRESULT(157),
    BadDataUnavailable = HRESULT(158),
    BadEntryExists = HRESULT(159),
    BadNoEntryExists = HRESULT(160),
    BadTimestampNotSupported = HRESULT(161),
    GoodEntryInserted = HRESULT(162),
    GoodEntryReplaced = HRESULT(163),
    Uncertain_DataSubNormal = HRESULT(164),
    GoodNoData = HRESULT(165),
    GoodMoreData = HRESULT(166),
    GoodCommunicationEvent = HRESULT(167),
    GoodShutdownEvent = HRESULT(168),
    GoodCallAgain = HRESULT(169),
    GoodNonCriticalTimeout = HRESULT(170),
    BadInvalidArgument = HRESULT(171),
    BadConnectionRejected = HRESULT(172),
    BadDisconnect = HRESULT(173),
    BadConnectionClosed = HRESULT(174),
    BadInvalidState = HRESULT(175),
    BadEndOfStream = HRESULT(176),
    BadNoDataAvailable = HRESULT(177),
    BadWaitingForResponse = HRESULT(178),
    BadOperationAbandoned = HRESULT(179),
    BadExpectedStreamToBlock = HRESULT(180),
    BadWouldBlock = HRESULT(181),
    BadSyntaxError = HRESULT(182),
    BadMaxConnectionsReached = HRESULT(183),
    BadRequestTooLarge = HRESULT(184),
    BadResponseTooLarge = HRESULT(185),
    GoodResultsMayBeIncomplete = HRESULT(186),
    BadEventNotAcknowledgeable = HRESULT(187),
    Uncertain_ReferenceNotDeleted = HRESULT(188),
    BadInvalidTimestampArgument = HRESULT(189),
    BadProtocolVersionUnsupported = HRESULT(190),
    BadStateNotActive = HRESULT(191),
    Uncertain_NotAllNodesAvailable = HRESULT(192),
    BadFilterOperatorInvalid = HRESULT(193),
    BadFilterOperatorUnsupported = HRESULT(194),
    BadFilterOperandCountMismatch = HRESULT(195),
    BadFilterElementInvalid = HRESULT(196),
    BadFilterLiteralInvalid = HRESULT(197),
    BadIdentityChangeNotSupported = HRESULT(198),
    BadNotTypeDefinition = HRESULT(200),
    BadViewTimestampInvalid = HRESULT(201),
    BadViewParameterMismatch = HRESULT(202),
    BadViewVersionInvalid = HRESULT(203),
    BadConditionAlreadyEnabled = HRESULT(204),
    BadDialogNotActive = HRESULT(205),
    BadDialogResponseInvalid = HRESULT(206),
    BadConditionBranchAlreadyAcked = HRESULT(207),
    BadConditionBranchAlreadyConfirmed = HRESULT(208),
    BadConditionAlreadyShelved = HRESULT(209),
    BadConditionNotShelved = HRESULT(210),
    BadShelvingTimeOutOfRange = HRESULT(211)
        
  };

  //raise appropriate exception if StatusCode is not Good
  void CheckStatusCode(StatusCode code);
}

#endif // opc_ua_errors_h

