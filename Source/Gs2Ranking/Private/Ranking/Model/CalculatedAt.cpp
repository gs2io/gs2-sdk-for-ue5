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

#include "Ranking/Model/CalculatedAt.h"

namespace Gs2::Ranking::Model
{
    FCalculatedAt::FCalculatedAt():
        CategoryNameValue(TOptional<FString>()),
        CalculatedAtValue(TOptional<int64>())
    {
    }

    FCalculatedAt::FCalculatedAt(
        const FCalculatedAt& From
    ):
        CategoryNameValue(From.CategoryNameValue),
        CalculatedAtValue(From.CalculatedAtValue)
    {
    }

    TSharedPtr<FCalculatedAt> FCalculatedAt::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FCalculatedAt> FCalculatedAt::WithCalculatedAt(
        const TOptional<int64> CalculatedAt
    )
    {
        this->CalculatedAtValue = CalculatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FCalculatedAt::GetCategoryName() const
    {
        return CategoryNameValue;
    }
    TOptional<int64> FCalculatedAt::GetCalculatedAt() const
    {
        return CalculatedAtValue;
    }

    FString FCalculatedAt::GetCalculatedAtString() const
    {
        if (!CalculatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CalculatedAtValue.GetValue());
    }

    TSharedPtr<FCalculatedAt> FCalculatedAt::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCalculatedAt>()
            ->WithCategoryName(Data->HasField(ANSI_TO_TCHAR("categoryName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("categoryName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCalculatedAt(Data->HasField(ANSI_TO_TCHAR("calculatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("calculatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FCalculatedAt::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryName", CategoryNameValue.GetValue());
        }
        if (CalculatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("calculatedAt", FString::Printf(TEXT("%lld"), CalculatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FCalculatedAt::TypeName = "CalculatedAt";
}