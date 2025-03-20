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

#include "Dictionary/Model/Gs2DictionaryEzLike.h"

namespace Gs2::UE5::Dictionary::Model
{

    TSharedPtr<FEzLike> FEzLike::WithLikeId(
        const TOptional<FString> LikeId
    )
    {
        this->LikeIdValue = LikeId;
        return SharedThis(this);
    }

    TSharedPtr<FEzLike> FEzLike::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzLike> FEzLike::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }
    TOptional<FString> FEzLike::GetLikeId() const
    {
        return LikeIdValue;
    }
    TOptional<FString> FEzLike::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzLike::GetName() const
    {
        return NameValue;
    }

    Gs2::Dictionary::Model::FLikePtr FEzLike::ToModel() const
    {
        return MakeShared<Gs2::Dictionary::Model::FLike>()
            ->WithLikeId(LikeIdValue)
            ->WithUserId(UserIdValue)
            ->WithName(NameValue);
    }

    TSharedPtr<FEzLike> FEzLike::FromModel(const Gs2::Dictionary::Model::FLikePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzLike>()
            ->WithLikeId(Model->GetLikeId())
            ->WithUserId(Model->GetUserId())
            ->WithName(Model->GetName());
    }
}