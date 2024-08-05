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

#include "Account/Result/GetAuthorizationUrlResult.h"

namespace Gs2::Account::Result
{
    FGetAuthorizationUrlResult::FGetAuthorizationUrlResult():
        AuthorizationUrlValue(TOptional<FString>())
    {
    }

    FGetAuthorizationUrlResult::FGetAuthorizationUrlResult(
        const FGetAuthorizationUrlResult& From
    ):
        AuthorizationUrlValue(From.AuthorizationUrlValue)
    {
    }

    TSharedPtr<FGetAuthorizationUrlResult> FGetAuthorizationUrlResult::WithAuthorizationUrl(
        const TOptional<FString> AuthorizationUrl
    )
    {
        this->AuthorizationUrlValue = AuthorizationUrl;
        return SharedThis(this);
    }

    TOptional<FString> FGetAuthorizationUrlResult::GetAuthorizationUrl() const
    {
        return AuthorizationUrlValue;
    }

    TSharedPtr<FGetAuthorizationUrlResult> FGetAuthorizationUrlResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetAuthorizationUrlResult>()
            ->WithAuthorizationUrl(Data->HasField(ANSI_TO_TCHAR("authorizationUrl")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("authorizationUrl"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetAuthorizationUrlResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AuthorizationUrlValue.IsSet())
        {
            JsonRootObject->SetStringField("authorizationUrl", AuthorizationUrlValue.GetValue());
        }
        return JsonRootObject;
    }
}