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

#include "Showcase/Model/RandomShowcase.h"

namespace Gs2::Showcase::Model
{
    FRandomShowcase::FRandomShowcase():
        RandomShowcaseIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MaximumNumberOfChoiceValue(TOptional<int32>()),
        DisplayItemsValue(nullptr),
        BaseTimestampValue(TOptional<int64>()),
        ResetIntervalHoursValue(TOptional<int32>()),
        SalesPeriodEventIdValue(TOptional<FString>())
    {
    }

    FRandomShowcase::FRandomShowcase(
        const FRandomShowcase& From
    ):
        RandomShowcaseIdValue(From.RandomShowcaseIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        MaximumNumberOfChoiceValue(From.MaximumNumberOfChoiceValue),
        DisplayItemsValue(From.DisplayItemsValue),
        BaseTimestampValue(From.BaseTimestampValue),
        ResetIntervalHoursValue(From.ResetIntervalHoursValue),
        SalesPeriodEventIdValue(From.SalesPeriodEventIdValue)
    {
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::WithRandomShowcaseId(
        const TOptional<FString> RandomShowcaseId
    )
    {
        this->RandomShowcaseIdValue = RandomShowcaseId;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::WithMaximumNumberOfChoice(
        const TOptional<int32> MaximumNumberOfChoice
    )
    {
        this->MaximumNumberOfChoiceValue = MaximumNumberOfChoice;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::WithDisplayItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> DisplayItems
    )
    {
        this->DisplayItemsValue = DisplayItems;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::WithBaseTimestamp(
        const TOptional<int64> BaseTimestamp
    )
    {
        this->BaseTimestampValue = BaseTimestamp;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::WithResetIntervalHours(
        const TOptional<int32> ResetIntervalHours
    )
    {
        this->ResetIntervalHoursValue = ResetIntervalHours;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::WithSalesPeriodEventId(
        const TOptional<FString> SalesPeriodEventId
    )
    {
        this->SalesPeriodEventIdValue = SalesPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FRandomShowcase::GetRandomShowcaseId() const
    {
        return RandomShowcaseIdValue;
    }
    TOptional<FString> FRandomShowcase::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRandomShowcase::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FRandomShowcase::GetMaximumNumberOfChoice() const
    {
        return MaximumNumberOfChoiceValue;
    }

    FString FRandomShowcase::GetMaximumNumberOfChoiceString() const
    {
        if (!MaximumNumberOfChoiceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumNumberOfChoiceValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> FRandomShowcase::GetDisplayItems() const
    {
        return DisplayItemsValue;
    }
    TOptional<int64> FRandomShowcase::GetBaseTimestamp() const
    {
        return BaseTimestampValue;
    }

    FString FRandomShowcase::GetBaseTimestampString() const
    {
        if (!BaseTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BaseTimestampValue.GetValue());
    }
    TOptional<int32> FRandomShowcase::GetResetIntervalHours() const
    {
        return ResetIntervalHoursValue;
    }

    FString FRandomShowcase::GetResetIntervalHoursString() const
    {
        if (!ResetIntervalHoursValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetIntervalHoursValue.GetValue());
    }
    TOptional<FString> FRandomShowcase::GetSalesPeriodEventId() const
    {
        return SalesPeriodEventIdValue;
    }

    TOptional<FString> FRandomShowcase::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):random:showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRandomShowcase::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):random:showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRandomShowcase::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):random:showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRandomShowcase::GetShowcaseNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):random:showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRandomShowcase> FRandomShowcase::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRandomShowcase>()
            ->WithRandomShowcaseId(Data->HasField("randomShowcaseId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("randomShowcaseId", v))
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
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
                 }() : MakeShared<TArray<Model::FRandomDisplayItemModelPtr>>())
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
                    FString v("");
                    if (Data->TryGetStringField("salesPeriodEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRandomShowcase::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RandomShowcaseIdValue.IsSet())
        {
            JsonRootObject->SetStringField("randomShowcaseId", RandomShowcaseIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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

    FString FRandomShowcase::TypeName = "RandomShowcase";
}