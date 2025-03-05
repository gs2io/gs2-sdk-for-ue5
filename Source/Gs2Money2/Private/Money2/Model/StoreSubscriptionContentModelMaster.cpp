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

#include "Money2/Model/StoreSubscriptionContentModelMaster.h"

namespace Gs2::Money2::Model
{
    FStoreSubscriptionContentModelMaster::FStoreSubscriptionContentModelMaster():
        StoreSubscriptionContentModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ScheduleNamespaceIdValue(TOptional<FString>()),
        TriggerNameValue(TOptional<FString>()),
        ReallocateSpanDaysValue(TOptional<int32>()),
        TriggerExtendModeValue(TOptional<FString>()),
        RollupHourValue(TOptional<int32>()),
        AppleAppStoreValue(nullptr),
        GooglePlayValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FStoreSubscriptionContentModelMaster::FStoreSubscriptionContentModelMaster(
        const FStoreSubscriptionContentModelMaster& From
    ):
        StoreSubscriptionContentModelIdValue(From.StoreSubscriptionContentModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ScheduleNamespaceIdValue(From.ScheduleNamespaceIdValue),
        TriggerNameValue(From.TriggerNameValue),
        ReallocateSpanDaysValue(From.ReallocateSpanDaysValue),
        TriggerExtendModeValue(From.TriggerExtendModeValue),
        RollupHourValue(From.RollupHourValue),
        AppleAppStoreValue(From.AppleAppStoreValue),
        GooglePlayValue(From.GooglePlayValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithStoreSubscriptionContentModelId(
        const TOptional<FString> StoreSubscriptionContentModelId
    )
    {
        this->StoreSubscriptionContentModelIdValue = StoreSubscriptionContentModelId;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithScheduleNamespaceId(
        const TOptional<FString> ScheduleNamespaceId
    )
    {
        this->ScheduleNamespaceIdValue = ScheduleNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithTriggerName(
        const TOptional<FString> TriggerName
    )
    {
        this->TriggerNameValue = TriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithReallocateSpanDays(
        const TOptional<int32> ReallocateSpanDays
    )
    {
        this->ReallocateSpanDaysValue = ReallocateSpanDays;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithTriggerExtendMode(
        const TOptional<FString> TriggerExtendMode
    )
    {
        this->TriggerExtendModeValue = TriggerExtendMode;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithRollupHour(
        const TOptional<int32> RollupHour
    )
    {
        this->RollupHourValue = RollupHour;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithAppleAppStore(
        const TSharedPtr<FAppleAppStoreSubscriptionContent> AppleAppStore
    )
    {
        this->AppleAppStoreValue = AppleAppStore;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithGooglePlay(
        const TSharedPtr<FGooglePlaySubscriptionContent> GooglePlay
    )
    {
        this->GooglePlayValue = GooglePlay;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FStoreSubscriptionContentModelMaster::GetStoreSubscriptionContentModelId() const
    {
        return StoreSubscriptionContentModelIdValue;
    }
    TOptional<FString> FStoreSubscriptionContentModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FStoreSubscriptionContentModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FStoreSubscriptionContentModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FStoreSubscriptionContentModelMaster::GetScheduleNamespaceId() const
    {
        return ScheduleNamespaceIdValue;
    }
    TOptional<FString> FStoreSubscriptionContentModelMaster::GetTriggerName() const
    {
        return TriggerNameValue;
    }
    TOptional<int32> FStoreSubscriptionContentModelMaster::GetReallocateSpanDays() const
    {
        return ReallocateSpanDaysValue;
    }

    FString FStoreSubscriptionContentModelMaster::GetReallocateSpanDaysString() const
    {
        if (!ReallocateSpanDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ReallocateSpanDaysValue.GetValue());
    }
    TOptional<FString> FStoreSubscriptionContentModelMaster::GetTriggerExtendMode() const
    {
        return TriggerExtendModeValue;
    }
    TOptional<int32> FStoreSubscriptionContentModelMaster::GetRollupHour() const
    {
        return RollupHourValue;
    }

    FString FStoreSubscriptionContentModelMaster::GetRollupHourString() const
    {
        if (!RollupHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RollupHourValue.GetValue());
    }
    TSharedPtr<FAppleAppStoreSubscriptionContent> FStoreSubscriptionContentModelMaster::GetAppleAppStore() const
    {
        return AppleAppStoreValue;
    }
    TSharedPtr<FGooglePlaySubscriptionContent> FStoreSubscriptionContentModelMaster::GetGooglePlay() const
    {
        return GooglePlayValue;
    }
    TOptional<int64> FStoreSubscriptionContentModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FStoreSubscriptionContentModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FStoreSubscriptionContentModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FStoreSubscriptionContentModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FStoreSubscriptionContentModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FStoreSubscriptionContentModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FStoreSubscriptionContentModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):master:subscription:content:(?<contentName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStoreSubscriptionContentModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):master:subscription:content:(?<contentName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStoreSubscriptionContentModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):master:subscription:content:(?<contentName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStoreSubscriptionContentModelMaster::GetContentNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):master:subscription:content:(?<contentName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStoreSubscriptionContentModelMaster> FStoreSubscriptionContentModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStoreSubscriptionContentModelMaster>()
            ->WithStoreSubscriptionContentModelId(Data->HasField(ANSI_TO_TCHAR("storeSubscriptionContentModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("storeSubscriptionContentModelId"), v))
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
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScheduleNamespaceId(Data->HasField(ANSI_TO_TCHAR("scheduleNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scheduleNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTriggerName(Data->HasField(ANSI_TO_TCHAR("triggerName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("triggerName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReallocateSpanDays(Data->HasField(ANSI_TO_TCHAR("reallocateSpanDays")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("reallocateSpanDays"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithTriggerExtendMode(Data->HasField(ANSI_TO_TCHAR("triggerExtendMode")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("triggerExtendMode"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRollupHour(Data->HasField(ANSI_TO_TCHAR("rollupHour")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("rollupHour"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAppleAppStore(Data->HasField(ANSI_TO_TCHAR("appleAppStore")) ? [Data]() -> Model::FAppleAppStoreSubscriptionContentPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("appleAppStore")))
                    {
                        return nullptr;
                    }
                    return Model::FAppleAppStoreSubscriptionContent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("appleAppStore")));
                 }() : nullptr)
            ->WithGooglePlay(Data->HasField(ANSI_TO_TCHAR("googlePlay")) ? [Data]() -> Model::FGooglePlaySubscriptionContentPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("googlePlay")))
                    {
                        return nullptr;
                    }
                    return Model::FGooglePlaySubscriptionContent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("googlePlay")));
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

    TSharedPtr<FJsonObject> FStoreSubscriptionContentModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StoreSubscriptionContentModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("storeSubscriptionContentModelId", StoreSubscriptionContentModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ScheduleNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scheduleNamespaceId", ScheduleNamespaceIdValue.GetValue());
        }
        if (TriggerNameValue.IsSet())
        {
            JsonRootObject->SetStringField("triggerName", TriggerNameValue.GetValue());
        }
        if (ReallocateSpanDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("reallocateSpanDays", ReallocateSpanDaysValue.GetValue());
        }
        if (TriggerExtendModeValue.IsSet())
        {
            JsonRootObject->SetStringField("triggerExtendMode", TriggerExtendModeValue.GetValue());
        }
        if (RollupHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("rollupHour", RollupHourValue.GetValue());
        }
        if (AppleAppStoreValue != nullptr && AppleAppStoreValue.IsValid())
        {
            JsonRootObject->SetObjectField("appleAppStore", AppleAppStoreValue->ToJson());
        }
        if (GooglePlayValue != nullptr && GooglePlayValue.IsValid())
        {
            JsonRootObject->SetObjectField("googlePlay", GooglePlayValue->ToJson());
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

    FString FStoreSubscriptionContentModelMaster::TypeName = "StoreSubscriptionContentModelMaster";
}