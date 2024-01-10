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

#include "Idle/Request/CreateCategoryModelMasterRequest.h"

namespace Gs2::Idle::Request
{
    FCreateCategoryModelMasterRequest::FCreateCategoryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        RewardIntervalMinutesValue(TOptional<int32>()),
        DefaultMaximumIdleMinutesValue(TOptional<int32>()),
        AcquireActionsValue(nullptr),
        IdlePeriodScheduleIdValue(TOptional<FString>()),
        ReceivePeriodScheduleIdValue(TOptional<FString>())
    {
    }

    FCreateCategoryModelMasterRequest::FCreateCategoryModelMasterRequest(
        const FCreateCategoryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        RewardIntervalMinutesValue(From.RewardIntervalMinutesValue),
        DefaultMaximumIdleMinutesValue(From.DefaultMaximumIdleMinutesValue),
        AcquireActionsValue(From.AcquireActionsValue),
        IdlePeriodScheduleIdValue(From.IdlePeriodScheduleIdValue),
        ReceivePeriodScheduleIdValue(From.ReceivePeriodScheduleIdValue)
    {
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithRewardIntervalMinutes(
        const TOptional<int32> RewardIntervalMinutes
    )
    {
        this->RewardIntervalMinutesValue = RewardIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithDefaultMaximumIdleMinutes(
        const TOptional<int32> DefaultMaximumIdleMinutes
    )
    {
        this->DefaultMaximumIdleMinutesValue = DefaultMaximumIdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithIdlePeriodScheduleId(
        const TOptional<FString> IdlePeriodScheduleId
    )
    {
        this->IdlePeriodScheduleIdValue = IdlePeriodScheduleId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::WithReceivePeriodScheduleId(
        const TOptional<FString> ReceivePeriodScheduleId
    )
    {
        this->ReceivePeriodScheduleIdValue = ReceivePeriodScheduleId;
        return SharedThis(this);
    }

    TOptional<FString> FCreateCategoryModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateCategoryModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateCategoryModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateCategoryModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateCategoryModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FCreateCategoryModelMasterRequest::GetRewardIntervalMinutes() const
    {
        return RewardIntervalMinutesValue;
    }

    FString FCreateCategoryModelMasterRequest::GetRewardIntervalMinutesString() const
    {
        if (!RewardIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RewardIntervalMinutesValue.GetValue());
    }

    TOptional<int32> FCreateCategoryModelMasterRequest::GetDefaultMaximumIdleMinutes() const
    {
        return DefaultMaximumIdleMinutesValue;
    }

    FString FCreateCategoryModelMasterRequest::GetDefaultMaximumIdleMinutesString() const
    {
        if (!DefaultMaximumIdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DefaultMaximumIdleMinutesValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> FCreateCategoryModelMasterRequest::GetAcquireActions() const
    {
        if (!AcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionsValue;
    }

    TOptional<FString> FCreateCategoryModelMasterRequest::GetIdlePeriodScheduleId() const
    {
        return IdlePeriodScheduleIdValue;
    }

    TOptional<FString> FCreateCategoryModelMasterRequest::GetReceivePeriodScheduleId() const
    {
        return ReceivePeriodScheduleIdValue;
    }

    TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateCategoryModelMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRewardIntervalMinutes(Data->HasField("rewardIntervalMinutes") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("rewardIntervalMinutes", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithDefaultMaximumIdleMinutes(Data->HasField("defaultMaximumIdleMinutes") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("defaultMaximumIdleMinutes", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithAcquireActions(Data->HasField("acquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionListPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionListPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("acquireActions") && Data->HasTypedField<EJson::Array>("acquireActions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("acquireActions"))
                      {
                          v->Add(Model::FAcquireActionList::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionListPtr>>())
            ->WithIdlePeriodScheduleId(Data->HasField("idlePeriodScheduleId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("idlePeriodScheduleId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithReceivePeriodScheduleId(Data->HasField("receivePeriodScheduleId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("receivePeriodScheduleId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateCategoryModelMasterRequest::ToJson() const
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
        if (RewardIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("rewardIntervalMinutes", RewardIntervalMinutesValue.GetValue());
        }
        if (DefaultMaximumIdleMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("defaultMaximumIdleMinutes", DefaultMaximumIdleMinutesValue.GetValue());
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
        }
        if (IdlePeriodScheduleIdValue.IsSet())
        {
            JsonRootObject->SetStringField("idlePeriodScheduleId", IdlePeriodScheduleIdValue.GetValue());
        }
        if (ReceivePeriodScheduleIdValue.IsSet())
        {
            JsonRootObject->SetStringField("receivePeriodScheduleId", ReceivePeriodScheduleIdValue.GetValue());
        }
        return JsonRootObject;
    }
}