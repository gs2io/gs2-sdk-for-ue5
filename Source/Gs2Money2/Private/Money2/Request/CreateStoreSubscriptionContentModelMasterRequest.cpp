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

#include "Money2/Request/CreateStoreSubscriptionContentModelMasterRequest.h"

namespace Gs2::Money2::Request
{
    FCreateStoreSubscriptionContentModelMasterRequest::FCreateStoreSubscriptionContentModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ScheduleNamespaceIdValue(TOptional<FString>()),
        TriggerNameValue(TOptional<FString>()),
        ReallocateSpanDaysValue(TOptional<int32>()),
        AppleAppStoreValue(nullptr),
        GooglePlayValue(nullptr)
    {
    }

    FCreateStoreSubscriptionContentModelMasterRequest::FCreateStoreSubscriptionContentModelMasterRequest(
        const FCreateStoreSubscriptionContentModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ScheduleNamespaceIdValue(From.ScheduleNamespaceIdValue),
        TriggerNameValue(From.TriggerNameValue),
        ReallocateSpanDaysValue(From.ReallocateSpanDaysValue),
        AppleAppStoreValue(From.AppleAppStoreValue),
        GooglePlayValue(From.GooglePlayValue)
    {
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithScheduleNamespaceId(
        const TOptional<FString> ScheduleNamespaceId
    )
    {
        this->ScheduleNamespaceIdValue = ScheduleNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithTriggerName(
        const TOptional<FString> TriggerName
    )
    {
        this->TriggerNameValue = TriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithReallocateSpanDays(
        const TOptional<int32> ReallocateSpanDays
    )
    {
        this->ReallocateSpanDaysValue = ReallocateSpanDays;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithAppleAppStore(
        const TSharedPtr<Model::FAppleAppStoreSubscriptionContent> AppleAppStore
    )
    {
        this->AppleAppStoreValue = AppleAppStore;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::WithGooglePlay(
        const TSharedPtr<Model::FGooglePlaySubscriptionContent> GooglePlay
    )
    {
        this->GooglePlayValue = GooglePlay;
        return SharedThis(this);
    }

    TOptional<FString> FCreateStoreSubscriptionContentModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateStoreSubscriptionContentModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateStoreSubscriptionContentModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateStoreSubscriptionContentModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateStoreSubscriptionContentModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FCreateStoreSubscriptionContentModelMasterRequest::GetScheduleNamespaceId() const
    {
        return ScheduleNamespaceIdValue;
    }

    TOptional<FString> FCreateStoreSubscriptionContentModelMasterRequest::GetTriggerName() const
    {
        return TriggerNameValue;
    }

    TOptional<int32> FCreateStoreSubscriptionContentModelMasterRequest::GetReallocateSpanDays() const
    {
        return ReallocateSpanDaysValue;
    }

    FString FCreateStoreSubscriptionContentModelMasterRequest::GetReallocateSpanDaysString() const
    {
        if (!ReallocateSpanDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ReallocateSpanDaysValue.GetValue());
    }

    TSharedPtr<Model::FAppleAppStoreSubscriptionContent> FCreateStoreSubscriptionContentModelMasterRequest::GetAppleAppStore() const
    {
        if (!AppleAppStoreValue.IsValid())
        {
            return nullptr;
        }
        return AppleAppStoreValue;
    }

    TSharedPtr<Model::FGooglePlaySubscriptionContent> FCreateStoreSubscriptionContentModelMasterRequest::GetGooglePlay() const
    {
        if (!GooglePlayValue.IsValid())
        {
            return nullptr;
        }
        return GooglePlayValue;
    }

    TSharedPtr<FCreateStoreSubscriptionContentModelMasterRequest> FCreateStoreSubscriptionContentModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateStoreSubscriptionContentModelMasterRequest>()
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

    TSharedPtr<FJsonObject> FCreateStoreSubscriptionContentModelMasterRequest::ToJson() const
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