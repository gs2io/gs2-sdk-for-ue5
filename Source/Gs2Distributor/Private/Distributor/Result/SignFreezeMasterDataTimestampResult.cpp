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

#include "Distributor/Result/SignFreezeMasterDataTimestampResult.h"

namespace Gs2::Distributor::Result
{
    FSignFreezeMasterDataTimestampResult::FSignFreezeMasterDataTimestampResult():
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>())
    {
    }

    FSignFreezeMasterDataTimestampResult::FSignFreezeMasterDataTimestampResult(
        const FSignFreezeMasterDataTimestampResult& From
    ):
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue)
    {
    }

    TSharedPtr<FSignFreezeMasterDataTimestampResult> FSignFreezeMasterDataTimestampResult::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FSignFreezeMasterDataTimestampResult> FSignFreezeMasterDataTimestampResult::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TOptional<FString> FSignFreezeMasterDataTimestampResult::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FSignFreezeMasterDataTimestampResult::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<FSignFreezeMasterDataTimestampResult> FSignFreezeMasterDataTimestampResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSignFreezeMasterDataTimestampResult>()
            ->WithBody(Data->HasField(ANSI_TO_TCHAR("body")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("body"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSignature(Data->HasField(ANSI_TO_TCHAR("signature")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("signature"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSignFreezeMasterDataTimestampResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
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