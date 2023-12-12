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

#include "StateMachine/Model/RandomUsed.h"

namespace Gs2::StateMachine::Model
{
    FRandomUsed::FRandomUsed():
        CategoryValue(TOptional<int64>()),
        UsedValue(TOptional<int64>())
    {
    }

    FRandomUsed::FRandomUsed(
        const FRandomUsed& From
    ):
        CategoryValue(From.CategoryValue),
        UsedValue(From.UsedValue)
    {
    }

    TSharedPtr<FRandomUsed> FRandomUsed::WithCategory(
        const TOptional<int64> Category
    )
    {
        this->CategoryValue = Category;
        return SharedThis(this);
    }

    TSharedPtr<FRandomUsed> FRandomUsed::WithUsed(
        const TOptional<int64> Used
    )
    {
        this->UsedValue = Used;
        return SharedThis(this);
    }
    TOptional<int64> FRandomUsed::GetCategory() const
    {
        return CategoryValue;
    }

    FString FRandomUsed::GetCategoryString() const
    {
        if (!CategoryValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CategoryValue.GetValue());
    }
    TOptional<int64> FRandomUsed::GetUsed() const
    {
        return UsedValue;
    }

    FString FRandomUsed::GetUsedString() const
    {
        if (!UsedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UsedValue.GetValue());
    }

    TSharedPtr<FRandomUsed> FRandomUsed::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRandomUsed>()
            ->WithCategory(Data->HasField("category") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("category", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUsed(Data->HasField("used") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("used", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRandomUsed::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CategoryValue.IsSet())
        {
            JsonRootObject->SetStringField("category", FString::Printf(TEXT("%lld"), CategoryValue.GetValue()));
        }
        if (UsedValue.IsSet())
        {
            JsonRootObject->SetStringField("used", FString::Printf(TEXT("%lld"), UsedValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRandomUsed::TypeName = "RandomUsed";
}