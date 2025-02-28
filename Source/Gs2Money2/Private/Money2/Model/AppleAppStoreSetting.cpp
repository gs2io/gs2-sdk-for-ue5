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

#include "Money2/Model/AppleAppStoreSetting.h"

namespace Gs2::Money2::Model
{
    FAppleAppStoreSetting::FAppleAppStoreSetting():
        BundleIdValue(TOptional<FString>()),
        TeamIdValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>()),
        PrivateKeyPemValue(TOptional<FString>())
    {
    }

    FAppleAppStoreSetting::FAppleAppStoreSetting(
        const FAppleAppStoreSetting& From
    ):
        BundleIdValue(From.BundleIdValue),
        TeamIdValue(From.TeamIdValue),
        KeyIdValue(From.KeyIdValue),
        PrivateKeyPemValue(From.PrivateKeyPemValue)
    {
    }

    TSharedPtr<FAppleAppStoreSetting> FAppleAppStoreSetting::WithBundleId(
        const TOptional<FString> BundleId
    )
    {
        this->BundleIdValue = BundleId;
        return SharedThis(this);
    }

    TSharedPtr<FAppleAppStoreSetting> FAppleAppStoreSetting::WithTeamId(
        const TOptional<FString> TeamId
    )
    {
        this->TeamIdValue = TeamId;
        return SharedThis(this);
    }

    TSharedPtr<FAppleAppStoreSetting> FAppleAppStoreSetting::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TSharedPtr<FAppleAppStoreSetting> FAppleAppStoreSetting::WithPrivateKeyPem(
        const TOptional<FString> PrivateKeyPem
    )
    {
        this->PrivateKeyPemValue = PrivateKeyPem;
        return SharedThis(this);
    }
    TOptional<FString> FAppleAppStoreSetting::GetBundleId() const
    {
        return BundleIdValue;
    }
    TOptional<FString> FAppleAppStoreSetting::GetTeamId() const
    {
        return TeamIdValue;
    }
    TOptional<FString> FAppleAppStoreSetting::GetKeyId() const
    {
        return KeyIdValue;
    }
    TOptional<FString> FAppleAppStoreSetting::GetPrivateKeyPem() const
    {
        return PrivateKeyPemValue;
    }

    TSharedPtr<FAppleAppStoreSetting> FAppleAppStoreSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAppleAppStoreSetting>()
            ->WithBundleId(Data->HasField(ANSI_TO_TCHAR("bundleId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("bundleId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTeamId(Data->HasField(ANSI_TO_TCHAR("teamId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("teamId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithKeyId(Data->HasField(ANSI_TO_TCHAR("keyId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("keyId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPrivateKeyPem(Data->HasField(ANSI_TO_TCHAR("privateKeyPem")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("privateKeyPem"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAppleAppStoreSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BundleIdValue.IsSet())
        {
            JsonRootObject->SetStringField("bundleId", BundleIdValue.GetValue());
        }
        if (TeamIdValue.IsSet())
        {
            JsonRootObject->SetStringField("teamId", TeamIdValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        if (PrivateKeyPemValue.IsSet())
        {
            JsonRootObject->SetStringField("privateKeyPem", PrivateKeyPemValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAppleAppStoreSetting::TypeName = "AppleAppStoreSetting";
}