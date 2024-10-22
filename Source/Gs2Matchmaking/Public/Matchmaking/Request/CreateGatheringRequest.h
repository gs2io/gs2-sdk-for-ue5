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
#include "../Model/Player.h"
#include "../Model/AttributeRange.h"
#include "../Model/CapacityOfRole.h"
#include "../Model/TimeSpan.h"

namespace Gs2::Matchmaking::Request
{
    class FCreateGatheringRequest;

    class GS2MATCHMAKING_API FCreateGatheringRequest final : public TSharedFromThis<FCreateGatheringRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<Model::FPlayer> PlayerValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRangesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> CapacityOfRolesValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<int64> ExpiresAtValue;
        TSharedPtr<Model::FTimeSpan> ExpiresAtTimeSpanValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateGatheringRequest();
        FCreateGatheringRequest(
            const FCreateGatheringRequest& From
        );
        ~FCreateGatheringRequest() = default;

        TSharedPtr<FCreateGatheringRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateGatheringRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateGatheringRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FCreateGatheringRequest> WithPlayer(const TSharedPtr<Model::FPlayer> Player);
        TSharedPtr<FCreateGatheringRequest> WithAttributeRanges(const TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRanges);
        TSharedPtr<FCreateGatheringRequest> WithCapacityOfRoles(const TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> CapacityOfRoles);
        TSharedPtr<FCreateGatheringRequest> WithAllowUserIds(
            const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FCreateGatheringRequest> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FCreateGatheringRequest> WithExpiresAtTimeSpan(const TSharedPtr<Model::FTimeSpan> ExpiresAtTimeSpan);
        TSharedPtr<FCreateGatheringRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<Model::FPlayer> GetPlayer() const;TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> GetAttributeRanges() const;TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> GetCapacityOfRoles() const;
        TSharedPtr<TArray<FString>> GetAllowUserIds() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TSharedPtr<Model::FTimeSpan> GetExpiresAtTimeSpan() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateGatheringRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateGatheringRequest> FCreateGatheringRequestPtr;
}