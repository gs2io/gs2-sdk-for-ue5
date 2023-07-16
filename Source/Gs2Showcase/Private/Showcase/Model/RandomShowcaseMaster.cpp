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

#include "Showcase/Model/RandomShowcaseMaster.h"

namespace Gs2::Showcase::Model
{
    FRandomShowcaseMaster::FRandomShowcaseMaster():
        ShowcaseIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MaximumNumberOfChoiceValue(TOptional<int32>()),
        DisplayItemsValue(nullptr),
        BaseTimestampValue(TOptional<int64>()),
        ResetIntervalHoursValue(TOptional<int32>()),
        SalesPeriodEventIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FRandomShowcaseMaster::FRandomShowcaseMaster(
        const FRandomShowcaseMaster& From
    ):
        ShowcaseIdValue(From.ShowcaseIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        MaximumNumberOfChoiceValue(From.MaximumNumberOfChoiceValue),
        DisplayItemsValue(From.DisplayItemsValue),
        BaseTimestampValue(From.BaseTimestampValue),
        ResetIntervalHoursValue(From.ResetIntervalHoursValue),
        SalesPeriodEventIdValue(From.SalesPeriodEventIdValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithShowcaseId(
        const TOptional<FString> ShowcaseId
    )
    {
        this->ShowcaseIdValue = ShowcaseId;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithMaximumNumberOfChoice(
        const TOptional<int32> MaximumNumberOfChoice
    )
    {
        this->MaximumNumberOfChoiceValue = MaximumNumberOfChoice;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithDisplayItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> DisplayItems
    )
    {
        this->DisplayItemsValue = DisplayItems;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithBaseTimestamp(
        const TOptional<int64> BaseTimestamp
    )
    {
        this->BaseTimestampValue = BaseTimestamp;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithResetIntervalHours(
        const TOptional<int32> ResetIntervalHours
    )
    {
        this->ResetIntervalHoursValue = ResetIntervalHours;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithSalesPeriodEventId(
        const TOptional<FString> SalesPeriodEventId
    )
    {
        this->SalesPeriodEventIdValue = SalesPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FRandomShowcaseMaster::GetShowcaseId() const
    {
        return ShowcaseIdValue;
    }
    TOptional<FString> FRandomShowcaseMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRandomShowcaseMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FRandomShowcaseMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FRandomShowcaseMaster::GetMaximumNumberOfChoice() const
    {
        return MaximumNumberOfChoiceValue;
    }

    FString FRandomShowcaseMaster::GetMaximumNumberOfChoiceString() const
    {
        if (!MaximumNumberOfChoiceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumNumberOfChoiceValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> FRandomShowcaseMaster::GetDisplayItems() const
    {
        return DisplayItemsValue;
    }
    TOptional<int64> FRandomShowcaseMaster::GetBaseTimestamp() const
    {
        return BaseTimestampValue;
    }

    FString FRandomShowcaseMaster::GetBaseTimestampString() const
    {
        if (!BaseTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BaseTimestampValue.GetValue());
    }
    TOptional<int32> FRandomShowcaseMaster::GetResetIntervalHours() const
    {
        return ResetIntervalHoursValue;
    }

    FString FRandomShowcaseMaster::GetResetIntervalHoursString() const
    {
        if (!ResetIntervalHoursValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetIntervalHoursValue.GetValue());
    }
    TOptional<FString> FRandomShowcaseMaster::GetSalesPeriodEventId() const
    {
        return SalesPeriodEventIdValue;
    }
    TOptional<int64> FRandomShowcaseMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FRandomShowcaseMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FRandomShowcaseMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FRandomShowcaseMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FRandomShowcaseMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):random:showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRandomShowcaseMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):random:showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRandomShowcaseMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):random:showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRandomShowcaseMaster::GetShowcaseNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):random:showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRandomShowcaseMaster> FRandomShowcaseMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRandomShowcaseMaster>()
            ->WithShowcaseId(Data->HasField("showcaseId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("showcaseId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
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
                    FString v;
                    if (Data->TryGetStringField("salesPeriodEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRandomShowcaseMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ShowcaseIdValue.IsSet())
        {
            JsonRootObject->SetStringField("showcaseId", ShowcaseIdValue.GetValue());
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
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRandomShowcaseMaster::TypeName = "RandomShowcaseMaster";
}