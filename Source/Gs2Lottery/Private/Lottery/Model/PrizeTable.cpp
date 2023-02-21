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

#include "Lottery/Model/PrizeTable.h"

namespace Gs2::Lottery::Model
{
    FPrizeTable::FPrizeTable():
        PrizeTableIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        PrizesValue(nullptr)
    {
    }

    FPrizeTable::FPrizeTable(
        const FPrizeTable& From
    ):
        PrizeTableIdValue(From.PrizeTableIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        PrizesValue(From.PrizesValue)
    {
    }

    TSharedPtr<FPrizeTable> FPrizeTable::WithPrizeTableId(
        const TOptional<FString> PrizeTableId
    )
    {
        this->PrizeTableIdValue = PrizeTableId;
        return SharedThis(this);
    }

    TSharedPtr<FPrizeTable> FPrizeTable::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FPrizeTable> FPrizeTable::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FPrizeTable> FPrizeTable::WithPrizes(
        const TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> Prizes
    )
    {
        this->PrizesValue = Prizes;
        return SharedThis(this);
    }
    TOptional<FString> FPrizeTable::GetPrizeTableId() const
    {
        return PrizeTableIdValue;
    }
    TOptional<FString> FPrizeTable::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FPrizeTable::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> FPrizeTable::GetPrizes() const
    {
        return PrizesValue;
    }

    TOptional<FString> FPrizeTable::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FPrizeTable::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FPrizeTable::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FPrizeTable::GetPrizeTableNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FPrizeTable> FPrizeTable::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrizeTable>()
            ->WithPrizeTableId(Data->HasField("prizeTableId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("prizeTableId", v))
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
            ->WithPrizes(Data->HasField("prizes") ? [Data]() -> TSharedPtr<TArray<Model::FPrizePtr>>
                {
                    auto v = MakeShared<TArray<Model::FPrizePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("prizes") && Data->HasTypedField<EJson::Array>("prizes"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("prizes"))
                        {
                            v->Add(Model::FPrize::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FPrizeTable::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PrizeTableIdValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeTableId", PrizeTableIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (PrizesValue != nullptr && PrizesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *PrizesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("prizes", v);
        }
        return JsonRootObject;
    }

    FString FPrizeTable::TypeName = "PrizeTable";
}