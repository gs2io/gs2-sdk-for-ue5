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

#include "Ranking/Request/UpdateCategoryModelMasterRequest.h"

namespace Gs2::Ranking::Request
{
    FUpdateCategoryModelMasterRequest::FUpdateCategoryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MinimumValueValue(TOptional<int64>()),
        MaximumValueValue(TOptional<int64>()),
        OrderDirectionValue(TOptional<FString>()),
        ScopeValue(TOptional<FString>()),
        UniqueByUserIdValue(TOptional<bool>()),
        SumValue(TOptional<bool>()),
        CalculateFixedTimingHourValue(TOptional<int32>()),
        CalculateFixedTimingMinuteValue(TOptional<int32>()),
        CalculateIntervalMinutesValue(TOptional<int32>()),
        AdditionalScopesValue(nullptr),
        EntryPeriodEventIdValue(TOptional<FString>()),
        AccessPeriodEventIdValue(TOptional<FString>()),
        IgnoreUserIdsValue(nullptr),
        GenerationValue(TOptional<FString>())
    {
    }

    FUpdateCategoryModelMasterRequest::FUpdateCategoryModelMasterRequest(
        const FUpdateCategoryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryNameValue(From.CategoryNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        MinimumValueValue(From.MinimumValueValue),
        MaximumValueValue(From.MaximumValueValue),
        OrderDirectionValue(From.OrderDirectionValue),
        ScopeValue(From.ScopeValue),
        UniqueByUserIdValue(From.UniqueByUserIdValue),
        SumValue(From.SumValue),
        CalculateFixedTimingHourValue(From.CalculateFixedTimingHourValue),
        CalculateFixedTimingMinuteValue(From.CalculateFixedTimingMinuteValue),
        CalculateIntervalMinutesValue(From.CalculateIntervalMinutesValue),
        AdditionalScopesValue(From.AdditionalScopesValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue),
        IgnoreUserIdsValue(From.IgnoreUserIdsValue),
        GenerationValue(From.GenerationValue)
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

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithUniqueByUserId(
        const TOptional<bool> UniqueByUserId
    )
    {
        this->UniqueByUserIdValue = UniqueByUserId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithCalculateFixedTimingHour(
        const TOptional<int32> CalculateFixedTimingHour
    )
    {
        this->CalculateFixedTimingHourValue = CalculateFixedTimingHour;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithCalculateFixedTimingMinute(
        const TOptional<int32> CalculateFixedTimingMinute
    )
    {
        this->CalculateFixedTimingMinuteValue = CalculateFixedTimingMinute;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithCalculateIntervalMinutes(
        const TOptional<int32> CalculateIntervalMinutes
    )
    {
        this->CalculateIntervalMinutesValue = CalculateIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithAdditionalScopes(
        const TSharedPtr<TArray<TSharedPtr<Model::FScope>>> AdditionalScopes
    )
    {
        this->AdditionalScopesValue = AdditionalScopes;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithIgnoreUserIds(
        const TSharedPtr<TArray<FString>> IgnoreUserIds
    )
    {
        this->IgnoreUserIdsValue = IgnoreUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithGeneration(
        const TOptional<FString> Generation
    )
    {
        this->GenerationValue = Generation;
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

    TOptional<int64> FUpdateCategoryModelMasterRequest::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }

    TOptional<int64> FUpdateCategoryModelMasterRequest::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetScope() const
    {
        return ScopeValue;
    }

    TOptional<bool> FUpdateCategoryModelMasterRequest::GetUniqueByUserId() const
    {
        return UniqueByUserIdValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetUniqueByUserIdString() const
    {
        if (!UniqueByUserIdValue.IsSet())
        {
            return FString("null");
        }
        return FString(UniqueByUserIdValue.GetValue() ? "true" : "false");
    }

    TOptional<bool> FUpdateCategoryModelMasterRequest::GetSum() const
    {
        return SumValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }

    TOptional<int32> FUpdateCategoryModelMasterRequest::GetCalculateFixedTimingHour() const
    {
        return CalculateFixedTimingHourValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetCalculateFixedTimingHourString() const
    {
        if (!CalculateFixedTimingHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CalculateFixedTimingHourValue.GetValue());
    }

    TOptional<int32> FUpdateCategoryModelMasterRequest::GetCalculateFixedTimingMinute() const
    {
        return CalculateFixedTimingMinuteValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetCalculateFixedTimingMinuteString() const
    {
        if (!CalculateFixedTimingMinuteValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CalculateFixedTimingMinuteValue.GetValue());
    }

    TOptional<int32> FUpdateCategoryModelMasterRequest::GetCalculateIntervalMinutes() const
    {
        return CalculateIntervalMinutesValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetCalculateIntervalMinutesString() const
    {
        if (!CalculateIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CalculateIntervalMinutesValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FScope>>> FUpdateCategoryModelMasterRequest::GetAdditionalScopes() const
    {
        if (!AdditionalScopesValue.IsValid())
        {
            return nullptr;
        }
        return AdditionalScopesValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    TSharedPtr<TArray<FString>> FUpdateCategoryModelMasterRequest::GetIgnoreUserIds() const
    {
        if (!IgnoreUserIdsValue.IsValid())
        {
            return nullptr;
        }
        return IgnoreUserIdsValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetGeneration() const
    {
        return GenerationValue;
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
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCategoryName(Data->HasField("categoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("categoryName", v))
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
            ->WithMinimumValue(Data->HasField("minimumValue") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("minimumValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithMaximumValue(Data->HasField("maximumValue") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("maximumValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithOrderDirection(Data->HasField("orderDirection") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("orderDirection", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScope(Data->HasField("scope") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("scope", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUniqueByUserId(Data->HasField("uniqueByUserId") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("uniqueByUserId", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithSum(Data->HasField("sum") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("sum", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithCalculateFixedTimingHour(Data->HasField("calculateFixedTimingHour") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("calculateFixedTimingHour", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithCalculateFixedTimingMinute(Data->HasField("calculateFixedTimingMinute") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("calculateFixedTimingMinute", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithCalculateIntervalMinutes(Data->HasField("calculateIntervalMinutes") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("calculateIntervalMinutes", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithAdditionalScopes(Data->HasField("additionalScopes") ? [Data]() -> TSharedPtr<TArray<Model::FScopePtr>>
              {
                  auto v = MakeShared<TArray<Model::FScopePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("additionalScopes") && Data->HasTypedField<EJson::Array>("additionalScopes"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("additionalScopes"))
                      {
                          v->Add(Model::FScope::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithEntryPeriodEventId(Data->HasField("entryPeriodEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("entryPeriodEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessPeriodEventId(Data->HasField("accessPeriodEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("accessPeriodEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithIgnoreUserIds(Data->HasField("ignoreUserIds") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("ignoreUserIds") && Data->HasTypedField<EJson::Array>("ignoreUserIds"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("ignoreUserIds"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithGeneration(Data->HasField("generation") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("generation", v))
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
        if (MinimumValueValue.IsSet())
        {
            JsonRootObject->SetStringField("minimumValue", FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue()));
        }
        if (MaximumValueValue.IsSet())
        {
            JsonRootObject->SetStringField("maximumValue", FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue()));
        }
        if (OrderDirectionValue.IsSet())
        {
            JsonRootObject->SetStringField("orderDirection", OrderDirectionValue.GetValue());
        }
        if (ScopeValue.IsSet())
        {
            JsonRootObject->SetStringField("scope", ScopeValue.GetValue());
        }
        if (UniqueByUserIdValue.IsSet())
        {
            JsonRootObject->SetBoolField("uniqueByUserId", UniqueByUserIdValue.GetValue());
        }
        if (SumValue.IsSet())
        {
            JsonRootObject->SetBoolField("sum", SumValue.GetValue());
        }
        if (CalculateFixedTimingHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("calculateFixedTimingHour", CalculateFixedTimingHourValue.GetValue());
        }
        if (CalculateFixedTimingMinuteValue.IsSet())
        {
            JsonRootObject->SetNumberField("calculateFixedTimingMinute", CalculateFixedTimingMinuteValue.GetValue());
        }
        if (CalculateIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("calculateIntervalMinutes", CalculateIntervalMinutesValue.GetValue());
        }
        if (AdditionalScopesValue != nullptr && AdditionalScopesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AdditionalScopesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("additionalScopes", v);
        }
        if (EntryPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("entryPeriodEventId", EntryPeriodEventIdValue.GetValue());
        }
        if (AccessPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("accessPeriodEventId", AccessPeriodEventIdValue.GetValue());
        }
        if (IgnoreUserIdsValue != nullptr && IgnoreUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *IgnoreUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("ignoreUserIds", v);
        }
        if (GenerationValue.IsSet())
        {
            JsonRootObject->SetStringField("generation", GenerationValue.GetValue());
        }
        return JsonRootObject;
    }
}