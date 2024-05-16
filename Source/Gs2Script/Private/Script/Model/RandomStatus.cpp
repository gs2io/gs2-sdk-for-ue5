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

#include "Script/Model/RandomStatus.h"

namespace Gs2::Script::Model
{
    FRandomStatus::FRandomStatus():
        SeedValue(TOptional<int64>()),
        UsedValue(nullptr)
    {
    }

    FRandomStatus::FRandomStatus(
        const FRandomStatus& From
    ):
        SeedValue(From.SeedValue),
        UsedValue(From.UsedValue)
    {
    }

    TSharedPtr<FRandomStatus> FRandomStatus::WithSeed(
        const TOptional<int64> Seed
    )
    {
        this->SeedValue = Seed;
        return SharedThis(this);
    }

    TSharedPtr<FRandomStatus> FRandomStatus::WithUsed(
        const TSharedPtr<TArray<TSharedPtr<Model::FRandomUsed>>> Used
    )
    {
        this->UsedValue = Used;
        return SharedThis(this);
    }
    TOptional<int64> FRandomStatus::GetSeed() const
    {
        return SeedValue;
    }

    FString FRandomStatus::GetSeedString() const
    {
        if (!SeedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeedValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRandomUsed>>> FRandomStatus::GetUsed() const
    {
        return UsedValue;
    }

    TSharedPtr<FRandomStatus> FRandomStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRandomStatus>()
            ->WithSeed(Data->HasField(ANSI_TO_TCHAR("seed")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("seed"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUsed(Data->HasField(ANSI_TO_TCHAR("used")) ? [Data]() -> TSharedPtr<TArray<Model::FRandomUsedPtr>>
                {
                    auto v = MakeShared<TArray<Model::FRandomUsedPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("used")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("used")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("used")))
                        {
                            v->Add(Model::FRandomUsed::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRandomUsedPtr>>());
    }

    TSharedPtr<FJsonObject> FRandomStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SeedValue.IsSet())
        {
            JsonRootObject->SetStringField("seed", FString::Printf(TEXT("%lld"), SeedValue.GetValue()));
        }
        if (UsedValue != nullptr && UsedValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *UsedValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("used", v);
        }
        return JsonRootObject;
    }

    FString FRandomStatus::TypeName = "RandomStatus";
}