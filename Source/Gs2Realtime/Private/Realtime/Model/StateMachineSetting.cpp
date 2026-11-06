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

#include "Realtime/Model/StateMachineSetting.h"

namespace Gs2::Realtime::Model
{
    FStateMachineSetting::FStateMachineSetting():
        NamespaceIdValue(TOptional<FString>()),
        VersionValue(TOptional<int64>())
    {
    }

    FStateMachineSetting::FStateMachineSetting(
        const FStateMachineSetting& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        VersionValue(From.VersionValue)
    {
    }

    TSharedPtr<FStateMachineSetting> FStateMachineSetting::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FStateMachineSetting> FStateMachineSetting::WithVersion(
        const TOptional<int64> Version
    )
    {
        this->VersionValue = Version;
        return SharedThis(this);
    }
    TOptional<FString> FStateMachineSetting::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<int64> FStateMachineSetting::GetVersion() const
    {
        return VersionValue;
    }

    FString FStateMachineSetting::GetVersionString() const
    {
        if (!VersionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), VersionValue.GetValue());
    }

    TSharedPtr<FStateMachineSetting> FStateMachineSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStateMachineSetting>()
            ->WithNamespaceId(Data->HasField(ANSI_TO_TCHAR("namespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVersion(Data->HasField(ANSI_TO_TCHAR("version")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("version"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FStateMachineSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("namespaceId"), NamespaceIdValue.GetValue());
        }
        if (VersionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("version"), FString::Printf(TEXT("%lld"), VersionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FStateMachineSetting::TypeName = "StateMachineSetting";
}