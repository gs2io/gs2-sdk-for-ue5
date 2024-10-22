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
#include "../Model/AttributeRange.h"

namespace Gs2::Matchmaking::Request
{
    class FUpdateGatheringRequest;

    class GS2MATCHMAKING_API FUpdateGatheringRequest final : public TSharedFromThis<FUpdateGatheringRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GatheringNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRangesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateGatheringRequest();
        FUpdateGatheringRequest(
            const FUpdateGatheringRequest& From
        );
        ~FUpdateGatheringRequest() = default;

        TSharedPtr<FUpdateGatheringRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateGatheringRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateGatheringRequest> WithGatheringName(const TOptional<FString> GatheringName);
        TSharedPtr<FUpdateGatheringRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUpdateGatheringRequest> WithAttributeRanges(const TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRanges);
        TSharedPtr<FUpdateGatheringRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGatheringName() const;
        TOptional<FString> GetAccessToken() const;TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> GetAttributeRanges() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateGatheringRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateGatheringRequest> FUpdateGatheringRequestPtr;
}