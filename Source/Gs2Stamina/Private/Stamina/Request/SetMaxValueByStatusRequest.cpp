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

#include "Stamina/Request/SetMaxValueByStatusRequest.h"

namespace Gs2::Stamina::Request
{
    FSetMaxValueByStatusRequest::FSetMaxValueByStatusRequest():
        NamespaceNameValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>()),
        SignedStatusBodyValue(TOptional<FString>()),
        SignedStatusSignatureValue(TOptional<FString>())
    {
    }

    FSetMaxValueByStatusRequest::FSetMaxValueByStatusRequest(
        const FSetMaxValueByStatusRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StaminaNameValue(From.StaminaNameValue),
        AccessTokenValue(From.AccessTokenValue),
        KeyIdValue(From.KeyIdValue),
        SignedStatusBodyValue(From.SignedStatusBodyValue),
        SignedStatusSignatureValue(From.SignedStatusSignatureValue)
    {
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::WithSignedStatusBody(
        const TOptional<FString> SignedStatusBody
    )
    {
        this->SignedStatusBodyValue = SignedStatusBody;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::WithSignedStatusSignature(
        const TOptional<FString> SignedStatusSignature
    )
    {
        this->SignedStatusSignatureValue = SignedStatusSignature;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetMaxValueByStatusRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetMaxValueByStatusRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetMaxValueByStatusRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TOptional<FString> FSetMaxValueByStatusRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FSetMaxValueByStatusRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TOptional<FString> FSetMaxValueByStatusRequest::GetSignedStatusBody() const
    {
        return SignedStatusBodyValue;
    }

    TOptional<FString> FSetMaxValueByStatusRequest::GetSignedStatusSignature() const
    {
        return SignedStatusSignatureValue;
    }

    TOptional<FString> FSetMaxValueByStatusRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetMaxValueByStatusRequest> FSetMaxValueByStatusRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetMaxValueByStatusRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStaminaName(Data->HasField(ANSI_TO_TCHAR("staminaName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("staminaName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
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
            ->WithSignedStatusBody(Data->HasField(ANSI_TO_TCHAR("signedStatusBody")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("signedStatusBody"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSignedStatusSignature(Data->HasField(ANSI_TO_TCHAR("signedStatusSignature")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("signedStatusSignature"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetMaxValueByStatusRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (StaminaNameValue.IsSet())
        {
            JsonRootObject->SetStringField("staminaName", StaminaNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        if (SignedStatusBodyValue.IsSet())
        {
            JsonRootObject->SetStringField("signedStatusBody", SignedStatusBodyValue.GetValue());
        }
        if (SignedStatusSignatureValue.IsSet())
        {
            JsonRootObject->SetStringField("signedStatusSignature", SignedStatusSignatureValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}