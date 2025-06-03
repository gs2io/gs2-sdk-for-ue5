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

#include "Freeze/Model/Microservice.h"

namespace Gs2::Freeze::Model
{
    FMicroservice::FMicroservice():
        NameValue(TOptional<FString>()),
        VersionValue(TOptional<FString>())
    {
    }

    FMicroservice::FMicroservice(
        const FMicroservice& From
    ):
        NameValue(From.NameValue),
        VersionValue(From.VersionValue)
    {
    }

    TSharedPtr<FMicroservice> FMicroservice::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMicroservice> FMicroservice::WithVersion(
        const TOptional<FString> Version
    )
    {
        this->VersionValue = Version;
        return SharedThis(this);
    }
    TOptional<FString> FMicroservice::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMicroservice::GetVersion() const
    {
        return VersionValue;
    }

    TSharedPtr<FMicroservice> FMicroservice::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMicroservice>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVersion(Data->HasField(ANSI_TO_TCHAR("version")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("version"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FMicroservice::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (VersionValue.IsSet())
        {
            JsonRootObject->SetStringField("version", VersionValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FMicroservice::TypeName = "Microservice";
}