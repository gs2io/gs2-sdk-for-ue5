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

namespace Gs2::Identifier::Request
{
    class FDescribeAttachedGuardsRequest;

    class GS2IDENTIFIER_API FDescribeAttachedGuardsRequest final : public TSharedFromThis<FDescribeAttachedGuardsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> ClientIdValue;
        TOptional<FString> UserNameValue;
        
    public:
        
        FDescribeAttachedGuardsRequest();
        FDescribeAttachedGuardsRequest(
            const FDescribeAttachedGuardsRequest& From
        );
        ~FDescribeAttachedGuardsRequest() = default;

        TSharedPtr<FDescribeAttachedGuardsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeAttachedGuardsRequest> WithClientId(const TOptional<FString> ClientId);
        TSharedPtr<FDescribeAttachedGuardsRequest> WithUserName(const TOptional<FString> UserName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetClientId() const;
        TOptional<FString> GetUserName() const;

        static TSharedPtr<FDescribeAttachedGuardsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeAttachedGuardsRequest> FDescribeAttachedGuardsRequestPtr;
}