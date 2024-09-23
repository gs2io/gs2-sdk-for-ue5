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

namespace Gs2::AdReward::Request
{
    class FConsumePointRequest;

    class GS2ADREWARD_API FConsumePointRequest final : public TSharedFromThis<FConsumePointRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> PointValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumePointRequest();
        FConsumePointRequest(
            const FConsumePointRequest& From
        );
        ~FConsumePointRequest() = default;

        TSharedPtr<FConsumePointRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumePointRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumePointRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FConsumePointRequest> WithPoint(const TOptional<int64> Point);
        TSharedPtr<FConsumePointRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetPoint() const;
        FString GetPointString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumePointRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumePointRequest, ESPMode::ThreadSafe> FConsumePointRequestPtr;
}