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

#include "Version/Result/CheckVersionByUserIdResult.h"

namespace Gs2::Version::Result
{
    FCheckVersionByUserIdResult::FCheckVersionByUserIdResult():
        ProjectTokenValue(TOptional<FString>()),
        WarningsValue(nullptr),
        ErrorsValue(nullptr)
    {
    }

    FCheckVersionByUserIdResult::FCheckVersionByUserIdResult(
        const FCheckVersionByUserIdResult& From
    ):
        ProjectTokenValue(From.ProjectTokenValue),
        WarningsValue(From.WarningsValue),
        ErrorsValue(From.ErrorsValue)
    {
    }

    TSharedPtr<FCheckVersionByUserIdResult> FCheckVersionByUserIdResult::WithProjectToken(
        const TOptional<FString> ProjectToken
    )
    {
        this->ProjectTokenValue = ProjectToken;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionByUserIdResult> FCheckVersionByUserIdResult::WithWarnings(
        const TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> Warnings
    )
    {
        this->WarningsValue = Warnings;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionByUserIdResult> FCheckVersionByUserIdResult::WithErrors(
        const TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> Errors
    )
    {
        this->ErrorsValue = Errors;
        return SharedThis(this);
    }

    TOptional<FString> FCheckVersionByUserIdResult::GetProjectToken() const
    {
        return ProjectTokenValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> FCheckVersionByUserIdResult::GetWarnings() const
    {
        if (!WarningsValue.IsValid())
        {
            return nullptr;
        }
        return WarningsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> FCheckVersionByUserIdResult::GetErrors() const
    {
        if (!ErrorsValue.IsValid())
        {
            return nullptr;
        }
        return ErrorsValue;
    }

    TSharedPtr<FCheckVersionByUserIdResult> FCheckVersionByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCheckVersionByUserIdResult>()
            ->WithProjectToken(Data->HasField(ANSI_TO_TCHAR("projectToken")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("projectToken"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithWarnings(Data->HasField(ANSI_TO_TCHAR("warnings")) ? [Data]() -> TSharedPtr<TArray<Model::FStatusPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FStatusPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("warnings")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("warnings")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("warnings")))
                        {
                            v->Add(Model::FStatus::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FStatusPtr>>())
            ->WithErrors(Data->HasField(ANSI_TO_TCHAR("errors")) ? [Data]() -> TSharedPtr<TArray<Model::FStatusPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FStatusPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("errors")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("errors")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("errors")))
                        {
                            v->Add(Model::FStatus::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FStatusPtr>>());
    }

    TSharedPtr<FJsonObject> FCheckVersionByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ProjectTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("projectToken", ProjectTokenValue.GetValue());
        }
        if (WarningsValue != nullptr && WarningsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *WarningsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("warnings", v);
        }
        if (ErrorsValue != nullptr && ErrorsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ErrorsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("errors", v);
        }
        return JsonRootObject;
    }
}