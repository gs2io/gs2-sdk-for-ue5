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

namespace Gs2::Dictionary::Model
{
    class GS2DICTIONARY_API FLike final : public FGs2Object, public TSharedFromThis<FLike>
    {
        TOptional<FString> LikeIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;

    public:
        FLike();
        FLike(
            const FLike& From
        );
        virtual ~FLike() override = default;

        TSharedPtr<FLike> WithLikeId(const TOptional<FString> LikeId);
        TSharedPtr<FLike> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FLike> WithName(const TOptional<FString> Name);

        TOptional<FString> GetLikeId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetName() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetEntryModelNameFromGrn(const FString Grn);

        static TSharedPtr<FLike> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLike, ESPMode::ThreadSafe> FLikePtr;
}