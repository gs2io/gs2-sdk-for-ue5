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

#include "Idle/Request/UpdateCategoryModelMasterRequest.h"

namespace Gs2::Idle::Request
{
    FUpdateCategoryModelMasterRequest::FUpdateCategoryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        RewardIntervalMinutesValue(TOptional<int32>()),
        DefaultMaximumIdleMinutesValue(TOptional<int32>()),
        AcquireActionsValue(nullptr),
        IdlePeriodScheduleIdValue(TOptional<FString>()),
        ReceivePeriodScheduleIdValue(TOptional<FString>())
    {
    }

    FUpdateCategoryModelMasterRequest::FUpdateCategoryModelMasterRequest(
        const FUpdateCategoryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryNameValue(From.CategoryNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        RewardIntervalMinutesValue(From.RewardIntervalMinutesValue),
        DefaultMaximumIdleMinutesValue(From.DefaultMaximumIdleMinutesValue),
        AcquireActionsValue(From.AcquireActionsValue),
        IdlePeriodScheduleIdValue(From.IdlePeriodScheduleIdValue),
        ReceivePeriodScheduleIdValue(From.ReceivePeriodScheduleIdValue)
    {
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithRewardIntervalMinutes(
        const TOptional<int32> RewardIntervalMinutes
    )
    {
        this->RewardIntervalMinutesValue = RewardIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithDefaultMaximumIdleMinutes(
        const TOptional<int32> DefaultMaximumIdleMinutes
    )
    {
        this->DefaultMaximumIdleMinutesValue = DefaultMaximumIdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithIdlePeriodScheduleId(
        const TOptional<FString> IdlePeriodScheduleId
    )
    {
        this->IdlePeriodScheduleIdValue = IdlePeriodScheduleId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithReceivePeriodScheduleId(
        const TOptional<FString> ReceivePeriodScheduleId
    )
    {
        this->ReceivePeriodScheduleIdValue = ReceivePeriodScheduleId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FUpdateCategoryModelMasterRequest::GetRewardIntervalMinutes() const
    {
        return RewardIntervalMinutesValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetRewardIntervalMinutesString() const
    {
        if (!RewardIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RewardIntervalMinutesValue.GetValue());
    }

    TOptional<int32> FUpdateCategoryModelMasterRequest::GetDefaultMaximumIdleMinutes() const
    {
        return DefaultMaximumIdleMinutesValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetDefaultMaximumIdleMinutesString() const
    {
        if (!DefaultMaximumIdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DefaultMaximumIdleMinutesValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> FUpdateCategoryModelMasterRequest::GetAcquireActions() const
    {
        if (!AcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionsValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetIdlePeriodScheduleId() const
    {
        return IdlePeriodScheduleIdValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetReceivePeriodScheduleId() const
    {
        return ReceivePeriodScheduleIdValue;
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCategoryModelMasterRequest>()
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
            ->WithCategoryName(Data->HasField("categoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("categoryName", v))
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
             }() : nullptr)
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

    TSharedPtr<FJsonObject> FUpdateCategoryModelMasterRequest::ToJson() const
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
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryName", CategoryNameValue.GetValue());
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