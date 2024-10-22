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
    class FCreateGatheringByUserIdRequest;

    class GS2MATCHMAKING_API FCreateGatheringByUserIdRequest final : public TSharedFromThis<FCreateGatheringByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Model::FPlayer> PlayerValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRangesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> CapacityOfRolesValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<int64> ExpiresAtValue;
        TSharedPtr<Model::FTimeSpan> ExpiresAtTimeSpanValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateGatheringByUserIdRequest();
        FCreateGatheringByUserIdRequest(
            const FCreateGatheringByUserIdRequest& From
        );
        ~FCreateGatheringByUserIdRequest() = default;

        TSharedPtr<FCreateGatheringByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithPlayer(const TSharedPtr<Model::FPlayer> Player);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithAttributeRanges(const TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRanges);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithCapacityOfRoles(const TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> CapacityOfRoles);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithAllowUserIds(
            const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithExpiresAtTimeSpan(const TSharedPtr<Model::FTimeSpan> ExpiresAtTimeSpan);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCreateGatheringByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<Model::FPlayer> GetPlayer() const;TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> GetAttributeRanges() const;TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> GetCapacityOfRoles() const;
        TSharedPtr<TArray<FString>> GetAllowUserIds() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TSharedPtr<Model::FTimeSpan> GetExpiresAtTimeSpan() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateGatheringByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequestPtr;
}