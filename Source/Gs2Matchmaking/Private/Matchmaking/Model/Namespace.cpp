/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Matchmaking/Model/Namespace.h"

namespace Gs2::Matchmaking::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        EnableRatingValue(TOptional<bool>()),
        EnableDisconnectDetectionValue(TOptional<FString>()),
        DisconnectDetectionTimeoutSecondsValue(TOptional<int32>()),
        CreateGatheringTriggerTypeValue(TOptional<FString>()),
        CreateGatheringTriggerRealtimeNamespaceIdValue(TOptional<FString>()),
        CreateGatheringTriggerScriptIdValue(TOptional<FString>()),
        CompleteMatchmakingTriggerTypeValue(TOptional<FString>()),
        CompleteMatchmakingTriggerRealtimeNamespaceIdValue(TOptional<FString>()),
        CompleteMatchmakingTriggerScriptIdValue(TOptional<FString>()),
        EnableCollaborateSeasonRatingValue(TOptional<FString>()),
        CollaborateSeasonRatingNamespaceIdValue(TOptional<FString>()),
        CollaborateSeasonRatingTtlValue(TOptional<int32>()),
        ChangeRatingScriptValue(nullptr),
        JoinNotificationValue(nullptr),
        LeaveNotificationValue(nullptr),
        CompleteNotificationValue(nullptr),
        ChangeRatingNotificationValue(nullptr),
        LogSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FNamespace::FNamespace(
        const FNamespace& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        EnableRatingValue(From.EnableRatingValue),
        EnableDisconnectDetectionValue(From.EnableDisconnectDetectionValue),
        DisconnectDetectionTimeoutSecondsValue(From.DisconnectDetectionTimeoutSecondsValue),
        CreateGatheringTriggerTypeValue(From.CreateGatheringTriggerTypeValue),
        CreateGatheringTriggerRealtimeNamespaceIdValue(From.CreateGatheringTriggerRealtimeNamespaceIdValue),
        CreateGatheringTriggerScriptIdValue(From.CreateGatheringTriggerScriptIdValue),
        CompleteMatchmakingTriggerTypeValue(From.CompleteMatchmakingTriggerTypeValue),
        CompleteMatchmakingTriggerRealtimeNamespaceIdValue(From.CompleteMatchmakingTriggerRealtimeNamespaceIdValue),
        CompleteMatchmakingTriggerScriptIdValue(From.CompleteMatchmakingTriggerScriptIdValue),
        EnableCollaborateSeasonRatingValue(From.EnableCollaborateSeasonRatingValue),
        CollaborateSeasonRatingNamespaceIdValue(From.CollaborateSeasonRatingNamespaceIdValue),
        CollaborateSeasonRatingTtlValue(From.CollaborateSeasonRatingTtlValue),
        ChangeRatingScriptValue(From.ChangeRatingScriptValue),
        JoinNotificationValue(From.JoinNotificationValue),
        LeaveNotificationValue(From.LeaveNotificationValue),
        CompleteNotificationValue(From.CompleteNotificationValue),
        ChangeRatingNotificationValue(From.ChangeRatingNotificationValue),
        LogSettingValue(From.LogSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FNamespace> FNamespace::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithTransactionSetting(
        const TSharedPtr<FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithEnableRating(
        const TOptional<bool> EnableRating
    )
    {
        this->EnableRatingValue = EnableRating;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithEnableDisconnectDetection(
        const TOptional<FString> EnableDisconnectDetection
    )
    {
        this->EnableDisconnectDetectionValue = EnableDisconnectDetection;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDisconnectDetectionTimeoutSeconds(
        const TOptional<int32> DisconnectDetectionTimeoutSeconds
    )
    {
        this->DisconnectDetectionTimeoutSecondsValue = DisconnectDetectionTimeoutSeconds;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateGatheringTriggerType(
        const TOptional<FString> CreateGatheringTriggerType
    )
    {
        this->CreateGatheringTriggerTypeValue = CreateGatheringTriggerType;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateGatheringTriggerRealtimeNamespaceId(
        const TOptional<FString> CreateGatheringTriggerRealtimeNamespaceId
    )
    {
        this->CreateGatheringTriggerRealtimeNamespaceIdValue = CreateGatheringTriggerRealtimeNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateGatheringTriggerScriptId(
        const TOptional<FString> CreateGatheringTriggerScriptId
    )
    {
        this->CreateGatheringTriggerScriptIdValue = CreateGatheringTriggerScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCompleteMatchmakingTriggerType(
        const TOptional<FString> CompleteMatchmakingTriggerType
    )
    {
        this->CompleteMatchmakingTriggerTypeValue = CompleteMatchmakingTriggerType;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCompleteMatchmakingTriggerRealtimeNamespaceId(
        const TOptional<FString> CompleteMatchmakingTriggerRealtimeNamespaceId
    )
    {
        this->CompleteMatchmakingTriggerRealtimeNamespaceIdValue = CompleteMatchmakingTriggerRealtimeNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCompleteMatchmakingTriggerScriptId(
        const TOptional<FString> CompleteMatchmakingTriggerScriptId
    )
    {
        this->CompleteMatchmakingTriggerScriptIdValue = CompleteMatchmakingTriggerScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithEnableCollaborateSeasonRating(
        const TOptional<FString> EnableCollaborateSeasonRating
    )
    {
        this->EnableCollaborateSeasonRatingValue = EnableCollaborateSeasonRating;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCollaborateSeasonRatingNamespaceId(
        const TOptional<FString> CollaborateSeasonRatingNamespaceId
    )
    {
        this->CollaborateSeasonRatingNamespaceIdValue = CollaborateSeasonRatingNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCollaborateSeasonRatingTtl(
        const TOptional<int32> CollaborateSeasonRatingTtl
    )
    {
        this->CollaborateSeasonRatingTtlValue = CollaborateSeasonRatingTtl;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithChangeRatingScript(
        const TSharedPtr<FScriptSetting> ChangeRatingScript
    )
    {
        this->ChangeRatingScriptValue = ChangeRatingScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithJoinNotification(
        const TSharedPtr<FNotificationSetting> JoinNotification
    )
    {
        this->JoinNotificationValue = JoinNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLeaveNotification(
        const TSharedPtr<FNotificationSetting> LeaveNotification
    )
    {
        this->LeaveNotificationValue = LeaveNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCompleteNotification(
        const TSharedPtr<FNotificationSetting> CompleteNotification
    )
    {
        this->CompleteNotificationValue = CompleteNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithChangeRatingNotification(
        const TSharedPtr<FNotificationSetting> ChangeRatingNotification
    )
    {
        this->ChangeRatingNotificationValue = ChangeRatingNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLogSetting(
        const TSharedPtr<FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FNamespace::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FNamespace::GetDescription() const
    {
        return DescriptionValue;
    }
    TSharedPtr<FTransactionSetting> FNamespace::GetTransactionSetting() const
    {
        return TransactionSettingValue;
    }
    TOptional<bool> FNamespace::GetEnableRating() const
    {
        return EnableRatingValue;
    }

    FString FNamespace::GetEnableRatingString() const
    {
        if (!EnableRatingValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableRatingValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FNamespace::GetEnableDisconnectDetection() const
    {
        return EnableDisconnectDetectionValue;
    }
    TOptional<int32> FNamespace::GetDisconnectDetectionTimeoutSeconds() const
    {
        return DisconnectDetectionTimeoutSecondsValue;
    }

    FString FNamespace::GetDisconnectDetectionTimeoutSecondsString() const
    {
        if (!DisconnectDetectionTimeoutSecondsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DisconnectDetectionTimeoutSecondsValue.GetValue());
    }
    TOptional<FString> FNamespace::GetCreateGatheringTriggerType() const
    {
        return CreateGatheringTriggerTypeValue;
    }
    TOptional<FString> FNamespace::GetCreateGatheringTriggerRealtimeNamespaceId() const
    {
        return CreateGatheringTriggerRealtimeNamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetCreateGatheringTriggerScriptId() const
    {
        return CreateGatheringTriggerScriptIdValue;
    }
    TOptional<FString> FNamespace::GetCompleteMatchmakingTriggerType() const
    {
        return CompleteMatchmakingTriggerTypeValue;
    }
    TOptional<FString> FNamespace::GetCompleteMatchmakingTriggerRealtimeNamespaceId() const
    {
        return CompleteMatchmakingTriggerRealtimeNamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetCompleteMatchmakingTriggerScriptId() const
    {
        return CompleteMatchmakingTriggerScriptIdValue;
    }
    TOptional<FString> FNamespace::GetEnableCollaborateSeasonRating() const
    {
        return EnableCollaborateSeasonRatingValue;
    }
    TOptional<FString> FNamespace::GetCollaborateSeasonRatingNamespaceId() const
    {
        return CollaborateSeasonRatingNamespaceIdValue;
    }
    TOptional<int32> FNamespace::GetCollaborateSeasonRatingTtl() const
    {
        return CollaborateSeasonRatingTtlValue;
    }

    FString FNamespace::GetCollaborateSeasonRatingTtlString() const
    {
        if (!CollaborateSeasonRatingTtlValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CollaborateSeasonRatingTtlValue.GetValue());
    }
    TSharedPtr<FScriptSetting> FNamespace::GetChangeRatingScript() const
    {
        return ChangeRatingScriptValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetJoinNotification() const
    {
        return JoinNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetLeaveNotification() const
    {
        return LeaveNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetCompleteNotification() const
    {
        return CompleteNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetChangeRatingNotification() const
    {
        return ChangeRatingNotificationValue;
    }
    TSharedPtr<FLogSetting> FNamespace::GetLogSetting() const
    {
        return LogSettingValue;
    }
    TOptional<int64> FNamespace::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FNamespace::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FNamespace::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetRevision() const
    {
        return RevisionValue;
    }

    FString FNamespace::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FNamespace::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FNamespace> FNamespace::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNamespace>()
            ->WithNamespaceId(Data->HasField(ANSI_TO_TCHAR("namespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionSetting(Data->HasField(ANSI_TO_TCHAR("transactionSetting")) ? [Data]() -> Model::FTransactionSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FTransactionSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSetting")));
                 }() : nullptr)
            ->WithEnableRating(Data->HasField(ANSI_TO_TCHAR("enableRating")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableRating"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithEnableDisconnectDetection(Data->HasField(ANSI_TO_TCHAR("enableDisconnectDetection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("enableDisconnectDetection"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDisconnectDetectionTimeoutSeconds(Data->HasField(ANSI_TO_TCHAR("disconnectDetectionTimeoutSeconds")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("disconnectDetectionTimeoutSeconds"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCreateGatheringTriggerType(Data->HasField(ANSI_TO_TCHAR("createGatheringTriggerType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("createGatheringTriggerType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreateGatheringTriggerRealtimeNamespaceId(Data->HasField(ANSI_TO_TCHAR("createGatheringTriggerRealtimeNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("createGatheringTriggerRealtimeNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreateGatheringTriggerScriptId(Data->HasField(ANSI_TO_TCHAR("createGatheringTriggerScriptId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("createGatheringTriggerScriptId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerType(Data->HasField(ANSI_TO_TCHAR("completeMatchmakingTriggerType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("completeMatchmakingTriggerType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerRealtimeNamespaceId(Data->HasField(ANSI_TO_TCHAR("completeMatchmakingTriggerRealtimeNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("completeMatchmakingTriggerRealtimeNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerScriptId(Data->HasField(ANSI_TO_TCHAR("completeMatchmakingTriggerScriptId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("completeMatchmakingTriggerScriptId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEnableCollaborateSeasonRating(Data->HasField(ANSI_TO_TCHAR("enableCollaborateSeasonRating")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("enableCollaborateSeasonRating"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCollaborateSeasonRatingNamespaceId(Data->HasField(ANSI_TO_TCHAR("collaborateSeasonRatingNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("collaborateSeasonRatingNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCollaborateSeasonRatingTtl(Data->HasField(ANSI_TO_TCHAR("collaborateSeasonRatingTtl")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("collaborateSeasonRatingTtl"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithChangeRatingScript(Data->HasField(ANSI_TO_TCHAR("changeRatingScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeRatingScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeRatingScript")));
                 }() : nullptr)
            ->WithJoinNotification(Data->HasField(ANSI_TO_TCHAR("joinNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("joinNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("joinNotification")));
                 }() : nullptr)
            ->WithLeaveNotification(Data->HasField(ANSI_TO_TCHAR("leaveNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("leaveNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("leaveNotification")));
                 }() : nullptr)
            ->WithCompleteNotification(Data->HasField(ANSI_TO_TCHAR("completeNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("completeNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("completeNotification")));
                 }() : nullptr)
            ->WithChangeRatingNotification(Data->HasField(ANSI_TO_TCHAR("changeRatingNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeRatingNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeRatingNotification")));
                 }() : nullptr)
            ->WithLogSetting(Data->HasField(ANSI_TO_TCHAR("logSetting")) ? [Data]() -> Model::FLogSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FLogSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("logSetting")));
                 }() : nullptr)
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FNamespace::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceId", NamespaceIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (EnableRatingValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableRating", EnableRatingValue.GetValue());
        }
        if (EnableDisconnectDetectionValue.IsSet())
        {
            JsonRootObject->SetStringField("enableDisconnectDetection", EnableDisconnectDetectionValue.GetValue());
        }
        if (DisconnectDetectionTimeoutSecondsValue.IsSet())
        {
            JsonRootObject->SetNumberField("disconnectDetectionTimeoutSeconds", DisconnectDetectionTimeoutSecondsValue.GetValue());
        }
        if (CreateGatheringTriggerTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("createGatheringTriggerType", CreateGatheringTriggerTypeValue.GetValue());
        }
        if (CreateGatheringTriggerRealtimeNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("createGatheringTriggerRealtimeNamespaceId", CreateGatheringTriggerRealtimeNamespaceIdValue.GetValue());
        }
        if (CreateGatheringTriggerScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("createGatheringTriggerScriptId", CreateGatheringTriggerScriptIdValue.GetValue());
        }
        if (CompleteMatchmakingTriggerTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("completeMatchmakingTriggerType", CompleteMatchmakingTriggerTypeValue.GetValue());
        }
        if (CompleteMatchmakingTriggerRealtimeNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("completeMatchmakingTriggerRealtimeNamespaceId", CompleteMatchmakingTriggerRealtimeNamespaceIdValue.GetValue());
        }
        if (CompleteMatchmakingTriggerScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("completeMatchmakingTriggerScriptId", CompleteMatchmakingTriggerScriptIdValue.GetValue());
        }
        if (EnableCollaborateSeasonRatingValue.IsSet())
        {
            JsonRootObject->SetStringField("enableCollaborateSeasonRating", EnableCollaborateSeasonRatingValue.GetValue());
        }
        if (CollaborateSeasonRatingNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("collaborateSeasonRatingNamespaceId", CollaborateSeasonRatingNamespaceIdValue.GetValue());
        }
        if (CollaborateSeasonRatingTtlValue.IsSet())
        {
            JsonRootObject->SetNumberField("collaborateSeasonRatingTtl", CollaborateSeasonRatingTtlValue.GetValue());
        }
        if (ChangeRatingScriptValue != nullptr && ChangeRatingScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeRatingScript", ChangeRatingScriptValue->ToJson());
        }
        if (JoinNotificationValue != nullptr && JoinNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("joinNotification", JoinNotificationValue->ToJson());
        }
        if (LeaveNotificationValue != nullptr && LeaveNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("leaveNotification", LeaveNotificationValue->ToJson());
        }
        if (CompleteNotificationValue != nullptr && CompleteNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("completeNotification", CompleteNotificationValue->ToJson());
        }
        if (ChangeRatingNotificationValue != nullptr && ChangeRatingNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeRatingNotification", ChangeRatingNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FNamespace::TypeName = "Namespace";
}