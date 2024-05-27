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
        GlobalRankingSettingValue(nullptr),
        EntryPeriodEventIdValue(TOptional<FString>()),
        AccessPeriodEventIdValue(TOptional<FString>()),
        UniqueByUserIdValue(TOptional<bool>()),
        SumValue(TOptional<bool>()),
        CalculateFixedTimingHourValue(TOptional<int32>()),
        CalculateFixedTimingMinuteValue(TOptional<int32>()),
        CalculateIntervalMinutesValue(TOptional<int32>()),
        AdditionalScopesValue(nullptr),
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
        GlobalRankingSettingValue(From.GlobalRankingSettingValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue),
        UniqueByUserIdValue(From.UniqueByUserIdValue),
        SumValue(From.SumValue),
        CalculateFixedTimingHourValue(From.CalculateFixedTimingHourValue),
        CalculateFixedTimingMinuteValue(From.CalculateFixedTimingMinuteValue),
        CalculateIntervalMinutesValue(From.CalculateIntervalMinutesValue),
        AdditionalScopesValue(From.AdditionalScopesValue),
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

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithGlobalRankingSetting(
        const TSharedPtr<Model::FGlobalRankingSetting> GlobalRankingSetting
    )
    {
        this->GlobalRankingSettingValue = GlobalRankingSetting;
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

    TSharedPtr<Model::FGlobalRankingSetting> FUpdateCategoryModelMasterRequest::GetGlobalRankingSetting() const
    {
        if (!GlobalRankingSettingValue.IsValid())
        {
            return nullptr;
        }
        return GlobalRankingSettingValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
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
            ->WithCategoryName(Data->HasField(ANSI_TO_TCHAR("categoryName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("categoryName"), v))
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
            ->WithMinimumValue(Data->HasField(ANSI_TO_TCHAR("minimumValue")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("minimumValue"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithMaximumValue(Data->HasField(ANSI_TO_TCHAR("maximumValue")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumValue"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithOrderDirection(Data->HasField(ANSI_TO_TCHAR("orderDirection")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("orderDirection"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScope(Data->HasField(ANSI_TO_TCHAR("scope")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scope"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithGlobalRankingSetting(Data->HasField(ANSI_TO_TCHAR("globalRankingSetting")) ? [Data]() -> Model::FGlobalRankingSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("globalRankingSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FGlobalRankingSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("globalRankingSetting")));
              }() : nullptr)
            ->WithEntryPeriodEventId(Data->HasField(ANSI_TO_TCHAR("entryPeriodEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("entryPeriodEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessPeriodEventId(Data->HasField(ANSI_TO_TCHAR("accessPeriodEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("accessPeriodEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUniqueByUserId(Data->HasField(ANSI_TO_TCHAR("uniqueByUserId")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("uniqueByUserId"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithSum(Data->HasField(ANSI_TO_TCHAR("sum")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("sum"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithCalculateFixedTimingHour(Data->HasField(ANSI_TO_TCHAR("calculateFixedTimingHour")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("calculateFixedTimingHour"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithCalculateFixedTimingMinute(Data->HasField(ANSI_TO_TCHAR("calculateFixedTimingMinute")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("calculateFixedTimingMinute"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithCalculateIntervalMinutes(Data->HasField(ANSI_TO_TCHAR("calculateIntervalMinutes")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("calculateIntervalMinutes"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithAdditionalScopes(Data->HasField(ANSI_TO_TCHAR("additionalScopes")) ? [Data]() -> TSharedPtr<TArray<Model::FScopePtr>>
              {
                  auto v = MakeShared<TArray<Model::FScopePtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("additionalScopes")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("additionalScopes")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("additionalScopes")))
                      {
                          v->Add(Model::FScope::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FScopePtr>>())
          ->WithIgnoreUserIds(Data->HasField(ANSI_TO_TCHAR("ignoreUserIds")) ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("ignoreUserIds")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("ignoreUserIds")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("ignoreUserIds")))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>())
            ->WithGeneration(Data->HasField(ANSI_TO_TCHAR("generation")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("generation"), v))
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
        if (GlobalRankingSettingValue != nullptr && GlobalRankingSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("globalRankingSetting", GlobalRankingSettingValue->ToJson());
        }
        if (EntryPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("entryPeriodEventId", EntryPeriodEventIdValue.GetValue());
        }
        if (AccessPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("accessPeriodEventId", AccessPeriodEventIdValue.GetValue());
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