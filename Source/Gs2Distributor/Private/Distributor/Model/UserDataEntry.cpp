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

#include "Distributor/Model/UserDataEntry.h"

namespace Gs2::Distributor::Model
{
    FUserDataEntry::FUserDataEntry():
        ServiceValue(TOptional<FString>()),
        NamespaceNameValue(TOptional<FString>()),
        KindValue(TOptional<FString>()),
        PayloadValue(TOptional<FString>())
    {
    }

    FUserDataEntry::FUserDataEntry(
        const FUserDataEntry& From
    ):
        ServiceValue(From.ServiceValue),
        NamespaceNameValue(From.NamespaceNameValue),
        KindValue(From.KindValue),
        PayloadValue(From.PayloadValue)
    {
    }

    TSharedPtr<FUserDataEntry> FUserDataEntry::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FUserDataEntry> FUserDataEntry::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUserDataEntry> FUserDataEntry::WithKind(
        const TOptional<FString> Kind
    )
    {
        this->KindValue = Kind;
        return SharedThis(this);
    }

    TSharedPtr<FUserDataEntry> FUserDataEntry::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }
    TOptional<FString> FUserDataEntry::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FUserDataEntry::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }
    TOptional<FString> FUserDataEntry::GetKind() const
    {
        return KindValue;
    }
    TOptional<FString> FUserDataEntry::GetPayload() const
    {
        return PayloadValue;
    }

    TSharedPtr<FUserDataEntry> FUserDataEntry::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUserDataEntry>()
            ->WithService(Data->HasField(ANSI_TO_TCHAR("service")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("service"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithKind(Data->HasField(ANSI_TO_TCHAR("kind")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("kind"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPayload(Data->HasField(ANSI_TO_TCHAR("payload")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("payload"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUserDataEntry::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ServiceValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("service"), ServiceValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("namespaceName"), NamespaceNameValue.GetValue());
        }
        if (KindValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("kind"), KindValue.GetValue());
        }
        if (PayloadValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("payload"), PayloadValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FUserDataEntry::TypeName = "UserDataEntry";
}