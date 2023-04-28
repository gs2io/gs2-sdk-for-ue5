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

#include "Showcase/Model/Showcase.h"

namespace Gs2::Showcase::Model
{
    FShowcase::FShowcase():
        ShowcaseIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        SalesPeriodEventIdValue(TOptional<FString>()),
        DisplayItemsValue(nullptr)
    {
    }

    FShowcase::FShowcase(
        const FShowcase& From
    ):
        ShowcaseIdValue(From.ShowcaseIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        SalesPeriodEventIdValue(From.SalesPeriodEventIdValue),
        DisplayItemsValue(From.DisplayItemsValue)
    {
    }

    TSharedPtr<FShowcase> FShowcase::WithShowcaseId(
        const TOptional<FString> ShowcaseId
    )
    {
        this->ShowcaseIdValue = ShowcaseId;
        return SharedThis(this);
    }

    TSharedPtr<FShowcase> FShowcase::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FShowcase> FShowcase::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FShowcase> FShowcase::WithSalesPeriodEventId(
        const TOptional<FString> SalesPeriodEventId
    )
    {
        this->SalesPeriodEventIdValue = SalesPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FShowcase> FShowcase::WithDisplayItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FDisplayItem>>> DisplayItems
    )
    {
        this->DisplayItemsValue = DisplayItems;
        return SharedThis(this);
    }
    TOptional<FString> FShowcase::GetShowcaseId() const
    {
        return ShowcaseIdValue;
    }
    TOptional<FString> FShowcase::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FShowcase::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FShowcase::GetSalesPeriodEventId() const
    {
        return SalesPeriodEventIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FDisplayItem>>> FShowcase::GetDisplayItems() const
    {
        return DisplayItemsValue;
    }

    TOptional<FString> FShowcase::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FShowcase::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FShowcase::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FShowcase::GetShowcaseNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):showcase:(?<showcaseName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FShowcase> FShowcase::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FShowcase>()
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSalesPeriodEventId(Data->HasField("salesPeriodEventId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("salesPeriodEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDisplayItems(Data->HasField("displayItems") ? [Data]() -> TSharedPtr<TArray<Model::FDisplayItemPtr>>
                {
                    auto v = MakeShared<TArray<Model::FDisplayItemPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("displayItems") && Data->HasTypedField<EJson::Array>("displayItems"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("displayItems"))
                        {
                            v->Add(Model::FDisplayItem::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FDisplayItemPtr>>());
    }

    TSharedPtr<FJsonObject> FShowcase::ToJson() const
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
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (SalesPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("salesPeriodEventId", SalesPeriodEventIdValue.GetValue());
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
        return JsonRootObject;
    }

    FString FShowcase::TypeName = "Showcase";
}