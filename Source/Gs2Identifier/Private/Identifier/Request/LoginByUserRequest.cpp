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

#include "Identifier/Request/LoginByUserRequest.h"

namespace Gs2::Identifier::Request
{
    FLoginByUserRequest::FLoginByUserRequest():
        UserNameValue(TOptional<FString>()),
        PasswordValue(TOptional<FString>()),
        OtpValue(TOptional<FString>())
    {
    }

    FLoginByUserRequest::FLoginByUserRequest(
        const FLoginByUserRequest& From
    ):
        UserNameValue(From.UserNameValue),
        PasswordValue(From.PasswordValue),
        OtpValue(From.OtpValue)
    {
    }

    TSharedPtr<FLoginByUserRequest> FLoginByUserRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FLoginByUserRequest> FLoginByUserRequest::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TSharedPtr<FLoginByUserRequest> FLoginByUserRequest::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<FLoginByUserRequest> FLoginByUserRequest::WithOtp(
        const TOptional<FString> Otp
    )
    {
        this->OtpValue = Otp;
        return SharedThis(this);
    }

    TOptional<FString> FLoginByUserRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FLoginByUserRequest::GetUserName() const
    {
        return UserNameValue;
    }

    TOptional<FString> FLoginByUserRequest::GetPassword() const
    {
        return PasswordValue;
    }

    TOptional<FString> FLoginByUserRequest::GetOtp() const
    {
        return OtpValue;
    }

    TSharedPtr<FLoginByUserRequest> FLoginByUserRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLoginByUserRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithUserName(Data->HasField(ANSI_TO_TCHAR("userName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPassword(Data->HasField(ANSI_TO_TCHAR("password")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("password"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithOtp(Data->HasField(ANSI_TO_TCHAR("otp")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("otp"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FLoginByUserRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (UserNameValue.IsSet())
        {
            JsonRootObject->SetStringField("userName", UserNameValue.GetValue());
        }
        if (PasswordValue.IsSet())
        {
            JsonRootObject->SetStringField("password", PasswordValue.GetValue());
        }
        if (OtpValue.IsSet())
        {
            JsonRootObject->SetStringField("otp", OtpValue.GetValue());
        }
        return JsonRootObject;
    }
}