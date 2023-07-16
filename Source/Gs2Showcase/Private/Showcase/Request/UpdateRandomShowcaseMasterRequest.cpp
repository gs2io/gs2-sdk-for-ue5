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

#include "Showcase/Request/UpdateRandomShowcaseMasterRequest.h"

namespace Gs2::Showcase::Request
{
    FUpdateRandomShowcaseMasterRequest::FUpdateRandomShowcaseMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ShowcaseNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MaximumNumberOfChoiceValue(TOptional<int32>()),
        DisplayItemsValue(nullptr),
        BaseTimestampValue(TOptional<int64>()),
        ResetIntervalHoursValue(TOptional<int32>()),
        SalesPeriodEventIdValue(TOptional<FString>())
    {
    }

    FUpdateRandomShowcaseMasterRequest::FUpdateRandomShowcaseMasterRequest(
        const FUpdateRandomShowcaseMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ShowcaseNameValue(From.ShowcaseNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        MaximumNumberOfChoiceValue(From.MaximumNumberOfChoiceValue),
        DisplayItemsValue(From.DisplayItemsValue),
        BaseTimestampValue(From.BaseTimestampValue),
        ResetIntervalHoursValue(From.ResetIntervalHoursValue),
        SalesPeriodEventIdValue(From.SalesPeriodEventIdValue)
    {
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithShowcaseName(
        const TOptional<FString> ShowcaseName
    )
    {
        this->ShowcaseNameValue = ShowcaseName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithMaximumNumberOfChoice(
        const TOptional<int32> MaximumNumberOfChoice
    )
    {
        this->MaximumNumberOfChoiceValue = MaximumNumberOfChoice;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithDisplayItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> DisplayItems
    )
    {
        this->DisplayItemsValue = DisplayItems;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithBaseTimestamp(
        const TOptional<int64> BaseTimestamp
    )
    {
        this->BaseTimestampValue = BaseTimestamp;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithResetIntervalHours(
        const TOptional<int32> ResetIntervalHours
    )
    {
        this->ResetIntervalHoursValue = ResetIntervalHours;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::WithSalesPeriodEventId(
        const TOptional<FString> SalesPeriodEventId
    )
    {
        this->SalesPeriodEventIdValue = SalesPeriodEventId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateRandomShowcaseMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateRandomShowcaseMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateRandomShowcaseMasterRequest::GetShowcaseName() const
    {
        return ShowcaseNameValue;
    }

    TOptional<FString> FUpdateRandomShowcaseMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateRandomShowcaseMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FUpdateRandomShowcaseMasterRequest::GetMaximumNumberOfChoice() const
    {
        return MaximumNumberOfChoiceValue;
    }

    FString FUpdateRandomShowcaseMasterRequest::GetMaximumNumberOfChoiceString() const
    {
        if (!MaximumNumberOfChoiceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumNumberOfChoiceValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> FUpdateRandomShowcaseMasterRequest::GetDisplayItems() const
    {
        if (!DisplayItemsValue.IsValid())
        {
            return nullptr;
        }
        return DisplayItemsValue;
    }

    TOptional<int64> FUpdateRandomShowcaseMasterRequest::GetBaseTimestamp() const
    {
        return BaseTimestampValue;
    }

    FString FUpdateRandomShowcaseMasterRequest::GetBaseTimestampString() const
    {
        if (!BaseTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BaseTimestampValue.GetValue());
    }

    TOptional<int32> FUpdateRandomShowcaseMasterRequest::GetResetIntervalHours() const
    {
        return ResetIntervalHoursValue;
    }

    FString FUpdateRandomShowcaseMasterRequest::GetResetIntervalHoursString() const
    {
        if (!ResetIntervalHoursValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetIntervalHoursValue.GetValue());
    }

    TOptional<FString> FUpdateRandomShowcaseMasterRequest::GetSalesPeriodEventId() const
    {
        return SalesPeriodEventIdValue;
    }

    TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateRandomShowcaseMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithShowcaseName(Data->HasField("showcaseName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("showcaseName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMaximumNumberOfChoice(Data->HasField("maximumNumberOfChoice") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("maximumNumberOfChoice", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDisplayItems(Data->HasField("displayItems") ? [Data]() -> TSharedPtr<TArray<Model::FRandomDisplayItemModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FRandomDisplayItemModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("displayItems") && Data->HasTypedField<EJson::Array>("displayItems"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("displayItems"))
                      {
                          v->Add(Model::FRandomDisplayItemModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithBaseTimestamp(Data->HasField("baseTimestamp") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("baseTimestamp", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithResetIntervalHours(Data->HasField("resetIntervalHours") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("resetIntervalHours", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithSalesPeriodEventId(Data->HasField("salesPeriodEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("salesPeriodEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateRandomShowcaseMasterRequest::ToJson() const
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
        if (ShowcaseNameValue.IsSet())
        {
            JsonRootObject->SetStringField("showcaseName", ShowcaseNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (MaximumNumberOfChoiceValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumNumberOfChoice", MaximumNumberOfChoiceValue.GetValue());
        }
        if (DisplayItemsValue != nullptr && DisplayItemsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *DisplayItemsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("displayItems", v);
        }
        if (BaseTimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("baseTimestamp", FString::Printf(TEXT("%lld"), BaseTimestampValue.GetValue()));
        }
        if (ResetIntervalHoursValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetIntervalHours", ResetIntervalHoursValue.GetValue());
        }
        if (SalesPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("salesPeriodEventId", SalesPeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }
}