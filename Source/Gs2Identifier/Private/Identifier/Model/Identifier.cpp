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

#include "Identifier/Model/Identifier.h"

namespace Gs2::Identifier::Model
{
    FIdentifier::FIdentifier():
        ClientIdValue(TOptional<FString>()),
        UserNameValue(TOptional<FString>()),
        ClientSecretValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FIdentifier::FIdentifier(
        const FIdentifier& From
    ):
        ClientIdValue(From.ClientIdValue),
        UserNameValue(From.UserNameValue),
        ClientSecretValue(From.ClientSecretValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FIdentifier> FIdentifier::WithClientId(
        const TOptional<FString> ClientId
    )
    {
        this->ClientIdValue = ClientId;
        return SharedThis(this);
    }

    TSharedPtr<FIdentifier> FIdentifier::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TSharedPtr<FIdentifier> FIdentifier::WithClientSecret(
        const TOptional<FString> ClientSecret
    )
    {
        this->ClientSecretValue = ClientSecret;
        return SharedThis(this);
    }

    TSharedPtr<FIdentifier> FIdentifier::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FIdentifier> FIdentifier::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FIdentifier::GetClientId() const
    {
        return ClientIdValue;
    }
    TOptional<FString> FIdentifier::GetUserName() const
    {
        return UserNameValue;
    }
    TOptional<FString> FIdentifier::GetClientSecret() const
    {
        return ClientSecretValue;
    }
    TOptional<int64> FIdentifier::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FIdentifier::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FIdentifier::GetRevision() const
    {
        return RevisionValue;
    }

    FString FIdentifier::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TSharedPtr<FIdentifier> FIdentifier::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIdentifier>()
            ->WithClientId(Data->HasField("clientId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("clientId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserName(Data->HasField("userName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithClientSecret(Data->HasField("clientSecret") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("clientSecret", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FIdentifier::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ClientIdValue.IsSet())
        {
            JsonRootObject->SetStringField("clientId", ClientIdValue.GetValue());
        }
        if (UserNameValue.IsSet())
        {
            JsonRootObject->SetStringField("userName", UserNameValue.GetValue());
        }
        if (ClientSecretValue.IsSet())
        {
            JsonRootObject->SetStringField("clientSecret", ClientSecretValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FIdentifier::TypeName = "Identifier";
}