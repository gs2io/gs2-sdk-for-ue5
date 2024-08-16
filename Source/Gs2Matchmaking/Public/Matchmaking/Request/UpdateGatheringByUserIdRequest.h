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
    class FUpdateGatheringByUserIdRequest;

    class GS2MATCHMAKING_API FUpdateGatheringByUserIdRequest final : public TSharedFromThis<FUpdateGatheringByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GatheringNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRangesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateGatheringByUserIdRequest();
        FUpdateGatheringByUserIdRequest(
            const FUpdateGatheringByUserIdRequest& From
        );
        ~FUpdateGatheringByUserIdRequest() = default;

        TSharedPtr<FUpdateGatheringByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateGatheringByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateGatheringByUserIdRequest> WithGatheringName(const TOptional<FString> GatheringName);
        TSharedPtr<FUpdateGatheringByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateGatheringByUserIdRequest> WithAttributeRanges(const TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRanges);
        TSharedPtr<FUpdateGatheringByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateGatheringByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGatheringName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> GetAttributeRanges() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateGatheringByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateGatheringByUserIdRequest> FUpdateGatheringByUserIdRequestPtr;
}