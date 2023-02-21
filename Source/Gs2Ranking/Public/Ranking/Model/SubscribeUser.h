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

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FSubscribeUser final : public TSharedFromThis<FSubscribeUser>
    {
        TOptional<FString> SubscribeUserIdValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;

    public:
        FSubscribeUser();
        FSubscribeUser(
            const FSubscribeUser& From
        );
        ~FSubscribeUser() = default;

        TSharedPtr<FSubscribeUser> WithSubscribeUserId(const TOptional<FString> SubscribeUserId);
        TSharedPtr<FSubscribeUser> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FSubscribeUser> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscribeUser> WithTargetUserId(const TOptional<FString> TargetUserId);

        TOptional<FString> GetSubscribeUserId() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetUserId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetTargetUserIdFromGrn(const FString Grn);

        static TSharedPtr<FSubscribeUser> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribeUser, ESPMode::ThreadSafe> FSubscribeUserPtr;
}