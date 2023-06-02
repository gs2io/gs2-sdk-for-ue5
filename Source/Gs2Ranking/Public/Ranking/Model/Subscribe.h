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
#include "Core/Gs2Object.h"

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FSubscribe final : public Gs2Object, public TSharedFromThis<FSubscribe>
    {
        TOptional<FString> SubscribeIdValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> TargetUserIdsValue;
        TSharedPtr<TArray<FString>> SubscribedUserIdsValue;
        TOptional<int64> CreatedAtValue;

    public:
        FSubscribe();
        FSubscribe(
            const FSubscribe& From
        );
        virtual ~FSubscribe() override = default;

        TSharedPtr<FSubscribe> WithSubscribeId(const TOptional<FString> SubscribeId);
        TSharedPtr<FSubscribe> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FSubscribe> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscribe> WithTargetUserIds(const TSharedPtr<TArray<FString>> TargetUserIds);
        TSharedPtr<FSubscribe> WithSubscribedUserIds(const TSharedPtr<TArray<FString>> SubscribedUserIds);
        TSharedPtr<FSubscribe> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetSubscribeId() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetTargetUserIds() const;
        TSharedPtr<TArray<FString>> GetSubscribedUserIds() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryNameFromGrn(const FString Grn);

        static TSharedPtr<FSubscribe> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribe, ESPMode::ThreadSafe> FSubscribePtr;
}