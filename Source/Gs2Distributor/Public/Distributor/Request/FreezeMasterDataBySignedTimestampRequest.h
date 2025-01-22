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

namespace Gs2::Distributor::Request
{
    class FFreezeMasterDataBySignedTimestampRequest;

    class GS2DISTRIBUTOR_API FFreezeMasterDataBySignedTimestampRequest final : public TSharedFromThis<FFreezeMasterDataBySignedTimestampRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FFreezeMasterDataBySignedTimestampRequest();
        FFreezeMasterDataBySignedTimestampRequest(
            const FFreezeMasterDataBySignedTimestampRequest& From
        );
        ~FFreezeMasterDataBySignedTimestampRequest() = default;

        TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> WithBody(const TOptional<FString> Body);
        TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> WithSignature(const TOptional<FString> Signature);
        TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FFreezeMasterDataBySignedTimestampRequest> FFreezeMasterDataBySignedTimestampRequestPtr;
}