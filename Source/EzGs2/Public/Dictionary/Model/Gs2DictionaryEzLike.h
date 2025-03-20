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
#include "Dictionary/Model/Like.h"

namespace Gs2::UE5::Dictionary::Model
{
	class EZGS2_API FEzLike final : public TSharedFromThis<FEzLike>
	{
        TOptional<FString> LikeIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;

	public:
        TSharedPtr<FEzLike> WithLikeId(const TOptional<FString> LikeId);
        TSharedPtr<FEzLike> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzLike> WithName(const TOptional<FString> Name);

        TOptional<FString> GetLikeId() const;

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetName() const;

        Gs2::Dictionary::Model::FLikePtr ToModel() const;
        static TSharedPtr<FEzLike> FromModel(Gs2::Dictionary::Model::FLikePtr Model);
    };
    typedef TSharedPtr<FEzLike> FEzLikePtr;
}