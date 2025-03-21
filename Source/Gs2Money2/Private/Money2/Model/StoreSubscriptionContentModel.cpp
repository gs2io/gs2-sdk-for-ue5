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

#include "Money2/Model/StoreSubscriptionContentModel.h"

namespace Gs2::Money2::Model
{
    FStoreSubscriptionContentModel::FStoreSubscriptionContentModel():
        StoreSubscriptionContentModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ScheduleNamespaceIdValue(TOptional<FString>()),
        TriggerNameValue(TOptional<FString>()),
        TriggerExtendModeValue(TOptional<FString>()),
        RollupHourValue(TOptional<int32>()),
        ReallocateSpanDaysValue(TOptional<int32>()),
        AppleAppStoreValue(nullptr),
        GooglePlayValue(nullptr)
    {
    }

    FStoreSubscriptionContentModel::FStoreSubscriptionContentModel(
        const FStoreSubscriptionContentModel& From
    ):
        StoreSubscriptionContentModelIdValue(From.StoreSubscriptionContentModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ScheduleNamespaceIdValue(From.ScheduleNamespaceIdValue),
        TriggerNameValue(From.TriggerNameValue),
        TriggerExtendModeValue(From.TriggerExtendModeValue),
        RollupHourValue(From.RollupHourValue),
        ReallocateSpanDaysValue(From.ReallocateSpanDaysValue),
        AppleAppStoreValue(From.AppleAppStoreValue),
        GooglePlayValue(From.GooglePlayValue)
    {
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithStoreSubscriptionContentModelId(
        const TOptional<FString> StoreSubscriptionContentModelId
    )
    {
        this->StoreSubscriptionContentModelIdValue = StoreSubscriptionContentModelId;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithScheduleNamespaceId(
        const TOptional<FString> ScheduleNamespaceId
    )
    {
        this->ScheduleNamespaceIdValue = ScheduleNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithTriggerName(
        const TOptional<FString> TriggerName
    )
    {
        this->TriggerNameValue = TriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithTriggerExtendMode(
        const TOptional<FString> TriggerExtendMode
    )
    {
        this->TriggerExtendModeValue = TriggerExtendMode;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithRollupHour(
        const TOptional<int32> RollupHour
    )
    {
        this->RollupHourValue = RollupHour;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithReallocateSpanDays(
        const TOptional<int32> ReallocateSpanDays
    )
    {
        this->ReallocateSpanDaysValue = ReallocateSpanDays;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithAppleAppStore(
        const TSharedPtr<FAppleAppStoreSubscriptionContent> AppleAppStore
    )
    {
        this->AppleAppStoreValue = AppleAppStore;
        return SharedThis(this);
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::WithGooglePlay(
        const TSharedPtr<FGooglePlaySubscriptionContent> GooglePlay
    )
    {
        this->GooglePlayValue = GooglePlay;
        return SharedThis(this);
    }
    TOptional<FString> FStoreSubscriptionContentModel::GetStoreSubscriptionContentModelId() const
    {
        return StoreSubscriptionContentModelIdValue;
    }
    TOptional<FString> FStoreSubscriptionContentModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FStoreSubscriptionContentModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FStoreSubscriptionContentModel::GetScheduleNamespaceId() const
    {
        return ScheduleNamespaceIdValue;
    }
    TOptional<FString> FStoreSubscriptionContentModel::GetTriggerName() const
    {
        return TriggerNameValue;
    }
    TOptional<FString> FStoreSubscriptionContentModel::GetTriggerExtendMode() const
    {
        return TriggerExtendModeValue;
    }
    TOptional<int32> FStoreSubscriptionContentModel::GetRollupHour() const
    {
        return RollupHourValue;
    }

    FString FStoreSubscriptionContentModel::GetRollupHourString() const
    {
        if (!RollupHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RollupHourValue.GetValue());
    }
    TOptional<int32> FStoreSubscriptionContentModel::GetReallocateSpanDays() const
    {
        return ReallocateSpanDaysValue;
    }

    FString FStoreSubscriptionContentModel::GetReallocateSpanDaysString() const
    {
        if (!ReallocateSpanDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ReallocateSpanDaysValue.GetValue());
    }
    TSharedPtr<FAppleAppStoreSubscriptionContent> FStoreSubscriptionContentModel::GetAppleAppStore() const
    {
        return AppleAppStoreValue;
    }
    TSharedPtr<FGooglePlaySubscriptionContent> FStoreSubscriptionContentModel::GetGooglePlay() const
    {
        return GooglePlayValue;
    }

    TOptional<FString> FStoreSubscriptionContentModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):model:subscription:content:(?<contentName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStoreSubscriptionContentModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):model:subscription:content:(?<contentName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStoreSubscriptionContentModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):model:subscription:content:(?<contentName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStoreSubscriptionContentModel::GetContentNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):model:subscription:content:(?<contentName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStoreSubscriptionContentModel> FStoreSubscriptionContentModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStoreSubscriptionContentModel>()
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
            ->WithReallocateSpanDays(Data->HasField(ANSI_TO_TCHAR("reallocateSpanDays")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("reallocateSpanDays"), v))
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
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FStoreSubscriptionContentModel::ToJson() const
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
        if (TriggerExtendModeValue.IsSet())
        {
            JsonRootObject->SetStringField("triggerExtendMode", TriggerExtendModeValue.GetValue());
        }
        if (RollupHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("rollupHour", RollupHourValue.GetValue());
        }
        if (ReallocateSpanDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("reallocateSpanDays", ReallocateSpanDaysValue.GetValue());
        }
        if (AppleAppStoreValue != nullptr && AppleAppStoreValue.IsValid())
        {
            JsonRootObject->SetObjectField("appleAppStore", AppleAppStoreValue->ToJson());
        }
        if (GooglePlayValue != nullptr && GooglePlayValue.IsValid())
        {
            JsonRootObject->SetObjectField("googlePlay", GooglePlayValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FStoreSubscriptionContentModel::TypeName = "StoreSubscriptionContentModel";
}