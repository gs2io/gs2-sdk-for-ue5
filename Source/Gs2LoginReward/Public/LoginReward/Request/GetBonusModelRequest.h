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

namespace Gs2::LoginReward::Request
{
    class FGetBonusModelRequest;

    class GS2LOGINREWARD_API FGetBonusModelRequest final : public TSharedFromThis<FGetBonusModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
        
    public:
        
        FGetBonusModelRequest();
        FGetBonusModelRequest(
            const FGetBonusModelRequest& From
        );
        ~FGetBonusModelRequest() = default;

        TSharedPtr<FGetBonusModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBonusModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBonusModelRequest> WithBonusModelName(const TOptional<FString> BonusModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;

        static TSharedPtr<FGetBonusModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBonusModelRequest> FGetBonusModelRequestPtr;
}