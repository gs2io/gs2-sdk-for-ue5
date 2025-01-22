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
    class FSignFreezeMasterDataTimestampRequest;

    class GS2DISTRIBUTOR_API FSignFreezeMasterDataTimestampRequest final : public TSharedFromThis<FSignFreezeMasterDataTimestampRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int64> TimestampValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FSignFreezeMasterDataTimestampRequest();
        FSignFreezeMasterDataTimestampRequest(
            const FSignFreezeMasterDataTimestampRequest& From
        );
        ~FSignFreezeMasterDataTimestampRequest() = default;

        TSharedPtr<FSignFreezeMasterDataTimestampRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSignFreezeMasterDataTimestampRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSignFreezeMasterDataTimestampRequest> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FSignFreezeMasterDataTimestampRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FSignFreezeMasterDataTimestampRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSignFreezeMasterDataTimestampRequest> FSignFreezeMasterDataTimestampRequestPtr;
}