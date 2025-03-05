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

#include "Money2/Request/UpdateStoreSubscriptionContentModelMasterRequest.h"

namespace Gs2::Money2::Request
{
    FUpdateStoreSubscriptionContentModelMasterRequest::FUpdateStoreSubscriptionContentModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ContentNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
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

    FUpdateStoreSubscriptionContentModelMasterRequest::FUpdateStoreSubscriptionContentModelMasterRequest(
        const FUpdateStoreSubscriptionContentModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ContentNameValue(From.ContentNameValue),
        DescriptionValue(From.DescriptionValue),
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

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithContentName(
        const TOptional<FString> ContentName
    )
    {
        this->ContentNameValue = ContentName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithScheduleNamespaceId(
        const TOptional<FString> ScheduleNamespaceId
    )
    {
        this->ScheduleNamespaceIdValue = ScheduleNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithTriggerName(
        const TOptional<FString> TriggerName
    )
    {
        this->TriggerNameValue = TriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithTriggerExtendMode(
        const TOptional<FString> TriggerExtendMode
    )
    {
        this->TriggerExtendModeValue = TriggerExtendMode;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithRollupHour(
        const TOptional<int32> RollupHour
    )
    {
        this->RollupHourValue = RollupHour;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithReallocateSpanDays(
        const TOptional<int32> ReallocateSpanDays
    )
    {
        this->ReallocateSpanDaysValue = ReallocateSpanDays;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithAppleAppStore(
        const TSharedPtr<Model::FAppleAppStoreSubscriptionContent> AppleAppStore
    )
    {
        this->AppleAppStoreValue = AppleAppStore;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::WithGooglePlay(
        const TSharedPtr<Model::FGooglePlaySubscriptionContent> GooglePlay
    )
    {
        this->GooglePlayValue = GooglePlay;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateStoreSubscriptionContentModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateStoreSubscriptionContentModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateStoreSubscriptionContentModelMasterRequest::GetContentName() const
    {
        return ContentNameValue;
    }

    TOptional<FString> FUpdateStoreSubscriptionContentModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateStoreSubscriptionContentModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateStoreSubscriptionContentModelMasterRequest::GetScheduleNamespaceId() const
    {
        return ScheduleNamespaceIdValue;
    }

    TOptional<FString> FUpdateStoreSubscriptionContentModelMasterRequest::GetTriggerName() const
    {
        return TriggerNameValue;
    }

    TOptional<FString> FUpdateStoreSubscriptionContentModelMasterRequest::GetTriggerExtendMode() const
    {
        return TriggerExtendModeValue;
    }

    TOptional<int32> FUpdateStoreSubscriptionContentModelMasterRequest::GetRollupHour() const
    {
        return RollupHourValue;
    }

    FString FUpdateStoreSubscriptionContentModelMasterRequest::GetRollupHourString() const
    {
        if (!RollupHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RollupHourValue.GetValue());
    }

    TOptional<int32> FUpdateStoreSubscriptionContentModelMasterRequest::GetReallocateSpanDays() const
    {
        return ReallocateSpanDaysValue;
    }

    FString FUpdateStoreSubscriptionContentModelMasterRequest::GetReallocateSpanDaysString() const
    {
        if (!ReallocateSpanDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ReallocateSpanDaysValue.GetValue());
    }

    TSharedPtr<Model::FAppleAppStoreSubscriptionContent> FUpdateStoreSubscriptionContentModelMasterRequest::GetAppleAppStore() const
    {
        if (!AppleAppStoreValue.IsValid())
        {
            return nullptr;
        }
        return AppleAppStoreValue;
    }

    TSharedPtr<Model::FGooglePlaySubscriptionContent> FUpdateStoreSubscriptionContentModelMasterRequest::GetGooglePlay() const
    {
        if (!GooglePlayValue.IsValid())
        {
            return nullptr;
        }
        return GooglePlayValue;
    }

    TSharedPtr<FUpdateStoreSubscriptionContentModelMasterRequest> FUpdateStoreSubscriptionContentModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateStoreSubscriptionContentModelMasterRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithContentName(Data->HasField(ANSI_TO_TCHAR("contentName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("contentName"), v))
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

    TSharedPtr<FJsonObject> FUpdateStoreSubscriptionContentModelMasterRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (ContentNameValue.IsSet())
        {
            JsonRootObject->SetStringField("contentName", ContentNameValue.GetValue());
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
}