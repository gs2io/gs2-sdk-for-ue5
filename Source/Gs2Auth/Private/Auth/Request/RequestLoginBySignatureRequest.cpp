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

#include "Auth/Request/LoginBySignatureRequest.h"

namespace Gs2::Auth::Request
{
    FLoginBySignatureRequest::FLoginBySignatureRequest():
        KeyIdValue(TOptional<FString>()),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>())
    {
    }

    FLoginBySignatureRequest::FLoginBySignatureRequest(
        const FLoginBySignatureRequest& From
    ):
        KeyIdValue(From.KeyIdValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue)
    {
    }

    TSharedPtr<FLoginBySignatureRequest> FLoginBySignatureRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FLoginBySignatureRequest> FLoginBySignatureRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TSharedPtr<FLoginBySignatureRequest> FLoginBySignatureRequest::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FLoginBySignatureRequest> FLoginBySignatureRequest::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TOptional<FString> FLoginBySignatureRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FLoginBySignatureRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TOptional<FString> FLoginBySignatureRequest::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FLoginBySignatureRequest::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<FLoginBySignatureRequest> FLoginBySignatureRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLoginBySignatureRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("keyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithBody(Data->HasField("body") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("body", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSignature(Data->HasField("signature") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("signature", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FLoginBySignatureRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        if (BodyValue.IsSet())
        {
            JsonRootObject->SetStringField("body", BodyValue.GetValue());
        }
        if (SignatureValue.IsSet())
        {
            JsonRootObject->SetStringField("signature", SignatureValue.GetValue());
        }
        return JsonRootObject;
    }
}