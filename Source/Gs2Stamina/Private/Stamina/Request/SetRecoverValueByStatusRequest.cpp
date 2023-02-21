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

#include "Stamina/Request/SetRecoverValueByStatusRequest.h"

namespace Gs2::Stamina::Request
{
    FSetRecoverValueByStatusRequest::FSetRecoverValueByStatusRequest():
        NamespaceNameValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>()),
        SignedStatusBodyValue(TOptional<FString>()),
        SignedStatusSignatureValue(TOptional<FString>())
    {
    }

    FSetRecoverValueByStatusRequest::FSetRecoverValueByStatusRequest(
        const FSetRecoverValueByStatusRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StaminaNameValue(From.StaminaNameValue),
        AccessTokenValue(From.AccessTokenValue),
        KeyIdValue(From.KeyIdValue),
        SignedStatusBodyValue(From.SignedStatusBodyValue),
        SignedStatusSignatureValue(From.SignedStatusSignatureValue)
    {
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::WithSignedStatusBody(
        const TOptional<FString> SignedStatusBody
    )
    {
        this->SignedStatusBodyValue = SignedStatusBody;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::WithSignedStatusSignature(
        const TOptional<FString> SignedStatusSignature
    )
    {
        this->SignedStatusSignatureValue = SignedStatusSignature;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetRecoverValueByStatusRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetRecoverValueByStatusRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetRecoverValueByStatusRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TOptional<FString> FSetRecoverValueByStatusRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FSetRecoverValueByStatusRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TOptional<FString> FSetRecoverValueByStatusRequest::GetSignedStatusBody() const
    {
        return SignedStatusBodyValue;
    }

    TOptional<FString> FSetRecoverValueByStatusRequest::GetSignedStatusSignature() const
    {
        return SignedStatusSignatureValue;
    }

    TOptional<FString> FSetRecoverValueByStatusRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetRecoverValueByStatusRequest> FSetRecoverValueByStatusRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetRecoverValueByStatusRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStaminaName(Data->HasField("staminaName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("staminaName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("keyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSignedStatusBody(Data->HasField("signedStatusBody") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("signedStatusBody", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSignedStatusSignature(Data->HasField("signedStatusSignature") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("signedStatusSignature", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetRecoverValueByStatusRequest::ToJson() const
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