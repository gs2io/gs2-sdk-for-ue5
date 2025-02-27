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
    class FFreezeMasterDataByTimestampRequest;

    class GS2DISTRIBUTOR_API FFreezeMasterDataByTimestampRequest final : public TSharedFromThis<FFreezeMasterDataByTimestampRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> TimestampValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FFreezeMasterDataByTimestampRequest();
        FFreezeMasterDataByTimestampRequest(
            const FFreezeMasterDataByTimestampRequest& From
        );
        ~FFreezeMasterDataByTimestampRequest() = default;

        TSharedPtr<FFreezeMasterDataByTimestampRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FFreezeMasterDataByTimestampRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FFreezeMasterDataByTimestampRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FFreezeMasterDataByTimestampRequest> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FFreezeMasterDataByTimestampRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FFreezeMasterDataByTimestampRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FFreezeMasterDataByTimestampRequest> FFreezeMasterDataByTimestampRequestPtr;
}