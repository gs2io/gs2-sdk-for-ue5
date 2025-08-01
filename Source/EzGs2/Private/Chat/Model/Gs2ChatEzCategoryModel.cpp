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

#include "Chat/Model/Gs2ChatEzCategoryModel.h"

namespace Gs2::UE5::Chat::Model
{

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithCategory(
        const TOptional<int32> Category
    )
    {
        this->CategoryValue = Category;
        return SharedThis(this);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithRejectAccessTokenPost(
        const TOptional<FString> RejectAccessTokenPost
    )
    {
        this->RejectAccessTokenPostValue = RejectAccessTokenPost;
        return SharedThis(this);
    }
    TOptional<int32> FEzCategoryModel::GetCategory() const
    {
        return CategoryValue;
    }

    FString FEzCategoryModel::GetCategoryString() const
    {
        if (!CategoryValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CategoryValue.GetValue());
    }
    TOptional<FString> FEzCategoryModel::GetRejectAccessTokenPost() const
    {
        return RejectAccessTokenPostValue;
    }

    Gs2::Chat::Model::FCategoryModelPtr FEzCategoryModel::ToModel() const
    {
        return MakeShared<Gs2::Chat::Model::FCategoryModel>()
            ->WithCategory(CategoryValue)
            ->WithRejectAccessTokenPost(RejectAccessTokenPostValue);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::FromModel(const Gs2::Chat::Model::FCategoryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCategoryModel>()
            ->WithCategory(Model->GetCategory())
            ->WithRejectAccessTokenPost(Model->GetRejectAccessTokenPost());
    }
}