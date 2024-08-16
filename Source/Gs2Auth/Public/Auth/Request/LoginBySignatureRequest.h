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

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"

namespace Gs2::Auth::Request
{
    class FLoginBySignatureRequest;

    class GS2AUTH_API FLoginBySignatureRequest final : public TSharedFromThis<FLoginBySignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FLoginBySignatureRequest();
        FLoginBySignatureRequest(
            const FLoginBySignatureRequest& From
        );
        ~FLoginBySignatureRequest() = default;

        TSharedPtr<FLoginBySignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FLoginBySignatureRequest> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FLoginBySignatureRequest> WithBody(const TOptional<FString> Body);
        TSharedPtr<FLoginBySignatureRequest> WithSignature(const TOptional<FString> Signature);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FLoginBySignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FLoginBySignatureRequest> FLoginBySignatureRequestPtr;
}