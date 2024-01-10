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

#include "Version/Result/CheckVersionResult.h"

namespace Gs2::Version::Result
{
    FCheckVersionResult::FCheckVersionResult():
        ProjectTokenValue(TOptional<FString>()),
        WarningsValue(nullptr),
        ErrorsValue(nullptr)
    {
    }

    FCheckVersionResult::FCheckVersionResult(
        const FCheckVersionResult& From
    ):
        ProjectTokenValue(From.ProjectTokenValue),
        WarningsValue(From.WarningsValue),
        ErrorsValue(From.ErrorsValue)
    {
    }

    TSharedPtr<FCheckVersionResult> FCheckVersionResult::WithProjectToken(
        const TOptional<FString> ProjectToken
    )
    {
        this->ProjectTokenValue = ProjectToken;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionResult> FCheckVersionResult::WithWarnings(
        const TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> Warnings
    )
    {
        this->WarningsValue = Warnings;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionResult> FCheckVersionResult::WithErrors(
        const TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> Errors
    )
    {
        this->ErrorsValue = Errors;
        return SharedThis(this);
    }

    TOptional<FString> FCheckVersionResult::GetProjectToken() const
    {
        return ProjectTokenValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> FCheckVersionResult::GetWarnings() const
    {
        if (!WarningsValue.IsValid())
        {
            return nullptr;
        }
        return WarningsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> FCheckVersionResult::GetErrors() const
    {
        if (!ErrorsValue.IsValid())
        {
            return nullptr;
        }
        return ErrorsValue;
    }

    TSharedPtr<FCheckVersionResult> FCheckVersionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCheckVersionResult>()
            ->WithProjectToken(Data->HasField("projectToken") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("projectToken", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithWarnings(Data->HasField("warnings") ? [Data]() -> TSharedPtr<TArray<Model::FStatusPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FStatusPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("warnings") && Data->HasTypedField<EJson::Array>("warnings"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("warnings"))
                        {
                            v->Add(Model::FStatus::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FStatusPtr>>())
            ->WithErrors(Data->HasField("errors") ? [Data]() -> TSharedPtr<TArray<Model::FStatusPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FStatusPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("errors") && Data->HasTypedField<EJson::Array>("errors"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("errors"))
                        {
                            v->Add(Model::FStatus::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FStatusPtr>>());
    }

    TSharedPtr<FJsonObject> FCheckVersionResult::ToJson() const
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