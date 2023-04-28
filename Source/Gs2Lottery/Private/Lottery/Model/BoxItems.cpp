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

#include "Lottery/Model/BoxItems.h"

namespace Gs2::Lottery::Model
{
    FBoxItems::FBoxItems():
        BoxIdValue(TOptional<FString>()),
        PrizeTableNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ItemsValue(nullptr)
    {
    }

    FBoxItems::FBoxItems(
        const FBoxItems& From
    ):
        BoxIdValue(From.BoxIdValue),
        PrizeTableNameValue(From.PrizeTableNameValue),
        UserIdValue(From.UserIdValue),
        ItemsValue(From.ItemsValue)
    {
    }

    TSharedPtr<FBoxItems> FBoxItems::WithBoxId(
        const TOptional<FString> BoxId
    )
    {
        this->BoxIdValue = BoxId;
        return SharedThis(this);
    }

    TSharedPtr<FBoxItems> FBoxItems::WithPrizeTableName(
        const TOptional<FString> PrizeTableName
    )
    {
        this->PrizeTableNameValue = PrizeTableName;
        return SharedThis(this);
    }

    TSharedPtr<FBoxItems> FBoxItems::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FBoxItems> FBoxItems::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FBoxItem>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }
    TOptional<FString> FBoxItems::GetBoxId() const
    {
        return BoxIdValue;
    }
    TOptional<FString> FBoxItems::GetPrizeTableName() const
    {
        return PrizeTableNameValue;
    }
    TOptional<FString> FBoxItems::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FBoxItem>>> FBoxItems::GetItems() const
    {
        return ItemsValue;
    }

    TOptional<FString> FBoxItems::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):user:(?<userId>.+):box:items:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBoxItems::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):user:(?<userId>.+):box:items:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBoxItems::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):user:(?<userId>.+):box:items:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBoxItems::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):user:(?<userId>.+):box:items:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBoxItems::GetPrizeTableNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):user:(?<userId>.+):box:items:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FBoxItems> FBoxItems::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBoxItems>()
            ->WithBoxId(Data->HasField("boxId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("boxId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPrizeTableName(Data->HasField("prizeTableName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("prizeTableName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FBoxItemPtr>>
                {
                    auto v = MakeShared<TArray<Model::FBoxItemPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FBoxItem::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FBoxItemPtr>>());
    }

    TSharedPtr<FJsonObject> FBoxItems::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BoxIdValue.IsSet())
        {
            JsonRootObject->SetStringField("boxId", BoxIdValue.GetValue());
        }
        if (PrizeTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeTableName", PrizeTableNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ItemsValue != nullptr && ItemsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("items", v);
        }
        return JsonRootObject;
    }

    FString FBoxItems::TypeName = "BoxItems";
}