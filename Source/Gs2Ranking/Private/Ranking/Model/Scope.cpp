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

#include "Ranking/Model/Scope.h"

namespace Gs2::Ranking::Model
{
    FScope::FScope():
        NameValue(TOptional<FString>()),
        TargetDaysValue(TOptional<int64>())
    {
    }

    FScope::FScope(
        const FScope& From
    ):
        NameValue(From.NameValue),
        TargetDaysValue(From.TargetDaysValue)
    {
    }

    TSharedPtr<FScope> FScope::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FScope> FScope::WithTargetDays(
        const TOptional<int64> TargetDays
    )
    {
        this->TargetDaysValue = TargetDays;
        return SharedThis(this);
    }
    TOptional<FString> FScope::GetName() const
    {
        return NameValue;
    }
    TOptional<int64> FScope::GetTargetDays() const
    {
        return TargetDaysValue;
    }

    FString FScope::GetTargetDaysString() const
    {
        if (!TargetDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TargetDaysValue.GetValue());
    }

    TSharedPtr<FScope> FScope::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FScope>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetDays(Data->HasField("targetDays") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("targetDays", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FScope::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (TargetDaysValue.IsSet())
        {
            JsonRootObject->SetStringField("targetDays", FString::Printf(TEXT("%lld"), TargetDaysValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FScope::TypeName = "Scope";
}