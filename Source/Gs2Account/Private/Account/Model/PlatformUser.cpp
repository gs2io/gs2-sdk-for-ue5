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

#include "Account/Model/PlatformUser.h"

namespace Gs2::Account::Model
{
    FPlatformUser::FPlatformUser():
        TypeValue(TOptional<int32>()),
        UserIdentifierValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>())
    {
    }

    FPlatformUser::FPlatformUser(
        const FPlatformUser& From
    ):
        TypeValue(From.TypeValue),
        UserIdentifierValue(From.UserIdentifierValue),
        UserIdValue(From.UserIdValue)
    {
    }

    TSharedPtr<FPlatformUser> FPlatformUser::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FPlatformUser> FPlatformUser::WithUserIdentifier(
        const TOptional<FString> UserIdentifier
    )
    {
        this->UserIdentifierValue = UserIdentifier;
        return SharedThis(this);
    }

    TSharedPtr<FPlatformUser> FPlatformUser::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<int32> FPlatformUser::GetType() const
    {
        return TypeValue;
    }

    FString FPlatformUser::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }
    TOptional<FString> FPlatformUser::GetUserIdentifier() const
    {
        return UserIdentifierValue;
    }
    TOptional<FString> FPlatformUser::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<FPlatformUser> FPlatformUser::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPlatformUser>()
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithUserIdentifier(Data->HasField(ANSI_TO_TCHAR("userIdentifier")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userIdentifier"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPlatformUser::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetNumberField("type", TypeValue.GetValue());
        }
        if (UserIdentifierValue.IsSet())
        {
            JsonRootObject->SetStringField("userIdentifier", UserIdentifierValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FPlatformUser::TypeName = "PlatformUser";
}