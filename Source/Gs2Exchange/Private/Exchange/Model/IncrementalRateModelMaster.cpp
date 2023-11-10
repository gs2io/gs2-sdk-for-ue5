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

#include "Exchange/Model/IncrementalRateModelMaster.h"

namespace Gs2::Exchange::Model
{
    FIncrementalRateModelMaster::FIncrementalRateModelMaster():
        IncrementalRateModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ConsumeActionValue(nullptr),
        CalculateTypeValue(TOptional<FString>()),
        BaseValueValue(TOptional<int64>()),
        CoefficientValueValue(TOptional<int64>()),
        CalculateScriptIdValue(TOptional<FString>()),
        ExchangeCountIdValue(TOptional<FString>()),
        MaximumExchangeCountValue(TOptional<int32>()),
        AcquireActionsValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FIncrementalRateModelMaster::FIncrementalRateModelMaster(
        const FIncrementalRateModelMaster& From
    ):
        IncrementalRateModelIdValue(From.IncrementalRateModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ConsumeActionValue(From.ConsumeActionValue),
        CalculateTypeValue(From.CalculateTypeValue),
        BaseValueValue(From.BaseValueValue),
        CoefficientValueValue(From.CoefficientValueValue),
        CalculateScriptIdValue(From.CalculateScriptIdValue),
        ExchangeCountIdValue(From.ExchangeCountIdValue),
        MaximumExchangeCountValue(From.MaximumExchangeCountValue),
        AcquireActionsValue(From.AcquireActionsValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithIncrementalRateModelId(
        const TOptional<FString> IncrementalRateModelId
    )
    {
        this->IncrementalRateModelIdValue = IncrementalRateModelId;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithConsumeAction(
        const TSharedPtr<FConsumeAction> ConsumeAction
    )
    {
        this->ConsumeActionValue = ConsumeAction;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithCalculateType(
        const TOptional<FString> CalculateType
    )
    {
        this->CalculateTypeValue = CalculateType;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithBaseValue(
        const TOptional<int64> BaseValue
    )
    {
        this->BaseValueValue = BaseValue;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithCoefficientValue(
        const TOptional<int64> CoefficientValue
    )
    {
        this->CoefficientValueValue = CoefficientValue;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithCalculateScriptId(
        const TOptional<FString> CalculateScriptId
    )
    {
        this->CalculateScriptIdValue = CalculateScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithExchangeCountId(
        const TOptional<FString> ExchangeCountId
    )
    {
        this->ExchangeCountIdValue = ExchangeCountId;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithMaximumExchangeCount(
        const TOptional<int32> MaximumExchangeCount
    )
    {
        this->MaximumExchangeCountValue = MaximumExchangeCount;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FIncrementalRateModelMaster::GetIncrementalRateModelId() const
    {
        return IncrementalRateModelIdValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<FConsumeAction> FIncrementalRateModelMaster::GetConsumeAction() const
    {
        return ConsumeActionValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetCalculateType() const
    {
        return CalculateTypeValue;
    }
    TOptional<int64> FIncrementalRateModelMaster::GetBaseValue() const
    {
        return BaseValueValue;
    }

    FString FIncrementalRateModelMaster::GetBaseValueString() const
    {
        if (!BaseValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BaseValueValue.GetValue());
    }
    TOptional<int64> FIncrementalRateModelMaster::GetCoefficientValue() const
    {
        return CoefficientValueValue;
    }

    FString FIncrementalRateModelMaster::GetCoefficientValueString() const
    {
        if (!CoefficientValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CoefficientValueValue.GetValue());
    }
    TOptional<FString> FIncrementalRateModelMaster::GetCalculateScriptId() const
    {
        return CalculateScriptIdValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetExchangeCountId() const
    {
        return ExchangeCountIdValue;
    }
    TOptional<int32> FIncrementalRateModelMaster::GetMaximumExchangeCount() const
    {
        return MaximumExchangeCountValue;
    }

    FString FIncrementalRateModelMaster::GetMaximumExchangeCountString() const
    {
        if (!MaximumExchangeCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumExchangeCountValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FIncrementalRateModelMaster::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<int64> FIncrementalRateModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FIncrementalRateModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FIncrementalRateModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FIncrementalRateModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FIncrementalRateModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FIncrementalRateModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FIncrementalRateModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):incremental:model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIncrementalRateModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):incremental:model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIncrementalRateModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):incremental:model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIncrementalRateModelMaster::GetRateNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):incremental:model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIncrementalRateModelMaster>()
            ->WithIncrementalRateModelId(Data->HasField("incrementalRateModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("incrementalRateModelId", v))
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
            ->WithConsumeAction(Data->HasField("consumeAction") ? [Data]() -> Model::FConsumeActionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("consumeAction"))
                    {
                        return nullptr;
                    }
                    return Model::FConsumeAction::FromJson(Data->GetObjectField("consumeAction"));
                 }() : nullptr)
            ->WithCalculateType(Data->HasField("calculateType") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("calculateType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBaseValue(Data->HasField("baseValue") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("baseValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCoefficientValue(Data->HasField("coefficientValue") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("coefficientValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCalculateScriptId(Data->HasField("calculateScriptId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("calculateScriptId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExchangeCountId(Data->HasField("exchangeCountId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("exchangeCountId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMaximumExchangeCount(Data->HasField("maximumExchangeCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("maximumExchangeCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAcquireActions(Data->HasField("acquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("acquireActions") && Data->HasTypedField<EJson::Array>("acquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("acquireActions"))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FIncrementalRateModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (IncrementalRateModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("incrementalRateModelId", IncrementalRateModelIdValue.GetValue());
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
        if (ConsumeActionValue != nullptr && ConsumeActionValue.IsValid())
        {
            JsonRootObject->SetObjectField("consumeAction", ConsumeActionValue->ToJson());
        }
        if (CalculateTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("calculateType", CalculateTypeValue.GetValue());
        }
        if (BaseValueValue.IsSet())
        {
            JsonRootObject->SetStringField("baseValue", FString::Printf(TEXT("%lld"), BaseValueValue.GetValue()));
        }
        if (CoefficientValueValue.IsSet())
        {
            JsonRootObject->SetStringField("coefficientValue", FString::Printf(TEXT("%lld"), CoefficientValueValue.GetValue()));
        }
        if (CalculateScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("calculateScriptId", CalculateScriptIdValue.GetValue());
        }
        if (ExchangeCountIdValue.IsSet())
        {
            JsonRootObject->SetStringField("exchangeCountId", ExchangeCountIdValue.GetValue());
        }
        if (MaximumExchangeCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumExchangeCount", MaximumExchangeCountValue.GetValue());
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

    FString FIncrementalRateModelMaster::TypeName = "IncrementalRateModelMaster";
}